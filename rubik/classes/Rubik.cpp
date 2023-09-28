#include "Rubik.h"
#include "auxiliares/constantes.h"
#include <stdio.h>
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

void Rubik::print(){
    // Imprimindo a primeira camada
    for(uint8_t i = 0; i < 3; i++){
        // Imprimindo a margem + o espaço vazio de uma face
        for(uint8_t j = 0; j < TAM_MAX_CARACTERES_VAZIOS + MARGEM_ESQUERDA; j++, std::cout << " ");

        // Imprimindo topo
        std::cout << " " << this->faces[F_TOPO]->getLine(i) << "\n";
    }

    // Imprimindo a segunda camada
    for(uint8_t i = 0; i < 3; i++){
        // Imprimindo a margem
        for(uint8_t j = 0; j < MARGEM_ESQUERDA; j++, std::cout << " ");

        // Face esquerda
        std::cout << this->faces[F_ESQUERDA]->getLine(i) << " ";

        // Face frontal
        std::cout << this->faces[F_FRENTE]->getLine(i) << " ";

        // Face direita
        std::cout << this->faces[F_DIREITA]->getLine(i) << " ";

        // Face posterior
        std::cout << this->faces[F_TRAS]->getLine(i) << " " << "\n";
    }

    // Imprimindo a terceira camada
    for(uint8_t i = 0; i < 3; i++){
        // Imprimindo a margem + o espaço vazio de uma face
        for(uint8_t j = 0; j < TAM_MAX_CARACTERES_VAZIOS + MARGEM_ESQUERDA; j++, std::cout << " ");

        // Imprimindo baixo
        std::cout << " " << this->faces[F_BAIXO]->getLine(i) << "\n";
    }
}

Rubik::~Rubik(){
    for(int i = 0; i < 6; i++)
        delete this->faces[i];
}