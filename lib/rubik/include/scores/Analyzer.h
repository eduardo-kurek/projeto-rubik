#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include "scores/Score.h"

template <typename TScore, typename TConfig>
requires std::derived_from<TScore, Score<TConfig>>
class Analyzer{

    using Scrambles = std::vector<std::vector<std::vector<const Move*>>>;

protected:
    TScore score;
    Scrambles* scrambles;
    std::vector<float> pontuations;
    std::vector<float> expectedPontuations = {95,90,85,80,75,70,65,60,55,50,45,40,35,30,25,20,15,10,5,0};

public:
    bool debug;

    Analyzer(Scrambles* scrambles, bool debug = false){
        if(scrambles->size() != 20)
            throw std::invalid_argument("A quantidade de conjuntos de embaralhamentos deve ser 20.");
        this->scrambles = scrambles;
        this->debug = debug;
    }

    void print_pontuations(){
        std::cout << "{\n";
        for(int i = 0; i < this->pontuations.size(); i++){
            std::cout << "\t\"" << i+1 << "\": ";
            std::cout << std::fixed << std::setprecision(2) << this->pontuations[i];
            std::cout << ",\n";
        }
        std::cout << "\b}\n" << std::endl;
    }
    float virtual analyze(TConfig config) = 0;

};