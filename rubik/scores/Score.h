#pragma once

#include <cstdint>
#include "../Rubik.h"
#include "../auxiliares/Corners.h"
#include "../auxiliares/Edges.h"

template <typename TConfig>
class Score{

protected:
    /* Configuração utilizada para realizar o cálculo */
    TConfig config;

    /* Score máximo possível */
    float maxScore = 0;

    /* Alvo da pontuação, em relação a qual objeto a pontuação será aplicada */
    Rubik target;

public:

    /* Construtor da classe, seta as propriedades necessárias */
    Score(TConfig config, Rubik target){
        this->config = config;
        this->target = target;
    }

    /* Calcula a pontuação do source em relação ao target da classe */
    virtual float calculate(const Rubik& source) = 0;

    /**
     * Calcula a pontuação normalizada, ou seja, uma porcentagem entre 0 a 100
     * do quanto o cubo está resolvido em relação ao score máximo
     */
    float calculateNormalized(const Rubik& source){
        float score = this->calculate(source) * 100;
        return score / this->getMaxScore();
    }

    /* define uma nova configuração */
    void configurate(TConfig config){
        this->config = config;
    }

    /* Obtém o score máximo possível */
    float getMaxScore() const{
        return this->maxScore;
    }

};