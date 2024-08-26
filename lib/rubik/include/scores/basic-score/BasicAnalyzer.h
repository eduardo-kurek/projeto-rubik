#pragma once

#include <omp.h>
#include "scores/Analyzer.h"
#include "scores/basic-score/BasicScore.h"
#include "scores/basic-score/BasicConfig.h"

class BasicAnalyzer : public Analyzer<BasicScore, BasicConfig>{

    using Scrambles = std::vector<std::vector<std::vector<const Move*>>>;

private:
    std::vector<float> divergences;
    float calculate_scramble(int i);
    void calculate_divergences();

public:
    BasicAnalyzer(Scrambles* scrambles, bool debug = false) : Analyzer(scrambles, debug){};
    BasicAnalyzer operator=(const BasicAnalyzer& a);
    float analyze(BasicConfig config) override;

};