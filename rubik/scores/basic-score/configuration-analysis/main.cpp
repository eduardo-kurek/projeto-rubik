#include <iostream>
#include <fstream>
#include <filesystem>
#include <utility>
#include <cmath>
#include <omp.h>
#include "../BasicScore.h"
#include "../../PontuationTable.h"
#ifdef _WIN32
#include <windows.h>
#endif

// #define DEBUG

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
    // 3 2 2 1 0 3 2 1 0

    // MONTANDO TABELA DE PONTUAÇÃO ATRAVÉS DOS VALORES INFORMADOS
    std::vector<float> cornerPontuation;
    std::vector<float> edgePontuations;

    for(int i = 1; i < 10; i++){
        if(i < 6) cornerPontuation.push_back(std::stof(argv[i]));
        else edgePontuations.push_back(std::stof(argv[i]));
    }

    // VERIFICANDO SE O PRIMEIRO VALOR DE CADA VETOR É O MAIOR DO VETOR INTEIRO
    if(*std::max_element(cornerPontuation.begin(), cornerPontuation.end()) != cornerPontuation[0])
        return nullptr;
    if(*std::max_element(edgePontuations.begin(), edgePontuations.end()) != edgePontuations[0])
        return nullptr;

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
    std::vector<float> pontuations(fileNames.size());

    #pragma omp parallel for num_threads(6)
    for(int i = 0; i < fileNames.size(); i++){
        pontuations[i] = average_pontuation_file(rootPath / fileNames[i], score);
    }

    return pontuations;
}

float analize_pontuations(std::vector<float> pontuations, std::vector<float> expectedPontuations, const float maxDiff, int lowerTreshold){
    
    if(pontuations.size() != 20){
        std::cerr << "Tamanho do vetor de pontuações inválido (" << pontuations.size() << ").\n";
        throw new std::invalid_argument("Tamanho do vetor de pontuações inválido");
    }

    if(expectedPontuations.size() != 20){
        std::cerr << "Tamanho do vetor de pontuações esperadas inválido.\n";
        throw new std::invalid_argument("Tamanho do vetor de pontuações esperadas inválido.");
    }

    if(lowerTreshold > 20 || lowerTreshold <= 0){
        std::cerr << "Limite inferior deve estar entre 1 e 20\n";
        throw new std::invalid_argument("Limite inferior deve estar entre 1 e 20.");
    }
    
    float sum = 0;

    // LOOP ATÉ OS 16 PRIMEIROS VALORES
    #pragma omp parallel for reduction(+:sum)
    for(int i = 0; i < lowerTreshold-1; i++){
        float diff = std::abs(pontuations[i] - expectedPontuations[i]);

        #ifdef DEBUG
            #pragma omp critical
            {
                std::cout << "Diferença do " << i+1 << "º arquivo: " << pontuations[i] << " - " <<
                expectedPontuations[i] << " = " << diff << ", portanto, soma " << 100 - diff << ".\n";
            }
        #endif
        
        // SE A DIFERENÇA FOR MAIOR QUE O PERMITIDO, CONFIGURAÇÃO INVÁLIDA
        if(diff > maxDiff){
            #ifdef DEBUG
                #pragma omp critical
                {
                    std::cout << "Diferença do " << i+1 << "º arquivo é maior que o permitido. (" << diff << " > " << maxDiff << ")\n";
                }
            #endif
            sum += 50 - diff;
        }
        else sum += 100 - diff;
    }

    // LOOP PARA O RESTANTE DOS VALORES
    #pragma omp parallel for reduction(+:sum)
    for(int i = lowerTreshold-1; i < 20; i++){
        float diff = std::abs(pontuations[i] - expectedPontuations[i]);

        #ifdef DEBUG
            #pragma omp critical
            {
                std::cout << "Diferença do " << i+1 << "º arquivo: " << pontuations[i] << " - " <<
                expectedPontuations[i] << " = " << diff << ", portanto, soma " << 100 - diff << ".\n";
            }
        #endif

        if(pontuations[i] > expectedPontuations[lowerTreshold-1] + maxDiff){
            #ifdef DEBUG
                #pragma omp critical
                {
                    std::cout << "Pontuação do " << i+1 << "º arquivo é maior que a do " << lowerTreshold << "º arquivo. (" <<
                    pontuations[i] << " <= " << pontuations[lowerTreshold-1] << ")\n";
                }
            #endif
            sum += 50 - diff;
        }else sum += 100 - diff;
    }

    return sum;
}

void print_pontuations(std::vector<float> pontuations){
    std::cout << "{\n";
    
    for(int i = 0; i < pontuations.size(); i++){
        std::cout << "\t\"" << i+1 << "\": ";
        std::cout << std::fixed << std::setprecision(2) << pontuations[i];
        std::cout << ",\n";
    }

    std::cout << "\b}\n";
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
    if(pontuationTable == nullptr){
        //std::cerr << "O primeiro valor de cada vetor deve ser o maior.\n";
        return 3;
    }

    BasicScore* score = new BasicScore(pontuationTable);

    // ARMAZENANDO A MÉDIA DE PONTUAÇÃO DE CADA ARQUIVO
    std::vector<float> pontuations = files_to_pontuation(fileNames, path, score);

    // IMPRIMINDO RESULTADOS NO FORMATO JSON
    #ifdef DEBUG
    print_pontuations(pontuations);
    #endif

    // ANALISANDO PONTUAÇÕES OBTIDAS
    std::vector<float> expectedPontuations = {
        95, 90, 85, 80, 75, 70, 65, 60, 55, 50, 
        45, 40, 35, 30, 27, 25 ,20, 15, 10, 8
    };
    float result = analize_pontuations(pontuations, expectedPontuations, 10, 14);

    std::cout << result << "\n";

    return 0;
}