#pragma once

#include "scores/Score.h"
#include "scores/basic-score/BasicConfig.h"
#include <vector>

class BasicScore : public Score<BasicConfig>{

    int pow = 3;
    int minSynergyScore = 30; // 6 + 2^pow * 3
    int maxSynergyScore = 2931606; // (9^pow - min)^2 * 6

    float getScoreByState(Corners::State state);
    float getScoreByState(Edges::State state);

public:
    using _TConfig = BasicConfig;
    BasicScore(BasicConfig config = BasicConfig(), Rubik target = Rubik());
    float calculate(const Rubik& source) override;

};