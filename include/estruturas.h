// estruturas.h
#include <assert.h>
#include "puzzle.h"

// Fila
typedef struct nodo_fila {
    Estado* estado;
    struct nodo_fila* prox;
} NodoFila;

typedef struct fila {
    NodoFila* ini;
    NodoFila* fim;
} Fila;

// Pilha
typedef struct nodo_pilha {
    Estado* estado;
    struct nodo_pilha* prox;
} NodoPilha;

typedef struct pilha {
    NodoPilha* topo;
} Pilha;

// Lista para A* (ordenada por custo)
typedef struct nodo_lista {
    Estado* estado;
    int prioridade;
    struct nodo_lista* prox;
} NodoLista;

typedef struct lista {
    NodoLista* ini;
} Lista;


// Criação
Fila* criarFila();
Pilha* criarPilha();
Lista* criarLista();

// Operações
void filaInserir(Fila* f, Estado* e);
Estado* filaRemover(Fila* f);
int filaVazia(Fila* f);

void pilhaInserir(Pilha* p, Estado* e);
Estado* pilhaRemover(Pilha* p);
int pilhaVazia(Pilha* p);

void listaInserir(Lista* l, Estado* e, int prioridade);
Estado* listaRemover(Lista* l);
int listaVazia(Lista* l);


// Interface genérica para o laço universal
// 1 = fila   2 = pilha   3 = lista ordenada
void adicionar(void* estrutura, int tipo, Estado* e, int prioridade);
Estado* remover(void* estrutura, int tipo);
int estruturaVazia(void* estrutura, int tipo);
