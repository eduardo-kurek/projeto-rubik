#include "Move.h"
#include "Layer.h"
#include "enums/Faces.h"
#include "enums/Turn.h"

const Move MOV_F = {
        {TOP, RIGHT, BOTTOM, LEFT},
        {&LAYER_D, &LAYER_L, &LAYER_UA, &LAYER_RA},
        FRONT, CLOCKWISE, 1, "F", {FA, F2}, {B, BA, B2}
};
const Move* F = &MOV_F;

const Move MOV_FA = {
        {TOP, LEFT, BOTTOM, RIGHT},
        {&LAYER_DA, &LAYER_R, &LAYER_U, &LAYER_LA},
        FRONT, ANTICLOCKWISE, 1, "F'", {F, F2}, {B, BA, B2}
};
const Move* FA = &MOV_FA;

const Move MOV_F2 = {
        {TOP, RIGHT, BOTTOM, LEFT},
        {&LAYER_D, &LAYER_L, &LAYER_UA, &LAYER_RA},
        FRONT, CLOCKWISE, 2, "F2", {F, FA}, {B, BA, B2}
};
const Move* F2 = &MOV_F2;

const Move MOV_U = {
        {FRONT, LEFT, BACK, RIGHT},
        {&LAYER_U, &LAYER_U, &LAYER_U, &LAYER_U},
        TOP, CLOCKWISE, 1, "U", {UA, U2}, {D, DA, D2}
};
const Move* U = &MOV_U;

const Move MOV_UA = {
        {FRONT, RIGHT, BACK, LEFT},
        {&LAYER_UA, &LAYER_UA, &LAYER_UA, &LAYER_UA},
        TOP, ANTICLOCKWISE, 1, "U", {U, U2}, {D, DA, D2}
};
const Move* UA = &MOV_UA;

const Move MOV_U2 = {
        {FRONT, LEFT, BACK, RIGHT},
        {&LAYER_U, &LAYER_U, &LAYER_U, &LAYER_U},
        TOP, CLOCKWISE, 2, "U2", {U, UA}, {D, DA, D2}
};
const Move* U2 = &MOV_U2;

const Move MOV_R = {
        {FRONT, TOP, BACK, BOTTOM},
        {&LAYER_RA, &LAYER_RA, &LAYER_L, &LAYER_RA},
        RIGHT, CLOCKWISE, 1, "R", {RA, R2}, {L, LA, L2}
};
const Move* R = &MOV_R;

const Move MOV_RA = {
        {FRONT, BOTTOM, BACK, TOP},
        {&LAYER_R, &LAYER_R, &LAYER_LA, &LAYER_R},
        RIGHT, ANTICLOCKWISE, 1, "R'", {R, R2}, {L, LA, L2}
};
const Move* RA = &MOV_RA;

const Move MOV_R2 = {
        {FRONT, TOP, BACK, BOTTOM},
        {&LAYER_RA, &LAYER_RA, &LAYER_L, &LAYER_RA},
        RIGHT, CLOCKWISE, 2, "R2", {R, RA}, {L, LA, L2}
};
const Move* R2 = &MOV_R2;

const Move MOV_D = {
        {FRONT, RIGHT, BACK, LEFT},
        {&LAYER_D, &LAYER_D, &LAYER_D, &LAYER_D},
        BOTTOM, CLOCKWISE, 1, "D", {DA, D2}, {U, UA, U2}
};
const Move* D = &MOV_D;

const Move MOV_DA = {
        {FRONT, LEFT, BACK, RIGHT},
        {&LAYER_DA, &LAYER_DA, &LAYER_DA, &LAYER_DA},
        BOTTOM, ANTICLOCKWISE, 1, "D'", {D, D2}, {U, UA, U2}
};
const Move* DA = &MOV_DA;

const Move MOV_D2 = {
        {FRONT, RIGHT, BACK, LEFT},
        {&LAYER_D, &LAYER_D, &LAYER_D, &LAYER_D},
        BOTTOM, CLOCKWISE, 2, "D2", {D, DA}, {U, UA, U2}
};
const Move* D2 = &MOV_D2;

const Move MOV_L = {
        {FRONT, BOTTOM, BACK, TOP},
        {&LAYER_L, &LAYER_L, &LAYER_RA, &LAYER_L},
        LEFT, CLOCKWISE, 1, "L", {LA, L2}, {R, RA, R2}
};
const Move* L = &MOV_L;

const Move MOV_LA = {
        {FRONT, TOP, BACK, BOTTOM},
        {&LAYER_LA, &LAYER_LA, &LAYER_R, &LAYER_LA},
        LEFT, ANTICLOCKWISE, 1, "L'", {L, L2}, {R, RA, R2}
};
const Move* LA = &MOV_LA;

const Move MOV_L2 = {
        {FRONT, BOTTOM, BACK, TOP},
        {&LAYER_L, &LAYER_L, &LAYER_RA, &LAYER_L},
        LEFT, CLOCKWISE, 2, "L2", {L, LA}, {R, RA, R2}
};
const Move* L2 = &MOV_L2;

const Move MOV_B = {
        {TOP, LEFT, BOTTOM, RIGHT},
        {&LAYER_UA, &LAYER_L, &LAYER_D, &LAYER_RA},
        BACK, CLOCKWISE, 1, "B", {BA, B2}, {F, FA, F2}
};
const Move* B = &MOV_B;

const Move MOV_BA = {
        {TOP, RIGHT, BOTTOM, LEFT},
        {&LAYER_U, &LAYER_R, &LAYER_DA, &LAYER_LA},
        BACK, ANTICLOCKWISE, 1, "B'", {B, B2}, {F, FA, F2}
};
const Move* BA = &MOV_BA;

const Move MOV_B2 = {
        {TOP, LEFT, BOTTOM, RIGHT},
        {&LAYER_UA, &LAYER_L, &LAYER_D, &LAYER_RA},
        BACK, CLOCKWISE, 2, "B2", {B, BA}, {F, FA, F2}
};
const Move* B2 = &MOV_B2;