#include "helpers/Face.h"
#include "helpers/constantes.h"
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

FacePosition Face::extract() const{
    FacePosition facePosition{
        this->stickers[0][0].getColor(),
        this->stickers[0][1].getColor(),
        this->stickers[0][2].getColor(),
        this->stickers[1][0].getColor(),
        this->stickers[1][2].getColor(),
        this->stickers[2][0].getColor(),
        this->stickers[2][1].getColor(),
        this->stickers[2][2].getColor()
    };
    return facePosition;
}

void Face::setPosition(const FacePosition& facePosition, const Color& centralColor){
    this->stickers[0][0] = Sticker(facePosition.colors[0]);    
    this->stickers[0][1] = Sticker(facePosition.colors[1]);
    this->stickers[0][2] = Sticker(facePosition.colors[2]);
    this->stickers[1][0] = Sticker(facePosition.colors[3]);
    this->stickers[1][1] = Sticker(&centralColor);
    this->stickers[1][2] = Sticker(facePosition.colors[4]);
    this->stickers[2][0] = Sticker(facePosition.colors[5]);
    this->stickers[2][1] = Sticker(facePosition.colors[6]);
    this->stickers[2][2] = Sticker(facePosition.colors[7]);
}

std::array<const Color*, 3> Face::getLayerColors(const Layer& layer) const{
    std::array<const Color*, 3> colors;
    for(uint8_t i = 0; i < 3; i++){
        Coord x = layer.stickers[i].x;
        Coord y = layer.stickers[i].y;
        colors[i] = this->stickers[x][y].getColor();
    }
    return colors;
}

void Face::setLayer(const Layer& layer, std::array<const Color*, 3> colors){
    for(uint8_t i = 0; i < 3; i++){
        Coord x = layer.stickers[i].x;
        Coord y = layer.stickers[i].y;
        this->stickers[x][y] = Sticker(colors[i]);
    }
}

bool Face::operator==(const Face& face) const{
    for(uint8_t i = 0; i < 3; i++)
        for(uint8_t j = 0; j < 3; j++)
            if(!(this->stickers[i][j] == face.stickers[i][j])) return false;
    return true;
}