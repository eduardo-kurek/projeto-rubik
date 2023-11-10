#pragma once

#include "StickerCoord.h"

#include <vector>
#include "enums/Faces.h"
#include "enums/Coord.h"

class Corner{
    const StickerCoord* stickers[3];

public:
    Corner(const StickerCoord* stickers[3]);
    const StickerCoord*const* getStickers() const;
};

namespace Corners{

    extern const Corner* C1;
    extern const Corner* C2;
    extern const Corner* C3;
    extern const Corner* C4;
    extern const Corner* C5;
    extern const Corner* C6;
    extern const Corner* C7;
    extern const Corner* C8;

    extern const std::vector<const Corner*> CORNERS;

    enum State{
        CORRECT = 0,
        ORIENTED = 1,
        PERMUTED_CLOCKWISE = 2,
        PERMUTED_ANTICLOCKWISE = 3,
        INCORRECT = 4
    };

}