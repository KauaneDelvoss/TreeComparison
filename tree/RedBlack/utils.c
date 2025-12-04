#include <stdlib.h>
#include "utils.h"
#include "node.h"
#include <stdio.h>

long long comparacoes = 0;

// Protótipos de funções estáticas (privadas a este arquivo)
static NoRN* createRedBlackNode(ArvoreRN* arvoreRN, NoRN* pai, int valor);
static NoRN* addRedBlackNode(ArvoreRN* arvoreRN, NoRN* noRN, int valor);
static NoRN* locateRedBlack(ArvoreRN* arvoreRN, int valor);
static void balanceRedBlack(ArvoreRN* arvoreRN, NoRN* noRN);
static void rotateLeftRedBlack(ArvoreRN* arvoreRN, NoRN* noRN);
static void rotateRightRedBlack(ArvoreRN* arvoreRN, NoRN* noRN);
ArvoreRN* createRedBlackTree() {
    ArvoreRN *arvoreRN = malloc(sizeof(ArvoreRN));
    arvoreRN->nulo = NULL;
    arvoreRN->raiz = NULL;

    arvoreRN->nulo = createRedBlackNode(arvoreRN, NULL, 0);
    arvoreRN->nulo->cor = Preto;

    return arvoreRN;
}

int isRedBlackEmpty(ArvoreRN* arvoreRN) {
    return arvoreRN->raiz == NULL;
}

static NoRN* createRedBlackNode(ArvoreRN* arvoreRN, NoRN* pai, int valor) {
    NoRN* noRN = malloc(sizeof(NoRN));

    noRN->pai = pai;    
    noRN->valor = valor;
    noRN->direita = arvoreRN->nulo;
    noRN->esquerda = arvoreRN->nulo;

    return noRN;
}

static NoRN* addRedBlackNode(ArvoreRN* arvoreRN, NoRN* noRN, int valor) {
    comparacoes++;
    if (valor > noRN->valor) {
        comparacoes++;
        if (noRN->direita == arvoreRN->nulo) {
            noRN->direita = createRedBlackNode(arvoreRN, noRN, valor);     
            noRN->direita->cor = Vermelho;       
        		
            return noRN->direita;
        } else {
            return addRedBlackNode(arvoreRN, noRN->direita, valor);
        }
    } else {
        comparacoes++;
        if (noRN->esquerda == arvoreRN->nulo) {
            noRN->esquerda = createRedBlackNode(arvoreRN, noRN, valor);
            noRN->esquerda->cor = Vermelho;
            
            return noRN->esquerda;
        } else {
            return addRedBlackNode(arvoreRN, noRN->esquerda, valor);
        }
    }
}

NoRN* insertRedBlack(ArvoreRN* arvoreRN, int valor) {
    comparacoes++;
    if (isRedBlackEmpty(arvoreRN)) {
        arvoreRN->raiz = createRedBlackNode(arvoreRN, arvoreRN->nulo, valor);
        arvoreRN->raiz->cor = Preto;
        	
        return arvoreRN->raiz;
    } else {
        NoRN* noRN = addRedBlackNode(arvoreRN, arvoreRN->raiz, valor);
        balanceRedBlack(arvoreRN, noRN);
        
        return noRN;
    }
}

void removeRedBlack(ArvoreRN* arvoreRN, int valor) {
    NoRN* no = locateRedBlack(arvoreRN, valor);

    comparacoes++;
    if (no != NULL) {
        while (1) {
            comparacoes++;
            if (no->esquerda == arvoreRN->nulo && no->direita == arvoreRN->nulo) {
                comparacoes++;
                if (no->pai == arvoreRN->nulo) {
                    arvoreRN->raiz = arvoreRN->nulo;
                } else if (no == no->pai->esquerda) {
                    no->pai->esquerda = arvoreRN->nulo;
                } else {
                    no->pai->direita = arvoreRN->nulo;
                }

                free(no);
                break;
            } else if (no->esquerda != arvoreRN->nulo && no->direita != arvoreRN->nulo) {
                NoRN* sucessor = no->direita;
                comparacoes++;
                while (sucessor->esquerda != arvoreRN->nulo) {
                    comparacoes++;
                    sucessor = sucessor->esquerda;
                }

                no->valor = sucessor->valor;
                no = sucessor;
            } else {
                comparacoes++;
                NoRN* filho = (no->esquerda != arvoreRN->nulo) ? no->esquerda : no->direita;
                filho->pai = no->pai;

                comparacoes++;
                if (no->pai == arvoreRN->nulo) {
                    arvoreRN->raiz = filho;
                } else if (no == no->pai->esquerda) {
                    no->pai->esquerda = filho;
                } else {
                    no->pai->direita = filho;
                }

                free(no);
                break;
            }
        }

        balanceRedBlack(arvoreRN, arvoreRN->raiz);
    }
}

static NoRN* locateRedBlack(ArvoreRN* arvoreRN, int valor) {
    comparacoes++;
    if (!isRedBlackEmpty(arvoreRN)) {
        NoRN* noRN = arvoreRN->raiz;

        comparacoes++;
        while (noRN != arvoreRN->nulo) {
            comparacoes++;
            comparacoes++;
            if (noRN->valor == valor) {
                return noRN;
            } else {
                noRN = valor < noRN->valor ? noRN->esquerda : noRN->direita;
            }
        }
    }

    return NULL;
}

