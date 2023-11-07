#include "rubik/Rubik.h"
#include "rubik/Solver.h"
#include "rubik/auxiliares/StickerCoord.h"
#include "rubik/auxiliares/Corners.h"
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
    auto t = Corners::C1->getIdle();
    auto g= Corners::C1->getClockwise();
    auto d = Corners::C1->getAntiClockwise();

    std::cout << t[0]->getFace() << t[1]->getFace() << t[2]->getFace() << std::endl;
    std::cout << g[0]->getFace() << g[1]->getFace() << g[2]->getFace() << std::endl;
    std::cout << d[0]->getFace() << d[1]->getFace() << d[2]->getFace() << std::endl;
}