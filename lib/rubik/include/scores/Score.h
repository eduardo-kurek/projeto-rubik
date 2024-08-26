#pragma once

#include <cstdint>
#include <iostream>
#include "Rubik.h"
#include "helpers/Corners.h"
#include "helpers/Edges.h"

class IScore{

protected:
    /* Score máximo possível */
    float maxScore;

    /* Alvo da pontuação, em relação a qual objeto a pontuação será aplicada */
    Rubik target;

public:
    IScore(Rubik target) : target(target) {
        this->maxScore = 44;
    }

    /* Calcula a pontuação do source em relação ao target da classe */
    virtual float calculate(const Rubik& source) = 0;

    /**
     * Calcula a pontuação normalizada, ou seja, uma porcentagem entre 0 a 100
     * do quanto o cubo está resolvido em relação ao score máximo
     */
    virtual float calculateNormalized(const Rubik& source){
        float score = this->calculate(source) * 100;
        return score / this->maxScore;
    }

    /* Obtém o score máximo possível */
    float getMaxScore() const{
        return maxScore;
    }

};

template <typename TConfig>
class Score : public IScore{

protected:
    /* Configuração utilizada para realizar o cálculo */
    TConfig config;

public:

    /* Construtor da classe, seta as propriedades necessárias */
    Score(TConfig config, Rubik target) : IScore(target){
        this->config = config;
    }

    /* Calcula a pontuação do source em relação ao target da classe */
    virtual float calculate(const Rubik& source) = 0;

    /* Define uma nova configuração */
    void configurate(TConfig config){
        this->config = config;
    }

};