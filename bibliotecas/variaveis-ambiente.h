#ifndef VARIAVEIS_AMBIENTE_H
#define VARIAVEIS_AMBIENTE_H

#include <stdlib.h>
#include <stdbool.h>

/**
 * Função que lê um arquivo linha a linha e define todas
 * as variáveis de ambiente encontrado nele.
 * @param arquivo
 * @return
 */
bool env_read(char arquivo[256]);

#endif