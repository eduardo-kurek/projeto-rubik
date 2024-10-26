#include "helpers/Pieces.h"

namespace Stickers{

    const StickerCoord *S1 = new StickerCoord(Faces::TOP, Coord::ZERO, Coord::ZERO);
    const StickerCoord *S2 = new StickerCoord(Faces::TOP, Coord::ZERO, Coord::ONE);
    const StickerCoord *S3 = new StickerCoord(Faces::TOP, Coord::ZERO, Coord::TWO);
    const StickerCoord *S4 = new StickerCoord(Faces::TOP, Coord::ONE, Coord::ZERO);
    const StickerCoord *S5 = new StickerCoord(Faces::TOP, Coord::ONE, Coord::ONE);
    const StickerCoord *S6 = new StickerCoord(Faces::TOP, Coord::ONE, Coord::TWO);
    const StickerCoord *S7 = new StickerCoord(Faces::TOP, Coord::TWO, Coord::ZERO);
    const StickerCoord *S8 = new StickerCoord(Faces::TOP, Coord::TWO, Coord::ONE);
    const StickerCoord *S9 = new StickerCoord(Faces::TOP, Coord::TWO, Coord::TWO);

    const StickerCoord *S10 = new StickerCoord(Faces::LEFT, Coord::ZERO, Coord::ZERO);
    const StickerCoord *S11 = new StickerCoord(Faces::LEFT, Coord::ZERO, Coord::ONE);
    const StickerCoord *S12 = new StickerCoord(Faces::LEFT, Coord::ZERO, Coord::TWO);
    const StickerCoord *S13 = new StickerCoord(Faces::LEFT, Coord::ONE, Coord::ZERO);
    const StickerCoord *S14 = new StickerCoord(Faces::LEFT, Coord::ONE, Coord::ONE);
    const StickerCoord *S15 = new StickerCoord(Faces::LEFT, Coord::ONE, Coord::TWO);
    const StickerCoord *S16 = new StickerCoord(Faces::LEFT, Coord::TWO, Coord::ZERO);
    const StickerCoord *S17 = new StickerCoord(Faces::LEFT, Coord::TWO, Coord::ONE);
    const StickerCoord *S18 = new StickerCoord(Faces::LEFT, Coord::TWO, Coord::TWO);

    const StickerCoord *S19 = new StickerCoord(Faces::FRONT, Coord::ZERO, Coord::ZERO);
    const StickerCoord *S20 = new StickerCoord(Faces::FRONT, Coord::ZERO, Coord::ONE);
    const StickerCoord *S21 = new StickerCoord(Faces::FRONT, Coord::ZERO, Coord::TWO);
    const StickerCoord *S22 = new StickerCoord(Faces::FRONT, Coord::ONE, Coord::ZERO);
    const StickerCoord *S23 = new StickerCoord(Faces::FRONT, Coord::ONE, Coord::ONE);
    const StickerCoord *S24 = new StickerCoord(Faces::FRONT, Coord::ONE, Coord::TWO);
    const StickerCoord *S25 = new StickerCoord(Faces::FRONT, Coord::TWO, Coord::ZERO);
    const StickerCoord *S26 = new StickerCoord(Faces::FRONT, Coord::TWO, Coord::ONE);
    const StickerCoord *S27 = new StickerCoord(Faces::FRONT, Coord::TWO, Coord::TWO);

    const StickerCoord *S28 = new StickerCoord(Faces::RIGHT, Coord::ZERO, Coord::ZERO);
    const StickerCoord *S29 = new StickerCoord(Faces::RIGHT, Coord::ZERO, Coord::ONE);
    const StickerCoord *S30 = new StickerCoord(Faces::RIGHT, Coord::ZERO, Coord::TWO);
    const StickerCoord *S31 = new StickerCoord(Faces::RIGHT, Coord::ONE, Coord::ZERO);
    const StickerCoord *S32 = new StickerCoord(Faces::RIGHT, Coord::ONE, Coord::ONE);
    const StickerCoord *S33 = new StickerCoord(Faces::RIGHT, Coord::ONE, Coord::TWO);
    const StickerCoord *S34 = new StickerCoord(Faces::RIGHT, Coord::TWO, Coord::ZERO);
    const StickerCoord *S35 = new StickerCoord(Faces::RIGHT, Coord::TWO, Coord::ONE);
    const StickerCoord *S36 = new StickerCoord(Faces::RIGHT, Coord::TWO, Coord::TWO);

    const StickerCoord *S37 = new StickerCoord(Faces::BACK, Coord::ZERO, Coord::ZERO);
    const StickerCoord *S38 = new StickerCoord(Faces::BACK, Coord::ZERO, Coord::ONE);
    const StickerCoord *S39 = new StickerCoord(Faces::BACK, Coord::ZERO, Coord::TWO);
    const StickerCoord *S40 = new StickerCoord(Faces::BACK, Coord::ONE, Coord::ZERO);
    const StickerCoord *S41 = new StickerCoord(Faces::BACK, Coord::ONE, Coord::ONE);
    const StickerCoord *S42 = new StickerCoord(Faces::BACK, Coord::ONE, Coord::TWO);
    const StickerCoord *S43 = new StickerCoord(Faces::BACK, Coord::TWO, Coord::ZERO);
    const StickerCoord *S44 = new StickerCoord(Faces::BACK, Coord::TWO, Coord::ONE);
    const StickerCoord *S45 = new StickerCoord(Faces::BACK, Coord::TWO, Coord::TWO);

    const StickerCoord *S46 = new StickerCoord(Faces::BOTTOM, Coord::ZERO, Coord::ZERO);
    const StickerCoord *S47 = new StickerCoord(Faces::BOTTOM, Coord::ZERO, Coord::ONE);
    const StickerCoord *S48 = new StickerCoord(Faces::BOTTOM, Coord::ZERO, Coord::TWO);
    const StickerCoord *S49 = new StickerCoord(Faces::BOTTOM, Coord::ONE, Coord::ZERO);
    const StickerCoord *S50 = new StickerCoord(Faces::BOTTOM, Coord::ONE, Coord::ONE);
    const StickerCoord *S51 = new StickerCoord(Faces::BOTTOM, Coord::ONE, Coord::TWO);
    const StickerCoord *S52 = new StickerCoord(Faces::BOTTOM, Coord::TWO, Coord::ZERO);
    const StickerCoord *S53 = new StickerCoord(Faces::BOTTOM, Coord::TWO, Coord::ONE);
    const StickerCoord *S54 = new StickerCoord(Faces::BOTTOM, Coord::TWO, Coord::TWO);

}

namespace Corners{

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

    const StickerCoord* c8[3] = {Stickers::S48, Stickers::S27, Stickers::S34}; // Rever isso aqui, ta estranho... deveria ser new
    const Corner* C8 = new Corner(c8);

    const std::vector<const Corner*> CORNERS = {
        Corners::C1, Corners::C2, Corners::C3, Corners::C4,
        Corners::C5, Corners::C6, Corners::C7, Corners::C8,
    };
    
}

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