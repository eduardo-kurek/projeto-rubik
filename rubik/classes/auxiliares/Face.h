#pragma once

#include "Sticker.h"
#include <string>
#include <stdint.h>

class Face{

public:
    Sticker stickers[3][3];

    Face();
    explicit Face(const Color* color);
    std::string getLine(uint8_t lineNumber) const;
    void transpose();

};