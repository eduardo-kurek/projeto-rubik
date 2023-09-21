#include "../rubik.h"
#include "constantes.cpp"

/**
 * Copia todas as cores de uma face para outra, sempre da
 * origem para o destino
 * @param Face* origem: De onde virão os novos valores
 * @param Face* destino: Onde os novos valores devem ser copiados
 */
void face_copiar(const Face* origem, Face* destino){
    for(short int i = 0; i < QT_ADESIVOS_POR_LINHA; i++)
        for(short int j = 0; j < QT_ADESIVOS_POR_LINHA; j++)
            destino->adesivos[i][j] = origem->adesivos[i][j];
}

/**
 * Transpõe uma matriz 3x3 de adesivos (Face). Ou seja,
 * transforma as colunas em linhas, e vice-versa
 * @param face
 */
void face_transpor(Face* face){
    for(uint8_t i = 0; i < 3; i++){
        for(uint8_t j = i + 1; j < 3; j++){
            Adesivo* temp = face->adesivos[i][j];
            face->adesivos[i][j] = face->adesivos[j][i];
            face->adesivos[j][i] = temp;
        }
    }
}

/**
 * Troca duas linhas de uma determinada face
 * @param face: face alvo
 * @param lin1: número da primeira coluna
 * @param lin2: número da segunda coluna
 */
void face_trocar_linhas(Face* face, uint8_t lin1, uint8_t lin2){
    for(uint8_t i = 0; i < 3; i++){
        Adesivo* temp = face->adesivos[lin1][i];
        face->adesivos[lin1][i] = face->adesivos[lin2][i];
        face->adesivos[lin2][i] = temp;
    }
}

/**
 * Troca duas colunas de uma determinada face
 * @param face: face alvo
 * @param col1: número da primeira coluna
 * @param col2: número da segunda coluna
 */
void face_trocar_colunas(Face* face, uint8_t col1, uint8_t col2){
    for(uint8_t i = 0; i < 3; i++){
        Adesivo* temp = face->adesivos[i][col1];
        face->adesivos[i][col1] = face->adesivos[i][col2];
        face->adesivos[i][col2] = temp;
    }
}

/**
* Função responsável por girar uma determinada face do cubo
* @param face: face a ser girada
* @param sentido: sentido do movimento (0) horário, (1) anti-horário
*/
bool face_girar(Face* face, short int sentido){
    if(sentido != 0  && sentido != 1) return false;

    face_transpor(face);
    if(sentido) face_trocar_linhas(face, 0, 2);
    else face_trocar_colunas(face, 0, 2);

    return true;
}


/**
 * Obtém uma string de uma determinada linha
 * de uma face para impressão
 * @param face: Ponteiro da face que a string será extraida
 * @param linha: Qual linha da face deve ser extraida
 * @param str: Retorno da linha em formato de string
 */
void face_obter_linha(Face* face, const short int linha, char* str){
    str[0] = '\0';
    for(short int i = 0; i < QT_ADESIVOS_POR_LINHA; i++){
        strcat(str, face->adesivos[linha][i]->cor->ch);
        strcat(str, CHAR_QUAD);
        strcat(str, REDEFINIR_COR);
    }
}