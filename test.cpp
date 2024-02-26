#include "rubik/Rubik.h"
#include "rubik/Solver.h"
#include "rubik/auxiliares/StickerCoord.h"
#include "rubik/auxiliares/Corners.h"
#include "rubik/scores/PontuationTable.h"
#include "rubik/scores/basic-score/BasicScore.h"
#include "rubik/auxiliares/Move.h"
<<<<<<< HEAD
#include "RUBIK/auxiliares/Restriction.h"
#include "rubik/scores/basic-score/BasicScore.h"
=======
#include "rubik/auxiliares/Restriction.h"
>>>>>>> 446e3ec18681b2ef209e4b7e533907c6a07cbf1c
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

    // Rubik r1;
    // r1.move({U, FA, D});

    // Rubik r2;
    // r2.move({U, FA, D, F});

    // BasicScore scorer = BasicScore(new PontuationTable({0,0,0,0}, {1,1,-2,0}, 0));
    // std::cout << "PONTUAÇÃO DO PRIMEIRO: " << scorer.calculateNormalized(r1) << std::endl;
    // std::cout << "PONTUAÇÃO DO SEGUNDO: " << scorer.calculateNormalized(r2) << std::endl;

    Rubik r = Rubik();
    r.move(Move::stringToMoves("F R' F2 B R' F' U' F' U L' B2 R U' F' U2 F2 L2 U L2 D"));
    r.move(Move::stringToMoves("U F L' F' L B L D' B L' F' B U' R' F' R' L B L U"));
    r.print();

}