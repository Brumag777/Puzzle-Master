#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "CUnit/Basic.h"
#include "puzzle.h"

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
    I -> Tabuleiro = malloc (5 * sizeof (char *));
    for (int i = 0; i < 5; i++) I -> Tabuleiro [i] = malloc (4 * sizeof (char));

    I -> linhas = 5;
    I -> colunas = 3;
    I -> hTabuleiros = NULL;
    strcpy (I -> Tabuleiro [0], "abd");
    strcpy (I -> Tabuleiro [1], "abC");
    strcpy (I -> Tabuleiro [2], "aB#");
    strcpy (I -> Tabuleiro [3], "abC");
    strcpy (I -> Tabuleiro [4], "abd");
    CU_ASSERT_EQUAL (riscaCasasAux (I, 1, 2), 0);

    I -> linhas = 5;
    I -> colunas = 3;
    strcpy (I -> Tabuleiro [0], "aBb");
    strcpy (I -> Tabuleiro [1], "a#C");
    strcpy (I -> Tabuleiro [2], "aB#");
    strcpy (I -> Tabuleiro [3], "abC");
    strcpy (I -> Tabuleiro [4], "abd");
    CU_ASSERT_EQUAL (riscaCasasAux (I, 0, 1), 1);
    CU_ASSERT_EQUAL (I -> Tabuleiro [0][2], '#');
    CU_ASSERT_EQUAL (I -> Tabuleiro [3][1], '#');
    CU_ASSERT_EQUAL (I -> Tabuleiro [4][1], '#');

    for (int i = 0; i < 5; i++) free (I -> Tabuleiro [i]);
    free (I -> Tabuleiro);
    free (I);
}



// Testa a função 'riscaCasas'
void teste_riscaCasas () {

    IJ *I = malloc (sizeof (IJ));
    I -> Tabuleiro = malloc (5 * sizeof (char *));
    for (int i = 0; i < 5; i++) I -> Tabuleiro [i] = malloc (4 * sizeof (char));

    I -> linhas = 2;
    I -> colunas = 2;
    I -> hTabuleiros = NULL;
    strcpy (I -> Tabuleiro [0], "AB");
    strcpy (I -> Tabuleiro [1], "cd");
    CU_ASSERT_EQUAL (riscaCasas (I), 0);

    I -> linhas = 5;
    I -> colunas = 3;
    strcpy (I -> Tabuleiro [0], "abd");
    strcpy (I -> Tabuleiro [1], "abC");
    strcpy (I -> Tabuleiro [2], "aB#");
    strcpy (I -> Tabuleiro [3], "abC");
    strcpy (I -> Tabuleiro [4], "abd");
    CU_ASSERT_EQUAL (riscaCasas (I), 1);

    I -> linhas = 5;
    I -> colunas = 3;
    strcpy (I -> Tabuleiro [0], "aBb");
    strcpy (I -> Tabuleiro [1], "a#C");
    strcpy (I -> Tabuleiro [2], "aB#");
    strcpy (I -> Tabuleiro [3], "abC");
    strcpy (I -> Tabuleiro [4], "abd");
    CU_ASSERT_EQUAL (riscaCasas (I), 1);

    for (int i = 0; i < 5; i++) free (I -> Tabuleiro [i]);
    free (I -> Tabuleiro);
    free (I);
}



// Testa a função 'pintaCasasAux'
void teste_pintaCasasAux () {

    IJ *I = malloc (sizeof (IJ));
    I -> Tabuleiro = malloc (5 * sizeof (char *));
    for (int i = 0; i < 5; i++) I -> Tabuleiro [i] = malloc (4 * sizeof (char));

    I -> linhas = 5;
    I -> colunas = 3;
    I -> hTabuleiros = NULL;
    strcpy (I -> Tabuleiro [0], "aBb");
    strcpy (I -> Tabuleiro [1], "a#C");
    strcpy (I -> Tabuleiro [2], "aB#");
    strcpy (I -> Tabuleiro [3], "abC");
    strcpy (I -> Tabuleiro [4], "abd");
    CU_ASSERT_EQUAL (pintaCasasAux (I, 2, 2), 0);

    CU_ASSERT_EQUAL (pintaCasasAux (I, 1, 1), 1);
    CU_ASSERT_EQUAL (I -> Tabuleiro [1][0], 'A');

    for (int i = 0; i < 5; i++) free (I -> Tabuleiro [i]);
    free (I -> Tabuleiro);
    free (I);
}



