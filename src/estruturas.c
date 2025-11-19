// estruturas.c
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "estruturas.h"

// ==========================================================
// Fila
// ==========================================================

Fila* criarFila() {
    Fila* f = (Fila*) malloc(sizeof(Fila));
    f->ini = NULL;
    f->fim = NULL;
    return f;
}

void filaInserir(Fila* f, Estado* e) {
    NodoFila* novo = (NodoFila*) malloc(sizeof(NodoFila));
    novo->estado = e;
    novo->prox = NULL;

    if (f->fim == NULL) {
        f->ini = novo;
        f->fim = novo;
    } else {
        f->fim->prox = novo;
        f->fim = novo;
    }
}

Estado* filaRemover(Fila* f) {
    if (f->ini == NULL) return NULL;

    NodoFila* aux = f->ini;
    Estado* e = aux->estado;

    f->ini = aux->prox;
    if (f->ini == NULL) {
        f->fim = NULL;
    }

    free(aux);
    return e;
}

int filaVazia(Fila* f) {
    return (f->ini == NULL);
}



// ==========================================================
// Pilha
// ==========================================================

Pilha* criarPilha() {
    Pilha* p = (Pilha*) malloc(sizeof(Pilha));
    p->topo = NULL;
    return p;
}

void pilhaInserir(Pilha* p, Estado* e) {
    NodoPilha* novo = (NodoPilha*) malloc(sizeof(NodoPilha));
    novo->estado = e;
    novo->prox = p->topo;
    p->topo = novo;
}

Estado* pilhaRemover(Pilha* p) {
    if (p->topo == NULL) return NULL;

    NodoPilha* aux = p->topo;
    Estado* e = aux->estado;

    p->topo = aux->prox;
    free(aux);

    return e;
}

int pilhaVazia(Pilha* p) {
    return (p->topo == NULL);
}



// ==========================================================
// Lista Ordenada (para A*)
// ==========================================================

Lista* criarLista() {
    Lista* l = (Lista*) malloc(sizeof(Lista));
    l->ini = NULL;
    return l;
}

void listaInserir(Lista* l, Estado* e, int prioridade) {
    NodoLista* novo = (NodoLista*) malloc(sizeof(NodoLista));
    novo->estado = e;
    novo->prioridade = prioridade;
    novo->prox = NULL;

    if (l->ini == NULL || prioridade < l->ini->prioridade) {
        novo->prox = l->ini;
        l->ini = novo;
        return;
    }

    NodoLista* atual = l->ini;

    while (atual->prox != NULL && atual->prox->prioridade <= prioridade) {
        atual = atual->prox;
    }

    novo->prox = atual->prox;
    atual->prox = novo;
}

Estado* listaRemover(Lista* l) {
    if (l->ini == NULL) return NULL;

    NodoLista* aux = l->ini;
    Estado* e = aux->estado;

    l->ini = aux->prox;
    free(aux);

    return e;
}

int listaVazia(Lista* l) {
    return (l->ini == NULL);
}



// ==========================================================
// Interface Genérica — usada pelo laço universal
// ==========================================================

void adicionar(void* estrutura, int tipo, Estado* e, int prioridade) {
    assert(estrutura != NULL);

    if (tipo == 1) {
        filaInserir((Fila*) estrutura, e);
    }
    else if (tipo == 2) {
        pilhaInserir((Pilha*) estrutura, e);
    }
    else if (tipo == 3) {
        listaInserir((Lista*) estrutura, e, prioridade);
    }
}

Estado* remover(void* estrutura, int tipo) {
    assert(estrutura != NULL);

    if (tipo == 1) {
        return filaRemover((Fila*) estrutura);
    }
    else if (tipo == 2) {
        return pilhaRemover((Pilha*) estrutura);
    }
    else if (tipo == 3) {
        return listaRemover((Lista*) estrutura);
    }

    return NULL;
}

int estruturaVazia(void* estrutura, int tipo) {
    assert(estrutura != NULL);

    if (tipo == 1) {
        return filaVazia((Fila*) estrutura);
    }
    else if (tipo == 2) {
        return pilhaVazia((Pilha*) estrutura);
    }
    else if (tipo == 3) {
        return listaVazia((Lista*) estrutura);
    }

    return 1;
}
