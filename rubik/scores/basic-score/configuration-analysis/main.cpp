#include <iostream>
#include <fstream>
#include <filesystem>
#include <utility>
#include "../BasicScore.h"
#include "../../PontuationTable.h"
#ifdef _WIN32
#include <windows.h>
#endif

bool validate_files(std::filesystem::path path, std::vector<std::string> fileNames){
    for (const auto& fileName : fileNames) {
        std::filesystem::path filePath = path / fileName;
        if (!std::filesystem::exists(filePath)){
            std::cerr << fileName << " não existe dentro do caminho fornecido.\n";
            return false;
        }
    }
    return true;
}

PontuationTable* mount_pontuation_table(char* argv[]){
    // MONTANDO TABELA DE PONTUAÇÃO ATRAVÉS DOS VALORES INFORMADOS
    std::vector<float> cornerPontuation;
    std::vector<float> edgePontuations;

    for(int i = 1; i < 10; i++){
        if(i < 6) cornerPontuation.push_back(std::stof(argv[i]));
        else edgePontuations.push_back(std::stof(argv[i]));
    }

    return new PontuationTable(cornerPontuation, edgePontuations);
}

float average_pontuation_file(std::filesystem::path filePath, BasicScore* score){
    std::ifstream file(filePath);
    std::string scramble;
    float sum = 0;
    int count = 0;

    while (std::getline(file, scramble)){
        std::vector<const Move*> moves = Move::stringToMoves(scramble);
        Rubik rubik;
        rubik.move(moves);

        sum += score->calculateNormalized(rubik);
        count++;
    }

    return sum / count;
}

std::vector<float> files_to_pontuation(std::vector<std::string> fileNames, std::filesystem::path rootPath, BasicScore* score){
    std::vector<float> pontuations;
    pontuations.reserve(fileNames.size());

    for(const auto fileName : fileNames)
        pontuations.push_back(average_pontuation_file(rootPath / fileName, score));

    return pontuations;
}

void print_pontuations(std::vector<float> pontuations){
    std::cout << "{";
    
    for(int i = 0; i < pontuations.size(); i++){
        std::cout << "\"" << i+1 << "\": ";
        std::cout << std::fixed << std::setprecision(2) << pontuations[i];
        std::cout << ",";
    }

    std::cout << "\b}";
}

int main(int argc, char* argv[]){
    #ifdef _WIN32
        SetConsoleOutputCP(65001);
    #endif

    // VALIDANDO PARAMETROS
    if(argc < 10){
        std::cerr << "É preciso informar os 9 valores da tabela de pontuação, primeiro as corners, depois as edges.\n";
        return 1;
    }

    std::filesystem::path path = "../../../../scrambles/";
    std::vector<std::string> fileNames = {
        "1move.scr", "2moves.scr", "3moves.scr", "4moves.scr", "5moves.scr", 
        "6moves.scr", "7moves.scr", "8moves.scr", "9moves.scr", "10moves.scr", 
        "11moves.scr", "12moves.scr", "13moves.scr", "14moves.scr", "15moves.scr",
        "16moves.scr", "17moves.scr", "18moves.scr", "19moves.scr", "20moves.scr"
    };

    // VALIDANDO OS ARQUIVOS
    if(!validate_files(path, fileNames))
        return 2;

    // INSTÂNCIA DO SCORE
    PontuationTable* pontuationTable = mount_pontuation_table(argv);
    BasicScore* score = new BasicScore(pontuationTable);

    // ARMAZENANDO A MÉDIA DE PONTUAÇÃO DE CADA ARQUIVO
    std::vector<float> pontuations = files_to_pontuation(fileNames, path, score);

    // IMPRIMINDO RESULTADOS NO FORMATO JSON
    print_pontuations(pontuations);

    return 0;
}