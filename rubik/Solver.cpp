#include "Solver.h"

Solver::Solver(Rubik source){
    this->source = source;
}

Solver::Solver(Rubik source, Rubik target){
    this->source = source;
    this->target = target;
}

void Solver::setSource(Rubik source){
    this->source = source;
}

void Solver::setTarget(Rubik target){
    this->target = target;
}