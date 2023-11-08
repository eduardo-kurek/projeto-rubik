#pragma once

#include <cstdint>
#include "../Rubik.h"

class Score{

protected:
    const Rubik* target;

public:
    Score(const Rubik* target);
    virtual uint32_t calculate(const Rubik* source) = 0;
};