#ifndef UTILS
#define UTILS
#include "node.h"

No* criarNo(float valor);
int max(int a, int b);
int altura(No *no);
int fb(No *no);
No *rse(No *no);
No *rsd(No *no);
No* balancear(No *no);
No* inserir(No* no, float valor);
No* encontrarMinimo(No* no);
No* remover(No* raiz, float valor);
void imprimirEmOrdem(No *no);

#endif
