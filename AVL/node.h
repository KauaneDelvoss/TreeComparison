#ifndef NODE_H
#define NODE_H

#include <stdio.h>

typedef struct No {
    struct No *esquerda;
    struct No *direita;
    struct No *pai;
    float value;
} No;

#endif