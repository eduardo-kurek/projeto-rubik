#include "BasicScore.h"
#include "../auxiliares/Corners.h"
#include "../auxiliares/Edges.h"
#include <iostream>

BasicScore::BasicScore(const Rubik* target) : Score(target) {}

uint32_t BasicScore::calculate(const Rubik* source){
    if(source == nullptr) return 0;
    uint32_t score = 0;

    // COMPARANDO AS CORNERS
    int count = 0;
    for(auto& corner : Corners::CORNERS){
        Corners::State state = this->target->compareCorner(*source, *corner);
        switch(state){
            case Corners::State::CORRECT:
                score += this->correct;
                break;
            case Corners::State::ORIENTED:
                score += this->oriented;
                break;
            case Corners::State::PERMUTED_CLOCKWISE:
                score += this->permuted_clockwise;
                break;
            case Corners::State::PERMUTED_ANTICLOCKWISE:
                score += this->permuted_anticlockwise;
                break;
            case Corners::State::INCORRECT:
                score += this->incorrect;
                break;
            default: ;
        }

    }

    return score;
}