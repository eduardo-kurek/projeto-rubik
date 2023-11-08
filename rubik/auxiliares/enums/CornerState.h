#pragma once

enum CornerState{
    CORRECT = 0,
    ORIENTED = 1,
    PERMUTED_CLOCKWISE = 2,
    PERMUTED_ANTICLOCKWISE = 3,
    INCORRECT = 4
};