#include <stdio.h>
#include <stdlib.h>
#include "estruturas.h"

Container* criarContainer(int tipo) {
    Container *c = (Container*) malloc(sizeof(Container));
    if (c) {
        c->inicio = NULL;
        c->fim = NULL;
        c->tamanho = 0;
        c->tipo = tipo;
    }
    return c;
}

int containerVazio(Container *c) {
    return (c == NULL || c->inicio == NULL);//retorna 1 se vazio
}

void adicionarEstado(Container *c, Estado *e) {
    if (!c)
    {
        return;//pare tudo e saia para não dar erro fatal
    }

    //cria um novo nó
    No *novo = (No*) malloc(sizeof(No));
    novo->estado = e;
    novo->prox = NULL;

    if (c->tipo == 1) {
        novo->prox = c->inicio;//insere no inicio (pilha)
        c->inicio = novo;
        if (c->fim == NULL){
            c->fim = novo;
        }
    }
    else if (c->tipo == 2) { 
        if (c->fim != NULL) {
            c->fim->prox = novo;
        }
        c->fim = novo;
        if (c->inicio == NULL){
         c->inicio = novo;
        }
    }
    else {
        if (c->inicio == NULL || e->f < c->inicio->estado->f) {
            novo->prox = c->inicio;
            c->inicio = novo;
            if (c->fim == NULL){
                c->fim = novo;
            }//vira o primeiro
        }
        else {
            No *atual = c->inicio;

            while (atual->prox != NULL && atual->prox->estado->f <= e->f) {
                atual = atual->prox;
            }//f menor = mais urgente

            novo->prox = atual->prox;//eu aponto pro cara ruim
            atual->prox = novo;//o cara bom aponta pra mim

            if (novo->prox == NULL) {
                c->fim = novo;
            }
        }
    }
    c->tamanho++;
}

Estado* removerEstado(Container *c) {
    if (containerVazio(c)){
        return NULL;
    }

    No *temp = c->inicio;
    Estado *e = temp->estado;

    c->inicio = temp->prox;
    
    if (c->inicio == NULL) {
        c->fim = NULL;
    }

    free(temp);
    c->tamanho--;
    
    return e;
}