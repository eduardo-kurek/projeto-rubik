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
#include "../../rubik/scores/Analyzer.h"
#include "../../rubik/scores/basic-score/BasicScore.h"
#ifdef _WIN32
#include <windows.h>
#endif

//#define DEBUG

int main(int argc, char* argv[]){
    #ifdef _WIN32
        SetConsoleOutputCP(65001);
    #endif

    // VALIDANDO PARAMETROS
    if(argc < 10){
        std::cerr << "É preciso informar os 9 valores da tabela de pontuação, primeiro as corners, depois as edges e depois o buff.\n";
        return 1;
    }
    
    bool debug = false;
    if(argc > 10) debug = true;

    std::vector<std::string> args;
    for(int i = 1; i < argc; i++) args.push_back(argv[i]);

    std::string separator = "/";
    #ifdef _WIN32
        separator = "\\";
    #endif

    std::string path = "tuning"+separator+"scrambles"+separator;
    
    Analyzer<BasicScore> analyzer(path, args);

    if(!analyzer.validate_files()) return 2;
    if(!analyzer.mount_table()) return 3;

    std::cout << analyzer.analyse();

    #ifdef DEBUG
        analyzer.print_pontuations();
    #else
        if(debug) analyzer.print_pontuations();
    #endif

    return 0;
}