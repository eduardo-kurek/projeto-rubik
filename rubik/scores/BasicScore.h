#pragma once

#include "Score.h"

/**
 * - Caso a corner esteja no lugar correto e orientação correta: +2;
 * - Caso a corner esteja no lugar correto e orientação errada: +1;
 * - Caso a corner esteja no lugar errado e orientação errada: 0;
 */
class BasicScore : public Score{

public:
    BasicScore(const Rubik* target = new Rubik());
    uint32_t calculate(const Rubik* source) override;

};