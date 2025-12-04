#include <stdlib.h>
#include "utils.h"


static void rotacaoEsquerda(No **raiz, No *no);
static void rotacaoDireita(No **raiz, No *no);
static void rebalancearInsercao(No **raiz, No *no);

void inserir(No **raiz, float valor) {
    No *novo = (No*)malloc(sizeof(No));
    novo->value = valor;
    novo->esquerda = NULL;
    novo->direita = NULL;
    novo->pai = NULL;
    novo->cor = RED;

    if (*raiz == NULL) {
        *raiz = novo;
    } else {
        No *atual = *raiz;
        No *pai = NULL;
        while (atual != NULL) {
            pai = atual;
            if (valor < atual->value) {
                atual = atual->esquerda;
            } else {
                atual = atual->direita;
            }
        }
        novo->pai = pai;
        if (valor < pai->value) {
            pai->esquerda = novo;
        } else {
            pai->direita = novo;
        }
    }
    rebalancearInsercao(raiz, novo);
}

No* remover(No *no, float valor) {
    if (no == NULL) return NULL;
    
    if (valor < no->value) {
        no->esquerda = remover(no->esquerda, valor);
    } else if (valor > no->value) {
        no->direita = remover(no->direita, valor);
    } else {
        if (no->esquerda == NULL && no->direita == NULL) {
            free(no);
            return NULL;
        }
        if (no->esquerda == NULL) {
            No *temp = no->direita;
            free(no);
            return temp;
        }
        if (no->direita == NULL) {
            No *temp = no->esquerda;
            free(no);
            return temp;
        }
        
        No *temp = no->direita;
        while (temp->esquerda != NULL) temp = temp->esquerda;
        no->value = temp->value;
        no->direita = remover(no->direita, temp->value);
    }
    
    return no;
}

void imprimirEmOrdem(No *no) {
    if (no == NULL) return;
    
    imprimirEmOrdem(no->esquerda);
    printf("%.1f(%c) ", no->value, no->cor == RED ? 'V' : 'P');
    imprimirEmOrdem(no->direita);
}

static void rebalancearInsercao(No **raiz, No *no) {
    while (no->pai != NULL && no->pai->cor == RED) {
        if (no->pai == no->pai->pai->esquerda) {
            No *tio = no->pai->pai->direita;
            if (tio != NULL && tio->cor == RED) {
                no->pai->cor = BLACK;
                tio->cor = BLACK;
                no->pai->pai->cor = RED;
                no = no->pai->pai;
            } else {
                if (no == no->pai->direita) {
                    no = no->pai;
                    rotacaoEsquerda(raiz, no);
                }
                no->pai->cor = BLACK;
                no->pai->pai->cor = RED;
                rotacaoDireita(raiz, no->pai->pai);
            }
        } else {
            No *tio = no->pai->pai->esquerda;
            if (tio != NULL && tio->cor == RED) {
                no->pai->cor = BLACK;
                tio->cor = BLACK;
                no->pai->pai->cor = RED;
                no = no->pai->pai;
            } else {
                if (no == no->pai->esquerda) {
                    no = no->pai;
                    rotacaoDireita(raiz, no);
                }
                no->pai->cor = BLACK;
                no->pai->pai->cor = RED;
                rotacaoEsquerda(raiz, no->pai->pai);
            }
        }
    }
    (*raiz)->cor = BLACK;
}

static void rotacaoEsquerda(No **raiz, No *no) {
    No *temp = no->direita;
    no->direita = temp->esquerda;
    
    if (temp->esquerda != NULL)
        temp->esquerda->pai = no;
    
    temp->pai = no->pai;
    if (no->pai == NULL)
        *raiz = temp;
    else if (no == no->pai->esquerda)
        no->pai->esquerda = temp;
    else
        no->pai->direita = temp;
    
    temp->esquerda = no;
    no->pai = temp;
}

static void rotacaoDireita(No **raiz, No *no) {
    No *temp = no->esquerda;
    no->esquerda = temp->direita;
    
    if (temp->direita != NULL)
        temp->direita->pai = no;
    
    temp->pai = no->pai;
    if (no->pai == NULL)
        *raiz = temp;
    else if (no == no->pai->direita)
        no->pai->direita = temp;
    else
        no->pai->esquerda = temp;
    
    temp->direita = no;
    no->pai = temp;
}
