#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

// gcc main.c -o main -Wall -Wextra -pedantic -O1 -fsanitize=address -fno-omit-frame-pointer -g

// Extras
/*
1. Se o comando é inválido é escrito "Comando inválido"
2. Existe um comando chamado "h" (de help) que lista os comandos do jogo
*/

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
    }

    // Fecha o ficheiro do jogo
    fclose (jogo);

    return 0;
}

// Verifica se uma string representa uma coordenada válida
int coordenadaValida (int l, char c, int linhas, int colunas) {
    if (c < 'a' || c > 'a' + colunas - 1) return 0;

    if (l <= 0 || l > linhas) return 0;

    return 1;
}

void gravaJogo () {
    printf ("\nGravou o jogo :)\n\n");
}

void leJogo () {
    printf ("\nLeu o jogo :)\n\n");
}

void verificaJogo () {
    printf ("\nVerificou o jogo :)\n\n");
}

void ajudaJogo () {
    printf ("\nAjudou o jogo :)\n\n");
}

void AjudaJogo () {
    printf ("\nAjudou muito o jogo :)\n\n");
}

void ResolveJogo () {
    printf ("\nResolveu o jogo :)\n\n");
}

void desfazJogada () {
    printf ("\nDesfez a jogada :)\n\n");
}

void mudaCasaParaMaiuscula (int l, char c, IJ *InfoJogo) {
    printf ("\n");
    if (InfoJogo -> Tabuleiro [l - 1][c - 'a'] != '#') InfoJogo -> Tabuleiro [l - 1][c - 'a'] -= 'a' - 'A';
}

void mudaCasaParaVazio (int l, char c, IJ *InfoJogo) {
    printf ("\n");
    InfoJogo -> Tabuleiro [l - 1][c - 'a'] = '#';
}

// Lista todos os comandos do jogo
void listaComandos () {
    printf ("\nOs comandos do jogo são: \n");
    printf ("g: Grava o estado atual do jogo\n");
    printf ("l: Lê o estado do jogo\n");
    printf ("b <coordenada>: Coloca a letra da casa em maiúsculas\n");
    printf ("r <coordenada>: Coloca a casa vazia\n");
    printf ("v: Verifica o estado do jogo e aponta todas as restrições violadas\n");
    printf ("a: Ajuda mudando todas as casas que se pode inferir no estado atual do tabuleiro\n");
    printf ("A: Invoca o comando 'a' enquanto o jogo sofre alterações\n");
    printf ("R: Resolve o jogo\n");
    printf ("d: Desfaz a última jogada\n");
    printf ("s: Termina o jogo\n");
    printf ("h: Lista todos os comandos do jogo\n\n");
}

// Projeta o tabuleiro no seu estado atual
void vizualizaTabuleiro (IJ InfoJogo) {
    for (int i = 0; i < InfoJogo.colunas; i++) printf ("%s", InfoJogo.Tabuleiro [i]);
    printf ("\n");
}

int main () {
    IJ InfoJogo;

    // Inicia o jogo
    if (iniciaJogo (&InfoJogo)) return 1;

    // Corre o jogo
    int l;
    char c;
    char s [32] = "";
    while (strcmp (s, "s")) {
        vizualizaTabuleiro (InfoJogo);

        if (scanf ("%s", s) != 1) return 1;

        if (strcmp (s, "g") == 0) gravaJogo ();
        else if (strcmp (s, "l") == 0) leJogo ();
        else if (strcmp (s, "v") == 0) verificaJogo ();
        else if (strcmp (s, "a") == 0) ajudaJogo ();
        else if (strcmp (s, "A") == 0) AjudaJogo ();
        else if (strcmp (s, "R") == 0) ResolveJogo ();
        else if (strcmp (s, "d") == 0) desfazJogada ();
        else if (strcmp (s, "b") == 0) {
            if (scanf (" %c%d", &c, &l) != 2) return 1;
            if (coordenadaValida (l, c, InfoJogo.linhas, InfoJogo.colunas)) mudaCasaParaMaiuscula (l, c, &InfoJogo);
            else printf ("\nCoordenada inválida\n\n");
        }
        else if (strcmp (s, "r") == 0) {
            if (scanf (" %c%d", &c, &l) != 2) return 1;
            if (coordenadaValida (l, c, InfoJogo.linhas, InfoJogo.colunas)) mudaCasaParaVazio (l, c, &InfoJogo);
            else printf ("\nCoordenada inválida\n\n");
        }
        else if (strcmp (s, "h") == 0) listaComandos ();
        else if (strcmp (s, "s")) printf ("\nComando inválido\n\n");
    }

    // Libera a memória alocada
    for (int i = 0; i < InfoJogo.linhas; i++) {
        free (InfoJogo.Tabuleiro[i]);
        free (InfoJogo.TabuleiroInicial[i]);
    }
    free (InfoJogo.Tabuleiro);
    free (InfoJogo.TabuleiroInicial);

    return 0;
}