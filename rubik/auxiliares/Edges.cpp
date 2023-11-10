#include "Edges.h"

Edge::Edge(const StickerCoord* stickers[2])
        : stickers{stickers[0], stickers[1]} {}

const StickerCoord*const* Edge::getStickers() const{ return this->stickers; }

namespace Edges{

    const Edge* E1 = new Edge({Stickers::S2, Stickers::S38});
    const Edge* E2 = new Edge({Stickers::S4, Stickers::S11});
    const Edge* E3 = new Edge({Stickers::S6, Stickers::S29});
    const Edge* E4 = new Edge({Stickers::S8, Stickers::S20});

    const Edge* E5 = new Edge({Stickers::S13, Stickers::S42});
    const Edge* E6 = new Edge({Stickers::S33, Stickers::S40});
    const Edge* E7 = new Edge({Stickers::S15, Stickers::S22});
    const Edge* E8 = new Edge({Stickers::S31, Stickers::S24});

    const Edge* E9 = new Edge({Stickers::S53, Stickers::S44});
    const Edge* E10 = new Edge({Stickers::S49, Stickers::S17});
    const Edge* E11 = new Edge({Stickers::S51, Stickers::S35});
    const Edge* E12 = new Edge({Stickers::S47, Stickers::S26});

    const std::vector<const Corner*> CORNERS = {
        Edges::E1, Edges::E2, Edges::E3, Edges::E4,
        Edges::E5, Edges::E6, Edges::E7, Edges::E8,
        Edges::E9, Edges::E10, Edges::E11, Edges::E12,
    };

}