#pragma once

#include "Sticker.h"
#include "enums/Turn.h"
#include "enums/Coord.h"
#include <string>
#include <stdint.h>

class Face{

public:
    Sticker stickers[3][3];

    Face();
    explicit Face(const Color* color);
    std::string getLine(uint8_t lineNumber) const;
    void swapLines(Coord line1, Coord line2);
    void swapColumns(Coord column1, Coord column2);
    void rotate(Turn turn);
    void transpose();

};