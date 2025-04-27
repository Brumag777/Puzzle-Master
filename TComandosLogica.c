#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "CUnit/Basic.h"
#include "puzzle.h"

// Testa a função 'logicaGravar'
void teste_logicaGravar () {
    CU_ASSERT_EQUAL (logicaGravar (NULL, NULL), 1);
}



// Testa a função 'logicaLer'
void teste_logicaLer () {
    CU_ASSERT_EQUAL (logicaLer (NULL, NULL), 1);
}



// Testa a função 'logicaSair'
void teste_logicaSair () {
    ESTADO *e = malloc (sizeof (ESTADO));
    e -> info = NULL;
    e -> looping = true;

    CU_ASSERT_EQUAL (logicaSair (" ", NULL), 1);
    CU_ASSERT_EQUAL (e -> looping, true);
    CU_ASSERT_EQUAL (logicaSair (NULL, e), 0);
    CU_ASSERT_EQUAL (e -> looping, false);

    free (e);
}



// Testa a função 'logicaPintarCasa'
void teste_logicaPintarCasa () {
    ESTADO *e = malloc (sizeof (ESTADO));
    e -> info = malloc (sizeof (IJ));
    e -> info -> linhas = 5;
    e -> info -> colunas = 5;
    e -> info -> Tabuleiro = malloc (5 * sizeof (char *));
    for (int i = 0; i < 5; i++) e -> info -> Tabuleiro [i] = malloc (6 * sizeof (char));
    e -> info -> Tabuleiro [2][1] = '#';
    e -> info -> Tabuleiro [2][2] = 'Z';
    e -> info -> Tabuleiro [4][4] = 'a';

    CU_ASSERT_EQUAL (logicaPintarCasa (NULL, NULL), 1);
    CU_ASSERT_EQUAL (logicaPintarCasa ("b6", e), 2);
    CU_ASSERT_EQUAL (logicaPintarCasa ("b3", e), 3);
    CU_ASSERT_EQUAL (logicaPintarCasa ("c3", e), 4);
    CU_ASSERT_EQUAL (logicaPintarCasa ("e5", e), 0);
    CU_ASSERT_EQUAL (e -> info -> Tabuleiro [4][4], 'A');

    for (int i = 0; i < 5; i++) free (e -> info -> Tabuleiro [i]);
    free (e -> info -> Tabuleiro);
    free (e -> info);
    free (e);
}



// Testa a função 'logicaRiscarCasa'
void teste_logicaRiscarCasa () {
    ESTADO *e = malloc (sizeof (ESTADO));
    e -> info = malloc (sizeof (IJ));
    e -> info -> linhas = 5;
    e -> info -> colunas = 5;
    e -> info -> Tabuleiro = malloc (5 * sizeof (char *));
    for (int i = 0; i < 5; i++) e -> info -> Tabuleiro [i] = malloc (6 * sizeof (char));
    e -> info -> Tabuleiro [2][1] = '#';
    e -> info -> Tabuleiro [2][2] = 'Z';
    e -> info -> Tabuleiro [4][4] = 'a';

    CU_ASSERT_EQUAL (logicaRiscarCasa (NULL, NULL), 1);
    CU_ASSERT_EQUAL (logicaRiscarCasa ("b6", e), 2);
    CU_ASSERT_EQUAL (logicaRiscarCasa ("b3", e), 3);
    CU_ASSERT_EQUAL (logicaRiscarCasa ("c3", e), 4);
    CU_ASSERT_EQUAL (logicaRiscarCasa ("e5", e), 0);
    CU_ASSERT_EQUAL (e -> info -> Tabuleiro [4][4], '#');

    for (int i = 0; i < 5; i++) free (e -> info -> Tabuleiro [i]);
    free (e -> info -> Tabuleiro);
    free (e -> info);
    free (e);
}



// Testa a função 'logicaVizualizarHistorico'
void teste_logicaVizualizarHistorico () {
    ESTADO *e = malloc (sizeof (ESTADO));
    e -> info = malloc (sizeof (IJ));
    e -> info -> hTabuleiros = malloc (sizeof (HIST));
    e -> info -> hTabuleiros -> sp = 0;

    CU_ASSERT_EQUAL (logicaVizualizarHistorico (NULL, e), -2);

    e -> info -> hTabuleiros -> sp = 3;

    CU_ASSERT_EQUAL (logicaVizualizarHistorico (NULL, e), 1);
    CU_ASSERT_EQUAL (logicaVizualizarHistorico ("3", e), 3);
    CU_ASSERT_EQUAL (logicaVizualizarHistorico ("1", e), 1);
    CU_ASSERT_EQUAL (logicaVizualizarHistorico ("0", e), -1);
    CU_ASSERT_EQUAL (logicaVizualizarHistorico ("4", e), -3);

    free (e -> info -> hTabuleiros);
    free (e -> info);
    free (e);
}



