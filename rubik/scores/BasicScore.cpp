#include "BasicScore.h"
#include "../auxiliares/Corners.h"

#include <iostream>

BasicScore::BasicScore(const Rubik* target) : Score(target) {}

uint32_t BasicScore::calculate(const Rubik* source){
    if(source == nullptr) return 0;
    uint32_t score = 0;

    this->target->print();
    std::cout << std::endl;
    source->print();
    std::cout << std::endl;


    // COMPARANDO AS CORNERS
    int count = 0;
    for(auto& corner : Corners::CORNERS){
        CornerState state = this->target->compareCorner(*source, *corner);
        std::cout << "PONTUAÇÃO " << count++ << "°: " << state << std::endl << std::endl;
        switch(state){
            case CornerState::CORRECT:
                score += this->correct;
                break;
            case CornerState::ORIENTED:
                score += this->oriented;
                break;
            case CornerState::PERMUTED_CLOCKWISE:
                score += this->permuted_clockwise;
                break;
            case CornerState::PERMUTED_ANTICLOCKWISE:
                score += this->permuted_anticlockwise;
                break;
            case CornerState::INCORRECT:
                score += this->incorrect;
                break;
            default: ;
        }

    }

    return score;
}