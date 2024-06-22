#include "rubik/Rubik.h"
#include "rubik/solvers/Greedy.h"
#include "rubik/solvers/BruteForce.h"
#include "rubik/GeneticRubik.h"
#include "rubik/auxiliares/StickerCoord.h"
#include "rubik/solvers/EKGeneticSolver.h"
#include "rubik/auxiliares/Corners.h"
#include "rubik/scores/basic-score/BasicScore.h"
#include "rubik/auxiliares/Move.h"
#include "rubik/auxiliares/Restriction.h"
#include "rubik/scores/basic-score/BasicGeneticTunner.h"
#include "rubik/scores/basic-score/BasicAnalyzer.h"
#include "rubik/Utils.h"
#include <queue>
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <fstream>
#include <omp.h>
#include <stdlib.h>
#include <random>
#include <memory>
#include "services/Random.h"
#ifdef _WIN32
#include <windows.h>
#endif

int main(int argc, char* argv[]){
  // AJUSTANDO A CODIFICAÇÃO PARA UTF-8
  #ifdef _WIN32
    SetConsoleOutputCP(65001);
  #endif
  
  // std::string scramble_path = "tuning/scrambles/";
  // auto scrambles = Utils::read_scrambles(scramble_path);
  // BasicAnalyzer analyzer(&scrambles);

  // BasicGeneticTunner tunner(analyzer, 50, 1000);
  
  // std::vector<BasicConfig> initial_configs;
  // for(int i = 0; i < 100; i++){
  //   tunner.set_initial_configs(initial_configs);
  //   tunner.run();
  //   std::cout << "Iteração " << i << "\n";
  //   tunner.print_status();
  //   initial_configs = tunner.get_results();
  // }

  int count[20] = {0};
  int qt = 500;

  #pragma omp parallel for
  for(int i = 4; i < 20; i++){
    for(int j = 0; j < qt; j++){
      Rubik r;
      r.scramble(i+1);

      BasicConfig config;
      EKGeneticSolver<BasicScore> solver(r, config);
      solver.solve();
      if(solver.solved()) count[i]++;
      

      if(qt % 10 == 0){
        std::cout << "Iteração " << i << " - " << j << "\n";
      }
      
    }
  }

  // imprimindo resultados em porcentagem
  for(int i = 4; i < 20; i++){
    std::cout << "Soluções para " << i+1 << " movimentos: " << count[i] << " (" << (count[i]*100.0)/qt << "%)\n";
  }

  return 0;

}