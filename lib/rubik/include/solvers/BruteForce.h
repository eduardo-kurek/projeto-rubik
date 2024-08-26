#pragma once

#include "solvers/Solver.h"

class BruteForce : public Solver{

    private:
    uint32_t depth;
    void solve(Rubik rubik, uint32_t depth);

    public:
    BruteForce() : Solver() {};
    BruteForce(uint32_t depth);
    BruteForce(uint32_t depth, Rubik source);
    BruteForce(uint32_t depth, Rubik source, Rubik target);
    void setDepth(uint32_t depth);
    void solve() override;

};