#ifndef UTILS_B_H
#define UTILS_B_H

#include "node.h"
#include <stdio.h>

extern long long comparacoes;

ArvoreB* createBTree(int order);
NoB* createBNode(ArvoreB* arvore);
void traverseBTree(NoB* noB);
int binarySearchB(NoB* noB, int chave);
int locateKeyB(ArvoreB* arvore, int chave);
NoB* locateNodeB(ArvoreB* arvore, int chave);
void addKeyToNodeB(NoB* noB, NoB* novo, int chave);
void insertB(ArvoreB* arvore, int chave);
void removeB(ArvoreB* arvore, int chave);
void executeInsertionRoutine(FILE *file, int order);
void executeRemovalRoutine(FILE *file, int order);

#endif