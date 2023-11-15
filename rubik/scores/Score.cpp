#include "Score.h"

Score::Score(const Rubik* target){
    this->target = target;
}

float Score::getMaxScore() const{
    return this->maxScore;
}