#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "puzzle.h"

void vizualizaUltimosTabuleiros (Hist h, int linhas, int colunas, int q) {
    if (q == 1) printf ("\nO último tabuleiro é: \n\n");
    else printf ("\nOs últimos %d tabuleiros são: \n\n", q);

    for (int i = h -> sp - q; i < h -> sp; i++) {

        printf ("%d   ", i + 1);
            
        for (int j = 0; j < colunas; j++) printf ("%c ", 'a' + j);

        printf ("\n    ");

        for (int j = 0; j < colunas; j++) printf ("- ");
        putchar ('\n');

        for (int j = 0; j < linhas; j++) {
            
            printf ("%d | ", j + 1);

            for (int k = 0; k < colunas; k++)
                printf ("%c ", h -> TAnteriores [i][j][k]);
            putchar ('\n');
        }
        putchar ('\n');
    }
}



void inicializaStack (Hist h) {
    h -> sp = 0;
    h -> cap = 1;
    h -> TAnteriores = malloc (sizeof (char **));
}



void pushStack (Hist h, char **novoTabuleiro, int linhas) {
    if (h -> sp == h -> cap) {
        h -> cap *= 2;

        char ***aux = realloc (h -> TAnteriores, h -> cap * (sizeof (char **)));

        h -> TAnteriores = aux;
    }

    h -> TAnteriores [h -> sp] = malloc (linhas * sizeof (char *));

    for (int i = 0; i < linhas; i++) {
        h -> TAnteriores [h -> sp][i] = malloc ((strlen (novoTabuleiro [i]) + 1) * sizeof (char));
        strcpy (h -> TAnteriores [h -> sp][i], novoTabuleiro [i]);
    }

    h -> sp++;
}



void popStack (Hist h, int linhas) {
    if (h -> sp) {
        h -> sp--;
        if (h -> TAnteriores [h -> sp] != NULL) {
            for (int i = 0; i < linhas; i++)
                if (h -> TAnteriores [h -> sp][i] != NULL)
                    free (h -> TAnteriores [h -> sp][i]);
            free (h -> TAnteriores [h -> sp]);
        }
    }
}



void libertaStack (Hist h, int linhas) {
    if (h != NULL) {
        if (h -> TAnteriores != NULL) {
            for (int i = 0; i < h -> sp; i++)
                if (h -> TAnteriores [i] != NULL) {
                    for (int j = 0; j < linhas; j++)
                        if (h -> TAnteriores [i][j] != NULL)
                            free (h -> TAnteriores [i][j]);
                    free (h -> TAnteriores [i]);
                }
            free (h -> TAnteriores);
        }
        free (h);
    }
}