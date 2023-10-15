#include "Restriction.h"
#include "Move.h"
#include <iostream>
#include <algorithm>
#include <vector>

bool isComplementary(const Move* move1, const Move* move2){
    auto iterator = std::find(
        move2->complementaryMoves.begin(),
        move2->complementaryMoves.end(),
        move1
    );

    if(iterator == move2->complementaryMoves.end()) return false;
    return true;
}

std::vector<const Move*> Restriction::SUPPLEMENTATION(const Move* move, const Move* lastMove){
    std::vector<const Move*> restrictedMoves = {move};
    for(auto& suppMove : move->supplementaryMoves)
        restrictedMoves.push_back(suppMove);
    return restrictedMoves;
}
std::vector<const Move*> Restriction::SUPPLEMENTATION_ORACLE(const Move* move, const Move* lastMove){
    std::vector<const Move*> restrictedMoves = {move};
    for(auto& suppMove : move->supplementaryMoves)
        restrictedMoves.push_back(suppMove);

    if(lastMove != nullptr && isComplementary(move, lastMove))
        for(auto& compMove : move->complementaryMoves)
            restrictedMoves.push_back(compMove);

    return restrictedMoves;
}

std::vector<const Move*> Restriction::COMPLEMENTATION(const Move* move, const Move* lastMove){
    std::vector<const Move*> restrictedMoves;
    for(auto& compMove : move->complementaryMoves)
        restrictedMoves.push_back(compMove);
    return restrictedMoves;
}

std::vector<const Move*> Restriction::BOTH(const Move* move, const Move* lastMove){
    std::vector<const Move*> restrictedMoves = {move};

    for(auto& suppMove : move->supplementaryMoves)
        restrictedMoves.push_back(suppMove);
    for(auto& compMove : move->complementaryMoves)
        restrictedMoves.push_back(compMove);

    return restrictedMoves;
}

std::vector<const Move*> Restriction::NOTHING(const Move*, const Move*){
    return {};
}