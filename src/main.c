#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <time.h> // Necessário para o sorteio das frases
#include "estruturas.h"
#include "puzzle.h"
#include "busca.h"

void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// --- FRASES DO DRAGÃO ---
const char *frasesDragao[] = {
    "MEU FOGO ESTA MAIS QUENTE QUE SEU RACIOCINIO!",
    "HUMANOS SAO TÃO LENTOS... ESTOU COM FOME!",
    "VOCE CHAMA ISSO DE ESTRATEGIA?",
    "CUIDADO PARA NAO SE QUEIMAR COM TANTA BURRICE!",
    "TIC-TAC... A CAVERNA ESTA FECHANDO...",
    "JA ACABOU? AINDA NEM COMECEI A RIR.",
    "ATE UM GBLIN RESOLVERIA ISSO MAIS RAPIDO!",
    "VOCE VAI SER O MEU JANTAR OU NAO?",
    "ESTOU FICANDO ENTEDIADO...",
    "SEU MEDO TEM CHEIRO DE... FRACASSO."
};

void mostrarLogo() {
    printf(" .----------------.  .----------------. \n");
    printf("| .--------------. || .--------------. |\n");
    printf("| |     ____     | || |   ______     | |\n");
    printf("| |   .' __ '.   | || |  |_   __ \\   | |\n");
    printf("| |   | (__) |   | || |    | |__) |  | |\n");
    printf("| |   .`____'.   | || |    |  ___/   | |\n");
    printf("| |  | (____) |  | || |   _| |_      | |\n");
    printf("| |  '.______.'  | || |  |_____|     | |\n");
    printf("| '--------------' || '--------------' |\n");
    printf(" '----------------'  '----------------' \n");
    printf("      PUZZLE SOLVER - PI 2025\n");
    printf("  _____________________________________________\n\n");
}

void exibirVitoriaEpica(int nivel) {
    limparTela();
    printf("\n");
    printf("             ___________      \n");
    printf("            '._==_==_=_.'     \n");
    printf("            .-\\:      /-.    \n");
    printf("           | (|:.     |) |    \n");
    printf("            '-|:.     |-'     \n");
    printf("              \\::.    /      \n");
    printf("               '::. .'        \n");
    printf("                 ) (          \n");
    printf("               _.' '._        \n");
    printf("              `\"\"\"\"\"\"\"`       \n");
    printf("  ===================================\n");
    printf("   PARABENS! NIVEL %d COMPLETADO! \n", nivel);
    printf("  ===================================\n\n");
}

