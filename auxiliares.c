#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "puzzle.h"

// Verifica se um caractere é uma letra maiúscula
int eMaiuscula (char c) {
    return c >= 'A' && c <= 'Z';
}



// Verifica se um caractere é uma letra minúscula
int eMinuscula (char c) {
    return c >= 'a' && c <= 'z';
}



// Verifica se uma coordenada é válida (isto é, está dentro do tabuleiro)
int coordenadaValida (int l, char c, int linhas, int colunas) {
    return (!(c < 'a' || c > 'a' + colunas - 1 || l <= 0 || l > linhas));
}



// Imprime o tabuleiro atual do jogo
void visualizarTabuleiro (IJ *InfoJogo) {

    int i, j;

    // Imprime a estrutura do tabuleiro
    printf ("\n%d   ", InfoJogo -> hTabuleiros -> sp);
    for (j = 0; j < InfoJogo -> colunas; j++)
        printf ("%c ", 'a' + j);
    printf ("\n    ");
    for (j = 0; j < InfoJogo -> colunas; j++)
        printf ("- ");
    putchar ('\n');

    // Imprime o tabuleiro, percorrendo cada linha do mesmo
    for (i = 0; i < InfoJogo -> linhas; i++) {
        printf ("%d | ", i + 1);
        for (j = 0; j < InfoJogo -> colunas; j++)
            printf ("%c ", InfoJogo -> Tabuleiro [i][j]);
        putchar ('\n');
    }

    putchar ('\n');
}



// Verifica se um tabuleiro é válido
int tabuleiroValido (IJ *InfoJogo) {

    // Verifica se o tabuleiro não é nulo
    if (InfoJogo == NULL || InfoJogo -> Tabuleiro == NULL) return 0;

    char c;

    // Verifica se todas as casas do tabuleiro possuem caracteres válidos
    for (int i = 0; i < InfoJogo -> linhas; i++) {

        for (int j = 0; j < InfoJogo -> colunas; j++) {

            c = InfoJogo -> Tabuleiro [i][j];

            if (!(eMinuscula (c) || eMaiuscula (c) || c == '#')) {
                fprintf (stderr, "Erro: caractere inválido no tabuleiro (na coordenada %c%d).\n\n", j + 1 + 'a', i + 1);
                return 0;
            }
        }
    }

    return 1; 
}



// Verifica se as linhas não possuem casas brancas repetidas
int verificaLinhas (IJ *InfoJogo, char c, int linha, int coluna) {

    // Inteiro representante da validade da linha
    int validade = 1;
    
    // Percorre o resto da linha para procurar infrações
    for (int j = coluna + 1; j < InfoJogo -> colunas; j++)

        if (InfoJogo -> Tabuleiro [linha][j] == c) {
            printf ("Infração: Letra '%c' repetida na linha %d (colunas '%c' e '%c').\n", c, linha + 1, coluna + 'a', j + 'a');
            validade = 0;
        }

    return validade;
}




int verificaColunas (IJ *InfoJogo, char c, int linha, int coluna) {

    // Inteiro representante da validade da coluna
    int validade = 1;
    
    // Percorre o resto da coluna para procurar infrações
    for (int i = linha + 1; i < InfoJogo -> linhas; i++)

        if (InfoJogo -> Tabuleiro [i][coluna] == c) {
            printf ("Infração: Letra '%c' repetida na coluna '%c' (linhas %d e %d).\n", c, coluna + 'a', linha + 1, i + 1);
            validade = 0;
        }

    return validade;
}



// Inicializa os tabuleiros
void iniciarTabuleiro (ESTADO *e) {

    // Inicializa o tabuleiro principal
    e -> info = malloc (sizeof (IJ));
    e -> info -> Tabuleiro = NULL;
    e -> info -> linhas = 0;
    e -> info -> colunas = 0;

    // Inicializa o histórico de tabuleiros
    e -> info -> hTabuleiros = malloc (sizeof (HIST));
    inicializaStack (e -> info -> hTabuleiros);
}



// Liberta a memória alocada para os tabuleiros
void libertaTabuleiro (IJ *InfoJogo) {

    // Verifica se existe informação sobre o jogo
    if (InfoJogo == NULL) return;

    if (InfoJogo -> Tabuleiro != NULL) {

        // Liberta a memória alocada para cada linha do tabuleiro principal
        for (int i = 0; i < InfoJogo -> linhas; i++) 
            free (InfoJogo -> Tabuleiro [i]);

        // Liberta a memória alocada para o tabuleiro principal
        free (InfoJogo -> Tabuleiro);
    }

    // Liberta a memória alocada para o histórico de tabuleiros
    libertaStack (InfoJogo -> hTabuleiros, InfoJogo -> linhas);

    // Liberta a informação sobre o jogo
    free (InfoJogo);
}



// Calcula quantas letras estão ligadas à letra da posição dada
int contaLetrasLigadas (int linhas, int colunas, int Tabuleiro [linhas][colunas], int l, int c) {
    
    if (l < 0 || l >= linhas || c < 0 || c >= colunas || Tabuleiro [l][c] == 0) return 0;

    Tabuleiro [l][c] = 0;

    return 1 + contaLetrasLigadas (linhas, colunas, Tabuleiro, l + 1, c) +
               contaLetrasLigadas (linhas, colunas, Tabuleiro, l - 1, c) +
               contaLetrasLigadas (linhas, colunas, Tabuleiro, l, c + 1) +
               contaLetrasLigadas (linhas, colunas, Tabuleiro, l, c - 1);
}