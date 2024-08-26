#include "helpers/Color.h"

const Color* Color::getColorByCode(char code){
    switch(code){
        case 'B': return &BLUE;
        case 'Y': return &YELLOW;
        case 'R': return &RED;
        case 'W': return &WHITE;
        case 'O': return &ORANGE;
        case 'G': return &GREEN;
        default : return &NONE;
    }
}

const Color* COLORS[6] = {
        &BLUE, &YELLOW, &RED, &WHITE, &ORANGE, &GREEN
};