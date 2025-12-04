#ifndef UTILS
#define UTILS
#include "node.h"

extern long long comparacoes;

void executeInsertionRoutine(FILE *file);
void executeRemovalRoutine(FILE *file);
void balance(Arvore*, No*);
int height(No*);
int balanceFactor(No*);
No* rotateRight(Arvore*, No*);
No* rotateLeft(Arvore*, No*);
No* rotateLeftRight(Arvore*, No*);
No* rotateRightLeft(Arvore*, No*);
int max(int, int);

#endif