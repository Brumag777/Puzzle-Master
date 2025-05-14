#include "../Puzzle.h"

// Imprime um tabuleiro
void imprimeTabuleiro (int dL, int dC, char **Tabuleiro, int nTabuleiro, int flag) {

    // Imprime o número do tabuleiro (ou 'S' caso seja a solução do jogo)
    if (nTabuleiro) { 
        if      (nTabuleiro < 9)  printf ("\n%d   ", nTabuleiro);
        else if (nTabuleiro < 99) printf ("\n%d  ", nTabuleiro);
        else                      printf ("\n%d ", nTabuleiro);
    }
    else printf ("\nA solução do jogo atual é a seguinte:\n\nS   ");

    // Imprime o índice das colunas
    if (dL > 9) putchar (' ');
    for (int j = 0; j < dC; j++) printf ("%c ", 'a' + j);
    printf ("\n    ");

    // Imprime os '-' em baixo dos índices das colunas
    if (dL > 9) putchar (' ');
    for (int j = 0; j < dC; j++) printf ("- ");
    putchar ('\n');

    // Imprime o tabuleiro linha a linha
    for (int i = 0; i < dL; i++) {

        // Imprime o índice das linhas
        if (i < 9 && dL > 9) printf ("%2d | ", i + 1);
        else printf ("%d | ", i + 1);

        // Imprime a linha atual
        for (int j = 0; j < dC; j++)
            if (eMinuscula (Tabuleiro [i][j])) printf (CINZENTO "%c " RESET, Tabuleiro [i][j]);
            else printf ("%c ", Tabuleiro [i][j]);
        
        // Avança para a linha seguinte
        putchar ('\n');
    }

    if (flag) putchar ('\n');
}



// Imprime um tabuleiro destacando as infrações
void destacaInfracoes (int dL, int dC, char **Tabuleiro, int TabInfracoes [dL][dC], int eSolucao) {

    if (eSolucao) printf ("\nA solução do jogo atual é a seguinte:\n\nS   ");
    else printf ("\nI   ");

    // Imprime o índice das colunas
    if (dL > 9) putchar (' ');
    for (int j = 0; j < dC; j++) printf ("%c ", 'a' + j);
    printf ("\n    ");

    // Imprime os '-' em baixo dos índices das colunas
    if (dL > 9) putchar (' ');
    for (int j = 0; j < dC; j++) printf ("- ");
    putchar ('\n');

    // Imprime o tabuleiro linha a linha
    for (int i = 0; i < dL; i++) {

        // Imprime o índice das linhas
        if (i < 9 && dL > 9) printf ("%2d | ", i + 1);
        else printf ("%d | ", i + 1);

        // Imprime a linha atual
        for (int j = 0; j < dC; j++) {
            if (TabInfracoes [i][j] == 2) printf (CINZENTO "%c " RESET, Tabuleiro [i][j]);
            else if (TabInfracoes [i][j] == 1) printf (VERMELHO "%c " RESET, Tabuleiro [i][j]);
            else printf (VERDE "%c " RESET, Tabuleiro [i][j]);
        }
        
        // Avança para a linha seguinte
        putchar ('\n');
    }

    if (eSolucao) putchar ('\n');
}



// Imprime os jogos e as respetivas saves existentes
void imprimeSavesJogos (int savesJogos [100][100], int nSavesJogos [100]) {

    // Avança uma linha
    putchar ('\n');

    // Percorre os jogos
    for (int i = 1; i < 100; i++) {

        // Se existir este jogo, imprime as suas saves
        if (nSavesJogos [i]) {
            printf("O jogo %d possui a(s) seguinte(s) save(s): ", i);

            // Inteiro que indica se é a primeira save ou não
            int primeira = 1;

            // Procura as saves do jogo
            for (int j = 0; j < 100; j++) {
                if (savesJogos[i][j]) {
                    if (primeira == 0) printf(", ");
                    printf("%d", j);
                    primeira = 0;
                }
            }

            // Passa para a linha seguinte
            putchar ('\n');
        }
    }

    // Avança uma linha
    putchar ('\n');
}