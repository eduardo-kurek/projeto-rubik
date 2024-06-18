#pragma once

#include "../Config.h"
#include <array>

class BasicConfig : public Config{

    using Array = std::array<float, 4>;
    float array_bounds[2] = {-100.0f, 100.0f};
    float synergy_bounds[2] = {0.0f, 10.0f};

public:
    Array corners = {0, 0, 0, 0}; // [0]Correta, [1]orientada, [2]permutada (ambos os sentidos), [3]incorreta
    Array edges = {1 , 1, -2, 0}; // [0]Correta, [1]orientada, [2]permutada, [3]incorreta
    float synergy = 0;

    BasicConfig() = default;
    BasicConfig(bool);
    BasicConfig(Array corners, Array edges, float synergy) : corners(corners), edges(edges), synergy(synergy){};
    void print();
    void randomize_synergy();
    std::string toString();
    
};