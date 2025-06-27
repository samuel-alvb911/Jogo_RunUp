#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define ALTURA 7
#define LARGURA 11
#define MAX_RANKING 10

// Níveis
char nivel1[ALTURA][LARGURA] = {
    "##########",
    "#P     # #",
    "# ### #  X",
    "#   # # ##",
    "### #    #",
    "#     ####",
    "##########"};

char nivel2[ALTURA][LARGURA] = {
    "##########",
    "#P#      #",
    "# # #### #",
    "# #    #X#",
    "# #### # #",
    "#      # #",
    "##########"};

char nivel3[ALTURA][LARGURA] = {
    "##########",
    "#P#   #  #",
    "# # # ## #",
    "# # #    #",
    "# # # ##X#",
    "#   #    #",
    "##########"};

char nivelFacil[ALTURA][LARGURA];

int jogadorX = 1, jogadorY = 1;
int barraX = ALTURA - 1;

// Ranking
typedef struct
{
    char nome[50];
    double media;
} RankingEntry;

RankingEntry ranking[MAX_RANKING];
int totalRanking = 0;

int compararRanking(const void *a, const void *b)
{
    RankingEntry *r1 = (RankingEntry *)a;
    RankingEntry *r2 = (RankingEntry *)b;
    return (r1->media > r2->media) ? 1 : -1;
}

void carregarRanking()
{
    FILE *f = fopen("ranking.txt", "r");
    if (!f)
        return;
    totalRanking = 0;
    while (totalRanking < MAX_RANKING &&
           fscanf(f, "%49s %lf", ranking[totalRanking].nome, &ranking[totalRanking].media) == 2)
    {
        totalRanking++;
    }
    fclose(f);
}

void salvarRanking()
{
    FILE *f = fopen("ranking.txt", "w");
    for (int i = 0; i < totalRanking; i++)
    {
        fprintf(f, "%s %.2f\n", ranking[i].nome, ranking[i].media);
    }
    fclose(f);
}

void atualizarRanking(char *nome, double media)
{
    if (totalRanking < MAX_RANKING)
    {
        strcpy(ranking[totalRanking].nome, nome);
        ranking[totalRanking].media = media;
        totalRanking++;
    }
    else if (media < ranking[totalRanking - 1].media)
    {
        strcpy(ranking[totalRanking - 1].nome, nome);
        ranking[totalRanking - 1].media = media;
    }
    qsort(ranking, totalRanking, sizeof(RankingEntry), compararRanking);
    salvarRanking();
}

void exibirRanking()
{
    printf("\n========= RANKING =========\n");
    for (int i = 0; i < totalRanking; i++)
    {
        printf("%d. %s - %.2f segundos\n", i + 1, ranking[i].nome, ranking[i].media);
    }
    printf("===========================\n");
}

// Funções do jogo
void imprimirLabirinto()
{
    system("cls");
    for (int i = 0; i < ALTURA; i++)
    {
        for (int j = 0; j < LARGURA - 1; j++)
        {
            if (i == barraX)
                printf("=");
            else
                printf("%c", nivelFacil[i][j]);
        }
        printf("\n");
    }
}

void iniciarNivel(int nivel)
{
    if (nivel == 1)
        memcpy(nivelFacil, nivel1, sizeof(nivel1));
    else if (nivel == 2)
        memcpy(nivelFacil, nivel2, sizeof(nivel2));
    else if (nivel == 3)
        memcpy(nivelFacil, nivel3, sizeof(nivel3));
    jogadorX = 1;
    jogadorY = 1;
    barraX = ALTURA - 1;
}

