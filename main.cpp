#include <stdio.h>
#include "rubik/rubik.h"
#include "bibliotecas/variaveis-ambiente.h"
#ifdef _WIN32
#include <windows.h>
#endif

int main(int argc, char* argv[]){
    // AJUSTANDO A CODIFICAÇÃO PARA UTF-8
    #ifdef _WIN32
        SetConsoleOutputCP(65001);
    #endif

    // LENDO AS VARIÁVEIS DE AMBIENTE
    env_read(".env");

    Rubik* rubik = rubik_criar();
    char* scramble = rubik_embaralhar(rubik, 20);
    printf("Scramble: %s\n", scramble);
 
    rubik_imprimir(rubik);
}