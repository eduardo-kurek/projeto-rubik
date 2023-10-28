#pragma once

#include <cstdint>
#include "../Rubik.h"

class Score{

protected:
    uint32_t maxScore;
    const Rubik* target;

public:
    Score(const Rubik* target);
    virtual uint32_t calculate() = 0;
};