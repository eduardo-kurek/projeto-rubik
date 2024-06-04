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

void Face::swapLines(Coord line1, Coord line2){
    for(uint8_t i = 0; i < 3; i++){
        Sticker temp = this->stickers[line1][i];
        this->stickers[line1][i] = this->stickers[line2][i];
        this->stickers[line2][i] = temp;
    }
}

void Face::swapColumns(Coord column1, Coord column2){
    for(uint8_t i = 0; i < 3; i++){
        Sticker temp = this->stickers[i][column1];
        this->stickers[i][column1] = this->stickers[i][column2];
        this->stickers[i][column2] = temp;
    }
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

void Face::rotate(Turn turn){
    this->transpose();
    if(turn == CLOCKWISE) this->swapColumns(ZERO, TWO);
    else this->swapLines(ZERO, TWO);
}

const Color** Face::extractLayer(const Layer& layer){
    // OBTENDO O SENTIDO
    bool turn = (layer.si > layer.ei) || (layer.sj > layer.ej);

    uint8_t count = 0;
    const Color** colors = new const Color*[3];
    if(!turn){
        // SENTIDO HORÁRIO
        for (int x = layer.si; x <= layer.ei; x++)
            for (int y = layer.sj; y <= layer.ej; y++)
                colors[count++] = this->stickers[x][y].getColor();
    }
    else{
        // SENTIDO ANTI-HORÁRIO
        for (int x = layer.si; x >= layer.ei; x--)
            for (int y = layer.sj; y >= layer.ej; y--)
                colors[count++] = this->stickers[x][y].getColor();
    }

    return colors;
}

void Face::setLayer(const Layer& layer, const Color* colors[3]){
    // OBTENDO O SENTIDO
    bool turn = (layer.si > layer.ei) || (layer.sj > layer.ej);

    uint8_t count = 0;
    if(!turn){
        // SENTIDO HORÁRIO
        for (int x = layer.si; x <= layer.ei; x++)
            for (int y = layer.sj; y <= layer.ej; y++)
                this->stickers[x][y].setColor(colors[count++]);
    }
    else{
        // SENTIDO ANTI-HORÁRIO
        for (int x = layer.si; x >= layer.ei; x--)
            for (int y = layer.sj; y >= layer.ej; y--)
                this->stickers[x][y].setColor(colors[count++]);
    }
}

bool Face::operator==(const Face& face) const{
    for(uint8_t i = 0; i < 3; i++)
        for(uint8_t j = 0; j < 3; j++)
            if(!(this->stickers[i][j] == face.stickers[i][j])) return false;
    return true;
}