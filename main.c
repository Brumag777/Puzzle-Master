#include <stdio.h>
#include <string.h>

// gcc main.c -o main -Wall -Wextra -pedantic -O1 -fsanitize=address -fno-omit-frame-pointer -g

int iniciaJogo () {
    int linhas, colunas, i;
    FILE *arquivo;

    arquivo = fopen ("exemplo1.txt", "r");
    if (arquivo == NULL) {
        perror ("Erro ao abrir o arquivo");
        return 1;
    }

    fscanf (arquivo, "%d %d", &linhas, &colunas);

    char Tabuleiro [linhas][colunas + 1], TabuleiroInicial [linhas][colunas + 1];

    for (i = 0; i < linhas; i++) {
        fscanf (arquivo, "%s", Tabuleiro [i]);
        strcpy (TabuleiroInicial [i], Tabuleiro [i]);
        printf ("%s\n", Tabuleiro [i]);
    }

    fclose (arquivo);

    return 0;
}

int main () {
    iniciaJogo ();

    return 0;
}