#pragma once

#include "Solver.h"

class Greedy : public Solver{

    private:
    uint32_t depth;

    public:
    Greedy(uint32_t depth);

};