#include "scores/basic-score/BasicScore.h"
#include "helpers/Corners.h"
#include "helpers/Edges.h"
#include "helpers/Pieces.h"
#include <math.h>
#include <iomanip>
#include <iostream>

BasicScore::BasicScore(BasicConfig config, Rubik target) : Score(config, target){
    updateMaxScore();
}

float BasicScore::getScoreByState(Edges::State state){
    return this->config.edges[state];
}

float BasicScore::getScoreByState(Corners::State state){
    return this->config.corners[state];
}

float BasicScore::calculate(const Rubik &source){
    float score = 0;

    // CALCULANDO VALORES DAS CORNERS
    for(auto& corner : Corners::CORNERS){
        Corners::State state = corner->compare(this->target, source);
        score += this->getScoreByState(state);
    }

    // CALCULANDO VALORES DAS EDGES
    for(auto& edge : Edges::EDGES){
        Edges::State state = edge->compare(this->target, source);
        score += this->getScoreByState(state);
    }
    
    return score;
}