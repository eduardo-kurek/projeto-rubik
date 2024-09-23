#include "helpers/Move.h"
#include "helpers/Layer.h"
#include "helpers/enums/Faces.h"
#include "helpers/enums/Turn.h"
#include <iostream>
#include <sstream>
#include <iostream>
#include <stdexcept>

const Move MOV_F = {
        {TOP, RIGHT, BOTTOM, LEFT},
        {&LAYER_D, &LAYER_L, &LAYER_UA, &LAYER_R},
        FRONT, CLOCKWISE, 1, "F", 0, {FA, F2}, {B, BA, B2}
};
const Move* F = &MOV_F;

const Move MOV_FA = {
        {TOP, LEFT, BOTTOM, RIGHT},
        {&LAYER_DA, &LAYER_RA, &LAYER_U, &LAYER_LA},
        FRONT, ANTICLOCKWISE, 1, "F'", 1, {F, F2}, {B, BA, B2}
};
const Move* FA = &MOV_FA;

const Move MOV_F2 = {
        {TOP, RIGHT, BOTTOM, LEFT},
        {&LAYER_D, &LAYER_L, &LAYER_UA, &LAYER_R},
        FRONT, CLOCKWISE, 2, "F2", 2, {F, FA}, {B, BA, B2}
};
const Move* F2 = &MOV_F2;

const Move MOV_U = {
        {FRONT, LEFT, BACK, RIGHT},
        {&LAYER_U, &LAYER_U, &LAYER_U, &LAYER_U},
        TOP, CLOCKWISE, 1, "U", 3, {UA, U2}, {D, DA, D2}
};
const Move* U = &MOV_U;

const Move MOV_UA = {
        {FRONT, RIGHT, BACK, LEFT},
        {&LAYER_UA, &LAYER_UA, &LAYER_UA, &LAYER_UA},
        TOP, ANTICLOCKWISE, 1, "U'", 4, {U, U2}, {D, DA, D2}
};
const Move* UA = &MOV_UA;

const Move MOV_U2 = {
        {FRONT, LEFT, BACK, RIGHT},
        {&LAYER_U, &LAYER_U, &LAYER_U, &LAYER_U},
        TOP, CLOCKWISE, 2, "U2", 5, {U, UA}, {D, DA, D2}
};
const Move* U2 = &MOV_U2;

const Move MOV_R = {
        {FRONT, TOP, BACK, BOTTOM},
        {&LAYER_R, &LAYER_R, &LAYER_L, &LAYER_R},
        RIGHT, CLOCKWISE, 1, "R", 6, {RA, R2}, {L, LA, L2}
};
const Move* R = &MOV_R;

const Move MOV_RA = {
        {FRONT, BOTTOM, BACK, TOP},
        {&LAYER_RA, &LAYER_RA, &LAYER_LA, &LAYER_RA},
        RIGHT, ANTICLOCKWISE, 1, "R'", 7, {R, R2}, {L, LA, L2}
};
const Move* RA = &MOV_RA;

const Move MOV_R2 = {
        {FRONT, TOP, BACK, BOTTOM},
        {&LAYER_R, &LAYER_R, &LAYER_L, &LAYER_R},
        RIGHT, CLOCKWISE, 2, "R2", 8, {R, RA}, {L, LA, L2}
};
const Move* R2 = &MOV_R2;

const Move MOV_D = {
        {FRONT, RIGHT, BACK, LEFT},
        {&LAYER_D, &LAYER_D, &LAYER_D, &LAYER_D},
        BOTTOM, CLOCKWISE, 1, "D", 9, {DA, D2}, {U, UA, U2}
};
const Move* D = &MOV_D;

const Move MOV_DA = {
        {FRONT, LEFT, BACK, RIGHT},
        {&LAYER_DA, &LAYER_DA, &LAYER_DA, &LAYER_DA},
        BOTTOM, ANTICLOCKWISE, 1, "D'", 10, {D, D2}, {U, UA, U2}
};
const Move* DA = &MOV_DA;

const Move MOV_D2 = {
        {FRONT, RIGHT, BACK, LEFT},
        {&LAYER_D, &LAYER_D, &LAYER_D, &LAYER_D},
        BOTTOM, CLOCKWISE, 2, "D2", 11, {D, DA}, {U, UA, U2}
};
const Move* D2 = &MOV_D2;

const Move MOV_L = {
        {FRONT, BOTTOM, BACK, TOP},
        {&LAYER_L, &LAYER_L, &LAYER_R, &LAYER_L},
        LEFT, CLOCKWISE, 1, "L", 12, {LA, L2}, {R, RA, R2}
};
const Move* L = &MOV_L;

const Move MOV_LA = {
        {FRONT, TOP, BACK, BOTTOM},
        {&LAYER_LA, &LAYER_LA, &LAYER_RA, &LAYER_LA},
        LEFT, ANTICLOCKWISE, 1, "L'", 13, {L, L2}, {R, RA, R2}
};
const Move* LA = &MOV_LA;

const Move MOV_L2 = {
        {FRONT, BOTTOM, BACK, TOP},
        {&LAYER_L, &LAYER_L, &LAYER_R, &LAYER_L},
        LEFT, CLOCKWISE, 2, "L2", 14, {L, LA}, {R, RA, R2}
};
const Move* L2 = &MOV_L2;

const Move MOV_B = {
        {TOP, LEFT, BOTTOM, RIGHT},
        {&LAYER_UA, &LAYER_L, &LAYER_D, &LAYER_R},
        BACK, CLOCKWISE, 1, "B", 15, {BA, B2}, {F, FA, F2}
};
const Move* B = &MOV_B;

const Move MOV_BA = {
        {TOP, RIGHT, BOTTOM, LEFT},
        {&LAYER_U, &LAYER_RA, &LAYER_DA, &LAYER_LA},
        BACK, ANTICLOCKWISE, 1, "B'", 16, {B, B2}, {F, FA, F2}
};
const Move* BA = &MOV_BA;

const Move MOV_B2 = {
        {TOP, LEFT, BOTTOM, RIGHT},
        {&LAYER_UA, &LAYER_L, &LAYER_D, &LAYER_R},
        BACK, CLOCKWISE, 2, "B2", 17, {B, BA}, {F, FA, F2}
};
const Move* B2 = &MOV_B2;

const std::vector<const Move*> Moves = {
        F, FA, F2,
        U, UA, U2,
        R, RA, R2,
        D, DA, D2,
        L, LA, L2,
        B, BA, B2
};

const Move* Move::codToMove(const std::string str){
    for(auto move : Moves) if(move->name == str) return move;
    std::string msg = "Não é possível reconhecer o movimento: " + str;
    throw std::runtime_error(msg);
}

const std::vector<const Move*> Move::stringToMoves(const std::string str){
    std::vector<const Move*> moves;

    std::istringstream stream(str);
    std::string token;

    while (stream >> token)
        moves.push_back(Move::codToMove(token));

    return moves;
}