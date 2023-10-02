#pragma once

#include "Color.h"

class Sticker{
    const Color* color;

public:
    explicit Sticker(const Color* color);
    void setColor(const Color* color);
    const Color* getColor();
};