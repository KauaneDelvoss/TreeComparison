#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

static void b_tree_split_child(BNo *x, int i, int t);
static void b_tree_insert_nonfull(BNo *x, float k, int t);

BTree *criar_arvore_b(int t)
{
    if (t < 2)
    {
        fprintf(stderr, "Erro: A ordem 't' da Arvore B deve ser >= 2.\n");
        return NULL;
    }
    BTree *arvore = (BTree *)malloc(sizeof(BTree));
    arvore->t = t;

    BNo *raiz = (BNo *)malloc(sizeof(BNo));
    raiz->n = 0;
    raiz->folha = true;
    raiz->chaves = (float *)malloc((2 * t - 1) * sizeof(float));
    raiz->filhos = (BNo **)malloc((2 * t) * sizeof(BNo *));

    arvore->raiz = raiz;
    return arvore;
}

void inserir_arvore_b(BTree *arvore, float valor)
{
    BNo *raiz = arvore->raiz;
    int t = arvore->t;

    if (raiz->n == 2 * t - 1)
    {
        BNo *nova_raiz = (BNo *)malloc(sizeof(BNo));
        arvore->raiz = nova_raiz;
        nova_raiz->folha = false;
        nova_raiz->n = 0;
        nova_raiz->chaves = (float *)malloc((2 * t - 1) * sizeof(float));
        nova_raiz->filhos = (BNo **)malloc((2 * t) * sizeof(BNo *));
        nova_raiz->filhos[0] = raiz;

        b_tree_split_child(nova_raiz, 0, t);
        b_tree_insert_nonfull(nova_raiz, valor, t);
    }
    else
    {
        b_tree_insert_nonfull(raiz, valor, t);
    }
}

static void b_tree_split_child(BNo *x, int i, int t)
{
    BNo *y = x->filhos[i];
    BNo *z = (BNo *)malloc(sizeof(BNo));
    z->chaves = (float *)malloc((2 * t - 1) * sizeof(float));
    z->filhos = (BNo **)malloc((2 * t) * sizeof(BNo *));

    z->folha = y->folha;
    z->n = t - 1;

    for (int j = 0; j < t - 1; j++)
    {
        z->chaves[j] = y->chaves[j + t];
    }

    if (!y->folha)
    {
        for (int j = 0; j < t; j++)
        {
            z->filhos[j] = y->filhos[j + t];
        }
    }

    y->n = t - 1;

    for (int j = x->n; j >= i + 1; j--)
    {
        x->filhos[j + 1] = x->filhos[j];
    }

    x->filhos[i + 1] = z;

    for (int j = x->n - 1; j >= i; j--)
    {
        x->chaves[j + 1] = x->chaves[j];
    }

    x->chaves[i] = y->chaves[t - 1];
    x->n = x->n + 1;
}

static void b_tree_insert_nonfull(BNo *x, float k, int t)
{
    int i = x->n - 1;

    if (x->folha)
    {
        while (i >= 0 && k < x->chaves[i])
        {
            x->chaves[i + 1] = x->chaves[i];
            i--;
        }
        x->chaves[i + 1] = k;
        x->n = x->n + 1;
    }
    else
    {
        while (i >= 0 && k < x->chaves[i])
        {
            i--;
        }
        i++;

        if (x->filhos[i]->n == 2 * t - 1)
        {
            b_tree_split_child(x, i, t);
            if (k > x->chaves[i])
            {
                i++;
            }
        }
        b_tree_insert_nonfull(x->filhos[i], k, t);
    }
}

BNo *buscar_arvore_b(BNo *no, float valor)
{
    if (no == NULL)
        return NULL;

    int i = 0;
    while (i < no->n && valor > no->chaves[i])
    {
        i++;
    }

    if (i < no->n && valor == no->chaves[i])
    {
        return no;
    }

    if (no->folha)
    {
        return NULL;
    }

    return buscar_arvore_b(no->filhos[i], valor);
}

void imprimir_arvore_b(BNo *no)
{
    if (no == NULL)
        return;

    int i;
    for (i = 0; i < no->n; i++)
    {
        if (!no->folha)
        {
            imprimir_arvore_b(no->filhos[i]);
        }
        printf("%.1f ", no->chaves[i]);
    }

    if (!no->folha)
    {
        imprimir_arvore_b(no->filhos[i]);
    }
}

void liberar_arvore_b(BNo *no)
{
    if (no == NULL)
        return;

    if (!no->folha)
    {
        for (int i = 0; i <= no->n; i++)
        {
            liberar_arvore_b(no->filhos[i]);
        }
    }

    free(no->chaves);
    free(no->filhos);
    free(no);
}