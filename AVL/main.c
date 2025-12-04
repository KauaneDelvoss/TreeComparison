#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "utils.h"
#include "utils.C"

int main() {
    No *raiz = NULL;

    printf("Inserção:\n");
    raiz = inserir(raiz, 10.0);
    raiz = inserir(raiz, 20.0);
    raiz = inserir(raiz, 30.0);
    raiz = inserir(raiz, 40.0);
    raiz = inserir(raiz, 50.0);
    raiz = inserir(raiz, 25.0);

    printf("Em ordem: ");
    imprimirEmOrdem(raiz);
    printf("\nRaiz: %.1f\n", raiz->value);

    printf("\nRemoção: 30\n");
    raiz = remover(raiz, 30.0);
    
    printf("Em ordem: ");
    imprimirEmOrdem(raiz);
    printf("\nNova Raiz: %.1f\n", raiz->value);

    return 0;
}