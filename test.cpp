#include "rubik/Rubik.h"
#include "rubik/solvers/Greedy.h"
#include "rubik/solvers/Genetic.h"
#include "rubik/solvers/BruteForce.h"
#include "rubik/auxiliares/StickerCoord.h"
#include "rubik/auxiliares/Corners.h"
#include "rubik/scores/PontuationTable.h"
#include "rubik/scores/basic-score/BasicScore.h"
#include "rubik/auxiliares/Move.h"
#include "rubik/auxiliares/Restriction.h"
#include <queue>
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <fstream>
#include <omp.h>
#include <stdlib.h>
#include <random>
#include "services/Random.h"
#ifdef _WIN32
#include <windows.h>
#endif

int main(int argc, char* argv[]){
    // AJUSTANDO A CODIFICAÇÃO PARA UTF-8
    #ifdef _WIN32
        SetConsoleOutputCP(65001);
    #endif
    
    Rubik r;
    r.move({R, U, L, B2, D2, R2, L2, U, FA});

    PontuationTable pt({0, 0, 0, 0}, {1, 1, -2, 0}, 0);
    BasicScore bs(&pt);

    Genetic g(bs, r);
    g.solve();
    g.printFoundedSolves();
    
    r.move(g.getFoundedSolves()[0]);
    r.print();
    std::cout << "Score: " << bs.calculateNormalized(r) << std::endl;
}