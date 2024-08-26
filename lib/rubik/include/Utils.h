#pragma once

#include <vector>
#include <string>
#include "helpers/Move.h"

namespace Utils{
    std::vector<std::vector<std::vector<const Move*>>> read_scrambles(const std::string& scramble_path);
}