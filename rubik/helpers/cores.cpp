#include "../rubik.h"
#include "constantes.cpp"

/**
* Extrai as cores de uma determinada face e camada de uma instância do cubo,
* valores serão armazenados nas 'cores'
* @param rubik: instancia do cubo a ser extraido
* @param face: face que contém as camadas a serem extraidas
* @param camada: qual camada da face deve ser copiada
* @param cores: array para qual as cores serão copiadas
* @param sentido: sentido do movimento, 0 horário, 1 anti-horário
*/
void extrair_cores(Rubik* rubik, short int face, const Camada* camada, const Cor* cores[3]){

    // Formula para descobrir o sentido da camada
    bool sentido = (camada->ci > camada->ti) || (camada->cj > camada->tj);

    short int count = 0;
    if(!sentido){
        // Sentido horário
        for (int x = camada->ci; x <= camada->ti; x++)
            for (int y = camada->cj; y <= camada->tj; y++)
                cores[count++] = rubik->faces[face]->adesivos[x][y]->cor;
    }
    else{
        // Sentido anti-horário
        for (int x = camada->ci; x >= camada->ti; x--)
            for (int y = camada->cj; y >= camada->tj; y--)
                cores[count++] = rubik->faces[face]->adesivos[x][y]->cor;
    }
}

/**
* Função para clonar um array de cores para outro
* @param origem: de onde as cores devem ser copiadas
* @param destino: para onde elas serão copiadas
* @return bool: retorna true para sucesso, false para erro
*/
bool clonar_cores(const Cor* origem[3], const Cor* destino[3]){
    if(origem == NULL || destino == NULL) return false;
    for(int i = 0; i < 3; i++)
        destino[i] = origem[i];
    return true;
}

/**
* Converte um determinado caracter para sua respectiva cor
* @param ch: caracter a ser convertido
* @param cor: ponteiro para a cor depois de convertida
* @return bool: true para sucesso, e false para erro
*/
bool char_para_cor(char ch, const Cor** cor){
    switch(toupper(ch)){
        case 'B': *cor = &AZUL;
            break;
        case 'Y': *cor = &AMARELO;
            break;
        case 'R': *cor = &VERMELHO;
            break;
        case 'W': *cor = &BRANCO;
            break;
        case 'O': *cor = &LARANJA;
            break;
        case 'G': *cor = &VERDE;
            break;
        default: return false;
    }
    return true;
}