#pragma once

#include "Score.h"
#include "Config.h"

template <class Score, class Config>
class GeneticTunner{
    
public:
    virtual void run() = 0;

};