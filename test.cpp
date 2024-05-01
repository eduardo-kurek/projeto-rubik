#include "rubik/Rubik.h"
#include "rubik/solvers/Greedy.h"
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
#include <omp.h>
#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#endif

int main(int argc, char* argv[]){
    // AJUSTANDO A CODIFICAÇÃO PARA UTF-8
    #ifdef _WIN32
        SetConsoleOutputCP(65001);
    #endif
    
    Rubik r;
    r.move({FA, UA, B, DA});
    
    PontuationTable* pt = new PontuationTable({0,0,0,0}, {1,1,-1,0}, 0);
    BasicScore* bs = new BasicScore(pt);

    Greedy g(2, *bs, r);
    g.solve();
    g.printFoundedSolves();
    
}