#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "puzzle.h"

// Imprime o estado 3x3
void imprimirEstado(Estado e) {
    for (int i = 0; i < 9; i++) {
        if (e.tab[i] == 0) printf("   ");
        else printf(" %d ", e.tab[i]);
        if ((i+1) % 3 == 0) printf("\n");
    }
    printf("\n");
}

// Lê estado inicial do usuário
Estado lerEstadoInicial() {
    Estado e;
    printf("Digite o estado inicial (use 0 para o espaço vazio):\n");
    for (int i = 0; i < 9; i++) scanf("%d", &e.tab[i]);
    return e;
}

// Encontra índice do zero
static int encontrarZero(Estado e) {
    for (int i = 0; i < 9; i++) if (e.tab[i] == 0) return i;
    return -1;
}

// Gera estados vizinhos
int gerarSucessores(Estado atual, Estado sucessores[4]) {
    int zero = encontrarZero(atual);
    int linha = zero / 3;
    int coluna = zero % 3;
    int count = 0;

    int movimentos[4][2] = {
        {linha - 1, coluna},
        {linha + 1, coluna},
        {linha, coluna - 1},
        {linha, coluna + 1}
    };

    for (int m = 0; m < 4; m++) {
        int nl = movimentos[m][0];
        int nc = movimentos[m][1];

        if (nl >= 0 && nl < 3 && nc >= 0 && nc < 3) {
            Estado novo = atual;
            int newZero = nl * 3 + nc;

            int temp = novo.tab[newZero];
            novo.tab[newZero] = 0;
            novo.tab[zero] = temp;

            sucessores[count++] = novo;
        }
    }

    return count;
}

// Checa se é estado final
int ehFinal(Estado e) {
    int final[9] = {1,2,3,4,5,6,7,8,0};
    for (int i = 0; i < 9; i++) if (e.tab[i] != final[i]) return 0;
    return 1;
}

// Jogo manual simples
void jogarPuzzle(Estado inicial) {
    Estado atual = inicial;

    while (!ehFinal(atual)) {
        imprimirEstado(atual);
        printf("Escolha um movimento:\n");
        printf("1 - Cima\n2 - Baixo\n3 - Esquerda\n4 - Direita\n");

        int mov;
        scanf("%d", &mov);

        Estado suc[4];
        int q = gerarSucessores(atual, suc);

        if (mov < 1 || mov > q) {
            printf("Movimento inválido!\n");
            continue;
        }

        atual = suc[mov - 1];
    }

    printf("Parabéns! Você resolveu!\n");
}