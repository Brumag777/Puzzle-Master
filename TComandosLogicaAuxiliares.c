#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "CUnit/Basic.h"
#include "puzzle.h"

// Testes da função 'verificaInfracoes'
void teste_verificaInfracoes () {

    IJ *I = malloc (sizeof (IJ));
    I -> Tabuleiro = malloc (3 * sizeof (char *));
    for (int i = 0; i < 3; i++) I -> Tabuleiro [i] = malloc (4 * sizeof (char));

    I -> linhas = 3;
    I -> colunas = 3;
    I -> hTabuleiros = NULL;

    strcpy (I -> Tabuleiro [0], "abc");
    strcpy (I -> Tabuleiro [1], "A#f");
    strcpy (I -> Tabuleiro [2], "cDC");
    CU_ASSERT_EQUAL (verificaInfracoes (I, 0), 1);

    I -> Tabuleiro [0][1] = '#';
    CU_ASSERT_EQUAL (verificaInfracoes (I, 0), 0);

    I -> Tabuleiro [0][1] = 'b';
    I -> Tabuleiro [0][2] = 'C';
    CU_ASSERT_EQUAL (verificaInfracoes (I, 0), 0);

    I -> Tabuleiro [0][2] = 'c';
    I -> Tabuleiro [2][0] = 'C';
    CU_ASSERT_EQUAL (verificaInfracoes (I, 0), 0);

    for (int i = 0; i < 3; i++) free (I -> Tabuleiro [i]);
    free (I -> Tabuleiro);
    free (I);
}



// Testes da função 'verificaCaminhoOrtogonal'
void teste_verificaCaminhoOrtogonal () {
    
    IJ *I = malloc (sizeof (IJ));
    I -> Tabuleiro = malloc (3 * sizeof (char *));
    for (int i = 0; i < 3; i++) I -> Tabuleiro [i] = malloc (4 * sizeof (char));

    I -> linhas = 3;
    I -> colunas = 3;
    I -> hTabuleiros = NULL;

    strcpy (I -> Tabuleiro [0], "abc");
    strcpy (I -> Tabuleiro [1], "A#f");
    strcpy (I -> Tabuleiro [2], "cDC");
    CU_ASSERT_EQUAL (verificaCaminhoOrtogonal (I), 1);

    I -> Tabuleiro [0][0] = I -> Tabuleiro [2][0] = '#';
    CU_ASSERT_EQUAL (verificaCaminhoOrtogonal (I), 0);

    for (int i = 0; i < 3; i++) free (I -> Tabuleiro [i]);
    free (I -> Tabuleiro);
    free (I);
}



// Testes da função 'ajudaUmaVez'
void teste_ajudaUmaVez () {

    IJ *I = malloc (sizeof (IJ));
    I -> Tabuleiro = malloc (3 * sizeof (char *));
    for (int i = 0; i < 3; i++) I -> Tabuleiro [i] = malloc (4 * sizeof (char));

    I -> linhas = 3;
    I -> colunas = 3;
    I -> hTabuleiros = NULL;

    strcpy (I -> Tabuleiro [0], "abc");
    strcpy (I -> Tabuleiro [1], "abf");
    strcpy (I -> Tabuleiro [2], "cdc");
    CU_ASSERT_EQUAL (ajudaUmaVez (I), 0);

    strcpy (I -> Tabuleiro [0], "abc");
    strcpy (I -> Tabuleiro [1], "A#f");
    strcpy (I -> Tabuleiro [2], "cDC");

    CU_ASSERT_EQUAL (ajudaUmaVez (I), 1);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [0], "#B#"), 0);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [1], "A#F"), 0);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [2], "#DC"), 0);

    for (int i = 0; i < 3; i++) free (I -> Tabuleiro [i]);
    free (I -> Tabuleiro);
    free (I);
}



// Testes da função 'resolve'
void teste_resolve () {
    
    IJ *I = malloc (sizeof (IJ));
    I -> Tabuleiro = malloc (5 * sizeof (char *));
    for (int i = 0; i < 5; i++) I -> Tabuleiro [i] = malloc (6 * sizeof (char));

    I -> linhas = 5;
    I -> colunas = 5;
    I -> hTabuleiros = malloc (sizeof (HIST));

    strcpy (I -> Tabuleiro [0], "ecadc");
    strcpy (I -> Tabuleiro [1], "dcdec");
    strcpy (I -> Tabuleiro [2], "bddce");
    strcpy (I -> Tabuleiro [3], "cdeeb");
    strcpy (I -> Tabuleiro [4], "accbb");

    inicializaStack (I -> hTabuleiros);
    pushStack (I -> hTabuleiros, I -> Tabuleiro, 5, 5);

    CU_ASSERT_EQUAL (resolve (I), 1);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [0], "E#ADC"), 0);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [1], "DC#E#"), 0);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [2], "B#DCE"), 0);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [3], "CDE#B"), 0);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [4], "A#CB#"), 0);

    strcpy (I -> Tabuleiro [0], "ecadc");
    strcpy (I -> Tabuleiro [1], "dcdec");
    strcpy (I -> Tabuleiro [2], "bddde");
    strcpy (I -> Tabuleiro [3], "cddeb");
    strcpy (I -> Tabuleiro [4], "accbb");

    pushStack (I -> hTabuleiros, I -> Tabuleiro, 5, 5);

    CU_ASSERT_EQUAL (resolve (I), 0);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [0], "ecadc"), 0);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [1], "dcdec"), 0);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [2], "bddde"), 0);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [3], "cddeb"), 0);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [4], "accbb"), 0);

    libertaStack (I -> hTabuleiros);
    for (int i = 0; i < 5; i++) free (I -> Tabuleiro [i]);
    free (I -> Tabuleiro);
    free (I);
}



// Função principal
int main () {

    CU_initialize_registry ();

    CU_pSuite suite = CU_add_suite ("Testes - ComandosLogicaAuxiliares.c", NULL, NULL);

    CU_add_test (suite, "verificaInfracoes", teste_verificaInfracoes);
    CU_add_test (suite, "verificaCaminhoOrtogonal", teste_verificaCaminhoOrtogonal);
    CU_add_test (suite, "ajudaUmaVez", teste_ajudaUmaVez);
    CU_add_test (suite, "resolve", teste_resolve);

    CU_basic_set_mode (CU_BRM_VERBOSE);
    CU_basic_run_tests ();
    CU_cleanup_registry ();

    return 0;
}