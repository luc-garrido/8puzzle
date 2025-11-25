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
    int g;
    int f;
    int h;
    struct Estado *pai;
};

struct No {
    Estado *estado;
    struct No *prox;
};

struct Container {
    No *inicio;
    No *fim;
    int tamanho;
    int tipo; 
};

Container* criarContainer(int tipo);
void adicionarEstado(Container *c, Estado *e);
Estado* removerEstado(Container *c);
int containerVazio(Container *c);
#endif