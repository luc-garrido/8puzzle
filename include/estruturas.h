#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H
#include "estruturas.h"
#include <stdio.h>
#include <stdlib.h>

#define N 3

// 1. Definimos os nomes antecipadamente (Forward Declaration)
typedef struct Estado Estado;
typedef struct No No;
typedef struct Container Container;

// 2. Definimos a Struct Estado
struct Estado {
    int tabuleiro[N][N];
    int vazioX, vazioY;
    int g;
    int f; // F = G + H (Adicionado para o A*)
    int h;
    struct Estado *pai;
};

// 3. Definimos o Nó
struct No {
    Estado *estado;
    struct No *prox;
};

// 4. Definimos o Container
struct Container {
    No *inicio;
    No *fim;
    int tamanho;
    int tipo; 
};

// 5. Protótipos das funções
Container* criarContainer(int tipo);
void adicionarEstado(Container *c, Estado *e);
Estado* removerEstado(Container *c);
int containerVazio(Container *c);

#endif