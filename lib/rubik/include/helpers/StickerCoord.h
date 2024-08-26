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

namespace Stickers{

    extern const StickerCoord* S1;
    extern const StickerCoord* S2;
    extern const StickerCoord* S3;
    extern const StickerCoord* S4;
    extern const StickerCoord* S5;
    extern const StickerCoord* S6;
    extern const StickerCoord* S7;
    extern const StickerCoord* S8;
    extern const StickerCoord* S9;

    extern const StickerCoord* S10;
    extern const StickerCoord* S11;
    extern const StickerCoord* S12;
    extern const StickerCoord* S13;
    extern const StickerCoord* S14;
    extern const StickerCoord* S15;
    extern const StickerCoord* S16;
    extern const StickerCoord* S17;
    extern const StickerCoord* S18;

    extern const StickerCoord* S19;
    extern const StickerCoord* S20;
    extern const StickerCoord* S21;
    extern const StickerCoord* S22;
    extern const StickerCoord* S23;
    extern const StickerCoord* S24;
    extern const StickerCoord* S25;
    extern const StickerCoord* S26;
    extern const StickerCoord* S27;

    extern const StickerCoord* S28;
    extern const StickerCoord* S29;
    extern const StickerCoord* S30;
    extern const StickerCoord* S31;
    extern const StickerCoord* S32;
    extern const StickerCoord* S33;
    extern const StickerCoord* S34;
    extern const StickerCoord* S35;
    extern const StickerCoord* S36;

    extern const StickerCoord* S37;
    extern const StickerCoord* S38;
    extern const StickerCoord* S39;
    extern const StickerCoord* S40;
    extern const StickerCoord* S41;
    extern const StickerCoord* S42;
    extern const StickerCoord* S43;
    extern const StickerCoord* S44;
    extern const StickerCoord* S45;

    extern const StickerCoord* S46;
    extern const StickerCoord* S47;
    extern const StickerCoord* S48;
    extern const StickerCoord* S49;
    extern const StickerCoord* S50;
    extern const StickerCoord* S51;
    extern const StickerCoord* S52;
    extern const StickerCoord* S53;
    extern const StickerCoord* S54;

}