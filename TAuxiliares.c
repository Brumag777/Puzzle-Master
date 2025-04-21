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

    IJ *I;

    I -> linhas = 5;
    I -> colunas = 3;
    I -> hTabuleiros = NULL;
    char *aux1 [5] = {"abc", "def", "ghi", "jkl", "mno"};
    I -> Tabuleiro = aux1;

    CU_ASSERT_EQUAL (tabuleiroValido (I), 1);



    I -> linhas = 4;
    I -> colunas = 4;
    I -> hTabuleiros = NULL;
    char *aux2 [4] = {"bare", "t#ba", "Ret#", "bare"};
    I -> Tabuleiro = aux2;

    CU_ASSERT_EQUAL (tabuleiroValido (I), 1);



    I -> linhas = 2;
    I -> colunas = 2;
    I -> hTabuleiros = NULL;
    char *aux3 [2] = {"ba", "<3"};
    I -> Tabuleiro = aux3;

    CU_ASSERT_EQUAL (tabuleiroValido (I), 0);
}



int main () {

    if (CUE_SUCCESS != CU_initialize_registry ())
        return CU_get_error (); 

    CU_pSuite pSuite = NULL;

    pSuite = CU_add_suite ("sum_test_suite", 0, 0);
    if (NULL == pSuite) {
        CU_cleanup_registry ();
        return CU_get_error ();
    }

    if (NULL == CU_add_test (pSuite, "teste_eMaiuscula", teste_eMaiuscula)) {
        CU_cleanup_registry ();
        return CU_get_error ();
    }

    if (NULL == CU_add_test (pSuite, "teste_eMinuscula", teste_eMinuscula)) {
        CU_cleanup_registry ();
        return CU_get_error ();
    }

    if (NULL == CU_add_test (pSuite, "teste_coordenadaValida", teste_coordenadaValida)) {
        CU_cleanup_registry ();
        return CU_get_error ();
    }

    if (NULL == CU_add_test (pSuite, "teste_tabuleiroValido", teste_tabuleiroValido)) {
        CU_cleanup_registry ();
        return CU_get_error ();
    }

    CU_basic_run_tests ();
    return CU_get_error ();
}