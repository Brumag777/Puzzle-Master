#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "puzzle.h"

int eMaiuscula (char c) {
    return c >= 'A' && c <= 'Z';
}



int coordenadaValida (int l, char c, int linhas, int colunas) {
    if (c < 'a' || c > 'a' + colunas - 1 || l <= 0 || l > linhas) return 0;
    return 1;
}



void visualizarTabuleiro (IJ *InfoJogo) {
    int i, j;

    printf ("\n    ");

    for (j = 0; j < InfoJogo -> colunas; j++)
        printf ("%c ", 'a' + j);

    printf ("\n    ");
    for (j = 0; j < InfoJogo -> colunas; j++)
        printf ("- ");
    putchar ('\n');

    for (i = 0; i < InfoJogo -> linhas; i++) {
        printf ("%d | ", i + 1);
        for (j = 0; j < InfoJogo -> colunas; j++)
            printf ("%c ", InfoJogo -> Tabuleiro [i][j]);
        putchar ('\n');
    }
    putchar ('\n');
}



int tabuleiroValido (IJ *InfoJogo) {
    if (InfoJogo == NULL || InfoJogo -> Tabuleiro == NULL) return 0;

    char c;

    for (int i = 0; i < InfoJogo -> linhas; i++) {

        for (int j = 0; j < InfoJogo -> colunas; j++) {

            c = InfoJogo -> Tabuleiro [i][j];

            if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '#')) {
                fprintf (stderr, "Erro: caractere inválido no tabuleiro (na coordenada %c%d)\n\n", j + 1 + 'a', i + 1);
                return 0;
            }
        }
    }

    return 1; 
}



int verificaLinhas (IJ *InfoJogo, char c, int linha, int coluna) {
    int r = 1;
    
    for (int j = coluna + 1; j < InfoJogo -> colunas; j++)

        if (InfoJogo -> Tabuleiro [linha][j] == c) {
            printf ("Infração: Letra '%c' repetida na linha %d (colunas '%c' e '%c')\n", c, linha + 1, coluna + 'a', j + 'a');
            r = 0;
        }

    return r;
}




int verificaColunas (IJ *InfoJogo, char c, int linha, int coluna) {
    int r = 1;
    
    for (int i = linha + 1; i < InfoJogo -> linhas; i++)

        if (InfoJogo -> Tabuleiro [i][coluna] == c) {
            printf ("Infração: Letra '%c' repetida na coluna '%c' (linhas %d e %d)\n", c, coluna + 'a', linha + 1, i + 1);
            r = 0;
        }

    return r;
}



int verificaHashtag (IJ *InfoJogo, int linha, int coluna) {
    int r = 1;

    if (linha && !eMaiuscula (InfoJogo -> Tabuleiro [linha - 1][coluna])) {
        printf ("Infração: A casa %c%d não está pintada de branco\n", coluna + 'a', linha);
        r = 0;
    }

    if (linha + 1 < InfoJogo -> linhas && !eMaiuscula (InfoJogo -> Tabuleiro [linha + 1][coluna])) {
        printf ("Infração: A casa %c%d não está pintada de branco\n", coluna + 'a', linha + 2);
        r = 0;
    }

    if (coluna && !eMaiuscula (InfoJogo -> Tabuleiro [linha][coluna - 1])) {
        printf ("Infração: A casa %c%d não está pintada de branco\n", coluna + 'a' - 1, linha + 1);
        r = 0;
    }

    if (coluna + 1 < InfoJogo -> colunas && !eMaiuscula (InfoJogo -> Tabuleiro [linha][coluna + 1])) {
        printf ("Infração: A casa %c%d não está pintada de branco\n", coluna + 'a' + 1, linha + 1);
        r = 0;
    }

    return r;
}



void iniciarTabuleiro (ESTADO *e) {
    e -> info = malloc (sizeof (IJ));
    e -> info -> Tabuleiro = NULL;
    e -> info -> linhas = 0;
    e -> info -> colunas = 0;

    e -> info -> hTabuleiros = malloc (sizeof (HIST));
    inicializaStack (e -> info -> hTabuleiros);
}



void libertaTabuleiro (IJ *InfoJogo) {
    if (InfoJogo == NULL) return;

    if (InfoJogo -> Tabuleiro != NULL) {
        for (int i = 0; i < InfoJogo -> linhas; i++) 
            free (InfoJogo -> Tabuleiro [i]);
        free (InfoJogo -> Tabuleiro);
    }

    libertaStack (InfoJogo -> hTabuleiros, InfoJogo -> linhas);

    free (InfoJogo);
}

/*
    a b c d e
    ― ― ― ― ―
1 | a a a a a
2 | b b b b b
3 | c c c c c
4 | d d d d d
5 | e e e e e
*/