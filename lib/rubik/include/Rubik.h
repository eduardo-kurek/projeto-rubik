#pragma once

#include "helpers/Face.h"
#include "helpers/constantes.h"
#include "helpers/Move.h"
#include "helpers/Restriction.h"
#include <functional>
#include <cstdarg>
#include <string>
#include <queue>
#include <vector>

class Rubik{

    using RestrictionFunction = std::function<std::vector<const Move*>(const Move*, const Move*)>;

    Face faces[6];
    const Move* lastMove = nullptr;
    std::queue<const Move*> historic;
    std::vector<const Move*> restrictedMoves;
    RestrictionFunction restrictionFunction = Restriction::SUPPLEMENTATION_ORACLE;

    void restrict(const Move* move, const Move* lastMove);


public:
    bool forceRestrictedMoves = false;

    Rubik();
    explicit Rubik(const std::string& position);
    
    const Face* getFaces() const;
    void setRestrictionFunction(const RestrictionFunction& restrictionFunction);
    void clearRestrictedMoves();
    void clearHistoric();
    void print(bool clear = false) const;
    void printHistoric() const;
    std::vector<const Move*> getHistoric() const;
    std::string getHistoricString() const;
    void printRestrictedMoves() const;
    void reset();
    std::string extract() const;
    void setPosition(const std::string& position);
    void move(int numArgs, ...);
    void move(std::vector<const Move*> moves);
    std::vector<const Move*> getValidMoves();
    void scramble(int quantity = 20);

    friend std::ostream &operator<<(std::ostream &os, const Rubik* rubik);
    bool operator==(const Rubik& other) const;

};