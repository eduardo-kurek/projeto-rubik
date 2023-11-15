#include "rubik/Rubik.h"
#include "rubik/Solver.h"
#include "rubik/auxiliares/StickerCoord.h"
#include "rubik/auxiliares/Corners.h"
#include <iostream>
#include "rubik/scores/BasicScore.h"
#include "rubik/scores/PontuationTable.h"
#ifdef _WIN32
#include <windows.h>
#endif

int main(int argc, char* argv[]){
    // AJUSTANDO A CODIFICAÇÃO PARA UTF-8
    #ifdef _WIN32
        SetConsoleOutputCP(65001);
    #endif

//    Rubik* r = new Rubik();
//    r->move(18, R, U, DA, RA, L2, U2, B, D2, F, UA, FA, B2, LA, F2, B, R2, D, L);
//    r->printHistoric();
//    delete r;


//    Rubik r;
//    r.move(8, R, U2, L, B2, D, R2, F2, UA);
//
//    Rubik r2;
//
//    Solver solver;
//    solver.setSource(r);
//    solver.setTarget(r2);
//
//    solver.solve(8);
//
//    auto solves = solver.getFoundedSolves();
//
//    std::cout << "Soluções encontradas: " << std::endl;
//    for(auto& line : solves){
//        for(auto& move : line)
//            std::cout << move->name << " ";
//        std::cout << std::endl;
//    }

    Rubik* r = new Rubik();
    Rubik* r2 = new Rubik();

    r2->scramble(50);
    r2->printHistoric();

    PontuationTable* pt = new PontuationTable({3,2,2,1,0}, {3,2,1,0});
    BasicScore* bs = new BasicScore(pt, r);

    auto value = bs->calculate(*r2);
    std::cout << "score: " << value << ", max score: " << bs->getMaxScore() << std::endl;
}