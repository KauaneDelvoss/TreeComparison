#ifndef NODE_B_H
#define NODE_B_H

#include <stdio.h>
#include <stdbool.h>

typedef struct noB {
    int total;
    int* chaves;
    struct noB** filhos;
    struct noB* pai;
} NoB;

typedef struct arvoreB {
    NoB* raiz;
    int ordem;
} ArvoreB;

#endif
