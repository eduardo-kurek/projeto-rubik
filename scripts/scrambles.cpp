#include "../rubik/Rubik.h"
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

    int maxLines;
    string folderPath;

    string get_file_name(int moves_quantity){
        return folderPath + "scramble_"+std::to_string(moves_quantity) + ".scr";
    }

    void print_historic(const Rubik& r, std::ofstream& file){
        std::ostream& output = file.is_open() ? file : std::cout;

        for(auto& h : r.getHistoric()){
            output << h->name << " ";
        }
        output << '\n';
    }

    void __populate_all_possibilities(Rubik last, int depth, std::ofstream& file, int& count){
        for(auto& move : last.getValidMoves()){

            // VERIFICANDO SE AINDA É NECESSÁRIO IMPRIMIR MAIS MOVIMENTOS
            if(count == this->maxLines) return;

            if(depth == 0){
                // MOVIMENTANDO MODELO ATUAL
                count++;
                Rubik model = last;
                model.move(1, move);

                // IMPRESSÃO DO HISTÓRICO
                print_historic(model, file);
            }
            else{
                // INDO MAIS UM MOVIMENTO A FUNDO
                Rubik model = last;
                model.move(1, move);
                __populate_all_possibilities(model, depth-1, file, count);
            }

        }
    }
    
    void populate_all_possibilities(int moves_quantity){
        // LIMPANDO O ARQUIVO DE TEXTO
        std::ofstream file(this->get_file_name(moves_quantity));
        file.clear();

        // POPULANDO O ARQUIVO DE TEXTO
        int count = 0;
        Rubik r;
        __populate_all_possibilities(r, moves_quantity-1, file, count);
        file.close();
    }

    void populate_scrambled(int moves_quantity){
        std::ofstream file(this->get_file_name(moves_quantity));
        for(int i = 0; i < this->maxLines; i++){
            Rubik r;
            r.scramble(moves_quantity);
            print_historic(r, file);
        }
        file.close();
    }


    public:
    Populater(int maxLines, string folderPath){
        this->maxLines = maxLines;
        this->folderPath = folderPath;
    }

    void populate(){
        this->populate_all_possibilities(1);
        this->populate_all_possibilities(2);
        this->populate_all_possibilities(3);
        
        #pragma omp parallel for
        for(int i = 4; i <= 20; i++)
            this->populate_scrambled(i);
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

    string separator = "/";
    #ifdef _WIN32
        separator = "\\";
    #endif

    Populater populater(maxLines, ".."+separator +"database"+separator+"scrambles"+separator);
    populater.populate();

    populater.populate();
}