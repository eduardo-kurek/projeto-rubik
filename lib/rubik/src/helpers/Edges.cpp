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

    const StickerCoord* e1[2] = {Stickers::S2, Stickers::S38};
    const Edge* E1 = new Edge(e1);

    const StickerCoord* e2[2] = {Stickers::S4, Stickers::S11};
    const Edge* E2 = new Edge(e2);

    const StickerCoord* e3[2] = {Stickers::S6, Stickers::S29};
    const Edge* E3 = new Edge(e3);

    const StickerCoord* e4[2] = {Stickers::S8, Stickers::S20};
    const Edge* E4 = new Edge(e4);

    const StickerCoord* e5[2] = {Stickers::S13, Stickers::S42};
    const Edge* E5 = new Edge(e5);

    const StickerCoord* e6[2] = {Stickers::S33, Stickers::S40};
    const Edge* E6 = new Edge(e6);

    const StickerCoord* e7[2] = {Stickers::S15, Stickers::S22};
    const Edge* E7 = new Edge(e7);

    const StickerCoord* e8[2] = {Stickers::S31, Stickers::S24};
    const Edge* E8 = new Edge(e8);

    const StickerCoord* e9[2] = {Stickers::S53, Stickers::S44};
    const Edge* E9 = new Edge(e9);

    const StickerCoord* e10[2] = {Stickers::S49, Stickers::S17};
    const Edge* E10 = new Edge(e10);

    const StickerCoord* e11[2] = {Stickers::S51, Stickers::S35};
    const Edge* E11 = new Edge(e11);

    const StickerCoord* e12[2] = {Stickers::S47, Stickers::S26};
    const Edge* E12 = new Edge(e12);

    const std::vector<const Edge*> EDGES = {
        Edges::E1, Edges::E2, Edges::E3, Edges::E4,
        Edges::E5, Edges::E6, Edges::E7, Edges::E8,
        Edges::E9, Edges::E10, Edges::E11, Edges::E12,
    };

}