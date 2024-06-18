#include "BasicGeneticTunner.h"
#include "../../../services/Random.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <omp.h>

BasicGeneticTunner::Chromosome* BasicGeneticTunner::select(std::vector<Chromosome> &population){
    // Seleção por torneio de 2
    std::uniform_int_distribution<int> dist(0, population.size()-1);
    int i1 = svc::Random::Int(0, population.size()-1);
    int i2 = svc::Random::Int(0, population.size()-1);
    return i1 < i2 ? &population[i1] : &population[i2];
}

std::vector<BasicGeneticTunner::Chromosome> BasicGeneticTunner::crossover(Chromosome &parent1, Chromosome &parent2){
    // Fazendo o cortes dos pais e cruzamento
    Chromosome c1 = Chromosome(parent1.config);
    Chromosome c2 = Chromosome(parent2.config);
    std::swap(c1.config.edges, c2.config.corners);
    std::swap(c1.config.synergy, c2.config.synergy);
    this->fitness(c1);
    this->fitness(c2);

    // Gerando um filho intercalado
    Chromosome c3 = Chromosome(parent1.config);
    for(int i = 0; i < 4; i++){
        if(i % 2 == 1){
            c3.config.corners[i] = parent2.config.corners[i];
            c3.config.edges[i] = parent2.config.edges[i];
        }
    }
    this->fitness(c3);
    std::vector<Chromosome> children = {c1, c2, c3};
    return children;
}

void BasicGeneticTunner::mutate(Chromosome &r){
    // Trocando dois valores de lugar
    Chromosome c = Chromosome(BasicConfig(true));
    int i = svc::Random::Int(0, 3);
    int j = svc::Random::Int(0, 3);
    r.config.corners[i] = c.config.corners[i];
    r.config.edges[j] = c.config.edges[j];
    r.config.randomize_synergy();
    fitness(r);
}

void BasicGeneticTunner::sort(std::vector<Chromosome> &population){
    std::sort(population.begin(), population.end(), [](Chromosome& a, Chromosome& b){
        return a.fitness < b.fitness;
    });
}

void BasicGeneticTunner::fitness(Chromosome &c){
    auto analyzer = this->analyzer;
    c.fitness = analyzer.analyze(c.config);
}

void BasicGeneticTunner::remove_duplicates(std::vector<Chromosome>& population){
    std::unordered_map<std::string, Chromosome> unique;
    for(auto& c : population)
        unique.insert(std::make_pair(c.config.toString(), c));

    population.clear();
    for(auto& pair : unique)
        population.push_back(pair.second);

    this->sort(population);
}

std::vector<BasicGeneticTunner::Chromosome> BasicGeneticTunner::initialize(int n){
    std::vector<Chromosome> population = std::vector<Chromosome>(initial_configs.begin(), initial_configs.end());
    for(int i = 0; i < n; i++){
        Chromosome c = Chromosome(BasicConfig(true));
        fitness(c);
        population.push_back(c);
    }
    this->sort(population);
    return population;
}

std::vector<BasicGeneticTunner::Chromosome> BasicGeneticTunner::combine
    (std::vector<Chromosome> &population1, std::vector<Chromosome> &population2){
    std::vector<Chromosome> merged(population1.size() + population2.size());

    std::merge(population1.begin(), population1.end(), population2.begin(),
        population2.end(), merged.begin(), [](Chromosome& a, Chromosome& b){
            return a.fitness < b.fitness;
        });

    merged.resize(pop_size);
    return merged;
}

void BasicGeneticTunner::print_status(){
    std::cout << "Best individuals: " << std::endl;
    for(Chromosome& c : results){
        std::cout << "\tFitness: "<< std::fixed << std::setprecision(0) << std::setw(2) << c.fitness;
        std::cout << " | ";
        c.config.print();
    }
    std::cout << "\tMutation count: " << mutation_count << std::endl;
}

void BasicGeneticTunner::clear(){
    results.clear();
    mutation_count = 0;
}

void BasicGeneticTunner::set_initial_configs(std::vector<BasicConfig> configs){
    initial_configs.clear();
    for(BasicConfig& c : configs){
        Chromosome ch = Chromosome(c);
        this->fitness(ch);
        initial_configs.push_back(ch);
    }
}

void BasicGeneticTunner::clear_initial_configs(){
    this->initial_configs.clear();
}

void BasicGeneticTunner::run(){
    this->clear();
    #pragma omp parallel
    {
        std::vector<Chromosome> population = initialize(pop_size);

        for(int i = 0; i < qt_iterations; i++){
            Chromosome* parent1 = select(population);
            Chromosome* parent2;
            while((parent2 = select(population)) == parent1);
            std::vector<Chromosome> children = crossover(*parent1, *parent2);

            for(Chromosome& c : children){
                if(svc::Random::Int(1, mutation_rate[1]) <= mutation_rate[0]){
                    mutate(c);
                    #pragma omp critical
                    mutation_count++;
                }
            }

            this->sort(children);
            population = combine(population, children);
        }

        this->remove_duplicates(population);
        #pragma omp critical
        std::copy(population.begin(), population.begin() + 3, std::back_inserter(results));
    }

    this->sort(results);

}

std::vector<BasicConfig> BasicGeneticTunner::get_results(){
    std::vector<BasicConfig> ret(results.size());
    for(Chromosome& c : results) ret.push_back(c.config);
    return ret;
}
