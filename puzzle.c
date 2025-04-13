#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "puzzle.h"

// Comandos

bool gravar (char cmd, char *arg, ESTADO *e) {
    (void) e;  // Ignora o parâmetro e para evitar o warning de "unused parameter"

    if (cmd == 'g') {

        if (arg == NULL) {
            fprintf (stderr, "Erro: o comando g precisa de um argumento\n\n");
            return false;
        }

        FILE *f = fopen (arg, "w");

        if (f == NULL) {
            fprintf (stderr, "Erro ao abrir o ficheiro para escrita\n\n");
            return false;
        }

        IJ *info = e -> info;
        fprintf (f, "%d %d\n", info -> linhas, info -> colunas);
        for (int i = 0; i < info -> linhas; i++)
            fprintf(f, "%s", info->Tabuleiro[i]); // já inclui '\n'

        fclose(f);
        printf("Jogo gravado em '%s'\n", arg);
        putchar ('\n');
        return true;
    }

    return false;
}



bool ler (char cmd, char *arg, ESTADO *e) {
    if (cmd == 'l') {
        if (arg == NULL) {
            fprintf (stderr, "Erro: o comando l precisa de um argumento\n\n");
            return false;
        }

        auxLer (e, arg);
        putchar ('\n');
        return true;
    }

    return false;
}



bool sair (char cmd, char *arg, ESTADO *e) {
    if (arg == NULL && cmd == 's') {
        e -> looping = false;
        return true;
    } 
    
    return false;
}



bool mudarParaMaiuscula (char cmd, char *arg, ESTADO *e) {
    if (cmd == 'b') {

        if (arg == NULL) {
            fprintf (stderr, "Erro: o comando b precisa de um argumento (coordenada)\n\n");
            return false;
        }

        char c = arg [0]; // letra (corresponde à coluna)
        int l = atoi (arg + 1); // numero (corresponde à linha)

        if (!coordenadaValida (l, c, e -> info -> linhas, e -> info -> colunas)) {
            fprintf (stderr, "Erro: a coordenada é inválida\n\n");
            return false;
        }

        if (e -> info -> Tabuleiro [l - 1][c - 'a'] == '#') {
            fprintf (stderr, "Erro: a casa %c%d não contém uma letra minúscula.\n\n", c, l);
            return false;
        }

        e -> info -> Tabuleiro [l - 1][c - 'a'] -= 'a' - 'A';
        visualizarTabuleiro (e -> info);
        return true;
    }
    
    return false;
}



bool mudarParaVazia (char cmd, char *arg, ESTADO *e) {
    if (cmd == 'r') {

        if (arg == NULL) {
            fprintf (stderr, "Erro: o comando r precisa de um argumento (coordenada)\n\n");
            return false;
        }

        char c = arg[0]; // letra (corresponde à coluna)
        int l = atoi(arg + 1); // numero (corresponde à linha)

        if (!coordenadaValida (l, c, e -> info -> linhas, e -> info -> colunas)) {
            fprintf (stderr, "Erro: a coordenada é inválida\n\n");
            return false;
        } 

        e -> info -> Tabuleiro [l - 1][c - 'a'] = '#';
        visualizarTabuleiro (e -> info);
        return true;
    }
    
    return false;
}



bool listarComandos(char cmd, char *arg, ESTADO *e) {
    (void) e; // Ignora o parâmetro e para evitar o warning de "unused parameter"

    if (cmd == 'h') {

        if (arg != NULL) {
            fprintf (stderr, "Erro: o comando listarComandos não precisa de um argumento\n\n");
            return false;
        }

        printf ("\nOs comandos do jogo são:\n"
                "g: Grava o estado atual do jogo\n"
                "l: Lê o estado do jogo\n"
                "b <coordenada>: Coloca a letra da casa em maiúsculas\n"
                "r <coordenada>: Coloca a casa vazia\n"
                "v: Verifica o estado do jogo e aponta todas as restrições violadas\n"
                "a: Ajuda mudando todas as casas que se pode inferir no estado atual do tabuleiro\n"
                "A: Invoca o comando 'a' enquanto o jogo sofre alterações\n"
                "R: Resolve o jogo\n"
                "d: Desfaz a última jogada\n"
                "s: Termina o jogo\n"
                "h: Lista todos os comandos do jogo\n");
                putchar ('\n');
        return true;
    }

    return false;
}





// Auxiliares dos comandos

bool auxLer (ESTADO *e, char *arg) {                                                            
    
    FILE *Jogo = fopen (arg, "r");

    if (Jogo == NULL) {
        fprintf(stderr, "Erro: Ficheiro inválido\n");
        return false;
    }

    libertarTabuleiro (e -> info);

    if (fscanf(Jogo, "%d %d", &e -> info -> linhas, &e -> info -> colunas) != 2) { // é necessário verificar os fscanfs?
        fclose(Jogo);
        return false;
    }

    fgetc(Jogo);

    e -> info -> Tabuleiro = malloc (e -> info -> linhas * sizeof (char *));

    for (int i = 0; i < e -> info -> linhas; i++) {
        e -> info -> Tabuleiro [i] = malloc ((e -> info -> colunas + 2) * sizeof (char));
        if (fgets (e -> info -> Tabuleiro [i], e -> info -> colunas + 2, Jogo) == NULL) return false;
    }

    fclose (Jogo); 

    if (!tabuleiroValido(e -> info)) {
        fprintf (stderr, "Erro: Tabuleiro inválido\n");
        return false;
    }

    visualizarTabuleiro(e -> info);
    fprintf (stderr, "Ficheiro lido com sucesso\n");
    
    return true;
}





// Funcoes complementares

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



void libertarTabuleiro (IJ *InfoJogo) {
    if (InfoJogo -> Tabuleiro != NULL) {
        for (int i = 0; i < InfoJogo -> linhas; i++) 
            free (InfoJogo -> Tabuleiro [i]);
        free (InfoJogo -> Tabuleiro);
    }
}



void iniciarTabuleiro(ESTADO *e) {
    e -> info = malloc (sizeof (IJ));
    e -> info -> Tabuleiro = NULL;
    e -> info -> linhas = 0;
    e -> info -> colunas = 0;
}