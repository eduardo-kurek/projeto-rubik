#include "BasicScore.h"
#include "../../auxiliares/Corners.h"
#include "../../auxiliares/Edges.h"
#include <math.h>
#include <iomanip>
#include <iostream>

BasicScore::BasicScore(PontuationTable* pt, const Rubik* target) : Score(target) {
    this->pontuationTable = pt;
    this->maxScore = this->calculate(*target);
}

float BasicScore::getScoreByState(Edges::State state){
    return this->pontuationTable->getEdgePontuations()[state];
}

float BasicScore::getScoreByState(Corners::State state){
    return this->pontuationTable->getCornerPontuations()[state];
}

float BasicScore::calculate_face_synergy(const Face& target, const Face& source){
    float result = 0.0;
    return result;
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

    const Face* targetFaces = this->target->getFaces();
    const Face* sourceFaces = source.getFaces();
    for(int i = 0; i < 6; i++)
        score += this->calculate_face_synergy(targetFaces[i], sourceFaces[i]);

    return score;
}