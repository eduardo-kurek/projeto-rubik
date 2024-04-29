#pragma once

#include "Solver.h"
#include "../scores/Score.h"

class Greedy : public Solver{

private:
    uint32_t depth;
    Score* score;

    void _findBetter(Rubik& model, const Move* firstMove, uint32_t i, float* movesAccumulator);
    const Move* findBetter(Rubik& r);

public:
    Greedy(uint32_t depth, Score& score);
    Greedy(uint32_t depth, Score& score, Rubik source);
    Greedy(uint32_t depth, Score& score, Rubik source, Rubik target);
    void setDepth(uint32_t depth);
    void solve() override;

};