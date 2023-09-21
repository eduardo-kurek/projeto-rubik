#include "../rubik.h"

/**
     * Função auxiliar para alocar um adesivo
     * @param cor: Cor que o adesivo receberá
     * @return Adesivo*: Endereço do ponteiro criado
     */
Adesivo* adesivo_criar(const Cor* cor){
    Adesivo* adesivo = (Adesivo*)malloc(sizeof(Adesivo));
    adesivo->cor = cor;
    return adesivo;
}

/**
* Função auxiliar para desalocar um adesivo
* @Adesivo** adesivo: Endereço do ponteiro de um adesivo
*/
void adesivo_destruir(Adesivo** adesivo){
    free(*adesivo);
    *adesivo = NULL;
}

/**
 * Função auxiliar para alocar uma face
 * @param cor: Cor que a face devera inicializar
 * @return Face*: Endereço da face criada
 */
Face* face_criar(const Cor* cor){
    Face* face = (Face*)malloc(sizeof(Face));

    for(short int i = 0; i < 3; i++){
        for(short int j = 0; j < 3; j++){
            Adesivo* adesivo = adesivo_criar(cor);
            face->adesivos[i][j] = adesivo;
        }
    }

    return face;
}

/**
* Função auxiliar para alocar uma face
* @param Face** face: Endereço do ponteiro da face
*/
void face_destruir(Face** face){
    Face* f = *face;
    for(short int i = 0; i < 3; i++)
        for(short int j = 0; j < 3; j++)
            adesivo_destruir(&(f->adesivos[i][j]));
    *face = NULL;
}