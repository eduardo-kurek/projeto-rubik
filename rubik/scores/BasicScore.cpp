#include "BasicScore.h"
#include "../auxiliares/Corners.h"
#include "../auxiliares/Edges.h"
#include <iostream>

BasicScore::BasicScore(const Rubik* target) : Score(target) {}

float BasicScore::getScoreByState(Edges::State state){
    return this->edgePontuations[state];
}

float BasicScore::getScoreByState(Corners::State state){
    return this->cornerPontuations[state];
}

float BasicScore::calculate(const Rubik* source){
    if(source == nullptr) return 0;
    float score = 0;

    // CALCULANDO VALORES DAS CORNERS
    for(auto& corner : Corners::CORNERS){
        Corners::State state = this->target->compareCorner(*source, *corner);
        score += this->getScoreByState(state);
    }

    // CALCULANDO VALORES DAS EDGES
    for(auto& edge : Edges::EDGES){
        Edges::State state = this->target->compareEdge(*source, *edge);
        score += this->getScoreByState(state);
    }

    return score;
}