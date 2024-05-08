#include "../Rubik.h"
#include "../scores/Score.h"
#include "Solver.h"
#include <vector>

class Genetic : public Solver {

    struct Chromosome{
        Rubik rubik;
        float fitness;

        static bool greater(const Chromosome&, const Chromosome&);
    };

protected:
    Score* score;
    std::vector<Chromosome> population;
    uint32_t population_size = 5000;
    uint32_t gen_count = 0;
    uint32_t mutation_count = 0;
    uint32_t mutation_rate = 10; // 15%
    uint32_t mutation_gene_rate = 1; // 1%

    virtual void print_status();
    void sort_population();
    virtual void combine_children(std::vector<Chromosome>& children);
    virtual void initialize();
    virtual void fitness(Chromosome& c);
    virtual Chromosome select();
    virtual Chromosome crossover(Chromosome& parent1, Chromosome& parent2);
    virtual void apply_mutation(Chromosome& r);
    virtual void mutate(Chromosome& r);
    void next_generation();

public:
    Genetic(Score& score);
    Genetic(Score& score, Rubik source);
    void solve() override;

};