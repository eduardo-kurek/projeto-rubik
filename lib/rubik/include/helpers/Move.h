#pragma once

#include <cstdint>
#include <string>
#include "helpers/Layer.h"
#include "helpers/enums/Faces.h"
#include "helpers/enums/Turn.h"
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

    // Índice deste movimento no array de movimentos
    const uint8_t index;

    // Movimentos suplementares, ou seja, que envolvem o mesmo lado do movimento
    const std::vector<const Move*> supplementaryMoves;

    // Movimentos complementares, ou seja, que envolvem o lado oposto do movimento
    const std::vector<const Move*> complementaryMoves;

public:

    // Converte um código de um movimento, para o objeto Move
    // Dispara uma exceção caso o código fornecido seja invalido
    static const Move* codToMove(const std::string str);

    // Converte uma string para um vetor de movimentos
    static const std::vector<const Move*> stringToMoves(const std::string str);

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

extern const std::vector<const Move*> Moves;