#pragma once

#include "scores/Config.h"
#include <string>
#include <array>

/*
* Valores negativos podem causar comportamento inesperado, como por exemplo:
*
* Config: corners = {1, -5, -9, -6}, edges = {-96, -78, 35, -6}, synergy = 0
* Cubo com 10 movimentos testado:
* Max Score: -1144
* Score: -482
* Score em porcentagem: 42.1329
*
* Um valor em teoria maior do Score, resulta em uma porcentagem menor...
* O comportamento não é como o esperado, mas funciona mesmo com valores negativos
*/
class BasicConfig : public Config{

    using Array = std::array<float, 4>;
    float array_bounds[2] = {-100.0f, 100.0f};

public:
    Array corners = {1, -5, -9, -6}; // [0]Correta, [1]orientada, [2]permutada (ambos os sentidos), [3]incorreta
    Array edges = {-96, -78, 35, -6}; // [0]Correta, [1]orientada, [2]permutada, [3]incorreta

    BasicConfig() = default;
    BasicConfig(bool);
    BasicConfig(Array corners, Array edges) : corners(corners), edges(edges){};
    std::string toString();
    
};