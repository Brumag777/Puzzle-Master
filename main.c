#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// gcc main.c -o main -Wall -Wextra -pedantic -O1 -fsanitize=address -fno-omit-frame-pointer -g

typedef struct infoJogo {
    int linhas;
    int colunas;
    char **Tabuleiro;
    char **TabuleiroInicial;
} IJ;

int iniciaJogo (IJ *InfoJogo) {
    FILE *jogo; // Ficheiro do jogo

    // Abre o ficheiro do jogo
    jogo = fopen ("jogo1.txt", "r");
    if (jogo == NULL) return 1;

    // Lê a quantidade de linhas e de colunas do tabuleiro
    if (fscanf (jogo, "%d %d", &InfoJogo -> linhas, &InfoJogo -> colunas) != 2) return 1;
    fgetc (jogo); // Descarta o '\n' após a primeira linha

    // Aloca memória para os tabuleiros
    InfoJogo -> Tabuleiro = malloc (InfoJogo -> linhas * sizeof (char *)); // Tabuleiro do jogo
    InfoJogo -> TabuleiroInicial = malloc (InfoJogo -> linhas * sizeof (char *)); // Tabuleiro inicial do jogo

    // Lê o tabuleiro do jogo
    for (int i = 0; i < InfoJogo -> linhas; i++) {
        InfoJogo -> Tabuleiro [i] = malloc ((InfoJogo -> colunas + 2) * sizeof (char));
        InfoJogo -> TabuleiroInicial [i] = malloc ((InfoJogo -> colunas + 2) * sizeof (char));

        if (fgets (InfoJogo -> Tabuleiro [i], InfoJogo -> colunas + 2, jogo) == NULL) return 1;
        strcpy (InfoJogo -> TabuleiroInicial [i], InfoJogo -> Tabuleiro [i]);
        printf ("%s", InfoJogo -> Tabuleiro [i]);
    }

    // Fecha o ficheiro do jogo
    fclose (jogo);

    return 0;
}

int main () {
    IJ InfoJogo;

    if (iniciaJogo (&InfoJogo)) return 1;

    // Libera a memória alocada
    for (int i = 0; i < InfoJogo.linhas; i++) {
        free (InfoJogo.Tabuleiro[i]);
        free (InfoJogo.TabuleiroInicial[i]);
    }
    free (InfoJogo.Tabuleiro);
    free (InfoJogo.TabuleiroInicial);

    return 0;
}