#pragma once

#include <concepts>
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <unordered_map>
#include <omp.h>
#include <string>
#include <memory>
#include "Random.h"

template <typename Derived, typename Base>
std::vector<Derived*> dynamic_cast_vector(const std::vector<Base*>& base_vector) {
    std::vector<Derived*> derived_vector;
    for(Base* base_ptr : base_vector){
        Derived* derived_ptr = dynamic_cast<Derived*>(base_ptr);
        derived_vector.push_back(derived_ptr);
    }
    return derived_vector;
}

template <class TValue>
class Chromosome {

protected:
    virtual void _mutate(void*) = 0;

public:
    using _TValue = TValue;
    std::unique_ptr<TValue> value;
    double fitness;

    void initialize(TValue* value){
        this->value = value;
        this->evaluate();
    }

    void initialize(){
        this->randomize();
        this->evaluate();
    }

    void mutate(void* param = nullptr){
        this->_mutate(param);
        this->evaluate();
    };

    bool operator==(const Chromosome<TValue>& other) const { return this->value == other.value; }
    virtual bool operator<(const Chromosome<TValue>& other) const { return this->fitness > other.fitness; }
    virtual void evaluate(void* param = nullptr) = 0;
    virtual void randomize(void* param = nullptr) = 0;
    virtual std::string toString() const = 0;
    virtual std::vector<std::unique_ptr<Chromosome<TValue>>> crossover(const Chromosome<TValue>& parent) const = 0;

};

template <typename TChromosome>
concept IsChromosome = std::derived_from<TChromosome, Chromosome<typename TChromosome::_TValue>>;

template <IsChromosome TChromosome>
class Genetic{

protected:
    std::vector<std::unique_ptr<TChromosome>> population;
    int max_population = 500;
    int gen_count = 0;
    int mutation_count = 0;
    int mutation_rate[2] = {10, 1000}; // [0] / [1] = 1%
    float best_fitness = 0;
    int stagnation = 0;
    
    virtual void print_status(){
        std::cout << "===================================" << std::endl;
        std::cout << "Geração: " << gen_count << std::endl;
        std::cout << "Tamanho da população: " << population.size() << std::endl;
        std::cout << "Quantidade de mutações: " << mutation_count << std::endl;
        std::cout << "Estagnação: " << stagnation << std::endl;
        std::cout << "5 melhores indivíduos: " << std::endl;
        for(uint16_t i = 0; i < 5; i++)
            std::cout << "\t" << i+1 << "° -> (f: " << population[i]->fitness << "); ";
        std::cout << std::endl;
    }

    void sort(){
        std::sort(population.begin(), population.end());
    }

    virtual void clear(){
        mutation_count = 0;
        gen_count = 0;
        best_fitness = 0;
        stagnation = 0;
        population.clear();
    }

    void remove_duplicates(){
        return;
        std::cout << "Iniciando remoção de duplicados" << std::endl;
        std::unordered_map<std::string, TChromosome*> unique;
        int count = 0;
        for(TChromosome* c : population){

            try{
                count++;
                std::cout << "String: " << count << " " << c->toString() << std::endl;
                unique.insert(std::make_pair(c->toString(), c));
            }catch(...){
                std::cout << "Erro ao tentar inserir" << std::endl;
            }

        }

        std::cout << "Meio remoção de duplicados" << std::endl;
        
        population.clear();
        for(auto& pair : unique)
            population.push_back(pair.second);

        sort();
        std::cout << "Finalizando remoção de deuplicados" << std::endl;
    }

    virtual void initialize(){
        for(int i = 0; i < max_population - population.size(); i++){
            population.push_back(std::make_unique(TChromosome()));
        }
        sort();
    };

    virtual bool loop_condiction(int i) const {
        return i < 10;
    }

    virtual void finalize(){
        print_status();
        clear();
    }

    void combine_children(std::vector<TChromosome*>& children){
        std::vector<std::unique_ptr<TChromosome>> merged;
        merged.reserve(population.size() + children.size());
        std::move(population.begin(), population.end(), std::back_inserter(merged));
        std::move(children.begin(), children.end(), std::back_inserter(merged));
        population = std::move(merged);
        population.resize(max_population);
        this->sort();
    }

    virtual const TChromosome* select() const{
        // Seleção por torneio de 2
        std::uniform_int_distribution<int> dist(0, population.size()-1);
        int i1 = dist(svc::Random::MT);
        int i2 = dist(svc::Random::MT);
        return i1 < i2 ? population[i1] : population[i2];
    }

    std::vector<TChromosome*> cast_vector(const auto& base_vector) {
        std::vector<TChromosome*> derived_vector;
        for(auto base_ptr : base_vector){
            TChromosome* derived_ptr = dynamic_cast<TChromosome*>(base_ptr);
            derived_vector.push_back(derived_ptr);
        }
        return std::move(derived_vector);
    }

    virtual std::vector<TChromosome*> generate_individuals(){
        const TChromosome* parent1 = select();
        const TChromosome* parent2 = select(); // Pode ser o mesmo pai (Arrumar)
        std::vector<TChromosome*> children = cast_vector(parent1->crossover(*parent2));

        for(auto& child : children){
            if(svc::Random::Int(1, mutation_rate[1]) < mutation_rate[0] + stagnation * 2){
                child->mutate();
                mutation_count++;
            }
        }

        return std::move(children);
    }

    virtual void next_generation(){
        std::vector<TChromosome*> children;
        uint32_t new_size = population.size() * 1.5f;
        
        #pragma omp parallel
        {
            std::vector<TChromosome*> private_children;

            #pragma omp for
            for(uint32_t i = 0; i < population.size(); i++){
                auto children = generate_individuals();
                private_children.insert(private_children.end(), children.begin(), children.end());
            }
            
            #pragma omp critical
            {
                children.insert(children.end(), private_children.begin(), private_children.end());
            }
        }

        std::sort(children.begin(), children.end());
        combine_children(children);
        remove_duplicates();
        gen_count++;
    }

    virtual void loop(){
        std::cout << "Estou no loop" << std::endl;
        next_generation();
        std::cout << "Ba no loop" << std::endl;
        if(best_fitness == population[0]->fitness) stagnation++;
        else stagnation = 0;
        best_fitness = population[0]->fitness;
    }

public:
    Genetic() = default;
    ~Genetic(){ this->population.clear(); }

    void run(){
        this->initialize();
        for(int i = 0; this->loop_condiction(i); i++) this->loop();
        this->finalize();
    };

};