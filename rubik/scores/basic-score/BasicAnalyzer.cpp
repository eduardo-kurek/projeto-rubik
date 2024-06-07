#include "BasicAnalyzer.h"
#include <omp.h>

float BasicAnalyzer::calculate_scramble(int i){
    float sum = 0;
    int count = 0;

    float expected = this->expectedPontuations[i];

    for(int j = 0; j < this->scrambles[i].size(); j++){
        std::vector<const Move*> moves = this->scrambles[i][j];
        Rubik rubik;
        rubik.move(moves);

        // CALCULANDO O ERRO MÉDIO QUADRÁTICO (MSE)
        float diff = abs(score.calculateNormalized(rubik) - expected);
        sum += diff * diff;
        count++;
    }

    return sum / count;
}

void BasicAnalyzer::calculate_pontuations(){
    this->pontuations = std::vector<float>();
    this->pontuations.resize(20);

    #pragma omp parallel for
    for(int i = 0; i < 20; i++)
        this->pontuations[i] = this->calculate_scramble(i);
}

float BasicAnalyzer::analyze(BasicConfig config){
    this->score = BasicScore(config);
    this->calculate_pontuations();

    float sum = 0;

    // SOMANDO TODOS OS RESULTADOS
    #pragma omp parallel for reduction(+:sum)
    for(int i = 0; i < this->pontuations.size(); i++)
        sum += this->pontuations[i];

    if(debug) this->print_pontuations();
    return sum;
}