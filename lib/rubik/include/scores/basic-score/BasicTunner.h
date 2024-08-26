#pragma once

#include "scores/basic-score/BasicAnalyzer.h"
#include "scores/basic-score/BasicScore.h"
#include "scores/basic-score/BasicConfig.h"
#include "scores/Tunner.h"

class BasicTunner : public Tunner<BasicAnalyzer, BasicScore, BasicConfig>{

protected:
    BasicConfig getConfig(std::vector<float>& values) override;

public:
    BasicTunner(BasicAnalyzer& analyzer, int resultSize = 5) : Tunner(analyzer, resultSize) {}

};