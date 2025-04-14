#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "puzzle.h"

int coordenadaValida (int l, char c, int linhas, int colunas) {
    if (c < 'a' || c > 'a' + colunas - 1 || l <= 0 || l > linhas) return 0;
    return 1;
}



void visualizarTabuleiro (IJ *InfoJogo) {
    putchar ('\n');
    for (int i = 0; i < InfoJogo -> linhas; i++) printf ("%s", InfoJogo -> Tabuleiro [i]);
    printf ("\n\n");
}



int tabuleiroValido (IJ *InfoJogo) {
    // Verifica que há informação sobre o jogo e o tabuleiro não é vazio
    if (InfoJogo == NULL || InfoJogo -> Tabuleiro == NULL) return 0;

    char c;

    for (int i = 0; i < InfoJogo -> linhas; i++) {

        for (int j = 0; j < InfoJogo -> colunas; j++) {

            c = InfoJogo -> Tabuleiro [i][j];

            // Verifica se os caracteres no tabuleiro são válidos
            if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '#')) {
                fprintf(stderr, "Erro: caractere inválido no tabuleiro (na coordenada %c%d)\n\n", j + 1 + 'a', i + 1);
                return 0;
            }
        }
    }

    return 1; 
}



void iniciarTabuleiro(ESTADO *e) {
    e -> info = malloc (sizeof (IJ));
    e -> info -> Tabuleiro = NULL;
    e -> info -> TAnteriores = malloc (sizeof (Tabuleiros));
    e -> info -> TAnteriores -> Tabuleiros = NULL;
    e -> info -> TAnteriores -> sp = 0;
    e -> info -> linhas = 0;
    e -> info -> colunas = 0;
}



void resetaTabuleiro (IJ *InfoJogo) {
    if (InfoJogo == NULL) return;
    
    int i, j;

    if (InfoJogo -> Tabuleiro != NULL) {
        for (i = 0; i < InfoJogo -> linhas; i++) 
            free (InfoJogo -> Tabuleiro [i]);
        free (InfoJogo -> Tabuleiro);
    }

    if (InfoJogo -> TAnteriores != NULL) {
        if (InfoJogo -> TAnteriores -> Tabuleiros != NULL) {
            for (i = 0; i < InfoJogo -> TAnteriores -> sp; i++) {
                if (InfoJogo -> TAnteriores -> Tabuleiros [i] != NULL) {
                    for (j = 0; j < InfoJogo -> linhas; j++) {
                        free (InfoJogo -> TAnteriores -> Tabuleiros [i][j]);
                    }
                    free (InfoJogo -> TAnteriores -> Tabuleiros [i]);
                }
            }
            free (InfoJogo -> TAnteriores -> Tabuleiros);
            InfoJogo -> TAnteriores -> Tabuleiros = NULL;
        }
        free (InfoJogo -> TAnteriores);
        InfoJogo -> TAnteriores = NULL;
    }
}