#pragma once

#include "Rubik.h"
#include "helpers/Corners.h"
#include "helpers/Edges.h"

template <class TConfig>
class Score{

private:
    float maxScore = 0;
    
protected:
    Rubik target;
    TConfig config;
    void updateMaxScore(){
        this->maxScore = calculate(this->target);
    }

public:
    Score(TConfig config, Rubik target)
        : config(config), target(target){}

    virtual float calculate(const Rubik& source) = 0;

    float calculateNormalized(const Rubik& source){
        float score = this->calculate(source) * 100;
        if(this->maxScore == 0) return score;
        return score / this->maxScore;
    }

    void configurate(TConfig& config){
        this->config = config;
        updateMaxScore();
    }

    float getMaxScore(){
        return maxScore;
    }
};