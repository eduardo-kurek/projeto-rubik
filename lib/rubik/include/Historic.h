#pragma once

#include "helpers/Move.h"
#include <queue>
#include <vector>
#include <iostream>

#define HISTORIC_SIZE 50

class Historic{

    std::queue<const Move*> moves;

public:
    void add(const Move* move);
    void clear();
    void print() const;
    std::vector<const Move*> toVector() const;
    std::string toString() const;
    
};