#include "rubik/Rubik.h"
#include "rubik/Solver.h"
#include "rubik/auxiliares/StickerCoord.h"
#include <iostream>
#include "rubik/scores/BasicScore.h"
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

//    Rubik* r = new Rubik();
//    BasicScore* bs = new BasicScore(r);
//
//    bs->calculate();
    auto f = Stickers::S1->getFace();

    std::cout << f;
}