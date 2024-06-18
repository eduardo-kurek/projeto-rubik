#include "BasicConfig.h"
#include "../../../services/Random.h"
#include <iostream>

BasicConfig::BasicConfig(bool){
    this->corners = {
        (float)svc::Random::Int(array_bounds[0], array_bounds[1]),
        (float)svc::Random::Int(array_bounds[0], array_bounds[1]),
        (float)svc::Random::Int(array_bounds[0], array_bounds[1]),
        (float)svc::Random::Int(array_bounds[0], array_bounds[1]),
    };

    this->edges = {
        (float)svc::Random::Int(array_bounds[0], array_bounds[1]),
        (float)svc::Random::Int(array_bounds[0], array_bounds[1]),
        (float)svc::Random::Int(array_bounds[0], array_bounds[1]),
        (float)svc::Random::Int(array_bounds[0], array_bounds[1]),
    };

    this->synergy = svc::Random::Float(synergy_bounds[0], synergy_bounds[1]);
}

void BasicConfig::print(){
    std::cout << "[";
    for(auto c : this->corners)
        std::cout << c << ", ";
    std::cout << "\b\b] [";
    for(auto e : this->edges)
        std::cout << e << ", ";
    std::cout << "\b\b] ";
    std::cout << this->synergy << std::endl;
}

void BasicConfig::randomize_synergy(){
    this->synergy = svc::Random::Float(synergy_bounds[0], synergy_bounds[1]);
}