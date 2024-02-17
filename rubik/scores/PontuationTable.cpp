#include "PontuationTable.h"

PontuationTable::PontuationTable(std::vector<float> cornerPontuation, 
    std::vector<float> edgePontuations, float buffSynergy){
    this->cornerPontuation = cornerPontuation;
    this->edgePontuations = edgePontuations;
    this->bufffSynergy = buffSynergy;
}

std::vector<float> PontuationTable::getCornerPontuations() const{
    return this->cornerPontuation;
}

std::vector<float> PontuationTable::getEdgePontuations() const{
    return this->edgePontuations;
}

float PontuationTable::getBuffSynergy() const{
    return this->bufffSynergy;
}
