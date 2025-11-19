#include <stdio.h>
#include <stdlib.h>
#include <assert.h> // conforme instrução obrigatória

#include "puzzle.h"
#include "estruturas.h"
#include "busca.h"

int main() {
    int escolha;

    printf("===== 8-PUZZLE =====\n");
    printf("1 - Jogar manualmente\n");
    printf("2 - Resolver com IA\n");
    printf("Escolha: ");
    scanf("%d", &escolha);

    Estado inicial = lerEstadoInicial();

    if (escolha == 1) {
        jogarPuzzle(inicial);
    }
    else if (escolha == 2) {
        printf("Escolha a busca:\n");
        printf("1 - Busca em Largura\n");
        printf("2 - Busca em Profundidade Limitada Iterativa (IDDFS)\n");
        printf("3 - A*\n");
        printf("Escolha: ");
        int alg;
        scanf("%d", &alg);

        if (alg == 1) buscaLargura(&inicial);
        else if (alg == 2) buscaProfundidadeLimitadaIterativa(&inicial);
        else if (alg == 3) buscaAEstrela(&inicial);
        else printf("Opção inválida!\n");
    }
    else {
        printf("Opção inválida!\n");
    }

    return 0;
}