#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "puzzle.h"

// Imprime os últimos q elementos do histórico de tabuleiros
void visualizaUltimosTabuleiros (Hist h, int q, int flag) {

    if (flag) {
        if (q == 1) printf ("\nO último tabuleiro é: \n");
        else printf ("\nOs últimos %d tabuleiros são: \n", q);
    }
    
    putchar ('\n');

    // Para percorrer cada um dos tabuleiros
    for (int i = h -> sp - q; i < h -> sp; i++) {

        // Imprime o número do tabuleiro
        if      (i < 9)  printf ("%d   ", i + 1);
        else if (i < 99) printf ("%d  ", i + 1);
        else             printf ("%d ", i + 1);

        // Imprime o índice das colunas
        if (h -> linhas [i] > 9) putchar (' ');
        for (int j = 0; j < h -> colunas [i]; j++) 
            printf ("%c ", 'a' + j);
        printf ("\n    ");

        // Imprime os '-' em baixo dos índices das colunas
        if (h -> linhas [i] > 9) putchar (' ');
        for (int j = 0; j < h -> colunas [i]; j++)
            printf ("- ");
        putchar ('\n');

        // Para percorrer cada linha dos tabuleiros
        for (int j = 0; j < h -> linhas [i]; j++) {

            // Imprime o índice das linhas
            if (j < 9 && h -> linhas [i] > 9) printf ("%2d | ", j + 1);
            else printf ("%d | ", j + 1);

            // Para percorrer cada coluna das linhas dos tabuleiros
            for (int k = 0; k < h -> colunas [i]; k++)
                printf ("%c ", h -> TAnteriores [i][j][k]);

            putchar ('\n');
        }
        putchar ('\n');
    }
}



// Inicializa o histórico
void inicializaStack (Hist h) {
    // Não é considerado nenhum tabuleiro no início
    h -> sp = 0;

    // A capacidade inicia em 1 para podermos duplicá-la posteriormente
    h -> cap = 1;

    // Aloca memória para o elemento singular da capacidade (isto é, para um tabuleiro)
    h -> TAnteriores = malloc (sizeof (char **));

    // Aloca memória para os arrays relativos às dimensões dos tabuleiros
    h -> linhas = malloc (sizeof (int));
    h -> colunas = malloc (sizeof (int));
}



// Adiciona um tabuleiro ao histórico
void pushStack (Hist h, char **novoTabuleiro, int linhas, int colunas) {

    // Duplica a capacidade do histórico caso o limite tenha sido alcançado
    if (h -> sp == h -> cap) {
        h -> cap *= 2;

        // Realoca memória de modo a duplicar a capacidade no heap (memória dinâmica)
        char ***aux1 = realloc (h -> TAnteriores, h -> cap * (sizeof (char **)));
        int *aux2 = realloc (h -> linhas, h -> cap * (sizeof (int)));
        int *aux3 = realloc (h -> colunas, h -> cap * (sizeof (int)));

        h -> TAnteriores = aux1;
        h -> linhas = aux2;
        h -> colunas = aux3;
    }



    // Adiciona as dimensões do novo tabuleiro
    h -> linhas [h -> sp] = linhas;
    h -> colunas [h -> sp] = colunas;



    // Aloca memória para o novo tabuleiro
    h -> TAnteriores [h -> sp] = malloc (linhas * sizeof (char *));

    // Aloca memória para cada do novo tabuleiro e define estas linhas
    for (int i = 0; i < linhas; i++) {
        h -> TAnteriores [h -> sp][i] = malloc ((strlen (novoTabuleiro [i]) + 1) * sizeof (char));
        strcpy (h -> TAnteriores [h -> sp][i], novoTabuleiro [i]);
    }

    // Incrementa a quantidade de tabuleiros considerados
    h -> sp++;
}



// Remove um tabuleiro do histórico
void popStack (Hist h) {

    // Verifica se sp é diferente de 0 (positivo)
    if (h -> sp) {

        // Decrementa a quantidade de tabuleiros considerados
        h -> sp--;

        // Liberta a memória do tabuleiro removido
        if (h -> TAnteriores [h -> sp] != NULL) {
            // Liberta memória de cada linha do tabuleiro
            for (int i = 0; i < h -> linhas [h -> sp]; i++)
                if (h -> TAnteriores [h -> sp][i] != NULL)
                    free (h -> TAnteriores [h -> sp][i]);
            free (h -> TAnteriores [h -> sp]);
        }
    }
}



// Liberta a memória alocada para o histórico
void libertaStack (Hist h) {

    if (h != NULL) {

        if (h -> TAnteriores != NULL) {

            // Percorre o array de tabuleiros
            for (int i = 0; i < h -> sp; i++)
                if (h -> TAnteriores [i] != NULL) {

                    // Percorre cada linha dos tabuleiros
                    for (int j = 0; j < h -> linhas [i]; j++)
                        if (h -> TAnteriores [i][j] != NULL)
                            free (h -> TAnteriores [i][j]);

                    free (h -> TAnteriores [i]);
                }
            free (h -> TAnteriores);
        }

        if (h -> linhas != NULL) free (h -> linhas);

        if (h -> colunas != NULL) free (h -> colunas);

        free (h);
    }
}