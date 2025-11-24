#ifndef PUZZLE_H
#define PUZZLE_H
#include "estruturas.h" 

Estado* criarEstadoInicial();
void imprimirEstado(Estado *e);
int movimentar(Estado *e, char direcao);
int ehEstadoFinal(Estado *e);

Estado* clonarEstado(Estado *original);
void gerarFilhos(Container *c, Estado *atual);
void embaralhar(Estado *e, int n);
int estadosSaoIguais(Estado *a, Estado *b);
int calcularHeuristica(Estado *e);

#endif