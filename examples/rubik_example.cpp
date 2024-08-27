#include "Rubik.h"
#include <iostream>
#include <string>

int main(){
    Rubik r;
    std::cout << "Cubo começa resolvido: " << std::endl << &r << std::endl;
    std::cout << "Realizando embaralhamento de 10 movimentos..." << std::endl;
    r.scramble(10);
    std::cout << "Cubo embaralhado: " << std::endl << &r << std::endl;

    std::cout << "Histórico de movimentos: " << std::endl;
    r.printHistoric();

    std::string pos = r.extract();
    std::cout << "Posição do cubo: " << pos << std::endl;

    Rubik r2(pos);
    std::cout << "Cubo criado a partir da posição: " << std::endl << &r2 << std::endl;

    return 0;
}