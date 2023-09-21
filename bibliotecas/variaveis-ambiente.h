#ifndef VARIAVEIS_AMBIENTE_H
#define VARIAVEIS_AMBIENTE_H

#include <stdlib.h>
#include <stdbool.h>

/**
 * Função que lê um arquivo linha a linha e define todas
 * as variáveis de ambiente encontrado nele.
 * @param nomeArquivo: nome do arquivo a ser lido
 * @return true caso o arquivo exista, false caso contrário
 */
bool env_read(const char* nomeArquivo);

#endif