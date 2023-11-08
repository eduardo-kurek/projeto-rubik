#pragma once

#include "Score.h"

class BasicScore : public Score{

    uint16_t correct = 3;
    uint16_t oriented = 2;
    uint16_t permuted_clockwise = 1;
    uint16_t permuted_anticlockwise = 1;
    uint16_t incorrect = 0;

public:
    BasicScore(const Rubik* target = new Rubik());
    uint32_t calculate(const Rubik* source) override;

};