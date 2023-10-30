#pragma once

#include "Score.h"

class BasicScore : public Score{

public:
    uint32_t calculate(const Rubik* source) override;
    BasicScore(const Rubik* target = new Rubik());

};