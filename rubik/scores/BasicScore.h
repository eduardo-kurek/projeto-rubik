#pragma once

#include "Score.h"
#include <vector>

class BasicScore : public virtual Score{

    float cornerPontuations[5] = {3, 2, 1, 1, 0};
    float edgePontuations[4] = {3, 2, 1, 0};

    float getScoreByState(Corners::State state) override;
    float getScoreByState(Edges::State state) override;

public:
    BasicScore(const Rubik* target = new Rubik());
    float calculate(const Rubik* source) override;

};