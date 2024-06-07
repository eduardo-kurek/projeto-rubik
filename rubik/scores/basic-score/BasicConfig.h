#pragma once

#include "../Config.h"
#include <array>

class BasicConfig : public Config{

    using Array = std::array<float, 4>;

public:
    Array corners = {0, 0, 0, 0}; // [0]Correta, [1]orientada, [2]permutada (ambos os sentidos), [3]incorreta
    Array edges = {1 , 1, -2, 0}; // [0]Correta, [1]orientada, [2]permutada, [3]incorreta
    float synergy = 0;

    BasicConfig() = default;
    BasicConfig(Array corners, Array edges, float synergy) : corners(corners), edges(edges), synergy(synergy){};
    
};