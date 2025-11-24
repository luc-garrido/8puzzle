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
    if (!c) {
        return;//pare tudo e saia para não dar erro fatal
    }

    //cria um novo nó
    No *novo = (No*) malloc(sizeof(No));
    novo->estado = e;
    novo->prox = NULL;

    if (c->tipo == 1) {
        novo->prox = c->inicio;//insere no inicio (pilha)
        c->inicio = novo;
        if (c->fim == NULL) {
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
            c->inicio = novo;//insere no início
            if (c->fim == NULL){//se for o primeiro
                c->fim = novo;//seta o fim
            }//vira o primeiro
        }
        else {
            No *atual = c->inicio;//começa do início

            while (atual->prox != NULL && atual->prox->estado->f <= e->f) {
                atual = atual->prox;//anda até achar o lugar correto
            }//f menor = mais urgente

            novo->prox = atual->prox;//eu aponto pro cara ruim
            atual->prox = novo;//o cara bom aponta pra mim

            if (novo->prox == NULL) {//se for o último
                c->fim = novo;//atualiza o fim se for o último
            }
        }
    }
    c->tamanho++;//incrementa o tamanho
}

Estado* removerEstado(Container *c) {//remove o estado conforme a estrutura
    if (containerVazio(c)){
        return NULL;//nada pra remover, se vazio
    }

    No *temp = c->inicio;//pega o nó do inicio
    Estado *e = temp->estado;//pega o estado do nó

    c->inicio = temp->prox;//avança o inicio para o próximo nó
    
    if (c->inicio == NULL) {//se a lista ficou vazia
        c->fim = NULL;//atualiza o fim também
    }

    free(temp);//libera o nó removido
    c->tamanho--;//decrementa o tamanho
    
    return e;//retorna o estado removido
}