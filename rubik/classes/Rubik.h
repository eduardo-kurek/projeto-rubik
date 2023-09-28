#pragma once

#include "auxiliares/Face.h"

class Rubik{
    Face* faces[6];

public:
    Rubik();
    void print(bool clear = false);
    ~Rubik();
    friend std::ostream& operator<<(std::ostream& os, const Rubik* rubik);
};