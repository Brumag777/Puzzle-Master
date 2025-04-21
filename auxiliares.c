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



// Verifica se as colunas não possuem casas brancas repetidas
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



// Verifica se as casas adjacentes às casas vazias não são vazias
int verificaCasaVazia (IJ *InfoJogo, int linha, int coluna) {

    // Inteiro representante da validade da casa
    int validade = 1;

    // Verifica a casa à direita
    if (coordenadaValida (linha + 1, coluna + 'a' + 1, InfoJogo -> linhas, InfoJogo -> colunas))
        if (InfoJogo -> Tabuleiro [linha][coluna + 1] == '#') {
            printf ("Infração: As casas vazias %c%d e %c%d estão juntas.\n", coluna + 'a', linha + 1, coluna + 'a' + 1, linha + 1);
            validade = 0;
        }

    // Verifica a casa abaixo
    if (coordenadaValida (linha + 2, coluna + 'a', InfoJogo -> linhas, InfoJogo -> colunas))
        if (InfoJogo -> Tabuleiro [linha + 1][coluna] == '#') {
            printf ("Infração: As casas vazias %c%d e %c%d estão juntas.\n", coluna + 'a', linha + 1, coluna + 'a', linha + 2);
            validade = 0;
        }

    return validade;
}



// Inicializa os tabuleiros
void iniciarTabuleiro (ESTADO *e, int flag) {

    // Inicializa o tabuleiro principal
    if (flag) e -> info = malloc (sizeof (IJ));
    e -> info -> Tabuleiro = NULL;
    e -> info -> linhas = 0;
    e -> info -> colunas = 0;

    // Inicializa o histórico de tabuleiros
    if (flag) {
        e -> info -> hTabuleiros = malloc (sizeof (HIST));
        inicializaStack (e -> info -> hTabuleiros);
    }
}



