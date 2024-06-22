#include "../Rubik.h"
#include "../scores/Score.h"
#include "../../services/Random.h"
#include "BruteForce.h"
#include "Solver.h"
#include <algorithm>
#include <vector>

template <typename TScore>
class EKGeneticSolver : public Solver {

    struct Chromosome{
        Rubik rubik;
        float fitness;

        static bool greater(const Chromosome& a, const Chromosome& b){
            return a.fitness > b.fitness;
        }
    };

protected:
    TScore score;
    std::vector<EKGeneticSolver::Chromosome> population;
    uint32_t population_size = 5000;
    uint32_t gen_count = 0;
    uint32_t mutation_count = 0;
    uint32_t mutation_rate[2] = {10, 1000}; // [0] / [1] = 1%
    float best_fitness = 0;
    uint32_t stagnation = 0;
    bool founded = false;

    virtual void print_status(){
        std::cout << "===================================" << std::endl;
        std::cout << "Geração: " << gen_count << std::endl;
        std::cout << "Tamanho da população: " << population.size() << std::endl;
        std::cout << "Quantidade de mutações: " << mutation_count << std::endl;
        std::cout << "Estagnação: " << stagnation << std::endl;
        std::cout << "5 melhores indivíduos: " << std::endl;
        for(uint16_t i = 0; i < 5; i++){
            std::cout << "\t" << i+1 << "° -> (f: " << population[i].fitness << "); ";
        }
        std::cout << std::endl;
    }

    void sort_population(){
        std::sort(population.begin(), population.end(), Chromosome::greater);
    }

    virtual void remove_duplicates(){
        std::unordered_map<std::string, Chromosome> unique;
        for(auto& c : population)
            unique.insert(std::make_pair(c.rubik.getHistoricString(), c));
        
        population.clear();
        for(auto& pair : unique)
            population.push_back(pair.second);

        sort_population();
    }

    virtual void combine_children(std::vector<Chromosome>& children){
        std::vector<Chromosome> merged(population.size() + children.size());

        std::merge(population.begin(), population.end(), children.begin(),
            children.end(), merged.begin(), Chromosome::greater);
        
        population = std::move(merged);
        population.resize(population_size);
    }

    virtual void initialize(){
        this->founded = false;
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

    virtual void fitness(Chromosome& c){
        c.fitness = score.calculateNormalized(c.rubik);
    }

    virtual Chromosome select(){
        // Seleção por torneio de 2
        std::uniform_int_distribution<int> dist(0, population.size()-1);
        int i1 = dist(svc::Random::MT);
        int i2 = dist(svc::Random::MT);
        return i1 < i2 ? population[i1] : population[i2];
    }

    virtual std::vector<Chromosome> crossover(Chromosome& parent1, Chromosome& parent2){
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
        std::vector<Chromosome> children = {child};
        return children;
    }

    virtual void mutate(Chromosome& r){
        Rubik mutated = this->source;
        auto historic = r.rubik.getHistoric();
        int rand = svc::Random::Int(1, historic.size());
        int mov = svc::Random::Int(0, 17);

        for(int i = 0; i < rand; i++) mutated.move({historic[i]});
        mutated.move({Moves[mov]});
        for(int i = rand; i < historic.size(); i++) mutated.move({historic[i]});

        r.rubik = mutated;
        fitness(r);
        mutation_count++;
    }

    void next_generation(){
        std::vector<Chromosome> children;
        uint32_t new_size = population.size() * 1.5f;
        
        #pragma omp parallel
        {
            std::vector<Chromosome> private_children;

            #pragma omp for
            for(uint32_t i = 0; i < population.size(); i++){
                Chromosome parent1 = select();
                Chromosome parent2 = select();
                while(parent1.rubik.getHistoricString() == parent2.rubik.getHistoricString())
                    parent2 = select();
                std::vector<Chromosome> crossover_children = crossover(parent1, parent2);

                for(auto& child : crossover_children)
                    if(svc::Random::Int(1, this->mutation_rate[1]) <= this->mutation_rate[0] + stagnation)
                        mutate(child);
            
                private_children.insert(private_children.end(), crossover_children.begin(), crossover_children.end());
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
    };

    bool check_solution(Chromosome& c){
        Rubik r = this->source;
        std::vector<const Move*> historic = c.rubik.getHistoric();
        for(int i = 0; i < historic.size() - 3; i++) r.move({historic[i]});
        r.clearRestrictedMoves();

        BruteForce bf(4, r);
        bf.solve();
        auto solutions = bf.getFoundedSolves();
        if(solutions.size() == 0) return false;

        std::vector<const Move*> solution = solutions[0];
        r.move(solution);
        c.rubik = r;
        fitness(c);
        return true;
    }

public:

    EKGeneticSolver(Rubik source, TScore::_TConfig config) : Solver(source){
        this->score = TScore(config);
    };

    void solve() override{
        initialize();
        best_fitness = population[0].fitness;
        int minGen = 300;

        while(true){
            next_generation();

            if(best_fitness == population[0].fitness) stagnation++;
            else stagnation = 0;
            best_fitness = population[0].fitness;

            if(population[0].fitness > 90 && check_solution(population[0])){
                this->founded = true;
                break;
            }
            if(this->gen_count > minGen && stagnation > 30) break;
        }

        //print_status();
        for(uint16_t i = 0; i < 5; i++){
            foundedSolves.push_back(population[i].rubik.getHistoric());
        }
    };
    bool solved(){ return this->founded; }

};