#include "Score.h"

Score::Score(const Rubik* target){
    this->target = target;
}

int Score::getMaxScore() const{
    return this->maxScore;
}