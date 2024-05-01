#include "Greedy.h"
#include <iostream>

void Greedy::_findBetter(Rubik& r, const Move* firstMove, uint32_t i, float* movesAccumulator){
    float value = this->score->calculate(r);
    movesAccumulator[firstMove->index] += value;
    
    if(i == this->depth) return;

    for(auto move : r.getValidMoves()){
        Rubik model = r;
        model.move({move});
        _findBetter(model, firstMove, i+1, movesAccumulator);
    }
}

const Move* Greedy::findBetter(Rubik& r){
    if(r == this->target) return nullptr;

    float movesAccumulator[18] = {0};
    auto validMoves = r.getValidMoves();
    
    #pragma omp parallel for
    for(int i = 0; i < validMoves.size(); i++){
        Rubik model = r;
        model.move({validMoves[i]});
        _findBetter(model, validMoves[i], 1, movesAccumulator);
    }

    int better = 0;
    float higher = 0;
    for(uint8_t i = 0; i < 18; i++){
        if(movesAccumulator[i] > higher){
            better = i;
            higher = movesAccumulator[i];
        }
    }

    return Moves[better];
}

Greedy::Greedy(uint32_t depth, Score& score)
    : Solver()
{
    this->depth = depth;
    this->score = &score;
}

Greedy::Greedy(uint32_t depth, Score& score, Rubik source)
    : Solver(source)
{
    this->depth = depth;
    this->score = &score;
}

Greedy::Greedy(uint32_t depth, Score& score, Rubik source, Rubik target)
    : Solver(source, target)
{
    this->depth = depth;
    this->score = &score;
}

void Greedy::solve(){
    this->clear();
    
    std::vector<const Move*> solve;
    Rubik model = this->source;

    while(true){
        const Move* move = this->findBetter(model);
        if(move == nullptr) break;
        solve.push_back(move);
        model.move({move});
        //std::cout << "Move encontrado: " << move->name << std::endl;
    }

    this->foundedSolves.push_back(solve);
}

void Greedy::setDepth(uint32_t depth){ this->depth = depth; }