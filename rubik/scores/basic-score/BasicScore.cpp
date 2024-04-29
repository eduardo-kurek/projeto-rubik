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

float BasicScore::calculate_face_synergy(const Rubik& source){
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
        for(uint8_t j = 0; j < 6; j++){
            int val = equals[j] * equals[j] - this->minSynergyScore;
            val < 0 ? val = 0 : val = val;
            res[i] += val;
        }
        
    }

    int sum = 0;
    for(uint8_t i = 0; i < 6; i++) sum += res[i];

    return 0;
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

    score += this->calculate_face_synergy(source);
    return score;
}