// Testa a função 'pintaCasas'
void teste_pintaCasas () {

    IJ *I = malloc (sizeof (IJ));
    I -> Tabuleiro = malloc (5 * sizeof (char *));
    for (int i = 0; i < 5; i++) I -> Tabuleiro [i] = malloc (4 * sizeof (char));

    I -> linhas = 2;
    I -> colunas = 2;
    I -> hTabuleiros = NULL;
    strcpy (I -> Tabuleiro [0], "A#");
    strcpy (I -> Tabuleiro [1], "bC");
    CU_ASSERT_EQUAL (pintaCasas (I), 0);

    I -> linhas = 5;
    I -> colunas = 3;
    strcpy (I -> Tabuleiro [0], "aBb");
    strcpy (I -> Tabuleiro [1], "a#C");
    strcpy (I -> Tabuleiro [2], "aB#");
    strcpy (I -> Tabuleiro [3], "abc");
    strcpy (I -> Tabuleiro [4], "abd");
    CU_ASSERT_EQUAL (pintaCasas (I), 1);
    CU_ASSERT_EQUAL (I -> Tabuleiro [1][0], 'A');
    CU_ASSERT_EQUAL (I -> Tabuleiro [3][2], 'C');

    for (int i = 0; i < 5; i++) free (I -> Tabuleiro [i]);
    free (I -> Tabuleiro);
    free (I);
}



// Testa a função 'testaPossibilidadesCasaAux'
void teste_testaPossibilidadesCasaAux () {

    IJ *I = malloc (sizeof (IJ));
    I -> Tabuleiro = malloc (5 * sizeof (char *));
    for (int i = 0; i < 5; i++) I -> Tabuleiro [i] = malloc (4 * sizeof (char));

    I -> linhas = 2;
    I -> colunas = 2;
    I -> hTabuleiros = NULL;
    strcpy (I -> Tabuleiro [0], "A#");
    strcpy (I -> Tabuleiro [1], "bC");
    CU_ASSERT_EQUAL (testaPossibilidadesCasaAux (I, 1, 0), 1);
    CU_ASSERT_EQUAL (I -> Tabuleiro [1][0], 'B');

    I -> linhas = 2;
    I -> colunas = 2;
    strcpy (I -> Tabuleiro [0], "A#");
    strcpy (I -> Tabuleiro [1], "bc");
    CU_ASSERT_EQUAL (testaPossibilidadesCasaAux (I, 1, 1), 0);

    I -> linhas = 5;
    I -> colunas = 3;
    strcpy (I -> Tabuleiro [0], "aBb");
    strcpy (I -> Tabuleiro [1], "a#C");
    strcpy (I -> Tabuleiro [2], "aB#");
    strcpy (I -> Tabuleiro [3], "abc");
    strcpy (I -> Tabuleiro [4], "abd");
    CU_ASSERT_EQUAL (testaPossibilidadesCasaAux (I, 0, 0), 1);
    CU_ASSERT_EQUAL (I -> Tabuleiro [0][0], 'A');

    for (int i = 0; i < 5; i++) free (I -> Tabuleiro [i]);
    free (I -> Tabuleiro);
    free (I);
}



// Testa a função 'testaPossibilidadesCasa'
void teste_testaPossibilidadesCasa () {

    IJ *I = malloc (sizeof (IJ));
    I -> Tabuleiro = malloc (5 * sizeof (char *));
    for (int i = 0; i < 5; i++) I -> Tabuleiro [i] = malloc (4 * sizeof (char));

    I -> linhas = 2;
    I -> colunas = 2;
    I -> hTabuleiros = NULL;
    strcpy (I -> Tabuleiro [0], "A#");
    strcpy (I -> Tabuleiro [1], "Bc");
    CU_ASSERT_EQUAL (testaPossibilidadesCasa (I), 0);

    I -> linhas = 3;
    I -> colunas = 3;
    strcpy (I -> Tabuleiro [0], "A#r");
    strcpy (I -> Tabuleiro [1], "bcf");
    strcpy (I -> Tabuleiro [2], "iop");
    CU_ASSERT_EQUAL (testaPossibilidadesCasa (I), 1);
    CU_ASSERT_EQUAL (I -> Tabuleiro [1][0], 'B');
    CU_ASSERT_EQUAL (I -> Tabuleiro [1][2], 'F');

    I -> linhas = 5;
    I -> colunas = 3;
    strcpy (I -> Tabuleiro [0], "aBb");
    strcpy (I -> Tabuleiro [1], "a#C");
    strcpy (I -> Tabuleiro [2], "aB#");
    strcpy (I -> Tabuleiro [3], "abc");
    strcpy (I -> Tabuleiro [4], "abd");
    CU_ASSERT_EQUAL (testaPossibilidadesCasa (I), 1);
    CU_ASSERT_EQUAL (I -> Tabuleiro [0][0], 'A');
    CU_ASSERT_EQUAL (I -> Tabuleiro [0][2], 'B');
    CU_ASSERT_EQUAL (I -> Tabuleiro [1][0], 'A');
    CU_ASSERT_EQUAL (I -> Tabuleiro [2][0], 'A');

    for (int i = 0; i < 5; i++) free (I -> Tabuleiro [i]);
    free (I -> Tabuleiro);
    free (I);
}



// Testa a função 'contaLetrasLigadas'
void teste_contaLetrasLigadas () {

    int aux [3][3] = {{1, 1, 1},
                      {0, 1, 1},
                      {1, 0, 1}};

    CU_ASSERT_EQUAL (contaLetrasLigadas (3, 3, aux, 2, 0), 1);

    CU_ASSERT_EQUAL (contaLetrasLigadas (3, 3, aux, 1, 1), 6);
}



