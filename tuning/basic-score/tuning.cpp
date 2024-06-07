#include <iostream>
#include "../../rubik/Utils.h"
#include "../../rubik/scores/basic-score/BasicAnalyzer.h"
#include "../../rubik/scores/basic-score/BasicTunner.h"
#ifdef _WIN32
#include <windows.h>
#endif

int main(int argc, char* argv[]){
    #ifdef _WIN32
        SetConsoleOutputCP(65001);
    #endif

    std::string scramble_path = "tuning/scrambles/";
    auto scrambles = Utils::read_scrambles(scramble_path);

    BasicAnalyzer analyzer(scrambles);
    BasicTunner tunner(analyzer);

    tunner.addParameter({0, 2});
    tunner.addParameter({0, 2});
    tunner.addParameter({0, 2});
    tunner.addParameter({0, 2});
    tunner.addParameter({0, 2});
    tunner.addParameter({0, 2});
    tunner.addParameter({0, 2});
    tunner.addParameter({0, 2});
    tunner.addParameter({0, 0});

    tunner.run();
    tunner.writeResults("results.tun");

    return 0;
}