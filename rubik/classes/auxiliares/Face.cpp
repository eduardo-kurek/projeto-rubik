#include "Face.h"
#include "constantes.h"
#include <string>

Face::Face(){
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            this->stickers[i][j] = Sticker();
}

Face::Face(const Color* color){
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            this->stickers[i][j] = Sticker(color);
}

std::string Face::getLine(uint8_t lineNumber) const{
    std::string line;
    for(uint8_t i = 0; i < 3; i++){
        line += this->stickers[lineNumber][i].getColor()->ch;
        line += CHAR_QUAD;
        line += REDEFINIR_COR;
    }
    
    return line;
}

void Face::transpose(){
    for(uint8_t i = 0; i < 3; i++){
        for(uint8_t j = i + 1; j < 3; j++){
            Sticker temp = this->stickers[i][j];
            this->stickers[i][j] = this->stickers[j][i];
            this->stickers[j][i] = temp;
        }
    }
}