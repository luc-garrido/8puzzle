#include <stdio.h>
#include <stdlib.h>
#include "estruturas.h"

// Cria o container (Pode ser PILHA=1 ou FILA=2)
Container* criarContainer(int tipo) {
    Container *c = (Container*) malloc(sizeof(Container));
    if (c) {
        c->inicio = NULL;
        c->fim = NULL;
        c->tamanho = 0;
        c->tipo = tipo; // 1=Pilha, 2=Fila
    }
    return c;
}

// Verifica se está vazio
int containerVazio(Container *c) {
    return (c == NULL || c->inicio == NULL);
}

// Adiciona um estado na estrutura
// A MÁGICA ACONTECE AQUI:
// Se for PILHA: Adiciona no INÍCIO (LIFO)
// Se for FILA:  Adiciona no FIM (FIFO)
// Substitua a função adicionarEstado no src/estruturas.c

void adicionarEstado(Container *c, Estado *e) {
    if (!c) return;

    No *novo = (No*) malloc(sizeof(No));
    novo->estado = e;
    novo->prox = NULL;

    if (c->tipo == 1) { 
        // --- TIPO 1: PILHA (LIFO) ---
        novo->prox = c->inicio;
        c->inicio = novo;
        if (c->fim == NULL) c->fim = novo;

    } else if (c->tipo == 2) { 
        // --- TIPO 2: FILA (FIFO) ---
        if (c->fim != NULL) {
            c->fim->prox = novo;
        }
        c->fim = novo;
        if (c->inicio == NULL) c->inicio = novo;

    } else {
        // --- TIPO 3: FILA DE PRIORIDADE (Ordenada por menor F para o A*) ---
        
        // Caso 1: Lista vazia ou o novo é menor que o primeiro
        if (c->inicio == NULL || e->f < c->inicio->estado->f) {
            novo->prox = c->inicio;
            c->inicio = novo;
            if (c->fim == NULL) c->fim = novo; // Se era vazia, ajusta o fim
        } else {
            // Caso 2: Procura a posição correta no meio ou fim
            No *atual = c->inicio;
            // Avança enquanto houver próximo e o F do próximo for menor que o F do novo
            while (atual->prox != NULL && atual->prox->estado->f <= e->f) {
                atual = atual->prox;
            }
            // Insere depois do 'atual'
            novo->prox = atual->prox;
            atual->prox = novo;
            
            // Se inseriu no final, atualiza o ponteiro fim
            if (novo->prox == NULL) {
                c->fim = novo;
            }
        }
    }
    c->tamanho++;
}

// Remove um estado da estrutura
// Para facilitar o laço genérico, SEMPRE removemos do INÍCIO.
// Na Pilha, removemos quem acabou de entrar (Topo).
// Na Fila, removemos quem estava esperando há mais tempo (Primeiro).
Estado* removerEstado(Container *c) {
    if (containerVazio(c)) return NULL;

    No *temp = c->inicio;
    Estado *e = temp->estado;

    c->inicio = temp->prox; // Avança o início
    
    if (c->inicio == NULL) {
        c->fim = NULL; // Se esvaziou, zera o fim também
    }

    free(temp); // Libera o NÓ, mas NÃO o estado (pois vamos usá-lo)
    c->tamanho--;
    
    return e;
}