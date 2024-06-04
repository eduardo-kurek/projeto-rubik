#pragma once

#include "Color.h"

class Sticker{
    const Color* color;

public:
    Sticker() : color(&NONE) {};
    explicit Sticker(const Color* color);
    void setColor(const Color* color);
    const Color* getColor() const;

    bool operator==(const Sticker& other) const;
};