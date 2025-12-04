#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include "node.h"

long long comparacoes = 0;

// Protótipos de funções estáticas (privadas a este arquivo)
static NoB* splitNodeB(ArvoreB* arvore, NoB* noB);
static void addKeyRecursiveB(ArvoreB* arvore, NoB* noB, NoB* novo, int chave);
static void removeKeyRecursiveB(ArvoreB* arvore, NoB* noB, int chave);
static void removeKeyFromNodeB(NoB* noB, int indice);
ArvoreB* createBTree(int order) {
    ArvoreB* a = malloc(sizeof(ArvoreB));
    a->ordem = order;
    a->raiz = createBNode(a);

    return a;
}

NoB* createBNode(ArvoreB* arvore) {
    int max = arvore->ordem * 2;
    NoB* noB = malloc(sizeof(NoB));

    noB->pai = NULL;

    noB->chaves = malloc(sizeof(int) * (max + 1));
    noB->filhos = malloc(sizeof(NoB) * (max + 2));
    noB->total = 0;

    for (int i = 0; i < max + 2; i++) {
        comparacoes++;
        noB->filhos[i] = NULL;
    }

    return noB;
}

void traverseBTree(NoB* noB) {
    comparacoes++;
    if (noB != NULL) {
        comparacoes++;
        for (int i = 0; i < noB->total; i++) {
            comparacoes++;
            traverseBTree(noB->filhos[i]);

            printf("%d ", noB->chaves[i]);
        }

        traverseBTree(noB->filhos[noB->total]);
    }
}

int binarySearchB(NoB* noB, int chave) {
    int inicio = 0, fim = noB->total - 1, meio;

    while (inicio <= fim) {
        comparacoes++;

        meio = (inicio + fim) / 2;

        comparacoes++;
        if (noB->chaves[meio] == chave) {
            return meio;	
        }
        else if (noB->chaves[meio] > chave) {
            fim = meio - 1;
        }
        else {
            inicio = meio + 1;
        }
    }
    return inicio;
}

int locateKeyB(ArvoreB* arvore, int chave) {
    NoB* noB = arvore->raiz;

    comparacoes++;
    while (noB != NULL) {
        comparacoes++;
        int i = binarySearchB(noB, chave);

        comparacoes++;
        if (i < noB->total && noB->chaves[i] == chave) {
            return 1;
        }
        else {
            noB = noB->filhos[i];
        }
    }

    return 0;
}

NoB* locateNodeB(ArvoreB* arvore, int chave) {
    NoB* noB = arvore->raiz;

    comparacoes++;
    while (noB != NULL) {
        comparacoes++;

        int i = binarySearchB(noB, chave);

        comparacoes++;
        if (noB->filhos[i] == NULL)
            return noB;
        else
            noB = noB->filhos[i];
    }

    return NULL;
}

void addKeyToNodeB(NoB* noB, NoB* novo, int chave) {
    int i = binarySearchB(noB, chave);

    comparacoes++;
    for (int j = noB->total - 1; j >= i; j--) {
        comparacoes++;
        noB->chaves[j + 1] = noB->chaves[j];
        noB->filhos[j + 2] = noB->filhos[j + 1];
    }

    noB->chaves[i] = chave;
    noB->filhos[i + 1] = novo;

    noB->total++;
}

int isOverflowingB(ArvoreB* arvore, NoB* noB) {
    comparacoes++;

    return noB->total > arvore->ordem * 2;
}

static NoB* splitNodeB(ArvoreB* arvore, NoB* noB) {
    int meio = noB->total / 2;
    NoB* novo = createBNode(arvore);
    novo->pai = noB->pai;

    comparacoes++;
    for (int i = meio + 1; i < noB->total; i++) {
        comparacoes++;
        novo->filhos[novo->total] = noB->filhos[i];
        novo->chaves[novo->total] = noB->chaves[i];
        comparacoes++;
        if (novo->filhos[novo->total] != NULL) novo->filhos[novo->total]->pai = novo;

        novo->total++;
    }

    novo->filhos[novo->total] = noB->filhos[noB->total];
    comparacoes++;
    if (novo->filhos[novo->total] != NULL) novo->filhos[novo->total]->pai = novo;
    noB->total = meio;
    return novo;
}

static void addKeyRecursiveB(ArvoreB* arvore, NoB* noB, NoB* novo, int chave) {
    comparacoes++;

    addKeyToNodeB(noB, novo, chave);

    comparacoes++;
    if (isOverflowingB(arvore, noB)) {
        int promovido = noB->chaves[arvore->ordem];
        NoB* novo = splitNodeB(arvore, noB);

        comparacoes++;
        if (noB->pai == NULL) {

            NoB* pai = createBNode(arvore);
            pai->filhos[0] = noB;
            addKeyToNodeB(pai, novo, promovido);

            noB->pai = pai;
            novo->pai = pai;
            arvore->raiz = pai;
        }
        else
            addKeyRecursiveB(arvore, noB->pai, novo, promovido);
    }
}

void insertB(ArvoreB* arvore, int chave) {
    NoB* noB = locateNodeB(arvore, chave);

    addKeyRecursiveB(arvore, noB, NULL, chave);
}

void removeB(ArvoreB* arvore, int chave) {
    comparacoes++;
    removeKeyRecursiveB(arvore, arvore->raiz, chave);
}

static void removeKeyRecursiveB(ArvoreB* arvore, NoB* noB, int chave) {
    comparacoes++;
    if (noB == NULL)
        return;

    int indice = binarySearchB(noB, chave);

    comparacoes++;
    if (indice < noB->total && noB->chaves[indice] == chave) {
        comparacoes++;
        if (noB->filhos[indice] != NULL) {
            NoB* noSubstituto = noB->filhos[indice + 1];

            comparacoes++;
            while (noSubstituto->filhos[0] != NULL) {
                comparacoes++;
                noSubstituto = noSubstituto->filhos[0];
            }

            noB->chaves[indice] = noSubstituto->chaves[0];

            removeKeyRecursiveB(arvore, noSubstituto, noSubstituto->chaves[0]);
        }
        else {
            removeKeyFromNodeB(noB, indice);
        }
    }
    else {
        removeKeyRecursiveB(arvore, noB->filhos[indice], chave);
    }
}

static void removeKeyFromNodeB(NoB* noB, int indice) {
    comparacoes++;
    for (int i = indice; i < noB->total - 1; i++) {
        comparacoes++;
        noB->chaves[i] = noB->chaves[i + 1];
        noB->filhos[i + 1] = noB->filhos[i + 2];
    }

    noB->total--;
}


void executeInsertionRoutine(FILE *file, int order) {
    ArvoreB* tree = createBTree(order);
    int value;
    while (fscanf(file, "%d", &value) != EOF) {
        insertB(tree, value);
    }
}

void executeRemovalRoutine(FILE *file, int order) {
    ArvoreB* tree = createBTree(order);
    int value;

    while (fscanf(file, "%d", &value) != EOF) {
        insertB(tree, value);
    }

    while (fscanf(file, "%d", &value) != EOF) {
        removeB(tree, value);
    }
}