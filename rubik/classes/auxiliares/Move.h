#pragma once

#include <cstdint>
#include <string>
#include "Layer.h"
#include "enums/Faces.h"
#include "enums/Turn.h"
#include <vector>

struct Move{

    // As 4 faces que envolvem o movimento
    const Faces faces[4];

    // As camadas respectivas destas 4 faces do movimento
    const Layer* layers[4];

    // A face fraca do movimento, ou seja, que apenas rotacionará
    const Faces weakSide;

    // Sentido de rotação da face fraca
    const Turn turn;

    // Quantidade de vezes do movimento
    const uint8_t quantity;

    // Nome do movimento
    const std::string name;

    // Movimentos suplementares, ou seja, que envolvem o mesmo lado do movimento
    const std::vector<const Move*> supplementaryMoves;

    // Movimentos complementares, ou seja, que envolvem o lado oposto do movimento
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