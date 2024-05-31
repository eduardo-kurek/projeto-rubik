#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include "../../rubik/scores/AnalyzerMultiple.h"
#include "../../rubik/scores/Tunner.h"
#include "../../rubik/scores/basic-score/BasicScore.h"
#include <type_traits>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <limits>
#include <omp.h>
#include <chrono>
#include <unordered_set>
#ifdef _WIN32
#include <windows.h>
#endif

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
int main(int argc, char* argv[]){
    #ifdef _WIN32
        SetConsoleOutputCP(65001);
    #endif

    if(argc < 2){
        std::cout << "[ERRO] [ARGUMENTOS] Nenhum arquivo de saída foi especificado.\n";
        return 1;
    }

    std::filesystem::path output = argv[1];

    std::string separator = "/";
    #ifdef _WIN32
        separator = "\\";
    #endif

    std::string scramblePath = "tuning"+separator+"scrambles"+separator;

    AnalyzerMultiple<BasicScore> analyzer(scramblePath);
    Tunner tunner(analyzer);

    tunner.addParameter({0, 1});
    tunner.addParameter({0, 1});
    tunner.addParameter({0, 1});
    tunner.addParameter({0, 1});
    tunner.addParameter({0, 1});
    tunner.addParameter({0, 1});
    tunner.addParameter({0, 1});
    tunner.addParameter({0, 1});
    tunner.addParameter({0, 1});

    tunner.run();

    tunner.writeResults(output);

    return 0;
}