#include "Face.h"
#include "constants.h"
#include <string>

Face::Face(const Color* color){
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            this->stickers[i][j] = new Sticker(color);
}

std::string Face::getLine(uint8_t lineNumber){
    std::string line;
    for(uint8_t i = 0; i < 3; i++){
        line += this->stickers[lineNumber][i]->getColor()->ch;
        line += CHAR_QUAD;
        line += REDEFINIR_COR;
    }
    
    return line;
}

Face::~Face(){
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            delete this->stickers[i][j];
}