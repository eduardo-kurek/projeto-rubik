#pragma once

#include <cstdint>

struct Layer{
    uint8_t si;
    uint8_t ei;
    uint8_t sj;
    uint8_t ej;

    Layer(uint8_t si, uint8_t ei, uint8_t sj, uint8_t ej);
};

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