#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H
#define N 3
#include <stdio.h>
#include <stdlib.h>

typedef struct Estado Estado;
typedef struct No No;
typedef struct Container Container;

struct Estado {
    int tabuleiro[N][N];
    int vazioX, vazioY;
    int g;//custo do caminho
    int f;//soma de g + h
    int h;//heuristica
    struct Estado *pai;//estado pai
};

struct No {//nó da lista ligada 
    Estado *estado;
    struct No *prox;
};

struct Container {
    No *inicio;
    No *fim;
    int tamanho;
    int tipo; 
};

Container* criarContainer(int tipo);//1-pilha,2-fila,3-prioridade
void adicionarEstado(Container *c, Estado *e);//c = container, e = estado a adicionar
Estado* removerEstado(Container *c);//remove e retorna o estado do inicio
int containerVazio(Container *c);//retorna 1 se vazio, 0 se nao
#endif