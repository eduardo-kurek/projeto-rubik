#include "Sticker.h"

Sticker::Sticker(const Color* cor){
    this->color = cor;
}

void Sticker::setColor(const Color* color){
    this->color = color;
}

const Color* Sticker::getColor(){
    return this->color;
}