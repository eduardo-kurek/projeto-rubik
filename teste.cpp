#include <iostream>
#include "rubik/auxiliares/Genetic.h"
#include "services/Random.h"
#include "rubik/scores/Score.h"
#include "rubik/scores/Config.h"
#include "rubik/scores/basic-score/BasicScore.h"
#include "rubik/scores/basic-score/BasicConfig.h"
#include <windows.h>
#include <vector>
#include <random>

class BasicConfigChromosome : public Chromosome<BasicConfig>{
  protected:
    void _mutate(void*) override{
      this->value = svc::Random::Int(0, 4999);
    }
  public:
  TestChromosome() { initialize(); };
  TestChromosome(int value) { initialize(value); };

  void randomize(void*) override{
    this->value = svc::Random::Int(0, 4999);
  }

  void evaluate(void*) override{
    this->fitness = 5000 - this->value;
  }

  std::string toString() const override{
    return std::to_string(this->value);
  }

  std::vector<Chromosome<int>*> crossover(const Chromosome<int>& parent) const override{
    int avg = (this->value + parent.value) / 2;
    Chromosome<int>* child = new TestChromosome(avg);
    return std::vector<Chromosome<int>*>(1, child);
  }
};

template <class T>
class MyGenetic : public Genetic<T>{
  protected:
  void loop() override{
    Genetic<T>::loop();
    this->print_status();
  }

  public:
  MyGenetic() : Genetic<T>(){};
};


int main() {
  #ifdef WIN32
  SetConsoleOutputCP(CP_UTF8);
  #endif

  MyGenetic<TestChromosome> g;
  g.run();

  return 0;
}