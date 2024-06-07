#include "BasicTunner.h"

BasicConfig BasicTunner::getConfig(std::vector<float>& values){
    if(values.size() != 9)
        throw std::invalid_argument("A quantidade de valores deve ser 9.");

    std::array<float, 4> corners;
    std::array<float, 4> edges;
    
    for(int i = 0; i < 4; i++){
        corners[i] = values[i];
        edges[i] = values[i+4];
    }

    BasicConfig cfg = BasicConfig(corners, edges, values[8]);
    return cfg;
};