// Testa a função 'logicaVerifica'
void teste_logicaVerifica () {
    ESTADO *e = malloc (sizeof (ESTADO));
    e -> info = malloc (sizeof (IJ));
    e -> info -> linhas = 3;
    e -> info -> colunas = 3;
    e -> info -> Tabuleiro = malloc (3 * sizeof (char *));
    for (int i = 0; i < 3; i++) e -> info -> Tabuleiro [i] = malloc (4 * sizeof (char));
    
    strcpy (e -> info -> Tabuleiro [0], "a#c");
    strcpy (e -> info -> Tabuleiro [1], "cba");
    strcpy (e -> info -> Tabuleiro [2], "Cab");

    CU_ASSERT_EQUAL (logicaVerifica (" ", NULL), -1);
    CU_ASSERT_EQUAL (logicaVerifica (NULL, e), 1);

    e -> info -> Tabuleiro [1][1] = '#';
    CU_ASSERT_EQUAL (logicaVerifica (NULL, e), 0);

    e -> info -> Tabuleiro [1][1] = 'b';
    e -> info -> Tabuleiro [1][0] = '#';
    CU_ASSERT_EQUAL (logicaVerifica (NULL, e), 0);

    e -> info -> Tabuleiro [1][0] = 'C';
    CU_ASSERT_EQUAL (logicaVerifica (NULL, e), 0);

    for (int i = 0; i < 3; i++) free (e -> info -> Tabuleiro [i]);
    free (e -> info -> Tabuleiro);
    free (e -> info);
    free (e);
}



// Testa a função 'logicaAjuda'
void teste_logicaAjuda () {
    ESTADO *e = malloc (sizeof (ESTADO));
    e -> info = malloc (sizeof (IJ));
    e -> info -> linhas = 3;
    e -> info -> colunas = 3;
    e -> info -> Tabuleiro = malloc (3 * sizeof (char *));
    for (int i = 0; i < 3; i++) e -> info -> Tabuleiro [i] = malloc (4 * sizeof (char));
    
    strcpy (e -> info -> Tabuleiro [0], "abc");
    strcpy (e -> info -> Tabuleiro [1], "cba");
    strcpy (e -> info -> Tabuleiro [2], "cab");

    CU_ASSERT_EQUAL (logicaAjuda ("argInvalido", NULL), 1);
    CU_ASSERT_EQUAL (logicaAjuda (NULL, e), 2);

    e -> info -> Tabuleiro [0][1] = '#';
    CU_ASSERT_EQUAL (logicaAjuda (NULL, e), 0);

    for (int i = 0; i < 3; i++) free (e -> info -> Tabuleiro [i]);
    free (e -> info -> Tabuleiro);
    free (e -> info);
    free (e);
}



// Testa a função 'logicaAjudaRep'
void teste_logicaAjudaRep () {
    ESTADO *e = malloc (sizeof (ESTADO));
    e -> info = malloc (sizeof (IJ));
    e -> info -> linhas = 3;
    e -> info -> colunas = 3;
    e -> info -> Tabuleiro = malloc (3 * sizeof (char *));
    for (int i = 0; i < 3; i++) e -> info -> Tabuleiro [i] = malloc (4 * sizeof (char));
    
    strcpy (e -> info -> Tabuleiro [0], "abc");
    strcpy (e -> info -> Tabuleiro [1], "cba");
    strcpy (e -> info -> Tabuleiro [2], "cab");

    CU_ASSERT_EQUAL (logicaAjudaRep (" ", NULL), 1);
    CU_ASSERT_EQUAL (logicaAjudaRep (NULL, e), 2);

    e -> info -> Tabuleiro [0][1] = '#';
    CU_ASSERT_EQUAL (logicaAjudaRep (NULL, e), 0);

    for (int i = 0; i < 3; i++) free (e -> info -> Tabuleiro [i]);
    free (e -> info -> Tabuleiro);
    free (e -> info);
    free (e);
}



// Testa a função 'logicaResolveJogo'
void teste_logicaResolveJogo () {
    CU_ASSERT_EQUAL (logicaAjudaRep (" ", NULL), 1);
}



// Testa a função 'logicaListarComandos'
void teste_logicaListarComandos () {
    CU_ASSERT_EQUAL (logicaListarComandos (" ", NULL), 1);
    CU_ASSERT_EQUAL (logicaListarComandos (NULL, NULL), 0);
}



// Função principal
int main () {

    CU_initialize_registry ();

    CU_pSuite suite = CU_add_suite ("Testes - Auxiliares.c", NULL, NULL);

    CU_add_test (suite, "logicaGravar", teste_logicaGravar);
    CU_add_test (suite, "logicaLer", teste_logicaLer);
    CU_add_test (suite, "logicaPintarCasa", teste_logicaPintarCasa);
    CU_add_test (suite, "logicaRiscarCasa", teste_logicaRiscarCasa);
    CU_add_test (suite, "logicaVizualizarHistorico", teste_logicaVizualizarHistorico);
    CU_add_test (suite, "logicaVerifica", teste_logicaVerifica);
    CU_add_test (suite, "logicaAjuda", teste_logicaAjuda);
    CU_add_test (suite, "logicaAjudaRep", teste_logicaAjudaRep);
    CU_add_test (suite, "logicaResolveJogo", teste_logicaResolveJogo);
    CU_add_test (suite, "logicaListarComandos", teste_logicaListarComandos);

    CU_basic_set_mode (CU_BRM_VERBOSE);
    CU_basic_run_tests ();
    CU_cleanup_registry ();

    return 0;
}