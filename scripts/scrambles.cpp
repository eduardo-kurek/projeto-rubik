#include "../rubik/Rubik.h"
#include "../managers/DatabaseManager.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <fstream>
#include <omp.h>
#ifdef _WIN32
#include <windows.h>
#endif

using string = std::string;

template<typename T>
using vector = std::vector<T>;

class Populater{

    const string tablePrefix = "scramble_";
    int maxLines;
    DatabaseManager* database;

    string historic_to_string(Rubik rubik){
        string result = "";
        for(auto& h : rubik.getHistoric())
            result += h->name.back() == '\'' ? h->name + "' " : h->name + " ";
        return result;
    }

    string get_table_name(int moves_quantity){
        return tablePrefix + std::to_string(moves_quantity);
    }

    void create_table(int moves_quantity){
        string tableName = this->get_table_name(moves_quantity);
        this->database->dropTable(tableName);
        this->database->createTable(tableName, {"scramble"}, {"VARCHAR(65)"});
    }

    void insert(int moves_quantity, Rubik rubik){
        string tableName = this->get_table_name(moves_quantity);
        this->database->insert(tableName, {"scramble"}, {this->historic_to_string(rubik)});
    }

    void __populate_all_possibilities(Rubik last, int depth, int& count, int moves_quantity){
        for(auto& move : last.getValidMoves()){

            // VERIFICANDO SE AINDA É NECESSÁRIO IMPRIMIR MAIS MOVIMENTOS
            if(count == this->maxLines) return;

            Rubik model = last;
            model.move(1, move);

            if(depth == 0){ // INSERINDO NO BANCO DE DADOS
                count++;
                this->insert(moves_quantity, model);
            }
            else{ // INDO MAIS UM MOVIMENTO A FUNDO
                __populate_all_possibilities(model, depth-1, count, moves_quantity);
            }
        }
    }

    void populate_all_possibilities(int moves_quantity){
        int count = 0;
        Rubik r;
        string tableName = this->get_table_name(moves_quantity);
        this->create_table(moves_quantity);
        this->__populate_all_possibilities(r, moves_quantity-1, count, moves_quantity);
    }

    void populate_scrambled(int moves_quantity){
        this->create_table(moves_quantity);

        for(int i = 0; i < this->maxLines; i++){
            Rubik r;
            r.scramble(moves_quantity);
            this->insert(moves_quantity, r);
        }
    }


    public:
    Populater(DatabaseManager* database, int maxLines){
        this->database = database;
        this->maxLines = maxLines;
    }

    void populate(){
        this->populate_all_possibilities(1);
        this->populate_all_possibilities(2);
        this->populate_all_possibilities(3);
        
        #pragma omp parallel for
        for(int i = 4; i <= 20; i++){
            #pragma omp critical
            {
                this->populate_scrambled(i);
            }
        }
    }

};

int main(int argc, char* argv[]){
    // AJUSTANDO A CODIFICAÇÃO PARA UTF-8
    #ifdef _WIN32
        SetConsoleOutputCP(65001);
    #endif

    if(argc < 3){
        std::cout << "É preciso informar dois argumentos para este programa: A SEED, e a QUANT de embaralhamentos em cada arquivo\n";
        return 1;
    }

    int seed = atoi(argv[1]);
    int maxLines = atoi(argv[2]);

    srand(seed);

    DatabaseManager* database = new DatabaseManager("../");
    Populater populater(database, maxLines);

    populater.populate();
}