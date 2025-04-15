#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "puzzle.h"

bool gravar (char cmd, char *arg, ESTADO *e) {
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
            fprintf(f, "%s", info -> Tabuleiro [i]); // já inclui '\n'

        fclose (f);
        printf ("Jogo gravado em '%s'\n", arg);
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

        pushStack (e -> info -> hTabuleiros, e -> info -> Tabuleiro, e -> info -> linhas);

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

        pushStack (e -> info -> hTabuleiros, e -> info -> Tabuleiro, e -> info -> linhas);

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

        char c = arg [0]; // letra (corresponde à coluna)
        int l = atoi (arg + 1); // numero (corresponde à linha)

        if (!coordenadaValida (l, c, e -> info -> linhas, e -> info -> colunas)) {
            fprintf (stderr, "Erro: a coordenada é inválida\n\n");
            return false;
        }

        if (e -> info -> Tabuleiro [l - 1][c - 'a'] == '#') {
            fprintf (stderr, "Erro: a coordenada %c%d já é vazia\n\n", c, l);
            return false;
        }

        e -> info -> Tabuleiro [l - 1][c - 'a'] = '#';
        visualizarTabuleiro (e -> info);

        pushStack (e -> info -> hTabuleiros, e -> info -> Tabuleiro, e -> info -> linhas);

        return true;
    }
    
    return false;
}



bool listarComandos (char cmd, char *arg, ESTADO *e) {
    (void) e; // Ignora o parâmetro e para evitar o warning de "unused parameter"

    if (cmd == 'h') {

        if (arg != NULL) {
            fprintf (stderr, "Erro: o comando listarComandos não precisa de um argumento\n\n");
            return false;
        }

        printf ("\nOs comandos do jogo são:\n"
                "g <ficheiro>: Grava o estado atual do jogo\n"
                "l <ficheiro>: Lê o estado do jogo\n"
                "b <coordenada>: Coloca a letra da casa em maiúsculas\n"
                "r <coordenada>: Coloca a casa vazia\n"
                "v: Verifica o estado do jogo e aponta todas as restrições violadas\n"
                "V <natural>: Permite ver os tabuleiros anteriores\n"
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



bool desfazerJogada (char cmd, char *arg, ESTADO *e) {
    if (cmd == 'd') {

        if (arg != NULL) {
            fprintf (stderr, "Erro: o comando desfazerJogada não precisa de um argumento\n\n");
            return false;
        }

        if (e -> info -> hTabuleiros -> sp < 2) {
            fprintf (stderr, "Erro: não há jogadas anteriores\n\n");
            return false;
        }

        for (int i = 0; i < e -> info -> linhas; i++)
            strcpy (e -> info -> Tabuleiro [i], e -> info -> hTabuleiros -> TAnteriores [e -> info -> hTabuleiros -> sp - 2][i]);

        popStack (e -> info -> hTabuleiros, e -> info -> linhas);

        visualizarTabuleiro (e -> info);

        return true;
    }

    return false;
}




bool vizualizarStack (char cmd, char *arg, ESTADO *e) {
    if (cmd == 'V') {

        if (arg == NULL) {
            fprintf (stderr, "Erro: o comando V precisa de um argumento (número natural)\n\n");
            return false;
        }

        int q = atoi (arg);

        if (q < 1) {
            fprintf (stderr, "Erro: o argumento deve ser um número natural\n\n");
            return false;
        }

        if (q > e -> info -> hTabuleiros -> sp) {
            fprintf (stderr, "Erro: o argumento é maior que o número de jogadas\n\n");
            return false;
        }

        vizualizaUltimosTabuleiros (e -> info -> hTabuleiros, e -> info -> linhas, e -> info -> colunas, q);

        return true;
    }

    return false;
}



bool verifica (char cmd, char *arg, ESTADO *e) {
    if (cmd == 'v') {

        if (arg != NULL) {
            fprintf (stderr, "Erro: o comando verifica não precisa de um argumento\n\n");
            return false;
        }

        putchar ('\n');

        int r = 1;

        for (int i = 0; i < e -> info -> linhas; i++)
            for (int j = 0; j < e -> info -> colunas; j++) {

                if (e -> info -> Tabuleiro [i][j] == '#')
                    if (r) r = verificaHashtag (e -> info, i, j);
                    else verificaHashtag (e -> info, i, j);
                
                else if (eMaiuscula (e -> info -> Tabuleiro [i][j])) {
                    if (r) r = verificaLinhas (e -> info, e -> info -> Tabuleiro [i][j], i, j);
                    else verificaLinhas (e -> info, e -> info -> Tabuleiro [i][j], i, j);
                    if (r) r = verificaColunas (e -> info, e -> info -> Tabuleiro [i][j], i, j);
                    else verificaColunas (e -> info, e -> info -> Tabuleiro [i][j], i, j);

                }
            }

        if (r) printf ("Não há nenhuma infração\n");

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

    libertaTabuleiro (e -> info);

    iniciarTabuleiro (e);

    if (fscanf (Jogo, "%d %d", &e -> info -> linhas, &e -> info -> colunas) != 2) {
        fclose (Jogo);
        return false;
    }

    fgetc (Jogo);

    e -> info -> Tabuleiro = malloc (e -> info -> linhas * sizeof (char *));

    for (int i = 0; i < e -> info -> linhas; i++) {
        e -> info -> Tabuleiro [i] = malloc ((e -> info -> colunas + 2) * sizeof (char));
        if (fgets (e -> info -> Tabuleiro [i], e -> info -> colunas + 2, Jogo) == NULL) return false;
    }

    fclose (Jogo); 

    if (!tabuleiroValido (e -> info)) {
        fprintf (stderr, "Erro: Tabuleiro inválido\n");
        return false;
    }

    visualizarTabuleiro (e -> info);
    fprintf (stderr, "Ficheiro lido com sucesso\n");
    
    return true;
}