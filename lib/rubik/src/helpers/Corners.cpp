#include "helpers/Corners.h"
#include <iostream>
#include <cstdio>
#include <vector>

namespace Corners{

    Corner::Corner(const StickerCoord* stickers[3])
            : stickers{stickers[0], stickers[1], stickers[2]} { }

    const StickerCoord*const* Corner::getStickers() const{ return this->stickers; }

    uint8_t Corner::countEqualStickers(const Rubik& reference, const Rubik& source, const uint8_t offset) const{
        uint8_t count = 0;
        auto stickers = this->getStickers();
        
        for(uint8_t i = 0; i < 3; i++){
            auto current = stickers[i];
            auto next = stickers[(i + offset) % 3];

            auto sourceSticker = source.getFaces()[current->getFace()].stickers[current->getLine()][current->getColumn()];
            auto referenceSticker = reference.getFaces()[next->getFace()].stickers[next->getLine()][next->getColumn()];

            if(sourceSticker == referenceSticker) count++;
        }

        return count;
    }

    Corners::State Corner::compare(const Rubik& reference, const Rubik& source) const{
        // VERIFICANDO A ORIENTAÇÃO DA PEÇA
        uint8_t corrects = this->countEqualStickers(reference, source);
        if(corrects == 1) return Corners::State::ORIENTED;
        if(corrects == 3) return Corners::State::CORRECT;

        // VERIFICANDO A PERMUTAÇÃO DA PEÇA NO SENTIDO HORÁRIO
        corrects = this->countEqualStickers(reference, source, 1);
        if(corrects == 3) return Corners::State::PERMUTED;

        // VERIFICANDO A PERMUTAÇÃO DA PEÇA NO SENTIDO ANTI-HORÁRIO
        corrects = this->countEqualStickers(reference, source, 2);
        if(corrects == 3) return Corners::State::PERMUTED;

        // PEÇA COMPLETAMENTE INCORRETA
        return Corners::State::INCORRECT;
    }

}