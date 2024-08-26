#include "helpers/StickerCoord.h"

StickerCoord::StickerCoord(Faces face, Coord line, Coord column)
    : face(face), line(line), column(column) {}

const Faces& StickerCoord::getFace() const { return this->face; }
const Coord& StickerCoord::getLine() const { return this->line; }
const Coord& StickerCoord::getColumn() const { return this->column; }


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