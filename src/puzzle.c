#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h> // Necessário para abs() na heurística
#include "puzzle.h"

// --- IMPLEMENTAÇÃO DAS FUNÇÕES DO PUZZLE ---

Estado* criarEstadoInicial() {
    Estado *novo = (Estado*) malloc(sizeof(Estado));
    // Estado resolvido como base
    int modelo[3][3] = {{1,2,3},{4,5,6},{7,8,0}};
    
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            novo->tabuleiro[i][j] = modelo[i][j];
            
    novo->vazioX = 2; 
    novo->vazioY = 2;
    novo->g = 0; 
    novo->h = 0; 
    novo->f = 0;
    novo->pai = NULL;
    return novo;
}

void imprimirEstado(Estado *e) {
    if(!e) return;
    
    printf("\n");
    printf("   +---+---+---+\n");
    
    for(int i=0; i<3; i++){
        printf("   |"); 
        for(int j=0; j<3; j++){
            if(e->tabuleiro[i][j] == 0) 
                printf(" . "); 
            else 
                printf(" %d ", e->tabuleiro[i][j]);
            
            printf("|");
        }
        printf("\n");
        printf("   +---+---+---+\n");
    }
    printf("\n");
}

int movimentar(Estado *e, char direcao) {
    int novaLinha = e->vazioX;
    int novaColuna = e->vazioY;

    switch(direcao) {
        case 'w': case 'W': novaLinha--; break;
        case 's': case 'S': novaLinha++; break;
        case 'a': case 'A': novaColuna--; break;
        case 'd': case 'D': novaColuna++; break;
        default: return 0;
    }

    // Verifica limites do tabuleiro
    if (novaLinha < 0 || novaLinha > 2 || novaColuna < 0 || novaColuna > 2) return 0;

    // Troca as peças
    int valorPeca = e->tabuleiro[novaLinha][novaColuna];
    e->tabuleiro[e->vazioX][e->vazioY] = valorPeca;
    e->tabuleiro[novaLinha][novaColuna] = 0;
    
    // Atualiza coordenadas do vazio
    e->vazioX = novaLinha; 
    e->vazioY = novaColuna;

    return 1;
}

int ehEstadoFinal(Estado *e) {
    if (!e) return 0;
    int objetivo[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
    
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if (e->tabuleiro[i][j] != objetivo[i][j]) return 0;
            
    return 1;
}

Estado* clonarEstado(Estado *original) {
    Estado *novo = (Estado*) malloc(sizeof(Estado));
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            novo->tabuleiro[i][j] = original->tabuleiro[i][j];
            
    novo->vazioX = original->vazioX; 
    novo->vazioY = original->vazioY;
    novo->g = original->g; 
    novo->h = 0; 
    novo->f = 0;
    novo->pai = original;
    return novo;
}

int estadosSaoIguais(Estado *a, Estado *b) {
    if (!a || !b) return 0;
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            if(a->tabuleiro[i][j] != b->tabuleiro[i][j]) return 0;
    return 1;
}

// --- HEURÍSTICA MANHATTAN (PARA O A*) ---
int calcularHeuristica(Estado *e) {
    int h = 0;
    // Posição correta de cada número (0 a 8)
    // objetivoPos[1] = {0,0} significa que o numero 1 deve estar na linha 0 col 0
    int objetivoPos[9][2] = {
        {2, 2}, // 0
        {0, 0}, // 1
        {0, 1}, // 2
        {0, 2}, // 3
        {1, 0}, // 4
        {1, 1}, // 5
        {1, 2}, // 6
        {2, 0}, // 7
        {2, 1}  // 8
    };

    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            int valor = e->tabuleiro[i][j];
            if (valor != 0) { 
                int linhaAlvo = objetivoPos[valor][0];
                int colAlvo = objetivoPos[valor][1];
                // Distância = diferença absoluta das linhas + diferença absoluta das colunas
                h += abs(i - linhaAlvo) + abs(j - colAlvo);
            }
        }
    }
    return h;
}

void gerarFilhos(Container *c, Estado *atual) {
    char movimentos[] = {'w', 's', 'a', 'd'};
    
    for(int i=0; i<4; i++) {
        Estado *filho = clonarEstado(atual);
        
        if (movimentar(filho, movimentos[i])) {
            filho->g++; 
            
            // Otimização: Não volta pro pai imediato
            if (atual->pai != NULL) {
                if (estadosSaoIguais(filho, atual->pai)) {
                    free(filho); 
                    continue;
                }
            }
            
            // Se for A* (Tipo 3), precisamos do H e F, mas quem chama é o busca.c
            // Porém, se deixarmos aqui não faz mal.
            // O importante é que ADICIONAR ESTADO não está implementado aqui, apenas chamado.
            adicionarEstado(c, filho);
        } else {
            free(filho);
        }
    }
}

void embaralhar(Estado *e, int n) {
    srand(time(NULL));
    char direcoes[] = {'w', 's', 'a', 'd'};
    
    // Reseta para resolvido antes de embaralhar
    int resolvido[3][3] = {{1,2,3},{4,5,6},{7,8,0}};
    for(int i=0; i<3; i++) for(int j=0; j<3; j++) e->tabuleiro[i][j] = resolvido[i][j];
    e->vazioX = 2; e->vazioY = 2; e->g = 0; e->pai = NULL;
    
    int movimentosFeitos = 0;
    while (movimentosFeitos < n) {
        if (movimentar(e, direcoes[rand() % 4])) {
            movimentosFeitos++;
        }
    }
}