#pragma once

#include <omp.h>
#include "../Analyzer.h"
#include "BasicScore.h"
#include "BasicConfig.h"

class BasicAnalyzer : public Analyzer<BasicScore, BasicConfig>{

    using Scrambles = std::vector<std::vector<std::vector<const Move*>>>;

private:
    float calculate_scramble(int i);
    void calculate_pontuations();

public:
    BasicAnalyzer(Scrambles scrambles, bool debug = false) : Analyzer(scrambles, debug){};
    float analyze(BasicConfig config) override;

};