// Testa a função 'percorreLinha'
void teste_percorreLinha () {

    IJ *I = malloc (sizeof (IJ));
    I -> Tabuleiro = malloc (5 * sizeof (char *));
    for (int i = 0; i < 5; i++) I -> Tabuleiro [i] = malloc (4 * sizeof (char));

    I -> linhas = 5;
    I -> colunas = 3;
    I -> hTabuleiros = NULL;
    strcpy (I -> Tabuleiro [0], "abd");
    strcpy (I -> Tabuleiro [1], "abC");
    strcpy (I -> Tabuleiro [2], "aB#");
    strcpy (I -> Tabuleiro [3], "abC");
    strcpy (I -> Tabuleiro [4], "abd");
    CU_ASSERT_EQUAL (percorreLinha (I, 'C', 1, 2), 0);

    I -> linhas = 5;
    I -> colunas = 3;
    strcpy (I -> Tabuleiro [0], "aBb");
    strcpy (I -> Tabuleiro [1], "a#C");
    strcpy (I -> Tabuleiro [2], "aB#");
    strcpy (I -> Tabuleiro [3], "abC");
    strcpy (I -> Tabuleiro [4], "abd");
    CU_ASSERT_EQUAL (percorreLinha (I, 'B', 0, 1), 1);
    CU_ASSERT_EQUAL (I -> Tabuleiro [0][2], '#');

    for (int i = 0; i < 5; i++) free (I -> Tabuleiro [i]);
    free (I -> Tabuleiro);
    free (I);
}



// Testa a função 'percorreColuna'
void teste_percorreColuna () {

    IJ *I = malloc (sizeof (IJ));
    I -> Tabuleiro = malloc (5 * sizeof (char *));
    for (int i = 0; i < 5; i++) I -> Tabuleiro [i] = malloc (4 * sizeof (char));

    I -> linhas = 5;
    I -> colunas = 3;
    I -> hTabuleiros = NULL;
    strcpy (I -> Tabuleiro [0], "abd");
    strcpy (I -> Tabuleiro [1], "abC");
    strcpy (I -> Tabuleiro [2], "aB#");
    strcpy (I -> Tabuleiro [3], "abC");
    strcpy (I -> Tabuleiro [4], "abd");
    CU_ASSERT_EQUAL (percorreColuna (I, 'C', 1, 2), 0);

    I -> linhas = 5;
    I -> colunas = 3;
    strcpy (I -> Tabuleiro [0], "aBb");
    strcpy (I -> Tabuleiro [1], "a#C");
    strcpy (I -> Tabuleiro [2], "aB#");
    strcpy (I -> Tabuleiro [3], "abC");
    strcpy (I -> Tabuleiro [4], "abd");
    CU_ASSERT_EQUAL (percorreColuna (I, 'B', 0, 1), 1);
    CU_ASSERT_EQUAL (I -> Tabuleiro [3][1], '#');
    CU_ASSERT_EQUAL (I -> Tabuleiro [4][1], '#');

    for (int i = 0; i < 5; i++) free (I -> Tabuleiro [i]);
    free (I -> Tabuleiro);
    free (I);
}



// Testa a função 'testeJogo'
void teste_testeJogo () {

    IJ *I = malloc (sizeof (IJ));
    I -> Tabuleiro = malloc (5 * sizeof (char *));
    for (int i = 0; i < 5; i++) I -> Tabuleiro [i] = malloc (6 * sizeof (char));

    I -> linhas = 5;
    I -> colunas = 5;
    I -> hTabuleiros = NULL;

    strcpy (I -> Tabuleiro [0], "E#ADC");
    strcpy (I -> Tabuleiro [1], "DC#E#");
    strcpy (I -> Tabuleiro [2], "B#DCE");
    strcpy (I -> Tabuleiro [3], "CDE#B");
    strcpy (I -> Tabuleiro [4], "A#CB#");
    CU_ASSERT_EQUAL (testeJogo (I), 1);

    I -> Tabuleiro [1][0] = '#';
    CU_ASSERT_EQUAL (testeJogo (I), 0);

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
    CU_add_test (suite, "riscaCasasAux", teste_riscaCasasAux);
    CU_add_test (suite, "riscaCasas", teste_riscaCasas);
    CU_add_test (suite, "pintaCasasAux", teste_pintaCasasAux);
    CU_add_test (suite, "pintaCasas", teste_pintaCasas);
    CU_add_test (suite, "testaPossibilidadesCasaAux", teste_testaPossibilidadesCasaAux);
    CU_add_test (suite, "testaPossibilidadesCasa", teste_testaPossibilidadesCasa);
    CU_add_test (suite, "contaLetrasLigadas", teste_contaLetrasLigadas);
    CU_add_test (suite, "percorreLinha", teste_percorreLinha);
    CU_add_test (suite, "percorreColuna", teste_percorreColuna);
    CU_add_test (suite, "testeJogo", teste_testeJogo);

    CU_basic_set_mode (CU_BRM_VERBOSE);
    CU_basic_run_tests ();
    CU_cleanup_registry ();

    return 0;
}