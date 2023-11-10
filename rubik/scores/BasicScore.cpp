#include "BasicScore.h"
#include "../auxiliares/Corners.h"
#include "../auxiliares/Edges.h"
#include <iostream>

BasicScore::BasicScore(const Rubik* target) : Score(target) {
    // ADICIONANDO O TOTAL DAS CORNERS
    this->maxScore += 8 * this->cornerPontuations[0];

    // ADICIONANDO O TOTAL DAS EDGES
    this->maxScore += 12 * this->edgePontuations[0];
}

float BasicScore::getScoreByState(Edges::State state){
    return this->edgePontuations[state];
}

float BasicScore::getScoreByState(Corners::State state){
    return this->cornerPontuations[state];
}

float BasicScore::calculate(const Rubik& source){
    float score = 0;

    // CALCULANDO VALORES DAS CORNERS
    for(auto& corner : Corners::CORNERS){
        Corners::State state = corner->compare(*this->target, source);
        score += this->getScoreByState(state);
    }

    // CALCULANDO VALORES DAS EDGES
    for(auto& edge : Edges::EDGES){
        Edges::State state = edge->compare(*this->target, source);
        score += this->getScoreByState(state);
    }

    return score;
}