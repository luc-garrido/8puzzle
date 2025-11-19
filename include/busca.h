// busca.h
#include <assert.h>
#include "puzzle.h"
#include "estruturas.h"

void buscaLargura(Estado* inicial);
void buscaProfundidade(Estado* inicial, int limite);
void buscaIDDFS(Estado* inicial);
void buscaAEstrela(Estado* inicial);

void mostrarSolucao(Estado* objetivo);
