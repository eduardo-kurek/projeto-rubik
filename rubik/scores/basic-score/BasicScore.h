#pragma once

#include "../Score.h"
#include "../PontuationTable.h"
#include <vector>

class BasicScore : public virtual Score{

    PontuationTable* pontuationTable;

    float getScoreByState(Corners::State state) override;
    float getScoreByState(Edges::State state) override;

public:
    BasicScore(PontuationTable* pt, const Rubik* target = new Rubik());
    float calculate(const Rubik& source) override;

};