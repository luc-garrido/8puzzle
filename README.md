# 🧩 8-Puzzle Solver (Implementação em C)
Este repositório contém a implementação de um simulador e solucionador para o problema do **8-Puzzle**, desenvolvido como parte do Projeto Integrador (PI) 2025 do curso de Ciência de Dados e Inteligência Artificial.
O projeto foi estruturado de forma modular, separando interfaces, implementações e estruturas de dados, cumprindo os requisitos de utilização de **Listas**, **Pilhas**, **Filas** e algoritmos de busca não-recursivos (**BFS**, **IDDFS**, **A***).
---
## 📂 Arquitetura do Projeto
O código segue o padrão de separação entre cabeçalhos (`include/`) e fonte (`src/`), garantindo encapsulamento e facilidade de manutenção.
```text
   /
   ├── include/           # Contratos e Definições de Tipos
   │   ├── estruturas.h
   │   ├── puzzle.h
   │   └── busca.h
   ├── src/               # Implementação Lógica
   │   ├── estruturas.c   # Gerenciamento de memória e contêineres de dados
   │   ├── puzzle.c       # Regras de negócio do jogo (Heurísticas, Movimentos)
   │   ├── busca.c        # Algoritmos de IA e Visualização de Solução
   │   └── main.c         # Entry point, CLI e Sistema de Gamificação
   │  └── README.md
```

🛠️ Documentação Técnica dos Módulos
------------------------------------

Abaixo descrevemos a responsabilidade técnica de cada arquivo e suas principais funções.

### 1\. Núcleo de Dados (src/estruturas.c)

Responsável por abstrair a estrutura de dados utilizada pelos algoritmos de busca. Implementa um **Contêiner Genérico** que pode se comportar como Pilha, Fila ou Fila de Prioridade dependendo da flag de inicialização.

*   **Structs Principais:**
    
    *   Estado: Representa a matriz 3x3, posição do vazio (x,y), custo $g$, heurística $h$, custo total $f$ e ponteiro para o estado pai.
        
    *   Container: Estrutura que mantém os ponteiros inicio e fim da lista encadeada e o tipo da estrutura.
        
*   **Funções:**
    
    *   criarContainer(int tipo): Aloca memória e define se a estrutura será LIFO (1), FIFO (2) ou Ordenada (3).
        
    *   adicionarEstado(Container \*c, Estado \*e):
        
        *   **Se Tipo 1 (Pilha):** Insere no início ($O(1)$).
            
        *   **Se Tipo 2 (Fila):** Insere no fim ($O(1)$).
            
        *   \*_Se Tipo 3 (Fila Prioridade/A_):\*\* Insere ordenado pelo menor valor de $f$ ($O(N)$).
            
    *   removerEstado(Container \*c): Remove e retorna sempre o primeiro elemento (comportamento adaptado pela inserção).
        
    *   containerVazio(Container \*c): Verifica underflow.
        

### 2\. Regras de Negócio (src/puzzle.c)

Contém a lógica matemática e as restrições do quebra-cabeça.

*   **Funções:**
    
    *   criarEstadoInicial(): Aloca e define um estado base resolvido.
        
    *   movimentar(Estado \*e, char direcao): Atualiza a matriz 3x3 trocando o espaço vazio (0) com a peça adjacente baseada em coordenadas cartesianas. Retorna 0 se o movimento for inválido (bater na parede).
        
    *   ehEstadoFinal(Estado \*e): Compara a matriz atual com a matriz objetivo {{1,2,3},{4,5,6},{7,8,0}}.
        
    *   clonarEstado(Estado \*original): Realiza uma _Deep Copy_ do estado para gerar nós filhos sem alterar o pai.
        
    *   embaralhar(Estado \*e, int n): Executa n movimentos aleatórios válidos para garantir que o estado gerado seja solucionável (evita problemas de paridade).
        
    *   calcularHeuristica(Estado \*e): Calcula a **Distância de Manhattan** ($\\sum |x\_{atual} - x\_{alvo}| + |y\_{atual} - y\_{alvo}|$) para uso no algoritmo A\*.
        
    *   estadosSaoIguais(...): Utilitário para comparação de matrizes (usado na poda de ciclos).
        

