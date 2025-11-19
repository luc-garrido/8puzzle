// busca.c
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "busca.h"

// ==========================================================
// LAÇO UNIVERSAL (OBRIGATÓRIO PELO TRABALHO)
// tipoEstrutura:
//    1 = fila (BFS)
//    2 = pilha (DFS)
//    3 = lista ordenada (A*)
// ==========================================================

void loopBusca(void* estrutura, int tipoEstrutura, Estado* inicial, int limite) {
    adicionar(estrutura, tipoEstrutura, inicial, inicial->custo);

    while (!estruturaVazia(estrutura, tipoEstrutura)) {

        Estado* atual = remover(estrutura, tipoEstrutura);

        // Se estiver usando limite (DFS limitada)
        if (limite != -1 && atual->profundidade > limite) {
            continue;
        }

        if (ehObjetivo(atual)) {
            mostrarSolucao(atual);
            return;
        }

        Estado filhos[4];
        int total = gerarSucessores(atual, filhos);

        for (int i = 0; i < total; i++) {
            Estado* novo = malloc(sizeof(Estado));
            *novo = filhos[i];
            novo->pai = atual;

            // prioridade só importa no A*
            int prioridade = novo->custo;

            adicionar(estrutura, tipoEstrutura, novo, prioridade);
        }
    }

    printf("Sem solução.\n");
}

// ==========================================================
// BFS - Busca em Largura
// ==========================================================

void buscaLargura(Estado* inicial) {
    Fila* f = criarFila();
    loopBusca(f, 1, inicial, -1); // -1 = sem limite
}

// ==========================================================
// DFS Limitada (sem recursão!)
// ==========================================================

void buscaProfundidade(Estado* inicial, int limite) {
    Pilha* p = criarPilha();
    loopBusca(p, 2, inicial, limite);
}

// ==========================================================
// IDDFS - Busca em Profundidade Limitada Iterativa
// ==========================================================

void buscaIDDFS(Estado* inicial) {
    int limite = 0;
    int encontrado = 0;

    while (!encontrado && limite <= 50) { // 50 evita loop infinito
        Pilha* p = criarPilha();
        printf("\n--- Tentando limite %d ---\n", limite);

        adicionar(p, 2, inicial, inicial->custo);

        while (!pilhaVazia(p)) {
            Estado* atual = pilhaRemover(p);

            if (ehObjetivo(atual)) {
                mostrarSolucao(atual);
                return;
            }

            if (atual->profundidade < limite) {
                Estado filhos[4];
                int total = gerarSucessores(atual, filhos);

                for (int i = 0; i < total; i++) {
                    Estado* novo = malloc(sizeof(Estado));
                    *novo = filhos[i];
                    novo->pai = atual;

                    pilhaInserir(p, novo);
                }
            }
        }

        limite++;
    }

    printf("Sem solução.\n");
}

// ==========================================================
// A* - Algoritmo A Estrela
// ==========================================================

void buscaAEstrela(Estado* inicial) {
    Lista* l = criarLista();

    inicial->custo = heuristicaManhattan(inicial);

    adicionar(l, 3, inicial, inicial->custo);

    while (!listaVazia(l)) {
        Estado* atual = listaRemover(l);

        if (ehObjetivo(atual)) {
            mostrarSolucao(atual);
            return;
        }

        Estado filhos[4];
        int total = gerarSucessores(atual, filhos);

        for (int i = 0; i < total; i++) {
            Estado* novo = malloc(sizeof(Estado));
            *novo = filhos[i];
            novo->pai = atual;

            int h = heuristicaManhattan(novo);
            novo->custo = novo->profundidade + h;

            listaInserir(l, novo, novo->custo);
        }
    }

    printf("Sem solução.\n");
}

// ==========================================================
// Mostrar Solução (caminho do início ao objetivo)
// ==========================================================

void mostrarSolucao(Estado* objetivo) {
    Estado* caminho[200];
    int tam = 0;

    Estado* atual = objetivo;
    while (atual != NULL && tam < 200) {
        caminho[tam++] = atual;
        atual = atual->pai;
    }

    // Imprime do início ao fim
    for (int i = tam - 1; i >= 0; i--) {
        imprimirPuzzle(caminho[i]);
        printf("\n");
    }

    printf("Total de passos: %d\n", tam - 1);
}
