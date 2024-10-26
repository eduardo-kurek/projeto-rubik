#include "helpers/StickerCoord.h"

StickerCoord::StickerCoord(Faces face, Coord line, Coord column)
    : face(face), line(line), column(column) {}

const Faces& StickerCoord::getFace() const { return this->face; }
const Coord& StickerCoord::getLine() const { return this->line; }
const Coord& StickerCoord::getColumn() const { return this->column; }