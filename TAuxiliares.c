#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "CUnit/Basic.h"
#include "puzzle.h"

// gcc TAuxiliares.c Auxiliares.c Comandos.c ComandosLogica.c ComandosLogicaAuxiliares.c Stack.c puzzle.h -Wall -Wextra -pedantic -O1 -fsanitize=address -fno-omit-frame-pointer -g -lcunit -o TAuxiliares

// Testa a função 'eMaiuscula'
void teste_eMaiuscula () {
    CU_ASSERT_EQUAL (eMaiuscula ('V'), 1);
    CU_ASSERT_EQUAL (eMaiuscula ('b'), 0);
    CU_ASSERT_EQUAL (eMaiuscula ('#'), 0);
    CU_ASSERT_EQUAL (eMaiuscula ('3'), 0);
}



// Testa a função 'eMinuscula'
void teste_eMinuscula () {
    CU_ASSERT_EQUAL (eMinuscula ('V'), 0);
    CU_ASSERT_EQUAL (eMinuscula ('b'), 1);
    CU_ASSERT_EQUAL (eMinuscula ('#'), 0);
    CU_ASSERT_EQUAL (eMinuscula ('3'), 0);
}



// Testa a função 'coordenadaValida'
void teste_coordenadaValida () {
    CU_ASSERT_EQUAL (coordenadaValida (3, 'v', 5, 5), 0);
    CU_ASSERT_EQUAL (coordenadaValida (3, 'b', 4, 5), 1);
    CU_ASSERT_EQUAL (coordenadaValida (3, 'd', 4, 3), 0);
    CU_ASSERT_EQUAL (coordenadaValida (35, 'v', 30, 30), 0);
}



// Testa a função 'tabuleiroValido'
void teste_tabuleiroValido () {

    IJ *I = malloc (sizeof (IJ));

    I -> linhas = 5;
    I -> colunas = 3;
    I -> hTabuleiros = NULL;
    char *aux1 [5] = {"abc", "def", "ghi", "jkl", "mno"};
    I -> Tabuleiro = aux1;
    CU_ASSERT_EQUAL (tabuleiroValido (I), 1);

    I -> linhas = 4;
    I -> colunas = 4;
    char *aux2 [4] = {"bare", "t#ba", "Ret#", "bare"};
    I -> Tabuleiro = aux2;
    CU_ASSERT_EQUAL (tabuleiroValido (I), 1);

    I -> linhas = 2;
    I -> colunas = 2;
    char *aux3 [2] = {"ba", "<3"};
    I -> Tabuleiro = aux3;
    CU_ASSERT_EQUAL (tabuleiroValido (I), 0);

    free (I);
}



// Testa a função 'verificaLinhas'
void teste_verificaLinhas () {

    IJ *I = malloc (sizeof (IJ));

    I -> linhas = 5;
    I -> colunas = 3;
    I -> hTabuleiros = NULL;
    char *aux1 [5] = {"abc", "abc", "abC", "abc", "abc"};
    I -> Tabuleiro = aux1;
    CU_ASSERT_EQUAL (verificaLinhas (I, 'C', 2, 2, 0), 1);

    I -> linhas = 4;
    I -> colunas = 4;
    char *aux2 [4] = {"Bare", "t#ba", "Ret#", "Bare"};
    I -> Tabuleiro = aux2;
    CU_ASSERT_EQUAL (verificaLinhas (I, 'B', 0, 0, 0), 1);

    I -> linhas = 4;
    I -> colunas = 4;
    char *aux3 [4] = {"BarB", "t#ba", "Ret#", "bare"};
    I -> Tabuleiro = aux3;
    CU_ASSERT_EQUAL (verificaLinhas (I, 'B', 0, 0, 0), 0);

    free (I);
}



// Testa a função 'verificaColunas'
void teste_verificaColunas () {

    IJ *I = malloc (sizeof (IJ));

    I -> linhas = 5;
    I -> colunas = 3;
    I -> hTabuleiros = NULL;
    char *aux1 [5] = {"abc", "abc", "abC", "abc", "abc"};
    I -> Tabuleiro = aux1;
    CU_ASSERT_EQUAL (verificaColunas (I, 'C', 2, 2, 0), 1);

    I -> linhas = 4;
    I -> colunas = 4;
    char *aux2 [4] = {"Bare", "t#ba", "Ret#", "Bare"};
    I -> Tabuleiro = aux2;
    CU_ASSERT_EQUAL (verificaColunas (I, 'B', 0, 0, 0), 0);

    I -> linhas = 4;
    I -> colunas = 4;
    char *aux3 [4] = {"BarB", "t#ba", "Ret#", "bare"};
    I -> Tabuleiro = aux3;
    CU_ASSERT_EQUAL (verificaColunas (I, 'B', 0, 0, 0), 1);

    free (I);
}



// Testa a função 'verificaCasaVazia'
void teste_verificaCasaVazia () {

    IJ *I = malloc (sizeof (IJ));

    I -> linhas = 5;
    I -> colunas = 3;
    I -> hTabuleiros = NULL;
    char *aux1 [5] = {"abc", "abC", "aB#", "abC", "abc"};
    I -> Tabuleiro = aux1;
    CU_ASSERT_EQUAL (verificaCasaVazia (I, 2, 2, 0), 1);

    I -> linhas = 4;
    I -> colunas = 4;
    char *aux2 [4] = {"Bare", "t##a", "Ret#", "Bare"};
    I -> Tabuleiro = aux2;
    CU_ASSERT_EQUAL (verificaCasaVazia (I, 1, 1, 0), 0);

    I -> linhas = 4;
    I -> colunas = 4;
    char *aux3 [4] = {"BArB", "T#Ba", "REto", "b#re"};
    I -> Tabuleiro = aux3;
    CU_ASSERT_EQUAL (verificaCasaVazia (I, 1, 1, 0), 1);

    free (I);
}



