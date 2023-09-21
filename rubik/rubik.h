#ifndef RUBIK
#define RUBIK

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdint.h>
#include <stdarg.h>

/**************************************************************
* STRUCTS
**************************************************************/
#pragma region

    typedef struct cor Cor;
    typedef struct adesivo Adesivo;
    typedef struct face Face;
    typedef struct camada Camada;
    typedef struct movimento Movimento;

    typedef struct no No;
    typedef struct historico Historico;

    typedef struct rubik Rubik;

#pragma endregion

/**************************************************************
* CONSTANTES
**************************************************************/
#pragma region

    // Caracter quadrado
    #define CHAR_QUAD "■ "

    // Constante de redefinir a cor
    #define REDEFINIR_COR "\033[0m"

    // Estado resolvido do cubo
    #define POS_RESOLVIDO "BBBBBBBB-YYYYYYYY-RRRRRRRR-WWWWWWWW-OOOOOOOO-GGGGGGGG"

    // Movimentos envolvendo a face U
    extern const Movimento* U;
    extern const Movimento* UA;
    extern const Movimento* U2;

    // Movimentos envolvendo a face D
    extern const Movimento* D;
    extern const Movimento* DA;
    extern const Movimento* D2;

    // Movimentos envolvendo a face R
    extern const Movimento* R;
    extern const Movimento* RA;
    extern const Movimento* R2;

    // Movimentos envolvendo a face L
    extern const Movimento* L;
    extern const Movimento* LA;
    extern const Movimento* L2;

    // Movimentos envolvendo a face F
    extern const Movimento* F;
    extern const Movimento* FA;
    extern const Movimento* F2;

    // Movimentos envolvendo a face B
    extern const Movimento* B;
    extern const Movimento* BA;
    extern const Movimento* B2;

    // Array contendo todos os movimentos disponíveis
    extern const Movimento** MOVIMENTOS[18];

#pragma endregion

/**************************************************************
* FUNÇÕES
**************************************************************/
#pragma region

    /**************************************************************
     *  Função responsável por criar todos os objetos necessários
     * para trabalhar com o cubo mágico, sendo eles: Rubik, Face
     * e adesivo. O cubo mágico é iniciado já resolvido
     *
     * @return Rubik*: Ponteiro para o novo rubik
    **************************************************************/
    Rubik* rubik_criar();

    /**************************************************************
    *  Função responsável por desalocar um objeto de cubo mágico
    *
    * @param Rubik** rubik: Endereço do ponteiro de um objeto
     *  rubik a ser destruido
    * @return void
    **************************************************************/
    void rubik_destruir(Rubik** rubik);

    /**************************************************************
    * Verifica se duas posições do cubo mágico são iguais
     *
    * @param char* pos1: string da 1° posição
    * @param char* pos2: string da 2° posição
    * @return true caso sejam iguais, false caso contrário
    **************************************************************/
    bool rubik_posicoes_iguais(char* pos1, char* pos2);

    /**************************************************************
    * Verifica se uma instância do cubo esteja resolvido
     *
    * @param Rubik* rubik: objeto a ser verificado
    * @return true caso esteja resolvido, false caso contrário
    **************************************************************/
    bool rubik_redefinir(Rubik* rubik);

    /**************************************************************
     * Função responsável por imprimir o estado atual do cubo
     * mágico, primeiro limpa o terminal, e depois imprime todas
     * as posições corretamente
     * 
     * @param Rubik* rubik: Instância do cubo a imprimir
     * @return void
    **************************************************************/
    void rubik_imprimir(Rubik* rubik);

    /**************************************************************
     * Função responsável por movimentar o cubo mágico
     * 
     * @param Rubik* rubik: Instância a ser movimentada
     * @param int qt: Quantidade de movimentos que seram executados
     * @param ...: Movimentos a serem executados
     * @return void
    **************************************************************/
    void rubik_movimentar(Rubik* rubik, int qt, ...);

    /**************************************************************
     * Define determinada posição de um cubo através da string
     * recebida
     * @param Rubik* rubik: objeto a ser definido
     * @param char* posicao: posição a ser definida
     * @return true para sucesso, false para erro
    **************************************************************/
    bool rubik_definir_posicao(Rubik* rubik, char* posicao);

    /**************************************************************
    * Redefine uma instância do cubo mágico à posição inicial
    *
    * @param Rubik* rubik: objeto a ser redefinido
    * @return bool: sempre true, a princípio
    **************************************************************/
    bool rubik_redefinir(Rubik* rubik);

    /**************************************************************
    * Converte um objeto cubo mágico para uma sequencia de
    * caracteres da seguinte forma:
    *  FFFFFFFF-UUUUUUUU-RRRRRRRR-DDDDDDDD-LLLLLLLL-BBBBBBBB
    * Onde os caracteres representam as cores de determinado
    * adesivo, sempre da esquerda para direita e de cima para
    * baixo (os adesivos do centro são omitidos).
    *
    * Cores: Azul: B, Amarelo: Y, Vermelho: R, Branco: W,
    * Laranja: O, Verde: G
    *
    * @param Rubik* rubik: instância a ser convertida
    * @return char*: string contendo o objeto convertido
    **************************************************************/
    char* rubik_exportar(Rubik* rubik);

    /**************************************************************
     * Converte uma sequencia de caracteres da seguinte forma:
     *  FFFFFFFF-UUUUUUUU-RRRRRRRR-DDDDDDDD-LLLLLLLL-BBBBBBBB
     *
     * Para um objeto cubo mágico
     *
     * @param char* pos: Posição a ser convertida
     * @return Rubik*: Instância do cubo mágico
    **************************************************************/
    Rubik* rubik_importar(char* pos);

    /**************************************************************
    * Embaralha um cubo mágico X vezes
    * @param Rubik* rubik: instância a ser embaralhada
    * @param short int qt: quantidade de movimentos aleatórios
    * @return string contendo os embaralhamentos realizados
    **************************************************************/
    char* rubik_embaralhar(Rubik* rubik, int qt);

    /**************************************************************
    * Imprime o histórico de movimentos do cubo
    * @param Rubik* rubik: instância do cubo contendo o histórico
    * @return void
    **************************************************************/
    void rubik_imprimir_historico(Rubik* rubik);

#pragma endregion

#endif