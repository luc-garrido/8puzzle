#include <stdio.h>
#include <stdlib.h>
#include "busca.h"
#include "puzzle.h"

void imprimirPecaSimples(int valor) {//imprime uma peca sem bordas
    if (valor == 0) {
        printf(" . ");
    }
    else {
        printf(" %d ", valor);
    }
}

void imprimirCaminhoLadoALado(Estado *final) {//imprime o caminho da solucao lado a lado
    int profundidade = final->g;
    Estado **historico = (Estado**) malloc(sizeof(Estado*) * (profundidade + 1));
    Estado *temp = final;
    for(int i = profundidade; i >= 0; i--) {
        historico[i] = temp;
        temp = temp->pai;
    }

    printf("\n=== CAMINHO DA SOLUCAO (%d Passos) ===\n", profundidade);

    int blocos = 5;
    for (int i = 0; i <= profundidade; i += blocos) {
        printf("\n");
        for (int k = i; k < i + blocos && k <= profundidade; k++) {
            printf("Passo %-2d     ", k); 
        }
        printf("\n");
        for (int linha = 0; linha < 3; linha++) {
            for (int k = i; k < i + blocos && k <= profundidade; k++) {
                Estado *e = historico[k];
                printf("[");
                imprimirPecaSimples(e->tabuleiro[linha][0]);
                imprimirPecaSimples(e->tabuleiro[linha][1]);
                imprimirPecaSimples(e->tabuleiro[linha][2]);
                printf("]  "); 
            }
            printf("\n");
        }
    }
    free(historico);
}

int executarBusca(Estado *inicial, int tipoEstrutura, int limiteProfundidade, int *totalVisitados) {
    Container *c = criarContainer(tipoEstrutura);
    Estado *primeiro = clonarEstado(inicial);

    if (tipoEstrutura == 3) {//A*
        primeiro->h = calcularHeuristica(primeiro);
        primeiro->f = primeiro->g + primeiro->h;
    }

    adicionarEstado(c, primeiro);
    
    while (!containerVazio(c)) {
        Estado *atual = removerEstado(c);
        (*totalVisitados)++;

        if (ehEstadoFinal(atual)) {
            system("cls");
            char *nomeAlgo;
            if (tipoEstrutura == 1){
                nomeAlgo = "Profundidade Iterativa (IDDFS)";
            }
            else if (tipoEstrutura == 2) {
                nomeAlgo = "Largura (BFS)";
            }
            else {
                nomeAlgo = "A* (A-Star com Heuristica Manhattan)";
            }
            printf("\n=== [SUCESSO] PUZZLE RESOLVIDO! ===\n");
            printf("Algoritmo...............: %s\n", nomeAlgo);
            printf("Estados visitados.......: %d\n", *totalVisitados);
            printf("Profundidade............: %d passos\n", atual->g);

            imprimirCaminhoLadoALado(atual);

            return 1;
        }
        
        if (atual->g < limiteProfundidade) {
            char movimentos[] = {'w', 's', 'a', 'd'};

            for(int i=0; i<4; i++) {
                Estado *filho = clonarEstado(atual);
                if (movimentar(filho, movimentos[i])) {
                    filho->g++;
                    if (atual->pai != NULL && estadosSaoIguais(filho, atual->pai)) {
                        free(filho); continue;
                    }

                    if (tipoEstrutura == 3) {
                        filho->h = calcularHeuristica(filho);
                        filho->f = filho->g + filho->h;
                    }

                    adicionarEstado(c, filho);
                }
                else {
                    free(filho);
                }
            }
        }
        else {
            free(atual); 
        }
    }
    return 0;
}

void realizarBusca(Estado *inicial, int tipoAlgoritmo) {
    system("cls"); 
    int visitados = 0;

    if (tipoAlgoritmo == 1) {
        printf("Iniciando Busca em LARGURA (BFS)...\n");
        executarBusca(inicial, 2, 50, &visitados);
    } 
    else if (tipoAlgoritmo == 2) {
        printf("Iniciando Busca A* (A-Star)...\n");
        executarBusca(inicial, 3, 60, &visitados); 
    }
    else {
        printf("Iniciando Busca em PROFUNDIDADE LIMITADA ITERATIVA...\n");
        int limiteMaximo = 50;
        int achou = 0;
        for (int limite = 1; limite <= limiteMaximo; limite++) {
            printf("Analisando profundidade: %d (Visitados: %d)...\r", limite, visitados);
            achou = executarBusca(inicial, 1, limite, &visitados);
            if (achou) break;
        }
        if (!achou) {
            printf("\nLimite maximo atingido sem solucao.\n");
        }
    }
}