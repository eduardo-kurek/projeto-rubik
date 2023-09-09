#ifndef CUBOMAGICO_BRANCH_H
#define CUBOMAGICO_BRANCH_H

#include "rubik.h"

// ESTRUTURAS
typedef struct branch Branch;
typedef struct branch_vector BVector;

// MÉTODOS BRANCH
Branch* branch_criar();
void branch_destruir(Branch** branch);
bool branch_find(Branch** brancs, Branch* target);

//MÉTODOS VETOR DE BRANCHS
BVector* branch_vector_create(long long int tam);
void branch_vector_destroy(BVector** bVector);
bool branch_vector_insert(BVector* bVector, Branch* branch);



#endif //CUBOMAGICO_BRANCH_H
