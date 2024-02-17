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
    
    Rubik* rubik = new Rubik();
    rubik->move({U});

    BasicScore* bs = new BasicScore(new PontuationTable({3,2,2,1,0}, {3,2,1,0}));

    float res = bs->calculateNormalized(*rubik);

    std::cout << "Pontuação total: " << res << std::endl;


}