#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "utils.h"

int main() {
    No *raiz = NULL;

    printf("Inserção:\n");
    inserir(&raiz, 10.0);
    inserir(&raiz, 20.0);
    inserir(&raiz, 30.0);
    inserir(&raiz, 40.0);
    inserir(&raiz, 50.0);
    inserir(&raiz, 25.0);

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
