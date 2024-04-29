#include "rubik/Rubik.h"
#include "rubik/solvers/BruteForce.h"
#include "rubik/auxiliares/StickerCoord.h"
#include "rubik/auxiliares/Corners.h"
#include "rubik/scores/PontuationTable.h"
#include "rubik/scores/basic-score/BasicScore.h"
#include "rubik/auxiliares/Move.h"
#include "rubik/auxiliares/Restriction.h"
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <fstream>
#include <omp.h>
#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#endif

void _findBetter(Score* score, Rubik* r, const Move* firstMove, int i, int depth, float* movesAcc){
    float value = score->calculate(*r);
    movesAcc[firstMove->index] += value;
    
    if(i == depth) return;

    for(auto move : r->getValidMoves()){
        Rubik model = *r;
        model.move({move});
        _findBetter(score, &model, firstMove, i+1, depth, movesAcc);
    }
}

const Move* findBetter(Score* score, const Rubik* r, int depth){
    if(r->extract() == POS_RESOLVIDO) return nullptr;

    Rubik rubik = *r;

    float movesAccumulator[18] = {0};

    auto validMoves = rubik.getValidMoves();
    
    #pragma omp parallel for
    for(int i = 0; i < validMoves.size(); i++){
        Rubik model = rubik;
        model.move({validMoves[i]});
        _findBetter(score, &model, validMoves[i], 1, depth, movesAccumulator);
    }

    int better = 0;
    float higher = 0;
    for(uint8_t i = 0; i < 18; i++){
        // std::cout << "Valor acumulado para o movimento " << Moves[i]->name << ": ";
        // std::cout << movesAccumulator[i] << std::endl;
        if(movesAccumulator[i] > higher){
            better = i;
            higher = movesAccumulator[i];
        }
    }

    return Moves[better];
}

std::vector<const Move*> solve(Rubik r, int depth){
    std::vector<const Move*> solucao;

    PontuationTable* pt = new PontuationTable({0, 0, 0, 0}, {1, 1, -1, 0}, 0);
    BasicScore* bs = new BasicScore(pt);

    Rubik model = r;
    model.clearHistoric();
    model.clearRestrictedMoves();

    while(true){
        const Move* move = findBetter(bs, &model, depth);
        if(move == nullptr) break;
        solucao.push_back(move);
        model.move({move});
        std::cout << "Move encontrado: " << move->name << std::endl;
    }

    return solucao;
}


int main(int argc, char* argv[]){
    // AJUSTANDO A CODIFICAÇÃO PARA UTF-8
    #ifdef _WIN32
        SetConsoleOutputCP(65001);
    #endif
    
    Rubik r;
    r.move({FA, UA, B, DA, R2});
/*
    srand(1290);

    r.scramble(4);

    std::cout << "Embaralhamento realizado : ";
    r.printHistoric();
    std::cout << std::endl;

    std::vector<const Move*> solucao = solve(r, 4);

    std::cout << "Solução encontrada: ";
    for(const Move* move : solucao){
        std::cout << move->name << " ";
    }
    std::cout << std::endl;*/
    
    /*
    PontuationTable* pt = new PontuationTable({0,0,0,0}, {1,1,-1,0}, 0);
    BasicScore* bs = new BasicScore(pt);
    r.clearHistoric();
    r.clearRestrictedMoves();

    auto move = findBetter(bs, &r);
    std::cout << "Melhor encontrado pelo algoritmo: ";
    std::cout << move->name << std::endl;*/

    BruteForce bf(5, r);
    
    bf.solve();
    bf.printFoundedSolves();
    

}