#include "Corners.h"
#include <vector>

Corner::Corner(const StickerCoord* coords[3])
    : coords{coords[0], coords[1], coords[2]} {}

const StickerCoord*const* Corner::getCoords() const{ return this->coords; }

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

    const StickerCoord* c8[3] = {Stickers::S48, Stickers::S27, Stickers::S34};
    const Corner* C8 = new Corner(c8);

    const std::vector<const Corner*> CORNERS = {
        Corners::C1, Corners::C2, Corners::C3, Corners::C4,
        Corners::C5, Corners::C6, Corners::C7, Corners::C8,
    };

}