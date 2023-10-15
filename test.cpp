#include "rubik/Rubik.h"
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
    r->move(1, L);

    Rubik* r2 = new Rubik();

    if(*r == *r2){
        std::cout << "Os cubos são iguais";
    }else{
        std::cout << "Os cubos são diferentes";
    }
}