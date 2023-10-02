#include "Color.h"

const Color* Color::getColorByCode(char code){
    switch(code){
        case 'B': return &AZUL;
        case 'Y': return &AMARELO;
        case 'R': return &VERMELHO;
        case 'W': return &BRANCO;
        case 'O': return &LARANJA;
        case 'G': return &VERDE;
        default : return &NONE;
    }
}

const Color* COLORS[6] = {
        &AZUL, &AMARELO, &VERMELHO, &BRANCO, &LARANJA, &VERDE
};