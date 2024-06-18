#pragma once

#include <vector>
#include "../GeneticTunner.h"
#include "BasicScore.h"
#include "BasicConfig.h"
#include "BasicAnalyzer.h"

class BasicGeneticTunner : public GeneticTunner<BasicScore, BasicConfig>{

    struct Chromosome{
        BasicConfig config;
        double fitness;
        
        Chromosome(){ this->config = BasicConfig(); }
        Chromosome(BasicConfig config) : config(config) {}
    };

    BasicAnalyzer& analyzer;
    int pop_size;
    unsigned long qt_iterations;
    int mutation_rate[2] = {20, 1000}; // ([0] / [1]) * 100 = n%
    int mutation_count = 0;
    std::vector<Chromosome> results;
    std::vector<Chromosome> initial_configs;

    Chromosome* select(std::vector<Chromosome>& population);
    std::vector<Chromosome> crossover(Chromosome& parent1, Chromosome& parent2);
    void mutate(Chromosome& r);
    void sort(std::vector<Chromosome>& population);
    void fitness(Chromosome& c);
    void remove_duplicates(std::vector<Chromosome>& population);
    std::vector<Chromosome> initialize(int n);
    std::vector<Chromosome> combine(std::vector<Chromosome>& population1, std::vector<Chromosome>& population2);

public:
    BasicGeneticTunner(BasicAnalyzer& analyzer, int pop_size = 100, unsigned long qt_iterations = 10000) 
        : GeneticTunner(), analyzer(analyzer), pop_size(pop_size), qt_iterations(qt_iterations) {}

    void run() override;
    std::vector<BasicConfig> get_results();
    void print_status();
    void clear();
    void set_initial_configs(std::vector<BasicConfig> configs);
    void clear_initial_configs();

};