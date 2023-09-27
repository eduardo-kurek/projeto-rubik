#include "Rubik.h"
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

Rubik::print(){
    std::string s = this->faces[0]->getLine(1);
    std::cout << s << "\n";
}

Rubik::~Rubik(){
    for(int i = 0; i < 6; i++)
        delete this->faces[i];
}