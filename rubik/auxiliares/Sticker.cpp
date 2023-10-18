#include "Sticker.h"

Sticker::Sticker(const Color* cor){
    this->color = cor;
}

bool Sticker::operator==(Sticker* sticker){
    return sticker->color->cod == this->color->cod;
}

void Sticker::setColor(const Color* color){
    this->color = color;
}

const Color* Sticker::getColor() const{
    return this->color;
}