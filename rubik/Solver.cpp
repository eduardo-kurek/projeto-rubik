#include "Solver.h"
#include <iostream>

//#define DEBUG 1;

Solver::Solver(){}

Solver::Solver(Rubik source){
    this->source = source;
}

Solver::Solver(Rubik source, Rubik target){
    this->source = source;
    this->target = target;
}

void Solver::setSource(Rubik source){
    this->source = source;
}

void Solver::setTarget(Rubik target){
    this->target = target;
}

void Solver::solve(Rubik rubik, uint8_t depth){
    using namespace std;

    // SE O CUBO ENVIADO JÁ ESTIVER "RESOLVIDO", ADICIONA O SEU HISTÓRICO ÀS SOLUÇÕES
#ifdef DEBUG
        cout << "Comparando o cubo: " << endl;
        rubik.print();
        cout << "Movimentos já realizados neste cubo: ";
        for(auto& move : rubik.getHistoric())
            cout << move->name << " ";
        cout << endl;
        cout << "Com o cubo: " << endl;
        this->target.print();
        cout << endl;
#endif
    if(rubik == this->target){
#ifdef DEBUG
        cout << "Comparação verdadeira" << endl;
#endif
        this->foundedSolves.push_back(rubik.getHistoric());
    }else{
#ifdef DEBUG
        cout << "Comparação falsa" << endl;
#endif
    }


#ifdef DEBUG
    cout << "--------------------------------------------------------" << endl;
#endif

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

void Solver::solve(uint8_t depth){
    this->foundedSolves = {{}};
    this->source.clearRestrictedMoves();
    this->source.clearHistoric();
    this->solve(this->source, depth);
}

std::vector<std::vector<const Move*>> Solver::getFoundedSolves(){
    return this->foundedSolves;
}