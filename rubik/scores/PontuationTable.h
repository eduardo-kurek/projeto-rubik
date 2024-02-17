#pragma once

#include <vector>

class PontuationTable{
    std::vector<float> cornerPontuation = {3, 2, 1, 0};
    std::vector<float> edgePontuations = {3, 2, 1, 0};
    float bufffSynergy = 0;

public:
    PontuationTable(std::vector<float> cornerPontuation, std::vector<float> edgePontuations, float buffSynergy);
    std::vector<float> getCornerPontuations() const;
    std::vector<float> getEdgePontuations() const;
    float getBuffSynergy() const;
};