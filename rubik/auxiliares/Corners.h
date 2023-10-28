#pragma once
#include <vector>
#include "enums/Faces.h"
#include "enums/Coord.h"

struct CoordSticker{
    Faces face;
    Coord line;
    Coord column;
};

struct Corner{
    CoordSticker coordIdle[3];
    CoordSticker coordClockwised[3];
    CoordSticker coordAnticlockwised[3];
};

extern const std::vector<const Corner*> CORNERS;