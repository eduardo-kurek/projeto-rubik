#ifndef _RUBIK_
#define _RUBIK_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdint.h>

/**************************************************************
* STRUCTS
**************************************************************/
#pragma region

    /**************************************************************
     * Objeto referente a cada cor
     *
     * @note char nome: nome da cor
     * @note int cod: código referente a cor, 1 à 6
     * @note char ch[15]: string referente ao codigo de impressão da cor
    **************************************************************/
    typedef struct cor{
        char nome[10];
        char cod;
        char ch[25];
    } Cor;

    /**************************************************************
     * Objeto referente a cada adesivo
     *
     * @note const Cor* cor: objeto 'Cor' que o adesivo está atrelado
    **************************************************************/
    typedef struct adesivo{
        const Cor* cor;
    } Adesivo;

    /**************************************************************
     * Objeto referente a cada face
     *
     * @note Adesivo* adesivos[3][3]: matriz contendo os adesivos da face
    **************************************************************/
    typedef struct face{
        Adesivo* adesivos[3][3];
    } Face;

    /**************************************************************
     * Objeto referente às camadas de qualquer face
     * Funciona através de índices para os loops
     * 
     * @note const short int ci: começo do índice 'i'
     * @note const short int ti: término do índice 'i'
     * @note const short int cj: começo do índice 'j'
     * @note const short int tj: término do índice 'j'
    **************************************************************/
    typedef struct camada{
        const short int ci;
        const short int ti;
        const short int cj;
        const short int tj;
    } Camada;

    /**************************************************************
     * Objeto referente aos movimentos possíveis do cubo
     * 
     * @note const short int faces[4]: as quatro faces que serão giradas
     * @note const Camada* camadas[4]: refere qual a camada de determi-
     *  nada face deve ser movida
     * @note const short int faceFraca: qual face deve ser apenas girada
     *  (-1) para nenhuma face
     * @note const short int sentido: qual o sentido a face fraca rodará
     *  horário (0) ou anti-horário (1)
     *  short int quantidade: quantidade de vezes que o movimento
     *  repetirá
     *  short int indice: indice que mapeia o movimento
    **************************************************************/
    typedef struct movimento{
        const short int faces[4];
        const Camada* camadas[4];
        const short int faceFraca;
        const short int sentido;
        short int quantidade;
        short int indice;
    } Movimento;

    /**************************************************************
    * Objeto referente ao cubo mágico
    *
    * @note Face* 0: objeto 'Face' referente a face frontal
    * @note Face* 1: objeto 'Face' referente a face superior
    * @note Face* 2: objeto 'Face' referente a face lateral dir.
    * @note Face* 3: objeto 'Face' referente a face inferior
    * @note Face* 4: objeto 'Face' referente a face lateral esq.
    * @note Face* 5: objeto 'Face' referente a face posterior
    * @note const Movimento* ultimo: Ultimo movimento realizado no cubo
    **************************************************************/
    typedef struct rubik{
        Face* faces[6];
        const Movimento* ultimo;
    } Rubik;

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
     * @param Movimento* mov: Qual movimento deve ser executado
     * @return void
    **************************************************************/
    void rubik_movimentar(Rubik* rubik, const Movimento* mov);

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
    * @return Rubik*: Instância do cubo mágico
    **************************************************************/
    void rubik_embaralhar(Rubik* rubik, short int qt);

#pragma endregion

#endif