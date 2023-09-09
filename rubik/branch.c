#include "branch.h"

// ESTRUTURA
struct branch{
    char* position;
    int lastMove;
};

struct branch_vector{
    Branch** vet;
    long long int tam;
    long long int qt;
};

// IMPLEMENTAÇÕES
Branch* branch_criar(){
    Branch* b = (Branch*)malloc(sizeof(Branch));
    b->position = POS_RESOLVIDO;
    b->lastMove = -1;
    return b;
}

void branch_destruir(Branch** branch){
    free(*branch);
    *branch = NULL;
}

// IMPLEMENTAÇÕES DO VETOR
BVector* branch_vector_create(long long int tam){
    BVector* bVector = (BVector*) malloc(sizeof(BVector));
    Branch** vet = (Branch**) calloc(tam, sizeof(Branch));

    bVector->tam = tam;
    bVector->qt = 0;
    bVector->vet = vet;

    return bVector;
}

void branch_vector_destroy(BVector** bVector){
    for(long long int i = 0;  i < (*bVector)->qt; i++)
        branch_destruir(&((*bVector)->vet[i]));
    free((*bVector)->vet);
    free(*bVector);
    *bVector = NULL;
}

bool branch_vector_insert(BVector* bVector, Branch* branch){
    if(bVector->qt == bVector->tam) return false;
    bVector->vet[bVector->qt++] = branch; return true;
}

