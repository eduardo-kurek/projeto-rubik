#include "scores/basic-score/BasicScore.h"
#include "helpers/Corners.h"
#include "helpers/Edges.h"
#include <math.h>
#include <iomanip>
#include <iostream>

BasicScore::BasicScore(BasicConfig config, Rubik target) : Score(config, target){
    this->maxScore = this->calculate(target);
}

float BasicScore::getScoreByState(Edges::State state){
    return this->config.edges[state];
}

float BasicScore::getScoreByState(Corners::State state){
    return this->config.corners[state];
}


float BasicScore::calculate_face_synergy(const Rubik& source, float score){
    int res[6] = {0};
    const Face* faces = source.getFaces();

    for(uint8_t i = 0; i < 6; i++){
        uint8_t equals[6] = {0};

        for(uint8_t j = 0; j < 3; j++){
            for(uint8_t k = 0; k < 3; k++){
                const Color* cor = faces[i].stickers[j][k].getColor();
                equals[cor->index]++;
            }
        }
        
        // Adicionando os resultados da face
        for(uint8_t j = 0; j < 6; j++) res[i] = std::pow(equals[j], this->pow);
        res[i] -= this->minSynergyScore;
        if(res[i] < 0) res[i] = 0;
        res[i] *= res[i];
    }

    // Calculando a soma dos resultados
    float sum = 0;
    for(uint8_t i = 0; i < 6; i++) sum += res[i];

    // Normalizando o resultado em relação ao score
    float norm = sum / this->maxSynergyScore;
    sum = norm * score;

    // Multiplicando o resultado pela sinergia
    sum *= this->config.synergy;
    return sum;
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

    score += this->calculate_face_synergy(source, score);
    return score;
}