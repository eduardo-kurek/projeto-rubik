#pragma once

#include "StickerCoord.h"


#include <vector>
#include "enums/Faces.h"
#include "enums/Coord.h"

struct Corner{
    const StickerCoord* coordIdle[3];
    const StickerCoord* coordClockwised[3];
    const StickerCoord* coordAnticlockwised[3];
};

namespace Corners{

    extern const Corner C1;
    extern const Corner C2;
    extern const Corner C3;
    extern const Corner C4;
    extern const Corner C5;
    extern const Corner C6;
    extern const Corner C7;
    extern const Corner C8;

    extern const std::vector<const Corner *> CORNERS;

}