### 3\. Motor de Inteligência Artificial (src/busca.c)

Implementa o laço principal de busca iterativa exigido no edital.

*   **Funções:**
    
    *   executarBusca(...): O loop genérico de busca.
        
        1.  Inicializa o Container adequado.
            
        2.  Enquanto não vazio: remove estado, verifica vitória, gera filhos.
            
        3.  Aplica poda simples (não gera filho igual ao pai) para evitar ciclos triviais.
            
    *   realizarBusca(...): Dispatcher que configura os parâmetros para cada estratégia:
        
        *   **BFS (Largura):** Chama executarBusca com Tipo 2 (Fila). Garante otimalidade.
            
        *   **IDDFS (Prof. Iterativa):** Loop externo que incrementa o limite de profundidade de 1 até MAX, chamando executarBusca com Tipo 1 (Pilha) a cada iteração.
            
        *   \*_A_ (A-Star):\*\* Chama executarBusca com Tipo 3 (Prioridade), utilizando $f(n) = g(n) + h(n)$.
            
    *   imprimirCaminhoLadoALado(...): Reconstrói a solução fazendo _backtracking_ pelos ponteiros pai e renderiza o passo a passo formatado horizontalmente.
        

### 4\. Interface e Gamificação (src/main.c)

Gerencia o ciclo de vida da aplicação, entrada do usuário e recursos visuais extras.

*   **Funcionalidades:**
    
    *   **Menu Interativo:** Loop principal com switch/case.
        
    *   **Validação de Input:** Funções como limparBuffer() protegem contra _buffer overflow_ ou loops infinitos caso o usuário digite caracteres em campos numéricos.
        
    *   **Modo Jogador (Game Loop):** Permite interação manual via teclado (WASD). Inclui lógica de detecção de vitória e progressão de dificuldade.
        
    *   **Easter Eggs (Boss Battle):** Implementação de artes ASCII e lógica de eventos condicionais (vitórias consecutivas acionam modos especiais de dificuldade elevada).
        

⚙️ Compilação e Execução
------------------------

O projeto utiliza apenas bibliotecas padrão do C (ANSI C99), garantindo compatibilidade com GCC, MinGW e CodeBlocks.

### Comando de Compilação (Terminal)

PowerShell

`gcc src/main.c src/puzzle.c src/estruturas.c src/busca.c -I include -o jogo.exe`

*   Flag -I include: Instrui o pré-processador a buscar headers na pasta include.
    

### Execução

PowerShell

`.\jogo.exe`

📊 Análise de Complexidade dos Algoritmos
-----------------------------------------

**Algoritmo      Estrutura de Dados      Complexidade de Tempo      Complexidade de Espaço      Observação
  BFS**          Fila (FIFO)             $O(b^d)$                   $O(b^d)$                    Encontra a solução ótima, mas alto consumo de memória.
**IDDFS**        Pilha (LIFO)            $O(b^d)$                   $O(b x d)$                  Memória linear. Recalcula estados, mas é seguro contra estouro de memória.
**A**\*          Fila de Prioridade      $O(b^d)$ (pior caso)       $O(b^d)$                    O mais eficiente na prática devido à heurística admissível (Manhattan).

_Onde $b$ é o fator de ramificação e $d$ é a profundidade da solução._

👥 Autores
----------

**Projeto Integrador 2025 - Ciência de Dados e IA**

*   **Lucas Monteiro Garrido** (RA: 25002705)
    
*   **Gabriel Falleiros** (RA: 25004456)
    
*   **Juan cesar marquez** (RA: 25009311)

*   **Lean Gabriel** (RA: xxxxxx)
