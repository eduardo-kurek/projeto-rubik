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
    void swapLines(uint8_t line1, uint8_t line2);
    void swapColumns(uint8_t column1, uint8_t column2);
    void transpose();

};