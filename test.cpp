#include "rubik/classes/Rubik.h"
#include <iostream>
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

    Rubik* r = new Rubik();
    r->printRestrictedMoves();
    r->move(1, R);
    r->printRestrictedMoves();
    r->forceRestrictedMoves = true;
    r->move(1, R);
    r->print();
    r->printRestrictedMoves();
    r->clearRestrictedMoves();
    std::cout << "Fim";
}