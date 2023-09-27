#pragma once

#include "Color.h"

class Sticker{
    const Color* color;

public:
    Sticker(const Color* color);
    const Color* getColor();
};