// Testa a função 'riscaCasasAux'
void teste_riscaCasasAux () {

    IJ *I = malloc (sizeof (IJ));

    I -> linhas = 5;
    I -> colunas = 3;
    I -> hTabuleiros = NULL;
    char *aux1 [5] = {"abd", "abC", "aB#", "abC", "abd"};
    I -> Tabuleiro = aux1;
    CU_ASSERT_EQUAL (riscaCasasAux (I, 2, 2), 0);

    I -> linhas = 5;
    I -> colunas = 3;
    char *aux2 [5] = {"aBb", "a#C", "aB#", "abC", "abd"};
    I -> Tabuleiro = aux2;
    CU_ASSERT_EQUAL (riscaCasasAux (I, 0, 1), 1);
    CU_ASSERT_EQUAL (I -> Tabuleiro [0][2], 'B');
    CU_ASSERT_EQUAL (I -> Tabuleiro [3][1], 'B');
    CU_ASSERT_EQUAL (I -> Tabuleiro [4][1], 'B');

    I -> linhas = 4;
    I -> colunas = 4;
    char *aux3 [4] = {"BArB", "T#Ba", "REto", "b#re"};
    I -> Tabuleiro = aux3;
    CU_ASSERT_EQUAL (verificaCasaVazia (I, 0, 1, 0), 0);

    free (I);
}



// Testa a função 'percorreLinha'
void teste_percorreLinha () {

    IJ *I = malloc (sizeof (IJ));
    I -> Tabuleiro = malloc (5 * sizeof (char *));
    for (int i = 0; i < 5; i++) I -> Tabuleiro [i] = malloc (6 * sizeof (char));

    I -> linhas = 5;
    I -> colunas = 3;
    I -> hTabuleiros = NULL;
    I -> Tabuleiro [0][0] = 'a', I -> Tabuleiro [0][1] = 'b', I -> Tabuleiro [0][2] = 'd';
    I -> Tabuleiro [1][0] = 'a', I -> Tabuleiro [1][1] = 'b', I -> Tabuleiro [1][2] = 'C';
    I -> Tabuleiro [2][0] = 'a', I -> Tabuleiro [2][1] = 'B', I -> Tabuleiro [2][2] = '#';
    I -> Tabuleiro [3][0] = 'a', I -> Tabuleiro [3][1] = 'b', I -> Tabuleiro [3][2] = 'C';
    I -> Tabuleiro [4][0] = 'a', I -> Tabuleiro [4][1] = 'b', I -> Tabuleiro [4][2] = 'd';
    CU_ASSERT_EQUAL (percorreLinha (I, 'C', 1, 2), 0);

    I -> linhas = 5;
    I -> colunas = 3;
    I -> Tabuleiro [0][0] = 'a', I -> Tabuleiro [0][1] = 'B', I -> Tabuleiro [0][2] = 'b';
    I -> Tabuleiro [1][0] = 'a', I -> Tabuleiro [1][1] = '#', I -> Tabuleiro [1][2] = 'C';
    I -> Tabuleiro [2][0] = 'a', I -> Tabuleiro [2][1] = 'B', I -> Tabuleiro [2][2] = '#';
    I -> Tabuleiro [3][0] = 'a', I -> Tabuleiro [3][1] = 'b', I -> Tabuleiro [3][2] = 'C';
    I -> Tabuleiro [4][0] = 'a', I -> Tabuleiro [4][1] = 'b', I -> Tabuleiro [4][2] = 'd';
    CU_ASSERT_EQUAL (percorreLinha (I, 'B', 0, 1), 1);
    CU_ASSERT_EQUAL (I -> Tabuleiro [0][2], 'B');

    for (int i = 0; i < 5; i++) free (I -> Tabuleiro [i]);
    free (I -> Tabuleiro);
    free (I);
}



// Função principal
int main () {

    CU_initialize_registry ();

    CU_pSuite suite = CU_add_suite ("Testes - Auxiliares.c", NULL, NULL);

    CU_add_test (suite, "eMaiuscula", teste_eMaiuscula);
    CU_add_test (suite, "eMinuscula", teste_eMinuscula);
    CU_add_test (suite, "coordenadaValida", teste_coordenadaValida);
    CU_add_test (suite, "tabuleiroValido", teste_tabuleiroValido);
    CU_add_test (suite, "verificaLinhas", teste_verificaLinhas);
    CU_add_test (suite, "verificaColunas", teste_verificaColunas);
    CU_add_test (suite, "verificaCasaVazia", teste_verificaCasaVazia);
    //CU_add_test (suite, "riscaCasasAux", teste_riscaCasasAux);
    CU_add_test (suite, "percorreLinha", teste_percorreLinha);


    CU_basic_set_mode (CU_BRM_VERBOSE);
    CU_basic_run_tests ();
    CU_cleanup_registry ();

    return 0;
}