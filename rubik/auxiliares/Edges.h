#pragma once

#include <vector>
#include "enums/Faces.h"
#include "enums/Coord.h"
#include "StickerCoord.h"

class Edge{
    const StickerCoord* stickers[2];

public:
    Edge(const StickerCoord* coords[2]);
    const StickerCoord*const* getStickers() const;
};

namespace Edges{

    extern const Edge* E1;
    extern const Edge* E2;
    extern const Edge* E3;
    extern const Edge* E4;
    extern const Edge* E5;
    extern const Edge* E6;
    extern const Edge* E7;
    extern const Edge* E8;
    extern const Edge* E9;
    extern const Edge* E10;
    extern const Edge* E11;
    extern const Edge* E12;
    extern const Edge* E13;
    extern const Edge* E14;

    extern const std::vector<const Edge*> EDGES;

    enum State{
        CORRECT = 0,
        ORIENTED = 1,
        PERMUTED = 2,
        INCORRET = 3
    };

}