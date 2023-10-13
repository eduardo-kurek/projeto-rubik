#pragma once

#include "auxiliares/Face.h"
#include "auxiliares/constantes.h"
#include "auxiliares/Move.h"
#include "auxiliares/Restriction.h"
#include <functional>
#include <cstdarg>
#include <string>
#include <list>

class Rubik{

    using RestrictionFunction = std::function<std::vector<const Move*>(const Move*)>;

private:
    Face faces[6];
    std::list<const Move*> historic;
    std::vector<const Move*> restrictedMoves;
    RestrictionFunction restrictionFunction = Restriction::SUPPLEMENTATION;

public:
    Rubik();

    explicit Rubik(const std::string& position);

    void setRestrictionFunction(const RestrictionFunction& restrictionFunction);

    void restrict(const Move* lastMove);

    void print(bool clear = false) const;

    void printHistoric();

    void printRestrictedMoves() const;

    void reset();

    std::string extract() const;

    void setPosition(const std::string& position);

    void move(int numArgs, ...);

    friend std::ostream &operator<<(std::ostream &os, const Rubik* rubik);

};