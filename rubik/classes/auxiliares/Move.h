#pragma once

#include <cstdint>
#include <string>
#include "Layer.h"
#include "enums/Faces.h"
#include "enums/Turn.h"
#include <vector>

struct Move{
    const Faces faces[4];
    const Layer* layers[4];
    const Faces weakSide;
    const Turn turn;
    const uint8_t quantity;
    const std::string name;
    const std::vector<const Move*> supplementaryMoves;
    const std::vector<const Move*> complementaryMoves;
};

extern const Move* U;
extern const Move* UA;
extern const Move* U2;

extern const Move* D;
extern const Move* DA;
extern const Move* D2;

extern const Move* R;
extern const Move* RA;
extern const Move* R2;

extern const Move* L;
extern const Move* LA;
extern const Move* L2;

extern const Move* FA;
extern const Move* F2;
extern const Move* F;

extern const Move* B;
extern const Move* BA;
extern const Move* B2;