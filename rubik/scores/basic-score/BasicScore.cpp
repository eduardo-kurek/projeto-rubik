#include "BasicScore.h"
#include "../../auxiliares/Corners.h"
#include "../../auxiliares/Edges.h"
#include <iomanip>
#include <math.h>
#include <iostream>

BasicScore::BasicScore(PontuationTable* pt, const Rubik* target) : Score(target) {
    this->pontuationTable = pt;

    Rubik rubik = *target;
    this->maxScore = this->calculate(rubik);
}

float BasicScore::getScoreByState(Edges::State state){
    return this->pontuationTable->getEdgePontuations()[state];
}

float BasicScore::getScoreByState(Corners::State state){
    return this->pontuationTable->getCornerPontuations()[state];
}

float BasicScore::calculate_synergy(const Face& target, const Face& source){
    float result = 0;

    // PONTUANDO LINHA A LINHA
    for(int i = 0; i < 3; i++){
        float acc = 0;
        int seq = 0;

        for(int j = 0; j < 3; j++){
            if(target.stickers[i][j].getColor() == source.stickers[i][j].getColor()){
                seq++;
            }
            else if(seq){
                acc += pow(3, seq);
                seq = 0;
            }
        }

        if(seq){
            acc += pow(3, seq);
            seq = 0;
        }

        result += acc;
    }

    // PONTUANDO COLUNA A COLUNA
    for(int i = 0; i < 3; i++){
        float acc = 0;
        int seq = 0;

        for(int j = 0; j < 3; j++){
            if(target.stickers[j][i].getColor() == source.stickers[j][i].getColor()) seq++;
            else if(seq){
                acc += pow(3, seq);
                seq = 0;
            }
        }

        if(seq){
            acc += pow(3, seq);
            seq = 0;
        }

        result += acc;
    }

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

    // CALCULANDO VALORES SINERGICOS DAS FACES
    const Face* sourceFaces = source.getFaces();
    const Face* targetFaces = this->target->getFaces();
    for(int i = 0; i < 6; i++)
        score += this->calculate_synergy(targetFaces[i], sourceFaces[i]);

    return score;
}