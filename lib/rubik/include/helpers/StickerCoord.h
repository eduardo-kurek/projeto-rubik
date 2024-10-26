#pragma once

#include "helpers/enums/Faces.h"
#include "helpers/enums/Coord.h"

class StickerCoord{
    Faces face;
    Coord line;
    Coord column;

public:
    StickerCoord(Faces face, Coord line, Coord column);
    const Faces& getFace() const ;
    const Coord& getLine() const ;
    const Coord& getColumn() const ;
};