#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <iomanip>
#include "../../rubik/scores/basic-score/BasicAnalyzer.h"
#include "../../rubik/Utils.h"
#ifdef _WIN32
#include <windows.h>
#endif

int main(int argc, char* argv[]){
    std::string separator = "/";
    #ifdef _WIN32
        SetConsoleOutputCP(65001);
    #endif

    // VALIDANDO PARAMETROS
    if(argc < 10){
        std::cerr << "É preciso informar os 9 valores de configuração." << std::endl;
        std::cerr << "0: Corner correta" << std::endl;
        std::cerr << "1: Corner orientada" << std::endl;
        std::cerr << "2: Corner permutada" << std::endl;
        std::cerr << "3: Corner incorreta" << std::endl;
        std::cerr << "4: Edge correta" << std::endl;
        std::cerr << "5: Edge orientada" << std::endl;
        std::cerr << "6: Edge permutada" << std::endl;
        std::cerr << "7: Edge incorreta" << std::endl;
        std::cerr << "8: Synergy" << std::endl;
        std::cerr << "9: Debug(opcional)" << std::endl;
        return 1;
    }
    
    std::string scramble_path = "tuning/scrambles/";
    auto scrambles = Utils::read_scrambles(scramble_path);
    
    bool debug = argc > 10 ? true : false;
    std::array<float, 4> corners = {std::stof(argv[1]), std::stof(argv[2]), std::stof(argv[3]), std::stof(argv[4])};
    std::array<float, 4> edges = {std::stof(argv[5]), std::stof(argv[6]), std::stof(argv[7]), std::stof(argv[8])};
    float buff = std::stof(argv[9]);

    BasicConfig cfg = BasicConfig(corners, edges, buff);
    BasicAnalyzer analyzer(scrambles, debug);
    float result = analyzer.analyze(cfg);

    std::cout << std::fixed << std::setprecision(2) << result << std::endl;

    return 0;
}