#pragma once

#include <vector>

class PontuationTable{
    std::vector<float> cornerPontuation = {3, 2, 1, 0};
    std::vector<float> edgePontuations = {3, 2, 1, 0};

public:
    PontuationTable(std::vector<float> cornerPontuation, std::vector<float> edgePontuations);
    std::vector<float> getCornerPontuations() const;
    std::vector<float> getEdgePontuations() const;
};