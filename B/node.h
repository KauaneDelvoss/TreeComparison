#ifndef NODE_B_H
#define NODE_B_H

#include <stdio.h>
#include <stdbool.h>

typedef struct BNo
{
    int n;
    bool folha;
    float *chaves;
    struct BNo **filhos;
} BNo;

typedef struct
{
    BNo *raiz;
    int t;
} BTree;

#endif
