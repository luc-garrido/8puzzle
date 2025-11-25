#include <stdio.h>
#include <stdlib.h>
#include "estruturas.h"

Container* criarContainer(int tipo)
{
    Container *c = (Container*) malloc(sizeof(Container));
    if (c)
    {
        c->inicio = NULL;
        c->fim = NULL;
        c->tamanho = 0;
        c->tipo = tipo;
    }
    return c;
}

int containerVazio(Container *c)
{
    if (c == NULL || c->inicio == NULL)
    {
        return 1;
    }
    return 0;
}

void adicionarEstado(Container *c, Estado *e)
{
    if (!c)
    {
        return;
    }

    No *novo = (No*) malloc(sizeof(No));
    novo->estado = e;
    novo->prox = NULL;

    if (c->tipo == 1)
    {
        novo->prox = c->inicio;
        c->inicio = novo;
        
        if (c->fim == NULL)
        {
            c->fim = novo;
        }
    }

    else if (c->tipo == 2)
    { 
        if (c->fim != NULL)
        {
            c->fim->prox = novo;
        }
        c->fim = novo;
        
        if (c->inicio == NULL)
        {
            c->inicio = novo;
        }
    }

    else
    {
        if (c->inicio == NULL || e->f < c->inicio->estado->f)
        {
            novo->prox = c->inicio;
            c->inicio = novo;
            
            if (c->fim == NULL)
            {
                c->fim = novo;
            }
        }
        else
        {
            No *atual = c->inicio;
            while (atual->prox != NULL && atual->prox->estado->f <= e->f)
            {
                atual = atual->prox;
            }

            novo->prox = atual->prox;
            atual->prox = novo;

            if (novo->prox == NULL)
            {
                c->fim = novo;
            }
        }
    }
    c->tamanho++;
}

Estado* removerEstado(Container *c)
{
    if (containerVazio(c))
    {
        return NULL;
    }

    No *temp = c->inicio;
    Estado *e = temp->estado;

    c->inicio = temp->prox;
    
    if (c->inicio == NULL)
    {
        c->fim = NULL;
    }

    free(temp);
    c->tamanho--;
    
    return e;
}