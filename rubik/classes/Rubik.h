#pragma once

#include "auxiliares/Face.h"

class Rubik{
    Face* faces[6];

public:
    Rubik();
    void print();
    ~Rubik();
};