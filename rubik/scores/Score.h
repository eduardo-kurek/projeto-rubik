#pragma once

#include <cstdint>
#include "../Rubik.h"
#include "../auxiliares/Corners.h"
#include "../auxiliares/Edges.h"

class Score{

protected:

    /* Score máximo possível */
    float maxScore = 0;

    /* Alvo da pontuação, em relação a qual objeto a pontuação será aplicada */
    const Rubik* target;

    /* Obtém o score da edge de acordo com o estado dela */
    virtual float getScoreByState(Edges::State state) = 0;

    /* Obtém o score da corner de acordo com o estado dela */
    virtual float getScoreByState(Corners::State state) = 0;

public:

    /* Construtor da classe, seta a propriedade target */
    Score(const Rubik* target);

    /* Calcula a pontuação do source em relação ao target da classe */
    virtual float calculate(const Rubik& source) = 0;

    /**
     * Calcula a pontuação normalizada, ou seja, uma porcentagem entre 0 a 100
     * do quanto o cubo está resolvido em relação ao score máximo
     */
    float calculateNormalized(const Rubik& source);

    /* Obtém o score máximo possível */
    float getMaxScore() const;

};