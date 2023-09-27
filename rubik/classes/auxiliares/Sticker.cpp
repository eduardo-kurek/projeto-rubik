#include "Sticker.h"

Sticker::Sticker(const Color* cor){
    this->color = cor;
}

const Color* Sticker::getColor(){
    return this->color;
}