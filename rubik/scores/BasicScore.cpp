#include "BasicScore.h"

#include <iostream>

BasicScore::BasicScore(const Rubik* target) : Score(target) {}

uint32_t BasicScore::calculate(){
    std::cout << "Olá mundo";
    return 0;
}