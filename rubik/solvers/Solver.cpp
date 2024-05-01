#include "Solver.h"
#include <iostream>
#include <omp.h>

Solver::Solver() {}

Solver::Solver(Rubik source){
    this->source = source;
}

Solver::Solver(Rubik source, Rubik target){
    this->source = source;
    this->target = target;
}

void Solver::setSource(Rubik source){ this->source = source; }
void Solver::setTarget(Rubik target){ this->target = target; }

void Solver::clear(){
    this->foundedSolves = {};
    this->source.clearRestrictedMoves();
    this->source.clearHistoric();
}

std::vector<std::vector<const Move*>> Solver::getFoundedSolves() const{
    return this->foundedSolves;
}

void Solver::printFoundedSolves() const{
    auto foundedSolves = this->getFoundedSolves();

    if(!foundedSolves.size()){
        std::cout << "No solves founded" << std::endl;
        return;
    }

    for(auto solve : foundedSolves){
        std::cout << "[";
        for(auto move : solve){
            std::cout << move->name << ", ";
        }
        std::cout << "\b\b" << "]" << std::endl;
    }
}
