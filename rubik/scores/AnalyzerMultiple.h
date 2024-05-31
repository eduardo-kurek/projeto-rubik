#include <iostream>
#include <fstream>
#include <filesystem>
#include <utility>
#include <type_traits>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <omp.h>
#include <string>
#include <vector>
#include "Score.h"
#include "PontuationTable.h"

template <typename TScore, typename = std::enable_if_t<std::is_base_of<Score, TScore>::value>>
class AnalyzerMultiple{

    private:
    
    PontuationTable* table = nullptr;
    TScore* score = nullptr;
    std::vector<std::vector<std::string>> fileContents;

    std::vector<float> expectedPontuations = {95,90,85,80,75,70,65,60,55,50,45,40,35,30,25,20,15,10,5,0};
    std::vector<float> pontuations;

    float calculate_file(int i){
        float sum = 0;
        int count = 0;

        for(int j = 0; j < this->fileContents[i].size(); j++){
            std::string line = this->fileContents[i][j];
            std::vector<const Move*> moves = Move::stringToMoves(line);
            Rubik rubik;
            rubik.move(moves);

            sum += this->score->calculateNormalized(rubik);
            count++;
        }

        return sum / count;
    }

    void calculate_pontuations(){
        this->pontuations = std::vector<float>();
        this->pontuations.resize(20);

        #pragma omp parallel for
        for(int i = 0; i < 20; i++)
            this->pontuations[i] = this->calculate_file(i);
    }

    bool mount_table(std::vector<int> config){
        // MONTANDO TABELA DE PONTUAÇÃO ATRAVÉS DOS VALORES INFORMADOS
        std::vector<float> cornerPontuation;
        std::vector<float> edgePontuations;

        for(int i = 0; i < 8; i++){
            if(i < 4) cornerPontuation.push_back(config[i]);
            else edgePontuations.push_back(config[i]);
        }

        // VERIFICANDO SE O PRIMEIRO VALOR DE CADA VETOR É O MAIOR DO VETOR INTEIRO
        if(*std::max_element(cornerPontuation.begin(), cornerPontuation.end()) != cornerPontuation[0])
            return false;
        if(*std::max_element(edgePontuations.begin(), edgePontuations.end()) != edgePontuations[0])
            return false;

        this->table = new PontuationTable(cornerPontuation, edgePontuations, config[8]);
        this->score = new TScore(this->table);
        return true;
    }

    public:

    AnalyzerMultiple() = default;

    AnalyzerMultiple(std::string& scramble_path){
        for(int i = 0; i < 20; i++){
            std::ifstream file(scramble_path + "scramble_" + std::to_string(i+1) + ".scr");
            if(!file.is_open()){
                std::cerr << "[ERRO] [ARQUIVO] O arquivo " << scramble_path + "scramble_" + std::to_string(i+1) + ".scr" << " não pôde ser aberto.\n";
                throw std::runtime_error("Arquivo não encontrado.");
            }

            std::vector<std::string> lines;
            std::string line;
            while(std::getline(file, line)) lines.push_back(line);
            this->fileContents.push_back(lines);
        }
    }

    float analyse(std::vector<int> config){
        if(config.size() != 9) return 0;
        if(!this->mount_table(config)) return 0;
        this->calculate_pontuations();

        float sum = 0;

        // CALCULANDO O ERRO MÉDIO QUADRÁTICO (MSE)
        #pragma omp parallel for reduction(+:sum)
        for(int i = 0; i < this->pontuations.size(); i ++){
            float diff = abs(this->pontuations[i] - this->expectedPontuations[i]);
            sum += diff * diff;
        }

        return sum;
    }

    float getResult(){ return this->result; }

};