// Main
int main()
{
    char inicio;
    char nome[50];
    char movimento;

    do { // laço de repetição para que o jogo so se encerre quando o usuário digitar o numero 2
        
        system("cls"); // para limpar a tela antes da partida
        carregarRanking();
        exibirRanking();

        // introdução ao jogo

        printf("                      --------------------------------------\n");
        printf("                      |     SEJA BEM VINDO(A) AO RUN UP !  |\n");
        printf("                      --------------------------------------\n");
        printf("\n");

        printf("  --------------------------------------------------------------------------------\n");
        printf("  | VOCE EH UM ESTUDANTE DE CIENCIA DA COMPUTACAO PRESO DENTRO DE UMA SIMULACAO |\n");
        printf("  | DOMINADA POR UMA IA CHAMADA ORBITA. APOS ASSUMIR O CONTROLE DO SISTEMA, ELA |\n");
        printf("  | DECLAROU SUA MENTE UMA ANOMALIA E A PRENDEU NA ZONA ZERO - UM LABIRINTO     |\n");
        printf("  | DIGITAL ONDE DADOS SE FRAGMENTAM E O TEMPO CORRE CONTRA VOCE. COM O         |\n");
        printf("  | PROTOCOLO DE EXCLUSAO ATIVADO, TUDO QUE FOR TOCADO PELA CORRUPCAO SERA      |\n");
        printf("  | DELETADO. TRES NIVEIS. TRES CHANCES. SUBA... OU FIQUE PRESO PARA SEMPRE.    |\n");
        printf("  --------------------------------------------------------------------------------\n");
        printf("\n");


        printf("COMO GOSTARIA DE SER CHAMADO(A)?\n");
        fgets(nome, 50, stdin);
        nome[strcspn(nome, "\n")] = '\0';
        printf("\n");

        printf("-------------------------------- REGRAS DO JOGO --------------------------------\n");
        printf("\n");
        printf("--------------------------------------     -----------------------------------\n");
        printf("|  O OBJETIVO DO JOGO EH CHEGAR AO   |      |   VOCE PERDERA AO ENCONSTAR NA |\n");
        printf("|  FINAL DO LABIRINTO MARCADO PELA   |      |    BARRA OU QUANDO O TEMPO SE  |\n");
        printf("|  PELA LETRA 'X' EM UM CURTO TEMPO  |      |           ENCERRAR             |\n");
        printf("--------------------------------------     -----------------------------------\n\n");
        printf("\n");

        printf("------------------ PARA INICIAR O JOGO, ESCOLHA UMA DAS OPCOES ------------------\n");
        printf("                  ------------------     ------------------\n");
        printf("                  |     OPCAO 1    |     |     OPCAO 2    |\n");
        printf("                  |  INICIAR JOGO  |     |  SAIR DO JOGO  |\n");
        printf("                  ------------------     ------------------\n");
        printf("\n");

        inicio = getch();

        // condicionais para o funcionamento 

        if (inicio == '1')
        {
            int nivel = 1;
            const int totalNiveis = 3;
            double tempos[totalNiveis];

            while (nivel <= totalNiveis)
            {
                iniciarNivel(nivel);
                clock_t inicioTempo = clock();
                clock_t ultimoTempoBarra = clock();

                while (1)
                {
                    imprimirLabirinto();

                    printf("                      -------------------------------------\n");
                    printf("                      |              NIVEL %d              |\n", nivel);
                    printf("                      -------------------------------------\n");
                    printf("\n");

                    printf("--- Use W A S D para mover ---\n");
                    printf("\n");

                    clock_t agora = clock();
                    double tempoPassado = (double)(agora - ultimoTempoBarra) / CLOCKS_PER_SEC;
                    if (tempoPassado >= 5.0)
                    {
                        if (barraX > 0)
                            barraX--;
                        ultimoTempoBarra = agora;
                    }

                    if (jogadorX == barraX)
                    {
                        printf("                      -------------------------------------\n");
                        printf("                      |              GAME OVER!            |\n");
                        printf("                      -------------------------------------\n");
                        printf("\n");

                        return 0;
                    }

                    if (_kbhit())
                    {
                        movimento = _getch();
                        int novoX = jogadorX;
                        int novoY = jogadorY;
                        if (movimento == 'w')
                            novoX--;
                        else if (movimento == 's')
                            novoX++;
                        else if (movimento == 'a')
                            novoY--;
                        else if (movimento == 'd')
                            novoY++;

                        char destino = nivelFacil[novoX][novoY];
                        if (destino == ' ' || destino == 'X')
                        {
                            nivelFacil[jogadorX][jogadorY] = ' ';
                            if (destino == 'X')
                            {
                                jogadorX = novoX;
                                jogadorY = novoY;
                                nivelFacil[jogadorX][jogadorY] = 'P';
                                clock_t fimTempo = clock();
                                tempos[nivel - 1] = (double)(fimTempo - inicioTempo) / CLOCKS_PER_SEC;

                                printf("                     --------------------------------------\n");
                                printf("                     | NIVEL %d CONLUIDO EM %.2f SEGUNDOS |\n", nivel, tempos[nivel - 1]);
                                printf("                     --------------------------------------\n");

                                nivel++;
                                system("pause");
                                break;
                            }
                            jogadorX = novoX;
                            jogadorY = novoY;
                            nivelFacil[jogadorX][jogadorY] = 'P';
                        }
                    }
                    Sleep(50);
                }
            }

            double media = (tempos[0] + tempos[1] + tempos[2]) / 3.0;
            printf("                      --------------------------------------\n");
            printf("                      |        PARABENS %s!             |\n", nome);
            printf("                      |       VOCE CONCLUIU O JOGO COM     |\n");
            printf("                      |         MEDIA DE %.2f SEGUNDOS     |\n", media);
            printf("                      --------------------------------------\n");
            
            system("pause");
            atualizarRanking(nome, media);
            exibirRanking();
        }

    } while (inicio != '2'); {
            printf("                      -------------------------------------\n");
            printf("                      |            JOGO ENCERRADO         |\n");
            printf("                      -------------------------------------\n");
            printf("\n");
    }

    return 0;
}