void traverseDepthInOrder(ArvoreRN* arvoreRN, NoRN* noRN, void (*callback)(int)) {
    comparacoes++;
    if (noRN != arvoreRN->nulo) {
        traverseDepthInOrder(arvoreRN, noRN->esquerda,callback);
        callback(noRN->valor);
        traverseDepthInOrder(arvoreRN, noRN->direita,callback);
    }
}

void traverseDepthPreOrder(ArvoreRN* arvoreRN, NoRN* noRN, void (*callback)(int)) {
    comparacoes++;
    if (noRN != arvoreRN->nulo) {
        callback(noRN->valor);
        traverseDepthPreOrder(arvoreRN, noRN->esquerda,callback);
        traverseDepthPreOrder(arvoreRN, noRN->direita,callback);
    }
}

void traverseDepthPostOrder(ArvoreRN* arvoreRN, NoRN* noRN, void (callback)(int)) {
    comparacoes++;
    if (noRN != arvoreRN->nulo) {
        traverseDepthPostOrder(arvoreRN, noRN->esquerda,callback);
        traverseDepthPostOrder(arvoreRN, noRN->direita,callback);
        callback(noRN->valor);
    }
}

void visitRedBlack(int valor){
    printf("%d ", valor);
}

static void balanceRedBlack(ArvoreRN* arvoreRN, NoRN* noRN) {
    comparacoes++;
    while (noRN->pai != NULL && noRN->pai->cor == Vermelho) {
        comparacoes++;
        comparacoes++;
        if (noRN->pai == noRN->pai->pai->esquerda) {
            NoRN *tio = noRN->pai->pai->direita;
            
            comparacoes++;
            if (tio->cor == Vermelho) {
                tio->cor = Preto;
                noRN->pai->cor = Preto; 

                noRN->pai->pai->cor = Vermelho;
                noRN = noRN->pai->pai;
            } else {
                comparacoes++;
                if (noRN == noRN->pai->direita) {
                    noRN = noRN->pai;
                    rotateLeftRedBlack(arvoreRN, noRN);
                } else {
                    noRN->pai->cor = Preto; 
                    noRN->pai->pai->cor = Vermelho;
                    rotateRightRedBlack(arvoreRN, noRN->pai->pai);
                }
            }
        } else {
            NoRN *tio = noRN->pai->pai->esquerda;
            
            comparacoes++;
            if (tio->cor == Vermelho) {
                tio->cor = Preto;
                noRN->pai->cor = Preto; 

                noRN->pai->pai->cor = Vermelho;
                noRN = noRN->pai->pai;
            } else {
                comparacoes++;
                if (noRN == noRN->pai->esquerda) {
                    noRN = noRN->pai;
                    rotateRightRedBlack(arvoreRN, noRN);
                } else {
                    noRN->pai->cor = Preto; 
                    noRN->pai->pai->cor = Vermelho;
                    rotateLeftRedBlack(arvoreRN, noRN->pai->pai);
                }
            }
        }
    }
    arvoreRN->raiz->cor = Preto;
}

static void rotateLeftRedBlack(ArvoreRN* arvoreRN, NoRN* noRN) {
    NoRN* direita = noRN->direita;
    noRN->direita = direita->esquerda; 

    comparacoes++;
    if (direita->esquerda != arvoreRN->nulo) {
        direita->esquerda->pai = noRN;
    }

    direita->pai = noRN->pai;
    
    comparacoes++;
    if (noRN->pai == arvoreRN->nulo) {
        arvoreRN->raiz = direita;
    } else if (noRN == noRN->pai->esquerda) {
        noRN->pai->esquerda = direita;
    } else {
        noRN->pai->direita = direita;
    }

    direita->esquerda = noRN;
    noRN->pai = direita;
}

static void rotateRightRedBlack(ArvoreRN* arvoreRN, NoRN* noRN) {
    NoRN* esquerda = noRN->esquerda;
    noRN->esquerda = esquerda->direita;
    
    comparacoes++;
    if (esquerda->direita != arvoreRN->nulo) {
        esquerda->direita->pai = noRN;
    }
    
    esquerda->pai = noRN->pai;
    
    comparacoes++;
    if (noRN->pai == arvoreRN->nulo) {
        arvoreRN->raiz = esquerda;
    } else if (noRN == noRN->pai->esquerda) {
        noRN->pai->esquerda = esquerda;
    } else {
        noRN->pai->direita = esquerda;
    }
    
    esquerda->direita = noRN;
    noRN->pai = esquerda;
}

void executeInsertionRoutine(FILE *file) {
    ArvoreRN* tree = createRedBlackTree();
    int value;
    while (fscanf(file, "%d", &value) != EOF) {
        insertRedBlack(tree, value);
    }
}

void executeRemovalRoutine(FILE *file) {
    ArvoreRN* tree = createRedBlackTree();
    int value;

    while (fscanf(file, "%d", &value) != EOF) {
        insertRedBlack(tree, value);
    }

    while (fscanf(file, "%d", &value) != EOF) {
        removeRedBlack(tree, value);
    }
}