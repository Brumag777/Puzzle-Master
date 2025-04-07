#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct infoJogo {
    int linhas;
    int colunas;
    char **Tabuleiro;
    char **TabuleiroAnterior;
    char Jogo [32];
} IJ;

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

        Jogo = fopen (s, "r");
        if (Jogo == NULL) printf ("Ficheiro inválido\n\n");
    }

    // Lê a quantidade de linhas e de colunas do tabuleiro
    if (fscanf (Jogo, "%d %d", &InfoJogo -> linhas, &InfoJogo -> colunas) != 2) return 1;
    fgetc (Jogo); // Descarta o '\n' após a primeira linha

    // Aloca memória para os tabuleiros
    InfoJogo -> Tabuleiro = malloc (InfoJogo -> linhas * sizeof (char *)); // Tabuleiro do jogo
    InfoJogo -> TabuleiroAnterior = malloc (InfoJogo -> linhas * sizeof (char *)); // Tabuleiro inicial do jogo

    // Lê o tabuleiro do jogo
    for (int i = 0; i < InfoJogo -> linhas; i++) {
        InfoJogo -> Tabuleiro [i] = malloc ((InfoJogo -> colunas + 2) * sizeof (char));
        InfoJogo -> TabuleiroAnterior [i] = malloc ((InfoJogo -> colunas + 2) * sizeof (char));

        if (fgets (InfoJogo -> Tabuleiro [i], InfoJogo -> colunas + 2, Jogo) == NULL) return 1;
        strcpy (InfoJogo -> TabuleiroAnterior [i], InfoJogo -> Tabuleiro [i]);
    }

    // Fecha o ficheiro do jogo
    fclose (Jogo);

    return 0;
}

// Verifica se uma string representa uma coordenada válida
int coordenadaValida (int l, char c, int linhas, int colunas) {
    if (c < 'a' || c > 'a' + colunas - 1) return 0;

    if (l <= 0 || l > linhas) return 0;

    return 1;
}

void gravaJogo () {}

void leJogo () {}

void verificaJogo () {}

void ajudaJogo () {}

void AjudaJogo () {}

void ResolveJogo () {}

void desfazJogada () {}

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
    char c;
    while (c != 's') {
        vizualizaTabuleiro (InfoJogo);

        if (scanf (" %c", &c) != 1) return 1;

        if (c == 'g') gravaJogo ();
        else if (c == 'l') leJogo ();
        else if (c == 'v') verificaJogo ();
        else if (c == 'a') ajudaJogo ();
        else if (c == 'A') AjudaJogo ();
        else if (c == 'R') ResolveJogo ();
        else if (c == 'd') desfazJogada ();
        else if (c == 'b') mudaCasaParaMaiuscula (&InfoJogo);
        else if (c == 'r') mudaCasaParaVazio (&InfoJogo);
        else if (c == 'h') listaComandos ();
        else if (c != 's') printf ("\nComando inválido\n");
        printf ("\n");
    }

    // Libera a memória alocada
    for (int i = 0; i < InfoJogo.linhas; i++) {
        free (InfoJogo.Tabuleiro[i]);
        free (InfoJogo.TabuleiroAnterior[i]);
    }
    free (InfoJogo.Tabuleiro);
    free (InfoJogo.TabuleiroAnterior);

    return 0;
}