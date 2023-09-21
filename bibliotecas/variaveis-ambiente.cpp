#include "variaveis-ambiente.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

bool env_read(const char* nomeArquivo){
    FILE* fp = fopen(nomeArquivo, "r");
    if(fp == NULL) return false;

    char str[256];
    while(!feof(fp)){
        // Lendo a linha
        fgets(str, 256, fp);

        // Separando a chave e o valor
        char* chave = strtok(str, "=");
        char* valor = strtok(NULL, "=");
        uint64_t n = strcspn(valor, "\n");
        valor[n] = 0;

        // Adicionando às variáveis de ambiente
        if(valor == NULL) return false;
        setenv(chave, valor, 1);
    }
    fclose(fp);
    return true;
}