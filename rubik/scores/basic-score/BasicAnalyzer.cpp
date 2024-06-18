#include "BasicAnalyzer.h"
#include <omp.h>

float BasicAnalyzer::calculate_scramble(int i){
    float sum = 0;
    int count = 0;

    float expected = this->expectedPontuations[i];

    for(int j = 0; j < (*this->scrambles)[i].size(); j++){
        std::vector<const Move*> moves = (*this->scrambles)[i][j];
        Rubik rubik;
        rubik.move(moves);

        // CALCULANDO O ERRO MÉDIO QUADRÁTICO (MSE)
        float res = score.calculateNormalized(rubik);
        this->pontuations[i] += res;
        float diff = abs(res - expected);
        sum += diff * diff;
        count++;
    }

    this->pontuations[i] /= count;
    return sum / count;
}

void BasicAnalyzer::calculate_divergences(){
    this->divergences = std::vector<float>(20);

    #pragma omp parallel for
    for(int i = 0; i < 20; i++)
        this->divergences[i] = this->calculate_scramble(i);
}

float BasicAnalyzer::analyze(BasicConfig config){
    this->pontuations = std::vector<float>(20);
    this->score = BasicScore(config);
    this->calculate_divergences();

    float sum = 0;

    // SOMANDO TODOS OS RESULTADOS
    #pragma omp parallel for reduction(+:sum)
    for(int i = 0; i < this->divergences.size(); i++)
        sum += this->divergences[i];

    if(debug) this->print_pontuations();
    return sum;
}