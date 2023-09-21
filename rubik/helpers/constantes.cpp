#ifndef CONSTANTES
#define CONSTANTES

#include "../rubik.h"

/**************************************************************
* VALORES CONSTANTES
**************************************************************/
#pragma region

    #define HORARIO 0
    #define ANTI_HORARIO 1

    #define F_FRENTE 0
    #define F_TOPO 1
    #define F_DIREITA 2
    #define F_BAIXO 3
    #define F_ESQUERDA 4
    #define F_TRAS 5

    #define QT_ADESIVOS_POR_LINHA 3
    #define TAM_MAX_STRING_LINHA 100
    #define TAM_MAX_CARACTERES_VAZIOS 6
    #define MARGEM_ESQUERDA 3

#pragma endregion

/**************************************************************
* OBJETOS CONSTANTES
**************************************************************/


#pragma region

    const Cor AZUL     = {"Azul", 'B', "\x1b[38;2;1;126;255m"};
    const Cor AMARELO  = {"Amarelo", 'Y', "\x1b[38;2;245;255;0m"};
    const Cor VERMELHO = {"Vermelho", 'R', "\x1b[38;2;220;0;0m"};
    const Cor BRANCO   = {"Branco", 'W', "\033[1;37m"};
    const Cor LARANJA  = {"Laranja", 'O', "\x1b[38;2;255;138;25m"};
    const Cor VERDE    = {"Verde", 'G', "\033[38;2;0;225;1m"};

    const Camada CAMADA_U   = {0, 0, 0, 2};
    const Camada CAMADA_UA  = {0, 0, 2, 0};
    const Camada CAMADA_D   = {2, 2, 0, 2};
    const Camada CAMADA_DA  = {2, 2, 2, 0};
    const Camada CAMADA_R   = {0, 2, 2, 2};
    const Camada CAMADA_RA  = {2, 0, 2, 2};
    const Camada CAMADA_L   = {0, 2, 0, 0};
    const Camada CAMADA_LA  = {2, 0, 0, 0};
    const Camada CAMADA_M   = {0, 2, 1, 1};
    const Camada CAMADA_MA  = {2, 0, 1, 1};
    const Camada CAMADA_E   = {1, 1, 0, 2};
    const Camada CAMADA_EA  = {1, 1, 2, 0};

    #pragma region Movimento_F
    const Movimento MOV_F = {
            {F_TOPO, F_DIREITA, F_BAIXO, F_ESQUERDA},
            {&CAMADA_D, &CAMADA_L, &CAMADA_UA, &CAMADA_RA},
            F_FRENTE, HORARIO, 1, 0, "F"
    };
    const Movimento* F = &MOV_F;

    const Movimento MOV_FA = {
            {F_TOPO, F_ESQUERDA, F_BAIXO, F_DIREITA},
            {&CAMADA_DA, &CAMADA_R, &CAMADA_U, &CAMADA_LA},
            F_FRENTE, ANTI_HORARIO, 1, 1, "F'"
    };
    const Movimento* FA = &MOV_FA;

    const Movimento MOV_F2 = {
            {F_TOPO, F_DIREITA, F_BAIXO, F_ESQUERDA},
            {&CAMADA_D, &CAMADA_L, &CAMADA_UA, &CAMADA_RA},
            F_FRENTE, HORARIO, 2, 2, "F2"
    };
    const Movimento* F2 = &MOV_F2;
    #pragma endregion

    #pragma region MOVIMENTO_U
    const Movimento MOV_U = {
            {F_FRENTE, F_ESQUERDA, F_TRAS, F_DIREITA},
            {&CAMADA_U, &CAMADA_U, &CAMADA_U, &CAMADA_U},
            F_TOPO, HORARIO, 1, 3, "U"
    };
    const Movimento* U = &MOV_U;

    const Movimento MOV_UA = {
            {F_FRENTE, F_DIREITA, F_TRAS, F_ESQUERDA},
            {&CAMADA_UA, &CAMADA_UA, &CAMADA_UA, &CAMADA_UA},
            F_TOPO, ANTI_HORARIO, 1, 4, "U'"
    };
    const Movimento* UA = &MOV_UA;

    const Movimento MOV_U2 = {
            {F_FRENTE, F_ESQUERDA, F_TRAS, F_DIREITA},
            {&CAMADA_U, &CAMADA_U, &CAMADA_U, &CAMADA_U},
            F_TOPO, HORARIO, 2, 5, "U2"
    };
    const Movimento* U2 = &MOV_U2;
    #pragma endregion

    #pragma region Movimento_R
    const Movimento MOV_R = {
            {F_FRENTE, F_TOPO, F_TRAS, F_BAIXO},
            {&CAMADA_RA, &CAMADA_RA, &CAMADA_L, &CAMADA_RA},
            F_DIREITA, HORARIO, 1, 6, "R"
    };
    const Movimento* R = &MOV_R;

    const Movimento MOV_RA = {
            {F_FRENTE, F_BAIXO, F_TRAS, F_TOPO},
            {&CAMADA_R, &CAMADA_R, &CAMADA_LA, &CAMADA_R},
            F_DIREITA, ANTI_HORARIO, 1, 7, "R'"
    };
    const Movimento* RA = &MOV_RA;

    const Movimento MOV_R2 = {
            {F_FRENTE, F_TOPO, F_TRAS, F_BAIXO},
            {&CAMADA_RA, &CAMADA_RA, &CAMADA_L, &CAMADA_RA},
            F_DIREITA, HORARIO, 2, 8, "R2"
    };
    const Movimento* R2 = &MOV_R2;
    #pragma endregion

    #pragma region MOVIMENTO_D
    const Movimento MOV_D = {
            {F_FRENTE, F_DIREITA, F_TRAS, F_ESQUERDA},
            {&CAMADA_D, &CAMADA_D, &CAMADA_D, &CAMADA_D},
            F_BAIXO, HORARIO, 1, 9, "D"
    };
    const Movimento* D = &MOV_D;

    const Movimento MOV_DA = {
            {F_FRENTE, F_ESQUERDA, F_TRAS, F_DIREITA},
            {&CAMADA_DA, &CAMADA_DA, &CAMADA_DA, &CAMADA_DA},
            F_BAIXO, ANTI_HORARIO, 1, 10, "D'"
    };
    const Movimento* DA = &MOV_DA;

    const Movimento MOV_D2 = {
            {F_FRENTE, F_DIREITA, F_TRAS, F_ESQUERDA},
            {&CAMADA_D, &CAMADA_D, &CAMADA_D, &CAMADA_D},
            F_BAIXO, HORARIO, 2, 11, "D2"
    };
    const Movimento* D2 = &MOV_D2;
    #pragma endregion

    #pragma region Movimento_L
    const Movimento MOV_L = {
            {F_FRENTE, F_BAIXO, F_TRAS, F_TOPO},
            {&CAMADA_L, &CAMADA_L, &CAMADA_RA, &CAMADA_L},
            F_ESQUERDA, HORARIO, 1, 12, "L"
    };
    const Movimento* L = &MOV_L;

    const Movimento MOV_LA = {
            {F_FRENTE, F_TOPO, F_TRAS, F_BAIXO},
            {&CAMADA_LA, &CAMADA_LA, &CAMADA_R, &CAMADA_LA},
            F_ESQUERDA, ANTI_HORARIO, 1, 13, "L'"
    };
    const Movimento* LA = &MOV_LA;

    const Movimento MOV_L2 = {
            {F_FRENTE, F_BAIXO, F_TRAS, F_TOPO},
            {&CAMADA_L, &CAMADA_L, &CAMADA_RA, &CAMADA_L},
            F_ESQUERDA, HORARIO, 2, 14, "L2"
    };
    const Movimento* L2 = &MOV_L2;
    #pragma endregion

    #pragma region Movimento_B
    const Movimento MOV_B = {
            {F_TOPO, F_ESQUERDA, F_BAIXO, F_DIREITA},
            {&CAMADA_UA, &CAMADA_L, &CAMADA_D, &CAMADA_RA},
            F_TRAS, HORARIO, 1, 15, "B"
    };
    const Movimento* B = &MOV_B;

    const Movimento MOV_BA = {
            {F_TOPO, F_DIREITA, F_BAIXO, F_ESQUERDA},
            {&CAMADA_U, &CAMADA_R, &CAMADA_DA, &CAMADA_LA},
            F_TRAS, ANTI_HORARIO, 1, 16, "B'"
    };
    const Movimento* BA = &MOV_BA;

    const Movimento MOV_B2 = {
            {F_TOPO, F_ESQUERDA, F_BAIXO, F_DIREITA},
            {&CAMADA_UA, &CAMADA_L, &CAMADA_D, &CAMADA_RA},
            F_TRAS, HORARIO, 2, 17, "B2"
    };
    const Movimento* B2 = &MOV_B2;
    #pragma endregion

    const Movimento** MOVIMENTOS[18] = {
            &F, &FA, &F2,
            &U, &UA, &U2,
            &R, &RA, &R2,
            &D, &DA, &D2,
            &L, &LA, &L2,
            &B, &BA, &B2
    };

#pragma endregion

#endif