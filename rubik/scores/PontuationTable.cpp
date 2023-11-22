#include "PontuationTable.h"

PontuationTable::PontuationTable(std::vector<float> cornerPontuation, std::vector<float> edgePontuations){
    this->cornerPontuation = cornerPontuation;
    this->edgePontuations = edgePontuations;
}

std::vector<float> PontuationTable::getCornerPontuations() const{
    return this->cornerPontuation;
}

std::vector<float> PontuationTable::getEdgePontuations() const{
    return this->edgePontuations;
}