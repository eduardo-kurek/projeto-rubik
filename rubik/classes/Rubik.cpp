#include "Rubik.h"
#include "auxiliares/constantes.h"
#include "auxiliares/Color.h"
#include <string>
#include <iostream>
#include <regex>

Rubik::Rubik(){
    for(int i = 0; i < 6; i++)
        this->faces[i] = Face(COLORS[i]);
}

Rubik::Rubik(const std::string& position){
    for(int i = 0; i < 6; i++)
        this->faces[i] = Face(COLORS[i]);
    this->setPosition(position);
}

void Rubik::setPosition(const std::string& position){
    // Padrão que a string deve ser enviada
    std::regex pattern("[BYRWOG]{8}-[BYRWOG]{8}-[BYRWOG]{8}-[BYRWOG]{8}-[BYRWOG]{8}-[BYRWOG]{8}");

    // Verifica se o padrão é válido
    if(!regex_match(position, pattern))
        throw std::runtime_error("O formato da string para inicializar um Rubik deve ser válida");

    // Código para definir a posição
    int count = 0;
    for(uint8_t face = 0; face < 6; face++){
        for(uint8_t i = 0; i < 3; i++){
            for(uint8_t j = 0; j < 3; j++){
                if(i != 1 || j != 1){
                    this->faces[face].stickers[i][j].setColor(Color::getColorByCode(position[count]));
                    count++;
                }
                else this->faces[face].stickers[i][j].setColor(COLORS[face]);
            }
        }
        count++;
    }
}

void Rubik::print(bool clear) const{
    if(clear){
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }
    std::cout << this;
}

void Rubik::reset(){
    this->setPosition(POS_RESOLVIDO);
}

std::string Rubik::extract() const{
    std::string str;

    for(uint8_t face = 0; face < 6; face++){
        for(uint8_t l = 0; l < 3; l++)
            for(uint8_t c = 0; c < 3; c++)
                if(l != 1 || c != 1) str += this->faces[face].stickers[l][c].getColor()->cod;
        if(face < 5) str += '-';
    }
    
    return str;
}

void Rubik::move(int numArgs, ...){
    va_list args;
    va_start(args, numArgs);

    for(int i = 0; i < numArgs; i++){
        const Move* mov = va_arg(args, const Move*);

        for(uint8_t qt = 0; qt < mov->quantity; qt++){

            const Color* aux[3] = {&NONE, &NONE, &NONE};
            for(uint8_t j = 0; j < 4; j++){
                // VARIÁVEIS AUXILIARES
                const uint8_t indexFace = mov->faces[j];
                const Layer* layer = mov->layers[j];
                const Color** colors = this->faces[indexFace].extractLayer(*layer);

                // SETANDO A CAMADA ATUAL
                if(j > 0) this->faces[indexFace].setLayer(*layer, aux);

                // AJUSTANDO O AUXILIAR
                for(int k = 0; k < 3; k++)
                    aux[k] = colors[k];

                delete[] colors;
            }

            // SETANDO A PRIMEIRA FACE DA LISTA
            this->faces[mov->faces[0]].setLayer(*mov->layers[0], aux);

            // GIRANDO A FACE FRACA NO SENTIDO RECEBIDO
            this->faces[mov->weakSide].rotate(mov->turn);
        }
    }

    va_end(args);
}

std::ostream& operator<<(std::ostream& os, const Rubik* rubik){
    // Imprimindo a primeira camada
    for(uint8_t i = 0; i < 3; i++){
        // Imprimindo a margem + o espaço vazio de uma face
        for(uint8_t j = 0; j < TAM_MAX_CARACTERES_VAZIOS + MARGEM_ESQUERDA; j++, os << " ");

        // Imprimindo topo
        os << " " << rubik->faces[TOP].getLine(i) << std::endl;
    }

    // Imprimindo a segunda camada
    for(uint8_t i = 0; i < 3; i++){
        // Imprimindo a margem
        for(uint8_t j = 0; j < MARGEM_ESQUERDA; j++, os << " ");

        // Face esquerda
        os << rubik->faces[LEFT].getLine(i) << " ";

        // Face frontal
        os << rubik->faces[FRONT].getLine(i) << " ";

        // Face direita
        os << rubik->faces[RIGHT].getLine(i) << " ";

        // Face posterior
        os << rubik->faces[BACK].getLine(i) << " " << std::endl;
    }

    // Imprimindo a terceira camada
    for(uint8_t i = 0; i < 3; i++){
        // Imprimindo a margem + o espaço vazio de uma face
        for(uint8_t j = 0; j < TAM_MAX_CARACTERES_VAZIOS + MARGEM_ESQUERDA; j++, os << " ");

        // Imprimindo baixo
        os << " " << rubik->faces[BOTTOM].getLine(i) << std::endl;
    }
    return os;
}