#pragma once

#include "../Score.h"
#include "BasicConfig.h"
#include <vector>

class BasicScore : public Score<BasicConfig>{

    int pow = 3;
    int minSynergyScore = 30; // 6 + 2^pow * 3
    int maxSynergyScore = 2931606; // (9^pow - min)^2 * 6

    float getScoreByState(Corners::State state);
    float getScoreByState(Edges::State state);
    
    /* Conta quantas cores iguais há em cada face e faz 
    uma conta quadrática para somar ao score final */
    float calculate_face_synergy(const Rubik& source, float score);

public:
    BasicScore(BasicConfig config = BasicConfig(), Rubik target = Rubik());
    float calculate(const Rubik& source) override;

};