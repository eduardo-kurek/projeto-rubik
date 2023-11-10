#pragma once

#include <cstdint>
#include "../Rubik.h"
#include "../auxiliares/Corners.h"
#include "../auxiliares/Edges.h"

class Score{

protected:

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

};