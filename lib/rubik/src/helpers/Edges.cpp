#include "helpers/Edges.h"

namespace Edges{

    Edge::Edge(const StickerCoord* stickers[2])
            : stickers{stickers[0], stickers[1]} {}

    const StickerCoord*const* Edge::getStickers() const{ return this->stickers; }

    uint8_t Edge::countEqualStickers(const Rubik& reference, const Rubik& source, const uint8_t offset) const{
        uint8_t count = 0;

        auto stickers = this->getStickers();
        for(uint8_t i = 0; i < 2; i++){
            auto current = stickers[i];
            auto next = stickers[(i + offset) % 2];

            auto sourceSticker = source.getFaces()[current->getFace()].stickers[current->getLine()][current->getColumn()];
            auto referenceSticker = reference.getFaces()[next->getFace()].stickers[next->getLine()][next->getColumn()];

            if(sourceSticker == referenceSticker) count++;
        }

        return count;
    }

    Edges::State Edge::compare(const Rubik& reference, const Rubik& source) const{
        // VERIFICA QUANTOS ADESIVOS BATEM NA PEÇA ORIGINAL
        uint8_t corrects = this->countEqualStickers(reference, source);
        if(corrects == 1) return Edges::State::ORIENTED;
        if(corrects == 2) return Edges::State::CORRECT;

        // VERIFICAR SE A PEÇA ESTA PERMUTADA
        corrects = countEqualStickers(reference, source, 1);
        if(corrects == 2) return Edges::State::PERMUTED;

        // PEÇA INCORRETA
        return Edges::State::INCORRET;
    }

}