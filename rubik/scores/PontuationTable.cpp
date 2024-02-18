#include "PontuationTable.h"

PontuationTable::PontuationTable(std::vector<float> cornerPontuation, std::vector<float> edgePontuations, float buff){
    this->cornerPontuation = cornerPontuation;
    this->edgePontuations = edgePontuations;
    this->buff = buff;
}

std::vector<float> PontuationTable::getCornerPontuations() const{
    return this->cornerPontuation;
}

std::vector<float> PontuationTable::getEdgePontuations() const{
    return this->edgePontuations;
}

float PontuationTable::getBuff() const{
    return this->buff;
}
