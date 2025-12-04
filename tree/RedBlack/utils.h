#ifndef UTILS_RN_H
#define UTILS_RN_H

#include "node.h"
#include <stdio.h>

extern long long comparacoes;

ArvoreRN* createRedBlackTree();
NoRN* insertRedBlack(ArvoreRN* arvoreRN, int valor);
void removeRedBlack(ArvoreRN* arvoreRN, int valor);
void executeInsertionRoutine(FILE *file);
void executeRemovalRoutine(FILE *file);

#endif