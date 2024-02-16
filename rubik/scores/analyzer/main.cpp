#include <iostream>
#include <fstream>
#include <filesystem>
#include <utility>
#include <type_traits>
#include <cmath>
#include <omp.h>
#include <string>
#include "../basic-score/BasicScore.h"
#include "../PontuationTable.h"
#include "../../../managers/DatabaseManager.h"
#ifdef _WIN32
#include <windows.h>
#endif

#define DEBUG

using string = std::string;

template<typename T>
using vector = std::vector<T>;

template <typename TScore, typename = std::enable_if_t<std::is_base_of<Score, TScore>::value>>
class Analyzer{

    private:
    DatabaseManager* database;

    vector<string> config;
    PontuationTable* table = nullptr;
    TScore* score = nullptr;

    vector<float> expectedPontuations = {95,90,85,80,75,70,65,60,55,50,45,40,35,30,25,20,15,10,5,0};
    vector<float> pontuations;

    float result;

    public:

    float calculate_table(string tableName){
        vector<vector<string>> result = this->database->select(tableName, {"scramble"});

        float sum = 0;
        int count = 0;
        
        for(vector<string> row : result){
            Rubik rubik;
            rubik.move(Move::stringToMoves(row[0]));

            sum += this->score->calculateNormalized(rubik);
            count++;
        }

        return sum / count;
    }

    void calculate_pontuations(){
        this->pontuations = vector<float>();
        this->pontuations.resize(20);

        #pragma omp parallel for
        for(int i = 0; i < 20; i++)
            this->pontuations[i] = this->calculate_table("scramble_" + std::to_string(i+1));
    }

    public:

    Analyzer(DatabaseManager* database, vector<string> config){
        this->database = database;
        this->config = config;
    }

    bool validate_tables(){
        for(int i = 1; i <= 20; i++){
            if(!this->database->tableExists("scramble_" + std::to_string(i)))
                return false;
        }
        return true;
    }

    bool mount_table(){
        // MONTANDO TABELA DE PONTUAÇÃO ATRAVÉS DOS VALORES INFORMADOS
        vector<float> cornerPontuation;
        vector<float> edgePontuations;

        for(int i = 0; i < 9; i++){
            if(i < 5) cornerPontuation.push_back(stof(this->config[i]));
            else edgePontuations.push_back(stof(this->config[i]));
        }

        // VERIFICANDO SE O PRIMEIRO VALOR DE CADA VETOR É O MAIOR DO VETOR INTEIRO
        if(*std::max_element(cornerPontuation.begin(), cornerPontuation.end()) != cornerPontuation[0])
            return false;
        if(*std::max_element(edgePontuations.begin(), edgePontuations.end()) != edgePontuations[0])
            return false;

        this->table = new PontuationTable(cornerPontuation, edgePontuations);
        this->score = new TScore(this->table);
        return true;
    }

    void print_pontuations(){
        if(this->pontuations.size() != 20) return;

        std::cout << "{\n";

        for(int i = 0; i < this->pontuations.size(); i++){
            std::cout << "\t\"" << i+1 << "\": ";
            std::cout << std::fixed << std::setprecision(2) << this->pontuations[i];
            std::cout << ",\n";
        }

        std::cout << "\b}\n";
    }

    float analyse(){
        if(this->table == nullptr) 
            throw std::runtime_error("É preciso validar a tabela de pontuação antes de analisar.");

        this->calculate_pontuations();

        float sum = 0;

        // CALCULANDO O ERRO MÉDIO QUADRÁTICO (MSE)
        #pragma omp parallel for reduction(+:sum)
        for(int i = 0; i < this->pontuations.size(); i ++){
            float diff = abs(this->pontuations[i] - this->expectedPontuations[i]);
            sum += diff * diff;
        }

        this->result = sum;
        return sum;
    }

    float getResult(){ return this->result; }

};

int main(int argc, char* argv[]){
    #ifdef _WIN32
        SetConsoleOutputCP(65001);
    #endif

    // VALIDANDO PARAMETROS
    if(argc < 10){
        std::cerr << "É preciso informar os 9 valores da tabela de pontuação, primeiro as corners, depois as edges.\n";
        return 1;
    }
    
    bool debug = false;
    if(argc > 10) debug = true;

    vector<string> args;
    for(int i = 1; i < argc; i++) args.push_back(argv[i]);
    
    DatabaseManager* database = new DatabaseManager("../../../");
    Analyzer<BasicScore> analyzer(database, args);

    if(!analyzer.validate_tables()) return 2;
    if(!analyzer.mount_table()) return 3;

    std::cout << analyzer.analyse();

    #ifdef DEBUG
        analyzer.print_pontuations();
    #else
        if(debug) analyzer.print_pontuations();
    #endif

    return 0;
}