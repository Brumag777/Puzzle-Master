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
            printf ("%c ", Tabuleiro [i][j]);
        
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
            if (TabInfracoes [i][j] == 2) printf ("%c ", Tabuleiro [i][j]);
            else if (TabInfracoes [i][j] == 1) printf (VERMELHO "%c " RESET, Tabuleiro [i][j]);
            else printf (VERDE "%c " RESET, Tabuleiro [i][j]);
        }
        
        // Avança para a linha seguinte
        putchar ('\n');
    }

    if (eSolucao) putchar ('\n');
}