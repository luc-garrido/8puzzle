#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "puzzle.h"

Estado* criarEstadoInicial()
{
    Estado *novo = (Estado*) malloc(sizeof(Estado));
    int modelo[3][3] = {{1,2,3},{4,5,6},{7,8,0}};
    
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            novo->tabuleiro[i][j] = modelo[i][j];
        }
    }
            
    novo->vazioX = 2; 
    novo->vazioY = 2;
    novo->g = 0; 
    novo->h = 0; 
    novo->f = 0;
    novo->pai = NULL;
    return novo;
}

void imprimirEstado(Estado *e)
{
    if(e == NULL)
    {
        return;
    }
    
    printf("\n");
    printf("   +---+---+---+\n");
    
    for(int i=0; i<3; i++)
    {
        printf("   |"); 
        for(int j=0; j<3; j++)
        {
            if(e->tabuleiro[i][j] == 0)
            {
                printf(" . "); 
            }
            else
            {
                printf(" %d ", e->tabuleiro[i][j]);
            }
            
            printf("|");
        }
        printf("\n");
        printf("   +---+---+---+\n");
    }
    printf("\n");
}

int movimentar(Estado *e, char direcao)
{
    int novaLinha = e->vazioX;
    int novaColuna = e->vazioY;

    switch(direcao)
    {
        case 'w': case 'W': 
            novaLinha--; 
            break;
        case 's': case 'S': 
            novaLinha++; 
            break;
        case 'a': case 'A': 
            novaColuna--; 
            break;
        case 'd': case 'D': 
            novaColuna++; 
            break;
        default: 
            return 0;
    }

    if (novaLinha < 0 || novaLinha > 2 || novaColuna < 0 || novaColuna > 2)
    {
        return 0;
    }

    int valorPeca = e->tabuleiro[novaLinha][novaColuna];
    e->tabuleiro[e->vazioX][e->vazioY] = valorPeca;
    e->tabuleiro[novaLinha][novaColuna] = 0;
    
    e->vazioX = novaLinha; 
    e->vazioY = novaColuna;

    return 1;
}

int ehEstadoFinal(Estado *e)
{
    if (e == NULL)
    {
        return 0;
    }
    
    int objetivo[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
    
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if (e->tabuleiro[i][j] != objetivo[i][j])
            {
                return 0;
            }
        }
    }
            
    return 1;
}

Estado* clonarEstado(Estado *original)
{
    Estado *novo = (Estado*) malloc(sizeof(Estado));
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            novo->tabuleiro[i][j] = original->tabuleiro[i][j];
        }
    }
            
    novo->vazioX = original->vazioX; 
    novo->vazioY = original->vazioY;
    novo->g = original->g; 
    novo->h = 0; 
    novo->f = 0;
    novo->pai = original;
    return novo;
}

int estadosSaoIguais(Estado *a, Estado *b)
{
    if (a == NULL || b == NULL)
    {
        return 0;
    }
    
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            if(a->tabuleiro[i][j] != b->tabuleiro[i][j])
            {
                return 0;
            }
        }
    }
    return 1;
}

int calcularHeuristica(Estado *e)
{
    int h = 0;
    int objetivoPos[9][2] = {
        {2, 2}, {0, 0}, {0, 1},
        {0, 2}, {1, 0}, {1, 1},
        {1, 2}, {2, 0}, {2, 1}
    };

    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            int valor = e->tabuleiro[i][j];
            if (valor != 0)
            { 
                int linhaAlvo = objetivoPos[valor][0];
                int colAlvo = objetivoPos[valor][1];
                h += abs(i - linhaAlvo) + abs(j - colAlvo);
            }
        }
    }
    return h;
}

void gerarFilhos(Container *c, Estado *atual)
{
    char movimentos[] = {'w', 's', 'a', 'd'};
    
    for(int i=0; i<4; i++)
    {
        Estado *filho = clonarEstado(atual);
        
        if (movimentar(filho, movimentos[i]))
        {
            filho->g++; 
            
            if (atual->pai != NULL)
            {
                if (estadosSaoIguais(filho, atual->pai))
                {
                    free(filho); 
                    continue;
                }
            }
            adicionarEstado(c, filho);
        }
        else
        {
            free(filho);
        }
    }
}

void embaralhar(Estado *e, int n)
{
    srand(time(NULL));
    char direcoes[] = {'w', 's', 'a', 'd'};
    
    int resolvido[3][3] = {{1,2,3},{4,5,6},{7,8,0}};
    
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            e->tabuleiro[i][j] = resolvido[i][j];
        }
    }
    e->vazioX = 2; 
    e->vazioY = 2; 
    e->g = 0; 
    e->pai = NULL;
    
    int movimentosFeitos = 0;
    while (movimentosFeitos < n)
    {
        if (movimentar(e, direcoes[rand() % 4]))
        {
            movimentosFeitos++;
        }
    }
}