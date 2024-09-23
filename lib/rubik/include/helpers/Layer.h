#pragma once

#include "helpers/StickerCoord.h"
#include <cstdint>
#include <array>

struct LayerCoord{
    Coord x;
    Coord y;
};

struct Layer{
    std::array<LayerCoord, 3> stickers;
};

extern const LayerCoord _00;
extern const LayerCoord _01;
extern const LayerCoord _02;
extern const LayerCoord _10;
extern const LayerCoord _11;
extern const LayerCoord _12;
extern const LayerCoord _20;
extern const LayerCoord _21;
extern const LayerCoord _22;

extern const Layer LAYER_U;
extern const Layer LAYER_UA;
extern const Layer LAYER_D;
extern const Layer LAYER_DA;
extern const Layer LAYER_R;
extern const Layer LAYER_RA;
extern const Layer LAYER_L;
extern const Layer LAYER_LA;
extern const Layer LAYER_M;
extern const Layer LAYER_MA;
extern const Layer LAYER_E;
extern const Layer LAYER_EA;