#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "puzzle.h"

// Desfaz a última jogada do jogo
int desfazUmaJogada (ESTADO *e) {

    // Verifica se existe um tabuleiro anterior
    if (e -> info -> hTabuleiros -> sp == 1) return 1;

    // Liberta a memória alocada para o tabuleiro anterior
    libertaTabuleiro (e -> info, 0);

    // Aloca memória para o novo tabuleiro
    iniciarTabuleiro (e, 0);

    // Altera as dimensões do tabuleiro para as dimensões do tabuleiro anterior
    e -> info -> linhas = e -> info -> hTabuleiros -> linhas [e -> info -> hTabuleiros -> sp - 2];
    e -> info -> colunas = e -> info -> hTabuleiros -> colunas [e -> info -> hTabuleiros -> sp - 2];

    // Aloca memória para o tabuleiro novo
    e -> info -> Tabuleiro = malloc (e -> info -> linhas * sizeof (char *));

    // Aloca memória para cada linha do tabuleiro novo e preenche-as com as linhas do tabuleiro anterior
    for (int i = 0; i < e -> info -> linhas; i++) {
        e -> info -> Tabuleiro [i] = malloc ((e -> info -> colunas + 2) * sizeof (char));
        strcpy (e -> info -> Tabuleiro [i], e -> info -> hTabuleiros -> TAnteriores [e -> info -> hTabuleiros -> sp - 2][i]);
    }

    // Remove o tabuleiro antigo do histórico de tabuleiros
    popStack (e -> info -> hTabuleiros);

    // Imprime o tabuleiro atualizado
    visualizarTabuleiro (e -> info);

    return 0;
}



// Procura infrações em relação à existência de casas riscadas juntas e de casa brancas na mesma linha ou coluna
int verificaInfracoes (IJ *I) {

    // Inteiro representante da validade do tabuleiro
    int validade = 1;

    // Percorre o tabuleiro para procurar infrações
    for (int i = 0; i < I -> linhas; i++)

        // Percorre cada linha do tabuleiro para procurar infrações
        for (int j = 0; j < I -> colunas; j++) {
                
            // Verifica se houve infrações relativas a casas brancas
            if (eMaiuscula (I -> Tabuleiro [i][j])) {
                if (!verificaLinhas (I, I -> Tabuleiro [i][j], i, j) ||
                    !verificaColunas (I, I -> Tabuleiro [i][j], i, j)) validade = 0;
            }

            // Verifica se houve infrações relativas a casas vazias
            else if (I -> Tabuleiro [i][j] == '#')
                if (!verificaCasaVazia (I, i, j)) validade = 0;
        }

    return validade;
}



// Procura infrações em relação à existência de um caminho ortogonal entre todas as letras
int verificaCaminhoOrtogonal (IJ *I) {

    // Cria um tabuleiro auxiliar para verificar os caminhos ortogonais
    int aux [I -> linhas][I -> colunas], nLetras, l, c;

    // No tabuleiro auxiliar, '0' representa as casas vazias e '1' representa as letras (as casas restantes)
    for (int i = nLetras = 0; i < I -> linhas; i++)
        for (int j = 0; j < I -> colunas; j++)
            if (I -> Tabuleiro [i][j] == '#') aux [i][j] = 0;
            else {
                l = i;
                c = j;
                aux [i][j] = 1;
                nLetras++;
            }

    // Verifica se o tabuleiro possui letras
    if (nLetras == 0) return 1;

    // Verifica se o número de letras total é igual ao número de letras ligadas a uma letra do tabuleiro
    return nLetras == contaLetrasLigadas (I -> linhas, I -> colunas, aux, l, c);
}



// Realiza alterações necessárias na posição atual
int ajudaUmaVez (IJ *I) {

    // Indicador de alterações
    int flag = 0;

    // Percorre o tabuleiro para riscar casas que não podem ser brancas pela existência de casas brancas iguais na mesma linha ou coluna
    for (int i = 0; i < I -> linhas; i++)
        for (int j = 0; j < I -> colunas; j++)
            if (eMaiuscula (I -> Tabuleiro [i][j])) 
                if (riscaCasas (I, i, j)) flag = 1;
    
    // Percorre o tabuleiro para pintar casas à volta das casas vazias de branco
    for (int i = 0; i < I -> linhas; i++)
        for (int j = 0; j < I -> colunas; j++)
            if (I -> Tabuleiro [i][j] == '#') 
                if (pintaCasas (I, i, j)) flag = 1;

    // Percorre o tabuleiro para pintar de branco as casas que não podem ser vazias por bloquear letras
    for (int i = 0; i < I -> linhas; i++)
        for (int j = 0; j < I -> colunas; j++)
            if (eMinuscula (I -> Tabuleiro [i][j])) 
                if (testaPossibilidadesCasa (I, i, j)) flag = 1;

    return flag;
}