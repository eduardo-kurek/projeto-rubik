#pragma once

#include "scores/Score.h"
#include "scores/Config.h"

template <class Score, class Config>
class GeneticTunner{
    
public:
    virtual void run() = 0;

};