#pragma once

#include "Rubik.h"
#include <cstdint>
#include <vector>

class Solver{

protected:
    using MovementsArray = std::vector<std::vector<const Move*>>;

    // Representa o ponto de partida da solução
    Rubik source = Rubik();

    // Representa o alvo da resolução, até onde ela deve chegar
    Rubik target = Rubik();

    // Soluções encontradas no cubo
    MovementsArray foundedSolves = {};

    void clear();

public:
    Solver();
    explicit Solver(Rubik source);
    Solver(Rubik source, Rubik target);

    void setSource(Rubik source);
    void setTarget(Rubik target);

    virtual void solve() = 0;
    MovementsArray getFoundedSolves() const;
    void printFoundedSolves() const;

};