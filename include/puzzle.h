#ifndef PUZZLE_H
#define PUZZLE_H

#include "estruturas.h" 

// Funções Básicas
Estado* criarEstadoInicial();
void imprimirEstado(Estado *e);
int movimentar(Estado *e, char direcao);
int ehEstadoFinal(Estado *e);

// Funções de Manipulação de Estado
Estado* clonarEstado(Estado *original);
void gerarFilhos(Container *c, Estado *atual);
void embaralhar(Estado *e, int n);

// --- FUNÇÕES QUE FALTAVAM ---
int estadosSaoIguais(Estado *a, Estado *b); // <--- O ERRO ERA A FALTA DISSO
int calcularHeuristica(Estado *e);          // <--- Necessário para o A*

#endif