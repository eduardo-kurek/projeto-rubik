#pragma once

#include "helpers/Face.h"
#include "helpers/constantes.h"
#include "helpers/Move.h"
#include "helpers/Restriction.h"
#include "Historic.h"
#include "RubikPosition.h"
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
    bool canExecute(const Move* mov) const;
    bool isMoveRestricted(const Move* mov) const;
    bool canForceMoves() const;
    void doMove(const Move* mov);
    void doSingleMove(const Move* mov);
    void doDoubleMove(const Move* mov);
    void swapRightShiftFaceLayers(const Faces* faces, const Layer*const layers[4]);
    void swapDoubleShiftFaceLayers(const Faces* faces, const Layer*const layers[4]);
    void setFaceLayer(const Faces face, const Layer* layer, std::array<const Color*, 3> colors);
    std::array<std::array<const Color*, 3>, 4> getLayerColorsArray(const Faces* face, const Layer*const layer[4]) const;
    void rotateWeakSide(const Move* mov);
    void setupAfterMove(const Move* mov);

public:
    bool forceRestrictedMoves = false; 

    Rubik();
    explicit Rubik(const RubikPosition& position);
    
    void move(int numArgs, ...);
    void move(const Move* mov);
    void move(std::vector<const Move*> moves);
    void scramble(int quantity = 20);
    void reset();
    void print(bool clear = false) const;
    RubikPosition extractPosition() const;
    void setPosition(const RubikPosition& position);
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