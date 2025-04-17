#include <stdio.h>

// Calcula quantas letras estão ligadas à letra da posição dada
int contaLetrasLigadas (int linhas, int colunas, int Tabuleiro [linhas][colunas], int l, int c) {
    if (l < 0 || l >= linhas || c < 0 || c >= colunas || Tabuleiro [l][c] == 0) return 0;

    Tabuleiro [l][c] = 0;

    return 1 + contaLetrasLigadas (linhas, colunas, Tabuleiro, l + 1, c) +
               contaLetrasLigadas (linhas, colunas, Tabuleiro, l - 1, c) +
               contaLetrasLigadas (linhas, colunas, Tabuleiro, l, c + 1) +
               contaLetrasLigadas (linhas, colunas, Tabuleiro, l, c - 1);
}

int main () {
    int Tabuleiro [5][5] = {{1, 0, 1, 1, 1},
                            {0, 1, 0, 1, 1},
                            {1, 0, 1, 0, 1},
                            {1, 1, 0, 1, 1},
                            {1, 1, 1, 1, 1}};

    printf ("%d\n", contaLetrasLigadas (5, 5, Tabuleiro, 4, 4));

    return 0;
}