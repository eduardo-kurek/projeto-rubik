#pragma once

#include "../Score.h"
#include "BasicConfig.h"
#include <vector>

class BasicScore : public virtual Score<BasicConfig>{

    int minSynergyScore = 15;

    float getScoreByState(Corners::State state);
    float getScoreByState(Edges::State state);
    float calculate_face_synergy(const Rubik& source);

public:
    BasicScore(BasicConfig config = BasicConfig(), const Rubik* target = new Rubik());
    float calculate(const Rubik& source) override;

};