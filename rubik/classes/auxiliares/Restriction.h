#pragma once

#include "Move.h"
#include <functional>

namespace Restriction{

    std::vector<const Move*> SUPPLEMENTATION(const Move* move);
    std::vector<const Move*> COMPLEMENTATION(const Move* move);
    std::vector<const Move*> BOTH(const Move* move);
    std::vector<const Move*> NOTHING(const Move*);
}