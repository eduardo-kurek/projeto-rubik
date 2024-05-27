#include "Genetic.h"
#include "../../services/Random.h"
#include "BruteForce.h"
#include <algorithm>
#include <iostream>

bool Genetic::Chromosome::greater(const Chromosome& a, const Chromosome & b){
    return a.fitness > b.fitness;
}

Genetic::Genetic(Score& score) : Solver(){
    this->score = &score;
}

Genetic::Genetic(Score& score, Rubik source) : Solver(source){
    this->score = &score;
}

void Genetic::solve(){
    initialize();
    
    for(uint16_t i = 0; i < 300; i++){
        if(population[0].fitness == 100.0f) break;
        next_generation();

        std::cout << "Best fitness: " << population[0].fitness << std::endl;
        if(best_fitness == population[0].fitness) stagnation++;
        else stagnation = 0;
        best_fitness = population[0].fitness;
        print_status();
    }

    // while(true){
    //     if(population[0].fitness == 100.0f) break;
    //     next_generation();
    // }

    print_status();
    for(uint16_t i = 0; i < 5; i++){
        foundedSolves.push_back(population[i].rubik.getHistoric());
    }
}

void Genetic::print_status(){
    std::cout << "===================================" << std::endl;
    std::cout << "Geração: " << gen_count << std::endl;
    std::cout << "Tamanho da população: " << population.size() << std::endl;
    std::cout << "Quantidade de mutações: " << mutation_count << std::endl;
    std::cout << "Estagnação: " << stagnation << std::endl;
    std::cout << "5 melhores indivíduos: " << std::endl;
    for(uint16_t i = 0; i < 5; i++){
        std::cout << "\t" << i+1 << "° -> (f: " << population[i].fitness << ", s: " << 
        this->score->calculateNormalized(population[i].rubik) << "); ";
        population[i].rubik.printHistoric();
    }
    std::cout << std::endl;
}

void Genetic::sort_population(){
    std::sort(population.begin(), population.end(), Chromosome::greater);
}

void Genetic::remove_duplicates(){
    std::unordered_map<std::string, Chromosome> unique;
    for(auto& c : population)
        unique.insert(std::make_pair(c.rubik.getHistoricString(), c));
    
    population.clear();
    for(auto& [_, c] : unique)
        population.push_back(c);

    sort_population();
}

void Genetic::combine_children(std::vector<Chromosome>& children){
    std::vector<Chromosome> merged(population.size() + children.size());

    std::merge(population.begin(), population.end(), children.begin(),
         children.end(), merged.begin(), Chromosome::greater);
    
    population = std::move(merged);

    if(svc::Random::Int(1, 1000) <= this->mutation_rate + stagnation * 5){
        apply_mutation();
    }

    population.resize(population_size);
}

void Genetic::initialize(){
    for(uint32_t i = 0; i < population_size; i++){
        Rubik rubik = this->source;
        std::uniform_int_distribution<int> dist(1, 20);
        int n = dist(svc::Random::MT);
        rubik.scramble(n);
        Chromosome c{rubik, 0};
        fitness(c);
        population.push_back(c);
    }

    sort_population();
}

void Genetic::fitness(Chromosome &c){
    c.fitness = score->calculateNormalized(c.rubik);
}

Genetic::Chromosome Genetic::select(){
    // Seleção por torneio de 2
    std::uniform_int_distribution<int> dist(0, population.size()-1);
    int i1 = dist(svc::Random::MT);
    int i2 = dist(svc::Random::MT);
    return i1 < i2 ? population[i1] : population[i2];
}

Genetic::Chromosome Genetic::crossover(Chromosome& parent1, Chromosome& parent2){
    Rubik rubik = this->source;
    
    std::vector<std::vector<const Move*>> historics = {
        parent1.rubik.getHistoric(), parent2.rubik.getHistoric()
    };
    
    if(parent2.fitness > parent1.fitness){
        historics = {
            parent2.rubik.getHistoric(), parent1.rubik.getHistoric()
        };
    }

    uint32_t size = (historics[0].size() + historics[1].size()) / 2;

    uint16_t p = 0;
    for(uint32_t i = 0; i < size; i++){
        if(i >= historics[0].size()) p = 1;
        else if(i >= historics[1].size()) p = 0;
        else ++p %= 2;

        rubik.move(1, historics[p][i]);
    }

    Chromosome child = Chromosome{rubik, 0};
    fitness(child);
    return child;
}

void Genetic::apply_mutation(Chromosome &r){
    r.rubik.scramble(1);
    mutation_count++;
}

void Genetic::mutate(Chromosome& r){
    Rubik mutated = this->source;
    for(auto& move : r.rubik.getHistoric()){
        if(svc::Random::Int(1, 1000) <= this->mutation_rate + stagnation * 5){
            if(svc::Random::Int(0, 1)) apply_mutation(r);
        }
        else mutated.move(1, move);
    }

    r.rubik = mutated;
}

void Genetic::next_generation(){
    std::vector<Chromosome> children;
    uint32_t new_size = population.size() * 1.5f;
    
    #pragma omp parallel
    {
        std::vector<Chromosome> private_children;

        #pragma omp for
        for(uint32_t i = 0; i < population.size(); i++){
            Chromosome parent1 = select();
            Chromosome parent2 = select(); // Pode ser o mesmo pai (Arrumar)
            Chromosome child = crossover(parent1, parent2);
            
            private_children.push_back(child);
        }
        
        #pragma omp critical
        {
            children.insert(children.end(), private_children.begin(), private_children.end());
        }
    }

    std::sort(children.begin(), children.end(), Chromosome::greater);
    combine_children(children);
    remove_duplicates();
    gen_count++;
}