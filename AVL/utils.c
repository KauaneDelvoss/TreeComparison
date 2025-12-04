#include "node.h"
#include <stdio.h>
#include <stdlib.h>

No *criarNo(float valor)
{
    No *novo = (No *)malloc(sizeof(No));
    novo->value = valor;
    novo->esquerda = NULL;
    novo->direita = NULL;
    novo->pai = NULL;
    return novo;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int altura(No *no)
{
    if (no == NULL) {
        return 0;
    }

    return 1 + max(altura(no->esquerda), altura(no->direita));
}

int fb(No *no)
{
    if (no == NULL) {
        return 0;
    }
    return altura(no->esquerda) - altura(no->direita);
}

No *rse(No *no)
{
    No *direita = no->direita;
    No *subEsqDaDireita = direita->esquerda;

    direita->esquerda = no;
    no->direita = subEsqDaDireita;

    direita->pai = no->pai;
    no->pai = direita;

    if (subEsqDaDireita != NULL) {
        subEsqDaDireita->pai = no;
    }

    return direita;
}

No *rsd(No *no)
{
    No *esquerda = no->esquerda;
    No *subDirDaEsquerda = esquerda->direita;

    esquerda->direita = no;
    no->esquerda = subDirDaEsquerda;

    esquerda->pai = no->pai;
    no->pai = esquerda;

    if (subDirDaEsquerda != NULL) {
        subDirDaEsquerda->pai = no;
    }

    return esquerda;
}

No *balancear(No *no)
{
    int fator = fb(no);

    if (fator > 1) {

        if (fb(no->esquerda) < 0) {
            no->esquerda = rse(no->esquerda);
        }
        return rsd(no);
    }

    if (fator < -1) {

        if (fb(no->direita) > 0) {
            no->direita = rsd(no->direita);
        }
        return rse(no);
    }

    return no;
}

No *inserir(No *no, float valor)
{

    if (no == NULL) {
        return criarNo(valor);
    }

    if (valor < no->value) {
        No *filhoEsquerdo = inserir(no->esquerda, valor);
        no->esquerda = filhoEsquerdo;
        filhoEsquerdo->pai = no;
    } else if (valor > no->value) {
        No *filhoDireito = inserir(no->direita, valor);
        no->direita = filhoDireito;
        filhoDireito->pai = no;
    } else {
        return no;
    }

    return balancear(no);
}

No *remover(No *raiz, float valor)
{

    if (raiz == NULL)
        return raiz;

    if (valor < raiz->value) {
        raiz->esquerda = remover(raiz->esquerda, valor);

        if (raiz->esquerda != NULL){
            raiz->esquerda->pai = raiz;
        }
    } else if (valor > raiz->value) {
        raiz->direita = remover(raiz->direita, valor);

        if (raiz->direita != NULL) {
            raiz->direita->pai = raiz;
        }
    } else {

        if ((raiz->esquerda == NULL) || (raiz->direita == NULL)) {
            No *temp = raiz->esquerda ? raiz->esquerda : raiz->direita;

            if (temp == NULL) {
                temp = raiz;
                raiz = NULL;
            } else {

                temp->pai = raiz->pai;

                No *toFree = raiz;
                raiz = temp;
                free(toFree);
                temp = NULL;
            }

            if (temp != NULL) {
                free(temp);
            }
        } else {
            No *temp = encontrarMinimo(raiz->direita);

            raiz->value = temp->value;

            raiz->direita = remover(raiz->direita, temp->value);
            
            if (raiz->direita != NULL) {
                raiz->direita->pai = raiz;
            }
        }
    }

    if (raiz == NULL) {
        return raiz;
    }

    return balancear(raiz);
}

void imprimirEmOrdem(No *no)
{
    if (no != NULL) {
        imprimirEmOrdem(no->esquerda);
        printf("%.1f ", no->value);
        imprimirEmOrdem(no->direita);
    }
}

No *encontrarMinimo(No *no)
{
    No *atual = no;

    while (atual->esquerda != NULL) {
        atual = atual->esquerda;
    }
    
    return atual;
}