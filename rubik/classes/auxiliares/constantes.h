#pragma once

// Caracter quadrado
#define CHAR_QUAD "■ "

// Constante de redefinir a cor
#define REDEFINIR_COR "\033[0m"

// Estado resolvido do cubo
#define POS_RESOLVIDO "BBBBBBBB-YYYYYYYY-RRRRRRRR-WWWWWWWW-OOOOOOOO-GGGGGGGG"

// Quantidade de caracteres que representa uma linha de uma face do cubo
#define TAM_MAX_CARACTERES_VAZIOS 6

// Margem de impressão de um cubo
#define MARGEM_ESQUERDA 3

// Sentidos de um movimento
#define HORARIO 0
#define ANTI_HORARIO 1

// Índices das faces do cubo
#define F_FRENTE 0
#define F_TOPO 1
#define F_DIREITA 2
#define F_BAIXO 3
#define F_ESQUERDA 4
#define F_TRAS 5