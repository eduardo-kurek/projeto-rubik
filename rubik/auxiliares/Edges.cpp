#include "Edges.h"

Edge::Edge(const StickerCoord* stickers[2])
        : stickers{stickers[0], stickers[1]} {}

const StickerCoord*const* Edge::getStickers() const{ return this->stickers; }

namespace Edges{

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