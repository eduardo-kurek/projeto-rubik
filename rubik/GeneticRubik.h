// #pragma once

// #include "Rubik.h"
// #include "scores/Config.h"
// #include "scores/Score.h"
// #include "auxiliares/Genetic.h"
// #include "scores/Score.h"
// #include <memory>
// #include <random>

// int count = 0;

// class RubikChromosome : public Chromosome<Rubik>{

// protected:
//     std::shared_ptr<IScore> score;

//     void _mutate(void*) override{
//         // Inserindo um movimento aleatório em algum lugar
//         /* TODO */
//     }

// public:
//     using _TValue = Rubik;

//     RubikChromosome() = default;

//     RubikChromosome(int qt_scramble, std::shared_ptr<IScore> score){
//         this->randomize(&qt_scramble);
//         this->score = score;
//         this->evaluate(nullptr);
//     }

//     RubikChromosome(Rubik value, std::shared_ptr<IScore> score){
//         this->value = std::make_unique<Rubik>(value);
//         this->score = score;
//         this->evaluate(nullptr);
//     }

//     void randomize(void* qt) override{
//         this->value = std::make_unique<Rubik>();
//         this->value->scramble(*(int*)qt);
//     };

//     void evaluate(void* score) override{
//         if(score == nullptr) return;
//         this->fitness = (double)this->score->calculateNormalized(*this->value);
//     }

//     std::vector<std::unique_ptr<Chromosome<Rubik>>> crossover(const Chromosome<Rubik>& parent) const override{
//         // Gerando 2 filhos a partir de um corte aleatório nos dois pais
//         std::vector<const Move*> moves1 = this->value->getHistoric();
//         std::vector<const Move*> moves2 = parent.value->getHistoric();

//         int cut1 = svc::Random::Int(0, moves1.size() - 1);
//         int cut2 = svc::Random::Int(0, moves2.size() - 1);
    
//         Rubik c1 = Rubik();
//         Rubik c2 = Rubik();

//         for(int i = 0; i < moves1.size(); i++){
//             if(i < cut1) c1.move(1, *moves1[i]);
//             else c2.move(1, *moves1[i]);
//         }

//         for(int i = 0; i < moves2.size(); i++){
//             if(i < cut2) c2.move(1, moves2[i]);
//             else c1.move(1, moves2[i]);
//         }

//         RubikChromosome* child1 = new RubikChromosome(c1, this->score);
//         RubikChromosome* child2 = new RubikChromosome(c2, this->score);
//         std::vector<std::unique_ptr<Chromosome<Rubik>>> children = {child1, child2};
//         return children;
//     }

//     std::string toString() const override{
//         return this->value->getHistoricString();
//     }

// };

// class GeneticRubik : public Genetic<RubikChromosome>{

// private:
//     std::shared_ptr<IScore> score;
    
// protected:

//     void initialize() override{
//         for(int i = 0; i < this->max_population - this->population.size(); i++){
//             // numero aleatorio entre 1 e 20
//             int qt_scramble = svc::Random::Int(1, 20);
//             this->population.push_back(std::make_unique<RubikChromosome>(qt_scramble, this->score));
//         }
//         this->sort();
//     };

//     // std::vector<RubikChromosome*> generate_individuals() override{
//     //     std::vector<RubikChromosome*> individuals = Genetic<TScore>::generate_individuals();
//     //     for(auto individual : individuals) individual->evaluate(&this->score);
//     //     return individuals;
//     // }

// public:
//     GeneticRubik(std::shared_ptr<IScore> score) : score(score) {}

// };