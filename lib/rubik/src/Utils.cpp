#include <omp.h>
#include <iostream>
#include <fstream>
#include "Utils.h"
#include "helpers/Move.h"

std::vector<std::vector<std::vector<const Move *>>> Utils::read_scrambles(const std::string& scramble_path){
    std::vector<std::vector<std::vector<const Move*>>> scrambles;
    
    for(int i = 0; i < 20; i++){
        std::ifstream file(scramble_path + "scramble_" + std::to_string(i+1) + ".scr");
        if(!file.is_open()){
            std::cerr << "[ERRO] [ARQUIVO] O arquivo " << scramble_path + "scramble_" + std::to_string(i+1) + ".scr" << " não pôde ser aberto.\n";
            throw std::runtime_error("Arquivo não encontrado.");
        }

        std::vector<std::vector<const Move*>> moves;
        std::string line;
        while(std::getline(file, line)){
            std::vector<const Move*> move = Move::stringToMoves(line);
            moves.push_back(move);
        }
        scrambles.push_back(moves);
    }

    return scrambles;
}