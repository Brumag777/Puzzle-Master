#include <stdlib.h>
#include <stdio.h>
#include "jogo.h"

// Concatena três strings
void ConcatenaStrings (char *s1, char *s2, char *s3) {
    int i, t = strlen (s1);

    for (i = 0; s2 [i]; i++) s1 [t + i] = s2 [i];
    t += i;

    for (i = 0; s3 [i]; i++) s1 [t + i] = s3 [i];
    s1 [t + i] = 0;
}

// Inicia o jogo
int iniciaJogo (IJ *InfoJogo) {
    FILE *Jogo = NULL; // Ficheiro do jogo

    // Abre o ficheiro do jogo
    while (Jogo == NULL) {
        printf ("Nome do ficheiro: ");
        if (scanf ("%s", InfoJogo -> Jogo) != 1) return 1;
        printf ("\n");

        char s [32] = "Jogos/";
        ConcatenaStrings (s, InfoJogo -> Jogo, ".txt");
        strcpy (InfoJogo -> Jogo, s);

        Jogo = fopen (InfoJogo -> Jogo, "r");
        if (Jogo == NULL) printf ("Ficheiro inválido\n\n");
    }

    // Lê a quantidade de linhas e de colunas do tabuleiro
    if (fscanf (Jogo, "%d %d", &InfoJogo -> linhas, &InfoJogo -> colunas) != 2) return 1;
    fgetc (Jogo); // Descarta o '\n' após a primeira linha

    // Aloca memória para os tabuleiros
    InfoJogo -> Tabuleiro = malloc (InfoJogo -> linhas * sizeof (char *));

    // Lê o tabuleiro do jogo
    for (int i = 0; i < InfoJogo -> linhas; i++) {
        InfoJogo -> Tabuleiro [i] = malloc ((InfoJogo -> colunas + 2) * sizeof (char));

        if (fgets (InfoJogo -> Tabuleiro [i], InfoJogo -> colunas + 2, Jogo) == NULL) return 1;
    }

    // Fecha o ficheiro do jogo
    fclose (Jogo);

    return 0;
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
    printf ("h: Lista todos os comandos do jogo\n");
}



// Muda a letra para maiuscula
int mudaCasaParaMaiuscula (IJ *InfoJogo) {
    int l;
    char c;
    if (scanf (" %c%d", &c, &l) != 2) return 1;
    
    if (!coordenadaValida (l, c, InfoJogo -> linhas, InfoJogo -> colunas)) {
        printf ("\nCoordenada Inválida\n");
        return 1;
    }

    if (InfoJogo -> Tabuleiro [l - 1][c - 'a'] != '#') InfoJogo -> Tabuleiro [l - 1][c - 'a'] -= 'a' - 'A';
    return 0;
}



// Muda a letra para '#'
int mudaCasaParaVazio (IJ *InfoJogo) {
    int l;
    char c;
    if (scanf (" %c%d", &c, &l) != 2) return 1;
    
    if (!coordenadaValida (l, c, InfoJogo -> linhas, InfoJogo -> colunas)) {
        printf ("\nCoordenada Inválida\n");
        return 1;
    }

    InfoJogo -> Tabuleiro [l - 1][c - 'a'] = '#';
    return 0;
}



// Verifica se uma string representa uma coordenada válida
int coordenadaValida (int l, char c, int linhas, int colunas) {
    if (c < 'a' || c > 'a' + colunas - 1) return 0;
    if (l <= 0 || l > linhas) return 0;
    return 1;
}



// Projeta o tabuleiro no seu estado atual
void vizualizaTabuleiro (IJ InfoJogo) {
    for (int i = 0; i < InfoJogo.colunas; i++) printf ("%s", InfoJogo.Tabuleiro [i]);
    printf ("\n");
}