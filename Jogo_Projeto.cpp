if (inicio == '1')
{
    int nivel = 1;                      // começa no nível 1
    const int totalNiveis = 3;         // total de níveis disponíveis (fácil, médio, difícil)
    double tempos[totalNiveis];        // vetor para armazenar o tempo de cada fase

    while (nivel <= totalNiveis)
    {
        iniciarNivel(nivel);                         // carrega o labirinto correspondente ao nível atual
        clock_t inicioTempo = clock();               // marca o tempo de início da fase
        clock_t ultimoTempoBarra = clock();          // marca a última vez que a barra desceu (para controlar o tempo da queda)

        while (1)
        {
            imprimirLabirinto();

            printf("                      -------------------------------------\n");
            printf("                      |              NIVEL %d              |\n", nivel);  // mostra qual é o nível atual
            printf("                      -------------------------------------\n");
            printf("\n");

            printf("--- Use W A S D para mover ---\n");
            printf("\n");

            // Verifica se já se passou 5 segundos desde a última queda da barra
            clock_t agora = clock();
            double tempoPassado = (double)(agora - ultimoTempoBarra) / CLOCKS_PER_SEC;
            if (tempoPassado >= 5.0)
            {
                if (barraX > 0)
                    barraX--;               // move a barra para cima (aproximando do jogador)
                ultimoTempoBarra = agora;   // reinicia o tempo da última queda
            }

            // Se a barra alcançar a posição do jogador, o jogo acaba
            if (jogadorX == barraX)
            {
                printf("                      -------------------------------------\n");
                printf("                      |              GAME OVER!            |\n");
                printf("                      -------------------------------------\n");
                printf("\n");

                return 0;
            }

            // Captura e processa o movimento do jogador
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

                        clock_t fimTempo = clock();    // marca o tempo de fim da fase
                        tempos[nivel - 1] = (double)(fimTempo - inicioTempo) / CLOCKS_PER_SEC; // calcula o tempo decorrido

                        // Mostra o tempo gasto na fase atual
                        printf("                     --------------------------------------\n");
                        printf("                     | NIVEL %d CONCLUIDO EM %.2f SEGUNDOS |\n", nivel, tempos[nivel - 1]);
                        printf("                     --------------------------------------\n");

                        nivel++;    // avança para o próximo nível
                        system("pause");
                        break;
                    }

                    jogadorX = novoX;
                    jogadorY = novoY;
                    nivelFacil[jogadorX][jogadorY] = 'P';
                }
            }

            Sleep(50); // pequena pausa para evitar uso excessivo da CPU
        }
    }

    // Calcula a média de tempo dos três níveis após a conclusão do jogo
    double media = (tempos[0] + tempos[1] + tempos[2]) / 3.0;
    printf("                      --------------------------------------\n");
    printf("                      |        PARABENS %s!             |\n", nome);
    printf("                      |       VOCE CONCLUIU O JOGO COM     |\n");
    printf("                      |         MEDIA DE %.2f SEGUNDOS     |\n", media);
    printf("                      --------------------------------------\n");

    system("pause");
    atualizarRanking(nome, media);  // registra o desempenho no ranking
    exibirRanking();                // mostra o ranking atualizado
}
