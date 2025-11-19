// puzzle.h
#include <assert.h>
#define PUZZLE_H
#include "estruturas.h"

typedef struct estado {
    int tab[9];
    int profundidade;
    int custo;
    struct estado* pai;
} Estado;

// Funções essenciais do puzzle
int ehObjetivo(Estado* e);
void imprimirPuzzle(Estado* e);
int estadosIguais(Estado* a, Estado* b);

// Sucessores
int encontrarPosVazio(Estado* e);
int gerarSucessores(Estado* e, Estado sucessores[4]);

// Heurísticas para A*
int heuristicaManhattan(Estado* e);
int heuristicaPecasFora(Estado* e);