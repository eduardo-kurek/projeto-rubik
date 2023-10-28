#include "Corners.h"
#include <vector>


const Corner c0 = {
    {
        {Faces::TOP, Coord::ZERO, Coord::ZERO},
        {Faces::LEFT, Coord::ZERO, Coord::ZERO},
        {Faces::BACK, Coord::ZERO, Coord::TWO},
    },
    {
        {Faces::BACK, Coord::ZERO, Coord::TWO},
        {Faces::TOP, Coord::ZERO, Coord::ZERO},
        {Faces::LEFT, Coord::ZERO, Coord::ZERO},
    },
    {
        {Faces::TOP, Coord::ZERO, Coord::ZERO},
        {Faces::LEFT, Coord::ZERO, Coord::ZERO},
        {Faces::BACK, Coord::ZERO, Coord::TWO},
    }

};

const std::vector<const Corner*> CORNERS = {};