// Liberta a memória alocada para os tabuleiros
void libertaTabuleiro (IJ *InfoJogo, int flag) {

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
    if (flag) libertaStack (InfoJogo -> hTabuleiros);

    // Liberta a informação sobre o jogo
    if (flag) free (InfoJogo);
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



// Pinta as casas à volta das casas vazias de branco
int pintaCasas (IJ *InfoJogo, int linha, int coluna) {

    // Indicador de alterações
    int flag = 0;

    // Verifica a casa acima
    if (coordenadaValida (linha, coluna + 'a', InfoJogo -> linhas, InfoJogo -> colunas))
        if (eMinuscula (InfoJogo -> Tabuleiro [linha - 1][coluna])) {
            InfoJogo -> Tabuleiro [linha - 1][coluna] += 'A' - 'a';
            flag = 1;
        }

    // Verifica a casa abaixo
    if (coordenadaValida (linha + 2, coluna + 'a', InfoJogo -> linhas, InfoJogo -> colunas))
        if (eMinuscula (InfoJogo -> Tabuleiro [linha + 1][coluna])) {
            InfoJogo -> Tabuleiro [linha + 1][coluna] += 'A' - 'a';
            flag = 1;
        }

    // Verifica a casa à esquerda
    if (coordenadaValida (linha + 1, coluna + 'a' - 1, InfoJogo -> linhas, InfoJogo -> colunas))
        if (eMinuscula (InfoJogo -> Tabuleiro [linha][coluna - 1])) {
            InfoJogo -> Tabuleiro [linha][coluna - 1] += 'A' - 'a';
            flag = 1;
        }

    // Verifica a casa à direita
    if (coordenadaValida (linha + 1, coluna + 'a' + 1, InfoJogo -> linhas, InfoJogo -> colunas))
        if (eMinuscula (InfoJogo -> Tabuleiro [linha][coluna + 1])) {
            InfoJogo -> Tabuleiro [linha][coluna + 1] += 'A' - 'a';
            flag = 1;
        }

    return flag;
}



// Risca as casas que deviam ser vazias
int riscaCasas (IJ *InfoJogo, int linha, int coluna) {

    // Indicador de alterações
    int flag = 0;

    // Percorre a linha
    if (percorreLinha (InfoJogo, InfoJogo -> Tabuleiro [linha][coluna], linha, coluna)) flag = 1;

    // Percorre a coluna
    if (percorreColuna (InfoJogo, InfoJogo -> Tabuleiro [linha][coluna], linha, coluna)) flag = 1;

    return flag;
}



// Testa as possibilidades de uma casa minúscula
int testaPossibilidadesCasa (IJ *InfoJogo, int linha, int coluna) {

    // Risca a casa de modo a realizar o teste
    char C = InfoJogo -> Tabuleiro [linha][coluna];
    InfoJogo -> Tabuleiro [linha][coluna] = '#';

    // Cria um tabuleiro auxiliar para verificar os caminhos ortogonais
    int aux [InfoJogo -> linhas][InfoJogo -> colunas], nLetras, l, c;

    // No tabuleiro auxiliar, '0' representa as casas vazias e '1' representa as letras (as casas restantes)
    for (int i = nLetras = 0; i < InfoJogo -> linhas; i++)
        for (int j = 0; j < InfoJogo -> colunas; j++)
            if (InfoJogo -> Tabuleiro [i][j] == '#') aux [i][j] = 0;
            else {
                l = i;
                c = j;
                aux [i][j] = 1;
                nLetras++;
            }

    // Verifica se o tabuleiro possui pelo menos uma letra
    if (nLetras == 0) return 0;

    // Verifica se existe um caminho ortogonal entre todas as letras
    if (nLetras != contaLetrasLigadas (InfoJogo -> linhas, InfoJogo -> colunas, aux, l, c)) {
        InfoJogo -> Tabuleiro [linha][coluna] = C + 'A' - 'a';
        return 1;
    }
    else InfoJogo -> Tabuleiro [linha][coluna] = C;
    return 0;
}



// Percorre a linha para riscar casas que deviam ser vazias
int percorreLinha (IJ *InfoJogo, char c, int linha, int coluna) {

    // Indicador de alterações
    int flag = 0;

    // Altera o 'c' para minúscula
    c += 'a' - 'A';

    for (int j = 0; j < InfoJogo -> colunas; j++)
        if (InfoJogo -> Tabuleiro [linha][j] == c && j != coluna) {
            InfoJogo -> Tabuleiro [linha][j] = '#';
            flag = 1;
        }

    return flag;
}



// Percorre a coluna para riscar casas que deviam ser vazias
int percorreColuna (IJ *InfoJogo, char c, int linha, int coluna) {

    // Indicador de alterações
    int flag = 0;

    // Altera o 'c' para minúscula
    c += 'a' - 'A';

    for (int i = 0; i < InfoJogo -> linhas; i++)
        if (InfoJogo -> Tabuleiro [i][coluna] == c && i != linha) {
            InfoJogo -> Tabuleiro [i][coluna] = '#';
            flag = 1;
        }

    return flag;
}



// Função auxiliar do comando 'a' (ajuda)
int ajudaAux (ESTADO *e) {

    // Indicador de alterações
    int flag = 0;
    
    // Percorre o tabuleiro para riscar casas que deviam ser vazias
    for (int i = 0; i < e -> info -> linhas; i++)
        for (int j = 0; j < e -> info -> colunas; j++)
            if (eMaiuscula (e -> info -> Tabuleiro [i][j])) 
                if (riscaCasas (e -> info, i, j)) flag = 1;
    
    // Percorre o tabuleiro para pintar casas à volta das casas vazias de branco
    for (int i = 0; i < e -> info -> linhas; i++)
        for (int j = 0; j < e -> info -> colunas; j++)
            if (e -> info -> Tabuleiro [i][j] == '#') 
                if (pintaCasas (e -> info, i, j)) flag = 1;

    // Percorre o tabuleiro para pintar de branco as casas que não podem ser vazias
    for (int i = 0; i < e -> info -> linhas; i++)
        for (int j = 0; j < e -> info -> colunas; j++)
            if (eMinuscula (e -> info -> Tabuleiro [i][j])) 
                if (testaPossibilidadesCasa (e -> info, i, j)) flag = 1;

    return flag;
}