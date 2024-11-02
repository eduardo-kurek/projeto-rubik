#include "scores/basic-score/BasicConfig.h"
#include "Random.h"
#include <iostream>
#include <sstream>

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
}

std::string BasicConfig::toString(){
    std::ostringstream oss;
    oss << "[";
    for(auto c : this->corners)
        oss << c << ", ";
    oss << "\b\b] [";
    for(auto e : this->edges)
        oss << e << ", ";
    oss << "\b\b] ";
    return oss.str();
}
