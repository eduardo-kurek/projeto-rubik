#pragma once

#include <vector>
#include "enums/Faces.h"
#include "enums/Coord.h"
#include "StickerCoord.h"
#include "../Rubik.h"
#include <cstdint>

namespace Edges{

    enum State{
        CORRECT = 0,
        ORIENTED = 1,
        PERMUTED = 2,
        INCORRET = 3
    };

    class Edge{
        const StickerCoord* stickers[2];

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
        Edge(const StickerCoord* coords[2]);
        const StickerCoord*const* getStickers() const;

        /**
         * Compara esta edge em relação a dois cubos diferentes
         * @param reference: referência para a comparação, ou seja, em qual
         * estado em quero chegar.
         * @param source: cubo a ser comparado, ou seja, estarei comparando
         * a source em relação à reference.
         * @return: estado da comparação
         */
        Edges::State compare(const Rubik& reference, const Rubik& source) const;
    };


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

}