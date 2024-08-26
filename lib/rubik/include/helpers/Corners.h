#pragma once

#include "StickerCoord.h"
#include <vector>
#include "helpers/enums/Faces.h"
#include "helpers/enums/Coord.h"
#include "Rubik.h"

namespace Corners{

    enum State{
        CORRECT = 0,
        ORIENTED = 1,
        PERMUTED = 2,
        INCORRECT = 3
    };

    class Corner{
        const StickerCoord* stickers[3];

        /**
         * Conta quantos adesivos estão iguais em relação a esta
         * peça de outro cubo mágico
         * @param reference: cubo mágico referência
         * @param source: cubo mágico fonte da comparação
         * @param offset: caso necessário comparar com o adesivo da "frente".
         * @return
         */
        uint8_t countEqualStickers(const Rubik& reference, const Rubik& source, const uint8_t offset = 0) const;

    public:
        Corner(const StickerCoord* stickers[3]);
        const StickerCoord*const* getStickers() const;

        /**
         * Compara esta corner em relação a dois cubos diferentes
         * @param reference: referência para a comparação, ou seja, em qual
         * estado em quero chegar.
         * @param source: cubo a ser comparado, ou seja, estarei comparando
         * a source em relação à reference.
         * @return: estado da comparação
         */
        Corners::State compare(const Rubik& reference, const Rubik& source) const;
    };

    extern const Corner* C1;
    extern const Corner* C2;
    extern const Corner* C3;
    extern const Corner* C4;
    extern const Corner* C5;
    extern const Corner* C6;
    extern const Corner* C7;
    extern const Corner* C8;

    extern const std::vector<const Corner*> CORNERS;
}