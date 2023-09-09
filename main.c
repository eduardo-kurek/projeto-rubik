#include <stdio.h>
#include "rubik/rubik.h"
#ifdef _WIN32
#include <windows.h>
#endif


int main(int argc, char* argv[]){
    // AJUSTANDO A CODIFICAÇÃO PARA UTF-8
    #ifdef _WIN32
        SetConsoleOutputCP(65001);
    #endif

    Rubik* rubik = rubik_criar();
    rubik_movimentar(rubik, RA);
    rubik_movimentar(rubik, FA);
    rubik_movimentar(rubik, D);
    rubik_movimentar(rubik, U);
    rubik_movimentar(rubik, B2);
    rubik_movimentar(rubik, RA);
    rubik_movimentar(rubik, D2);
    rubik_movimentar(rubik, B);
    rubik_movimentar(rubik, LA);
    rubik_movimentar(rubik, BA);

    // PLL T
//    rubik_movimentar(rubik, R);
//    rubik_movimentar(rubik, U);
//    rubik_movimentar(rubik, RA);
//    rubik_movimentar(rubik, UA);
//    rubik_movimentar(rubik, RA);
//    rubik_movimentar(rubik, F);
//    rubik_movimentar(rubik, R2);
//    rubik_movimentar(rubik, UA);
//    rubik_movimentar(rubik, RA);
//    rubik_movimentar(rubik, UA);
//    rubik_movimentar(rubik, R);
//    rubik_movimentar(rubik, U);
//    rubik_movimentar(rubik, RA);
//    rubik_movimentar(rubik, FA);

    rubik_imprimir(rubik);

    printf("\n");
    scanf("");
}