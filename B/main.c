#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "utils.h"

void testar_arvore_com_ordem(int ordem) {
    printf("\n--- Testando Arvore B de Ordem t=%d ---\n", ordem);
    
    BTree *arvore = criar_arvore_b(ordem);
    if (arvore == NULL) {
        return; 
    }

    float valores[] = {10, 20, 30, 40, 50, 25, 5, 15, 60, 70, 80, 35, 45};
    int num_valores = sizeof(valores) / sizeof(valores[0]);

    printf("Inserindo valores...\n");
    for (int i = 0; i < num_valores; i++) {
        inserir_arvore_b(arvore, valores[i]);
    }

    printf("Valores em ordem: ");
    imprimir_arvore_b(arvore->raiz);
    printf("\n");

    float valor_busca = 25.0;
    if (buscar_arvore_b(arvore->raiz, valor_busca) != NULL) {
        printf("Valor %.1f encontrado na arvore.\n", valor_busca);
    } else {
        printf("Valor %.1f NAO encontrado na arvore.\n", valor_busca);
    }

    valor_busca = 99.0;
    if (buscar_arvore_b(arvore->raiz, valor_busca) != NULL) {
        printf("Valor %.1f encontrado na arvore.\n", valor_busca);
    } else {
        printf("Valor %.1f NAO encontrado na arvore.\n", valor_busca);
    }

    liberar_arvore_b(arvore->raiz);
    free(arvore);
}

int main() {
    testar_arvore_com_ordem(2); 
    testar_arvore_com_ordem(5);
    testar_arvore_com_ordem(10);

    return 0;
}
