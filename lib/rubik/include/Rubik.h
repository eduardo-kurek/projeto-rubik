#pragma once

#include "helpers/Face.h"
#include "helpers/constantes.h"
#include "helpers/Move.h"
#include "helpers/Restriction.h"
#include "Historic.h"
#include <functional>
#include <cstdarg>
#include <string>
#include <queue>
#include <vector>

class Rubik{

    using RestrictionFunction = std::function<std::vector<const Move*>(const Move*, const Move*)>;

    Face faces[6];
    const Move* lastMove = nullptr;
    Historic historic;
    std::vector<const Move*> restrictedMoves;
    RestrictionFunction restrictionFunction = Restriction::SUPPLEMENTATION_ORACLE;


    void restrict(const Move* move, const Move* lastMove);


public:
    bool forceRestrictedMoves = false;

    Rubik();
    explicit Rubik(const std::string& position);
    
    void move(int numArgs, ...);
    void move(std::vector<const Move*> moves);
    void scramble(int quantity = 20);
    void reset();
    void print(bool clear = false) const;
    std::string extract() const;
    void setPosition(const std::string& position);
    void clearRestrictedMoves();
    void printRestrictedMoves() const;

    std::vector<const Move*> getHistoric() const;
    std::string getHistoricString() const;
    void printHistoric() const;
    void clearHistoric();

    const Face* getFaces() const;
    void setRestrictionFunction(const RestrictionFunction& restrictionFunction);
    std::vector<const Move*> getValidMoves();

    friend std::ostream &operator<<(std::ostream &os, const Rubik* rubik);
    bool operator==(const Rubik& other) const;

};