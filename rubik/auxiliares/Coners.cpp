#include "Corners.h"
#include <vector>

using namespace Corners;

const Corner C1 = {
        {&Stickers::S1, &Stickers::S10, &Stickers::S39},
        {&Stickers::S39, &Stickers::S1, &Stickers::S10},
        {&Stickers::S10, &Stickers::S39, &Stickers::S1},
};

const Corner C2 = {
        {&Stickers::S3, &Stickers::S37, &Stickers::S30},
        {&Stickers::S30, &Stickers::S3, &Stickers::S37},
        {&Stickers::S37, &Stickers::S30, &Stickers::S3},
};

const Corner C3 = {
        {&Stickers::S7, &Stickers::S19, &Stickers::S12},
        {&Stickers::S12, &Stickers::S7, &Stickers::S19},
        {&Stickers::S19, &Stickers::S12, &Stickers::S7},
};

const Corner C4 = {
        {&Stickers::S9, &Stickers::S28, &Stickers::S21},
        {&Stickers::S21, &Stickers::S9, &Stickers::S28},
        {&Stickers::S28, &Stickers::S21, &Stickers::S9},
};

const Corner C5 = {
        {&Stickers::S52, &Stickers::S45, &Stickers::S16},
        {&Stickers::S16, &Stickers::S52, &Stickers::S45},
        {&Stickers::S45, &Stickers::S16, &Stickers::S52},
};

const Corner C6 = {
        {&Stickers::S54, &Stickers::S36, &Stickers::S52},
        {&Stickers::S52, &Stickers::S54, &Stickers::S36},
        {&Stickers::S52, &Stickers::S54, &Stickers::S36},
};

const Corner C7 = {
        {&Stickers::S46, &Stickers::S18, &Stickers::S25},
        {&Stickers::S25, &Stickers::S46, &Stickers::S18},
        {&Stickers::S18, &Stickers::S25, &Stickers::S46},
};

const Corner C8 = {
        {&Stickers::S48, &Stickers::S27, &Stickers::S34},
        {&Stickers::S34, &Stickers::S48, &Stickers::S27},
        {&Stickers::S27, &Stickers::S34, &Stickers::S48},
};

const std::vector<const Corner*> CORNERS = {
    &Corners::C1, &Corners::C2, &Corners::C3, &Corners::C4,
    &Corners::C5, &Corners::C6, &Corners::C7, &Corners::C8,
};