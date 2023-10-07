#pragma once

#include <cstdint>
#include "Layer.h"

struct Move{
    const uint8_t faces[4];
    const Layer* layers[4];
    const uint8_t faceFraca;
    const short int sentido;
    short int quantidade;
    short int indice;
};