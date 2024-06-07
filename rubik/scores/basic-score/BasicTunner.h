#pragma once

#include "BasicAnalyzer.h"
#include "BasicScore.h"
#include "BasicConfig.h"
#include "../Tunner.h"

class BasicTunner : public Tunner<BasicAnalyzer, BasicScore, BasicConfig>{

protected:
    BasicConfig getConfig(std::vector<float>& values) override;

public:
    BasicTunner(BasicAnalyzer& analyzer, int resultSize = 5) : Tunner(analyzer, resultSize) {}

};