// --- TELA DE TRANSIÇÃO (DRAGÃO GIGANTE DE CORPO INTEIRO) ---
void exibirModoPesadelo() {
    limparTela();
    printf("\n");
    printf("                \\||/                     \n");
    printf("                |  @___oo                \n");
    printf("      /\\  /\\   / (__,,,,|               \n");
    printf("     ) /^\\) ^\\/ _)                       \n");
    printf("     )   /^\\/   _)                       \n");
    printf("     )   _ /  / _)                       \n");
    printf(" /\\  )/\\/ ||  | )_)                      \n");
    printf("<  >      |(,,) )__)                     \n");
    printf(" ||      /    \\)___)\\                    \n");
    printf(" | \\____(      )___) )___                \n");
    printf("  \\______(_______;;; __;;;               \n");
    printf("\n");
    printf("     [ !!! WARNING !!! ]     \n");
    printf("   ATIVANDO MODO BOSS BATTLE \n");
    printf("\n");
    printf("  VOCE ACORDOU O DRAGAO GUARDIAO...\n");
    printf("  PREPARE-SE PARA O MODO PESADELO!\n\n");
    
    printf("  PRESSIONE [ENTER] PARA A BATALHA...");
    limparBuffer(); 
    getchar(); 
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL)); // Inicializa semente aleatória
    int opcao = 0;

    do {
        limparTela();
        mostrarLogo();
        printf("  MENU PRINCIPAL:\n");
        printf("  [1] Jogar Manualmente (Modo Desafio)\n");
        printf("  [2] Resolver com IA (Autopilot)\n");
        printf("  [0] Sair\n");
        printf("\n  >> ");
        
        if (scanf("%d", &opcao) != 1) {
            printf("\n  [ERRO] Entrada invalida! Digite apenas numeros.\n");
            printf("  Pressione ENTER para tentar novamente...");
            limparBuffer(); getchar(); continue;
        }

        if(opcao == 1) {
            limparTela();
            mostrarLogo();
            Estado *jogo = criarEstadoInicial();
            char jogada;
            
            printf("  Digite a Dificuldade Inicial (Ex: 10): ");
            int dificuldadeAtual;
            while (scanf("%d", &dificuldadeAtual) != 1 || dificuldadeAtual < 0) {
                limparBuffer();
                printf("  Valor invalido! Digite um numero positivo: ");
            }
            
            int continuarJogando = 1;
            int vitoriasSeguidas = 0;

            // Loop de Progressão de Níveis
            while(continuarJogando) {
                printf("\n  Embaralhando nivel %d... Prepare-se!\n", dificuldadeAtual);
                for(int k=0; k<100000000; k++); // Delay
                
                embaralhar(jogo, dificuldadeAtual);
                
                int movimentosNaPartida = 0;
                int indiceFrase = -1;

                // Loop do Jogo Atual
                while (1) { 
                    limparTela();

                    // --- VISUAL IN-GAME E PROVOCAÇÕES ---
                    if (dificuldadeAtual >= 80) {
                        printf("  ############################################\n");
                        printf("  #      [!!!] BOSS BATTLE ATIVA [!!!]       #\n");
                        printf("  #      (Nivel %d - O Dragao vigia...)      #\n", dificuldadeAtual);
                        printf("  ############################################\n");
                        // Arte da Cabeça do Dragão
                        printf("                ,     \\    /      , \n");
                        printf("               / \\    )\\__/(     / \\ \n");
                        printf("              /   \\  (_\\  /_)   /   \\ \n");
                        printf("         ____/_____\\__\\@  @/___/_____\\____\n");
                        printf("        |             |\\../|              |\n");
                        printf("        |              \\VV/               |\n");
                        
                        // Lógica da Frase de Zoeira
                        if (movimentosNaPartida > 0 && movimentosNaPartida % 5 == 0) {
                            indiceFrase = rand() % 10; // Sorteia nova frase a cada 5 movimentos
                        }
                        
                        if (indiceFrase != -1) {
                            printf("\n  >> DRAGAO RUGE: \"%s\"\n", frasesDragao[indiceFrase]);
                        } else {
                            printf("\n  (O Dragao esta te observando em silencio...)\n");
                        }

                    } else {
                        printf("  === MODO JOGADOR (Nivel %d) ===\n", dificuldadeAtual);
                    }
                        
                    printf("\n  W A S D (Mover) | Q (Desistir)\n");
                    
                    if (vitoriasSeguidas > 0) printf("  COMBO DE VITORIAS: %d \n", vitoriasSeguidas);
                    
                    imprimirEstado(jogo);
                    
                    printf("  Sua jogada >> ");
                    scanf(" %c", &jogada);
                    jogada = tolower(jogada);

                    // --- DESISTÊNCIA COM ZOEIRA DO DRAGÃO ---
                    if (jogada == 'q') {
                        if (dificuldadeAtual >= 80) {
                            printf("\n  XXX O DRAGAO COSPIU FOGO NA SUA DESISTENCIA! XXX\n");
                            printf("  Fugindo chamuscado para o menu...\n\n");
                            printf("  [PRESSIONE ENTER PARA ACEITAR A DERROTA]");
                            limparBuffer(); getchar(); // Pausa
                        } else {
                            printf("\n  Desistindo...\n"); 
                            for(int k=0; k<300000000; k++); 
                        }
                        continuarJogando = 0; 
                        break;
                    }

                    if (jogada != 'w' && jogada != 'a' && jogada != 's' && jogada != 'd') {
                        printf("\n  [ERRO] Tecla invalida!\n  Pressione ENTER..."); limparBuffer(); getchar(); continue;
                    }
                    
                    if (!movimentar(jogo, jogada)) {
                        printf("\a\n  [OPS] Voce bateu na parede!\n  Pressione ENTER..."); limparBuffer(); getchar();
                    } else {
                        movimentosNaPartida++; // Incrementa movimento válido para ativar a zoeira
                    }

                    if (ehEstadoFinal(jogo)) {
                        vitoriasSeguidas++;
                        exibirVitoriaEpica(dificuldadeAtual);
                        
                        // GATILHO DO BOSS (3 Vitórias)
                        if (vitoriasSeguidas == 3 && dificuldadeAtual < 80) {
                            printf("\n  [!!!] VOCE ESTA IMBATIVEL! (3 vitorias seguidas)\n");
                            printf("  O DRAGAO ESTA ACORDANDO... Aceita o desafio? (S/N): ");
                            char respBoss;
                            scanf(" %c", &respBoss);
                            
                            if (tolower(respBoss) == 's') {
                                exibirModoPesadelo(); // Chama o Dragão Gigante
                                dificuldadeAtual = 80; 
                                vitoriasSeguidas = 0;  
                                break; 
                            }
                        }

                        printf("  Voce venceu o desafio de %d movimentos.\n", dificuldadeAtual);
                        printf("  Deseja aumentar a dificuldade para %d? (S/N): ", dificuldadeAtual + 5);
                        
                        char resp;
                        scanf(" %c", &resp);
                        
                        if (tolower(resp) == 's') {
                            dificuldadeAtual += 5;
                        } else {
                            continuarJogando = 0;
                        }
                        break; 
                    }
                }
            }
            free(jogo);

        } else if (opcao == 2) {
            // --- MODO IA ---
            limparTela();
            mostrarLogo();
            Estado *problema = criarEstadoInicial();
            
            printf("  Dificuldade (Movimentos de embaralhamento): ");
            int n;
            while (scanf("%d", &n) != 1 || n < 0) {
                limparBuffer(); printf("  Invalido: ");
            }
            embaralhar(problema, n);
            while(ehEstadoFinal(problema) && n > 0) embaralhar(problema, 1);

            int continuarMesmoTabuleiro = 1;
            while(continuarMesmoTabuleiro) {
                limparTela();
                printf("  --- ESTADO ATUAL DO PROBLEMA ---\n");
                printf("  (Voce pode testar varios algoritmos neste mesmo tabuleiro)\n");
                imprimirEstado(problema);
                
                printf("\n  Escolha a Inteligencia:\n");
                printf("  [1] Busca em Largura (BFS)\n");
                printf("  [2] A* (A-Star) - O mais rapido!\n");
                printf("  [3] Busca Prof. Limitada Iterativa (IDDFS)\n");
                printf("  [0] Voltar para Menu Principal\n");
                printf("  >> ");
                
                int algo;
                if (scanf("%d", &algo) != 1) {
                    limparBuffer(); algo = -1;
                }
                if (algo == 0) {
                    continuarMesmoTabuleiro = 0; 
                } else if (algo >= 1 && algo <= 3) {
                    realizarBusca(problema, algo);
                    printf("\n  Pressione ENTER para continuar testando...");
                    limparBuffer(); getchar(); 
                } else {
                    printf("\n  Opcao invalida!\n  Pressione ENTER...");
                    limparBuffer(); getchar();
                }
            }
            free(problema);

        } else if (opcao != 0) {
            printf("\n  [ERRO] Opcao %d nao existe.\n", opcao);
            printf("  Pressione ENTER...");
            limparBuffer(); getchar();
        }

    } while(opcao != 0);
    
    printf("  Encerrando... Ate mais!\n");
    return 0;
}