#pragma once

#include "helpers/Layer.h"
#include "helpers/Sticker.h"
#include "helpers/enums/Turn.h"
#include "helpers/enums/Coord.h"
#include "RubikPosition.h"
#include <string>
#include <stdint.h>
#include <array>

class Face{

public:
    Sticker stickers[3][3];

    Face();
    explicit Face(const Color* color);
    std::string getLine(uint8_t lineNumber) const;
    void swapLines(Coord line1, Coord line2);
    void swapColumns(Coord column1, Coord column2);
    void transpose();
    void rotate(Turn turn);
    FacePosition extract() const;
    void setPosition(const FacePosition& facePosition, const Color& centralColor);
    std::array<const Color*, 3> getLayerColors(const Layer& layer) const;
    void setLayer(const Layer& layer, std::array<const Color*, 3> colors);

    bool operator==(const Face& face) const;

};