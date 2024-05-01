#include "BruteForce.h"
#include <omp.h>
#include <iostream>

void BruteForce::solve(Rubik rubik, uint32_t depth){
    // SE O CUBO ENVIADO JÁ ESTIVER "RESOLVIDO", ADICIONA O SEU HISTÓRICO ÀS SOLUÇÕES
    if(rubik == this->target)
        this->foundedSolves.push_back(rubik.getHistoric());

    // CASO BASE
    if(depth == 0) return;

    // CONTINUA BUSCANDO POR MAIS SOLUÇÕES
    uint8_t newDepth = depth - 1;
    for(auto& move : rubik.getValidMoves()){

        // INICIANDO A INSTÂNCIA E A MOVENDO COM O NOVO MOVIMENTO
        Rubik model = rubik;
        model.move(1, move);

        // RESOLVENDO A NOVA INSTÂNCIA
        this->solve(model, newDepth);
    }
}

BruteForce::BruteForce(uint32_t depth)
    : Solver(){
    this->depth = depth;
}

BruteForce::BruteForce(uint32_t depth, Rubik source) 
    : Solver(source){
    this->depth = depth;
}

BruteForce::BruteForce(uint32_t depth, Rubik source, Rubik target)
    : Solver(source, target){
    this->depth = depth;
}

void BruteForce::setDepth(uint32_t depth){
    this->depth = depth;
}

void BruteForce::solve(){
    this->clear();
    
    if(this->depth == 0) return;
    uint8_t newDepth = this->depth - 1;

    #pragma omp parallel for num_threads(18)
    for(auto& move : this->source.getValidMoves()){
        Rubik model = this->source;
        model.move(1, move);
        this->solve(model, newDepth);
    }
}