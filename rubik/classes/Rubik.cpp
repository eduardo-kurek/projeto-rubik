#include "Rubik.h"
#include "auxiliares/constantes.h"
#include <string>
#include <iostream>

Rubik::Rubik(){
    const Color* cores[6] = {
        &AZUL,
        &AMARELO,
        &VERMELHO,
        &BRANCO,
        &LARANJA,
        &VERDE
    };

    for(int i = 0; i < 6; i++)
        this->faces[i] = new Face(cores[i]);
}

void Rubik::print(bool clear){
    if(clear){
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }
    std::cout << this;
}

Rubik::~Rubik(){
    for(int i = 0; i < 6; i++)
        delete this->faces[i];
}

std::ostream& operator<<(std::ostream& os, const Rubik* rubik){
    // Imprimindo a primeira camada
    for(uint8_t i = 0; i < 3; i++){
        // Imprimindo a margem + o espaço vazio de uma face
        for(uint8_t j = 0; j < TAM_MAX_CARACTERES_VAZIOS + MARGEM_ESQUERDA; j++, os << " ");

        // Imprimindo topo
        os << " " << rubik->faces[F_TOPO]->getLine(i) << "\n";
    }

    // Imprimindo a segunda camada
    for(uint8_t i = 0; i < 3; i++){
        // Imprimindo a margem
        for(uint8_t j = 0; j < MARGEM_ESQUERDA; j++, os << " ");

        // Face esquerda
        os << rubik->faces[F_ESQUERDA]->getLine(i) << " ";

        // Face frontal
        os << rubik->faces[F_FRENTE]->getLine(i) << " ";

        // Face direita
        os << rubik->faces[F_DIREITA]->getLine(i) << " ";

        // Face posterior
        os << rubik->faces[F_TRAS]->getLine(i) << " " << "\n";
    }

    // Imprimindo a terceira camada
    for(uint8_t i = 0; i < 3; i++){
        // Imprimindo a margem + o espaço vazio de uma face
        for(uint8_t j = 0; j < TAM_MAX_CARACTERES_VAZIOS + MARGEM_ESQUERDA; j++, os << " ");

        // Imprimindo baixo
        os << " " << rubik->faces[F_BAIXO]->getLine(i) << "\n";
    }
    return os;
}