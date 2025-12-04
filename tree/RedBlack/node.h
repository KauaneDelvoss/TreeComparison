#ifndef NODE_H
#define NODE_H

#include <stdio.h>

enum coloracao { Vermelho, Preto };
typedef enum coloracao Cor;

typedef struct noRN {
    struct noRN* pai;
    struct noRN* esquerda;
    struct noRN* direita;
    Cor cor;
    int valor;
} NoRN;

typedef struct arvoreRN {
    struct noRN* raiz;
    struct noRN* nulo; 
} ArvoreRN;

#endif
