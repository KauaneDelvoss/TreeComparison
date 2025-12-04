#include "node.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

long long comparacoes = 0;

void executeInsertionRoutine(FILE *file);
void executeRemovalRoutine(FILE *file);

Arvore* create() {
    Arvore *arvore = malloc(sizeof(Arvore));
    arvore->raiz = NULL;
  
    return arvore;
}

int isEmpty(Arvore* arvore) {
    return arvore->raiz == NULL;
}

void add(Arvore* arvore, int valor) {
    No* no = arvore->raiz;

    while (no != NULL) {
        comparacoes++;
        if (valor > no->valor) {
            comparacoes++;
            if (no->direita != NULL) {
                no = no->direita;
            } else {
                break;
            }
        } else {
            comparacoes++;
            if (no->esquerda != NULL) {
                no = no->esquerda;
            } else {
                break;
            }
        }
    }

    No* novo = malloc(sizeof(No));
    novo->valor = valor;
    novo->pai = no;
    novo->esquerda = NULL;
    novo->direita = NULL;
    novo->altura = 1;

    comparacoes++;
    if (no == NULL) {    
        arvore->raiz = novo;
    } else {
        comparacoes++;
        if (valor > no->valor) {
            no->direita = novo;
        } else {
            no->esquerda = novo;
        }
        
        balance(arvore, no);
    }
}

No* locate(No* no, int valor) {
    while (no != NULL) {
        comparacoes++;
        comparacoes++;
        if (no->valor == valor) {
            return no;
        }
        
        comparacoes++;
        no = valor < no->valor ? no->esquerda : no->direita;
    }

    return NULL;
}

void traverse(No* no, void (*callback)(int)) {
    if (no != NULL) {
        traverse(no->esquerda,callback);
        callback(no->valor);
        traverse(no->direita,callback);
    }
}

void visit(int valor){
    printf("%d ", valor);
}

void balance(Arvore* arvore, No* no) {
    comparacoes++;
    while (no != NULL) {
        comparacoes++;
        no->altura = max(height(no->esquerda), height(no->direita)) + 1;
        int fator = balanceFactor(no);

        comparacoes++;
        if (fator > 1) {
            comparacoes++;
            if (balanceFactor(no->esquerda) > 0) {
                rotateRight(arvore, no); 
            } else {
                rotateLeftRight(arvore, no);
            }
        } else if (fator < -1) {
            comparacoes++;
            if (balanceFactor(no->direita) < 0) {
                rotateLeft(arvore, no);
            } else {
                rotateRightLeft(arvore, no);
            }
        }

        no = no->pai; 
    }
}

int height(No* no){
    comparacoes++;
    return no != NULL ? no->altura : 0;
}

int balanceFactor(No* no) {
    int esquerda = 0,direita = 0;
  
    comparacoes++;
    if (no->esquerda != NULL) {
        esquerda = no->esquerda->altura;
    }

    comparacoes++;
    if (no->direita != NULL) {
        direita = no->direita->altura;
    }
  
    return esquerda - direita;
}

No* rotateLeft(Arvore* arvore, No* no) {
    No* pai = no->pai;
    No* direita = no->direita;

    comparacoes++;
    if (direita->esquerda != NULL) {
        direita->esquerda->pai = no;
    } 
  
    no->direita = direita->esquerda;
    no->pai = direita;

    direita->esquerda = no;
    direita->pai = pai;

    comparacoes++;
    if (pai == NULL) {
        arvore->raiz = direita;
    } else {
        comparacoes++;
        if (pai->esquerda == no) {
            pai->esquerda = direita;
        } else {
            pai->direita = direita;
        }
    }

    no->altura = max(height(no->esquerda), height(no->direita)) + 1;
    direita->altura = max(height(direita->esquerda), height(direita->direita)) + 1;

    return direita;
}

No* rotateRight(Arvore* arvore, No* no) {
    No* pai = no->pai;
    No* esquerda = no->esquerda;

    comparacoes++;
    if (esquerda->direita != NULL) {
        esquerda->direita->pai = no;
    } 
  
    no->esquerda = esquerda->direita;
    no->pai = esquerda;
  
    esquerda->direita = no;
    esquerda->pai = pai;

    comparacoes++;
    if (pai == NULL) {
        arvore->raiz = esquerda;
    } else {
        comparacoes++;
        if (pai->esquerda == no) {
            pai->esquerda = esquerda;
        } else {
            pai->direita = esquerda;
        }
    }

    no->altura = max(height(no->esquerda), height(no->direita)) + 1;
    esquerda->altura = max(height(esquerda->esquerda), height(esquerda->direita)) + 1;

    return esquerda;
}

No* rotateRightLeft(Arvore* arvore, No* no) {
    no->direita = rotateRight(arvore, no->direita);
    return rotateLeft(arvore, no);
}

No* rotateLeftRight(Arvore* arvore, No* no) {
    no->esquerda = rotateLeft(arvore, no->esquerda);
    return rotateRight(arvore, no);
}

void removeNode(Arvore* arvoreAVL, int valor) {
    No* no = locate(arvoreAVL->raiz, valor);

    comparacoes++;
    while (no != NULL) {
        comparacoes++;
        comparacoes++;
        if (no->esquerda == NULL && no->direita == NULL) {
            comparacoes++;
            if (no->pai == NULL) {
                arvoreAVL->raiz = NULL;
            } else {
                comparacoes++;
                if (no->pai->esquerda == no)
                    no->pai->esquerda = NULL;
                else
                    no->pai->direita = NULL;
            }
            free(no);
            break;
        } else if (no->esquerda != NULL && no->direita != NULL) {
            No* sucessor = no->direita;
            comparacoes++;
            while (sucessor->esquerda != NULL) {
                comparacoes++;
                sucessor = sucessor->esquerda;
            }

            no->valor = sucessor->valor;
            no = sucessor;
        } else {
            No* filho = (no->esquerda != NULL) ? no->esquerda : no->direita;
            filho->pai = no->pai;

            comparacoes++;
            if (no->pai == NULL) {
                arvoreAVL->raiz = filho;
            } else {
                if (no->pai->esquerda == no)
                    no->pai->esquerda = filho;
                else
                    no->pai->direita = filho;
            }

            free(no);
            break;
        }
    }

    if (no != NULL) {
        balance(arvoreAVL, arvoreAVL->raiz);
    }
}

void executeInsertionRoutine(FILE *file) {
    Arvore *arvore = create();
    int value;
    while (fscanf(file, "%d", &value) != EOF) {
       add(arvore, value);
    }
}

void executeRemovalRoutine(FILE *file) {
    Arvore *arvore = create();
    int value;

    while (fscanf(file, "%d", &value) != EOF) {
        add(arvore, value);
    }

    while (fscanf(file, "%d", &value) != EOF) {
        removeNode(arvore, value);
    }
}

int max(int a, int b) {
    comparacoes++;
    return a > b ? a : b;
}
