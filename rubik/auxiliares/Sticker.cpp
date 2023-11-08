#include "Sticker.h"

Sticker::Sticker(const Color* cor){
    this->color = cor;
}

bool Sticker::operator==(const Sticker& other){
    return other.getColor()->cod == this->getColor()->cod;
}

void Sticker::setColor(const Color* color){
    this->color = color;
}

const Color* Sticker::getColor() const{
    return this->color;
}