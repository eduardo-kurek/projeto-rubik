#pragma once

#include <iostream>
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
class Analyzer{

    private:

    std::vector<std::string> config;
    std::string scramblePath;
    PontuationTable* table = nullptr;
    TScore* score = nullptr;

    std::vector<float> expectedPontuations = {95,90,85,80,75,70,65,60,55,50,45,40,35,30,25,20,15,10,5,0};
    std::vector<float> pontuations;

    float result;

    public:

    float calculate_file(std::string filePath, int expectedPontuation){
        std::ifstream file(filePath);
        std::string scramble;
        float sum = 0;
        int count = 0;

        while (std::getline(file, scramble)){
            std::vector<const Move*> moves = Move::stringToMoves(scramble);
            Rubik rubik;
            rubik.move(moves);

            // CALCULANDO O ERRO MÉDIO QUADRÁTICO (MSE)
            float diff = abs(score->calculateNormalized(rubik) - expectedPontuation);
            sum += diff * diff;
            count++;
        }

        return sum / count;
    }

    void calculate_pontuations(){
        this->pontuations = std::vector<float>();
        this->pontuations.resize(20);

        #pragma omp parallel for
        for(int i = 0; i < 20; i++)
            this->pontuations[i] = this->calculate_file(this->get_scramble_path(i+1), this->expectedPontuations[i]);
    }

    std::string get_scramble_path(int i){
        return this->scramblePath + "scramble_" + std::to_string(i) + ".scr";
    }

    public:

    Analyzer(std::string scramblePath, std::vector<std::string> config){
        this->scramblePath = scramblePath;
        this->config = config;
    }

    bool validate_files(){
        for(int i = 1; i <= 20; i++){
            std::string fileName = this->get_scramble_path(i);
            if (!std::filesystem::exists(fileName)){
                std::cerr << fileName << " não existe dentro do caminho fornecido.\n";
                return false;
            }
        }
        return true;
    }

    bool mount_table(){
        // MONTANDO TABELA DE PONTUAÇÃO ATRAVÉS DOS VALORES INFORMADOS
        std::vector<float> cornerPontuation;
        std::vector<float> edgePontuations;

        for(int i = 0; i < 8; i++){
            if(i < 4) cornerPontuation.push_back(stof(this->config[i]));
            else edgePontuations.push_back(stof(this->config[i]));
        }

        delete this->table;
        delete this->score;

        this->table = new PontuationTable(cornerPontuation, edgePontuations, stof(this->config[8]));
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

        // SOMANDO TODOS OS RESULTADOS
        #pragma omp parallel for reduction(+:sum)
        for(int i = 0; i < this->pontuations.size(); i++)
            sum += this->pontuations[i];

        this->result = sum;
        return sum;
    }

    float getResult(){ return this->result; }

};