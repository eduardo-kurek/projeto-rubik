#include "Restriction.h"
#include "Move.h"
#include <iostream>
#include <vector>

std::vector<const Move*> Restriction::SUPPLEMENTATION(const Move* move){
    std::vector<const Move*> restrictedMoves = {move};
    for(auto& suppMove : move->supplementaryMoves)
        restrictedMoves.push_back(suppMove);
    return restrictedMoves;
}

std::vector<const Move*> Restriction::COMPLEMENTATION(const Move* move){
    std::vector<const Move*> restrictedMoves;
    for(auto& compMove : move->complementaryMoves)
        restrictedMoves.push_back(compMove);
    return restrictedMoves;
}

std::vector<const Move*> Restriction::BOTH(const Move* move){
    std::vector<const Move*> restrictedMoves = {move};

    for(auto& suppMove : move->supplementaryMoves)
        restrictedMoves.push_back(suppMove);
    for(auto& compMove : move->complementaryMoves)
        restrictedMoves.push_back(compMove);

    return restrictedMoves;
}

std::vector<const Move*> Restriction::NOTHING(const Move*){
    return {};
}