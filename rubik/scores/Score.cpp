#include "Score.h"

Score::Score(const Rubik* target){
    this->target = target;
}

float Score::getMaxScore() const{
    return this->maxScore;
}

float Score::calculateNormalized(const Rubik& source){
    float score = this->calculate(source) * 100;
    return score / this->getMaxScore();
}