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

    Rubik* r = new Rubik();
    r->print();
    r->move(1, R);
    r->print();
    delete r;
}