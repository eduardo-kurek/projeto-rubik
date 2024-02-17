#include "Corners.h"
#include <iostream>
#include <vector>

namespace Corners{

    Corner::Corner(const StickerCoord* stickers[3])
            : stickers{stickers[0], stickers[1], stickers[2]} {}

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

    const StickerCoord* c1[3] = {Stickers::S1, Stickers::S10, Stickers::S39};
    const Corner* C1 = new Corner(c1);

    const StickerCoord* c2[3] = {Stickers::S3, Stickers::S37, Stickers::S30};
    const Corner* C2 = new Corner(c2);

    const StickerCoord* c3[3] = {Stickers::S7, Stickers::S19, Stickers::S12};
    const Corner* C3 = new Corner(c3);

    const StickerCoord* c4[3] = {Stickers::S9, Stickers::S28, Stickers::S21};
    const Corner* C4 = new Corner(c4);

    const StickerCoord* c5[3] = {Stickers::S52, Stickers::S45, Stickers::S16};
    const Corner* C5 = new Corner(c5);

    const StickerCoord* c6[3] = {Stickers::S54, Stickers::S36, Stickers::S43};
    const Corner* C6 = new Corner(c6);

    const StickerCoord* c7[3] = {Stickers::S46, Stickers::S18, Stickers::S25};
    const Corner* C7 = new Corner(c7);

    const StickerCoord* c8[3] = {Stickers::S48, Stickers::S27, Stickers::S34};
    const Corner* C8 = new Corner(c8);

    const std::vector<const Corner*> CORNERS = {
        Corners::C1, Corners::C2, Corners::C3, Corners::C4,
        Corners::C5, Corners::C6, Corners::C7, Corners::C8,
    };

}