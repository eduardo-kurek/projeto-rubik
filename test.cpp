#include "rubik/Rubik.h"
#include "rubik/Solver.h"
#include "rubik/auxiliares/StickerCoord.h"
#include "rubik/auxiliares/Corners.h"
#include "rubik/scores/PontuationTable.h"
#include "rubik/scores/basic-score/BasicScore.h"
#include "rubik/auxiliares/Move.h"
#include "rubik/auxiliares/Restriction.h"
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <fstream>
#ifdef _WIN32
#include <windows.h>
#endif

int main(int argc, char* argv[]){
    // AJUSTANDO A CODIFICAÇÃO PARA UTF-8
    #ifdef _WIN32
        SetConsoleOutputCP(65001);
    #endif
    
    Rubik r;
    r.move({U, FA, D});

    BasicScore scorer = BasicScore(new PontuationTable({0,0,0,0}, {1,1,-2,0}, 0));
    std::cout << "PONTUAÇÃO DO PRIMEIRO: " << scorer.calculateNormalized(r) << std::endl;
    
}

//25 + 17 + 23 + 21 + 41 + 41 = 