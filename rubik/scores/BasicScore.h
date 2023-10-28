#pragma once

#include "Score.h"

class BasicScore : public Score{

public:
    uint32_t calculate() override;
    BasicScore(const Rubik* target = new Rubik());

};