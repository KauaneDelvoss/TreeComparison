#ifndef UTILS_B_H
#define UTILS_B_H

#include "node.h"

BTree* criar_arvore_b(int t);
void inserir_arvore_b(BTree *arvore, float valor);
BNo* buscar_arvore_b(BNo *no, float valor);
void imprimir_arvore_b(BNo *no);
void liberar_arvore_b(BNo *no);

#endif
