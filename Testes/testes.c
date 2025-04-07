#include "CUnit/Basic.h"
#include "jogo.h"
#include <stdio.h>
#include <stdlib.h>

void teste_IniciaJogo () {

    IJ jogo;

    // Inicializar o jogo 
    int result = iniciaJogo (&jogo);

    // Verifica se a inicialização foi bem-sucedida
    CU_ASSERT_EQUAL (result, 0);

    // Verificar as dimensões do tabuleiro
    CU_ASSERT_EQUAL (jogo.linhas, 5); 
    CU_ASSERT_EQUAL (jogo.colunas, 5); 

    // Verificar o conteúdo do tabuleiro
    CU_ASSERT_STRING_EQUAL (jogo.Tabuleiro [0], "ecadc\n");
    CU_ASSERT_STRING_EQUAL (jogo.Tabuleiro [1], "dcdec\n");
    CU_ASSERT_STRING_EQUAL (jogo.Tabuleiro [2], "bddce\n");
    CU_ASSERT_STRING_EQUAL (jogo.Tabuleiro [3], "cdeeb\n");
    CU_ASSERT_STRING_EQUAL (jogo.Tabuleiro [4], "accbb");

    // Libertar memória alocada
    for (int i = 0; i < jogo.linhas; i++) free (jogo.Tabuleiro[i]);
    free (jogo.Tabuleiro);
}



void teste_MudaCasaParaMaiuscula () {

    IJ jogo;
    iniciaJogo(&jogo);  

    /* ACHAM NECESSÁRIO?? */
    CU_ASSERT_EQUAL (jogo.Tabuleiro [0][0], 'e');  

    mudaCasaParaMaiuscula (&jogo);
    // Verifica se a casa foi alterada para maiúscula
    CU_ASSERT_EQUAL (jogo.Tabuleiro [0][0], 'E');  

    /* ACHAM QUE TAMBÉM É SEMPRE NECESSÁRIO ESTAR A FAZER ISTO? */
    for (int i = 0; i < jogo.linhas; i++) free(jogo.Tabuleiro[i]);
    free (jogo.Tabuleiro);
}



void teste_MudaCasaParaVazio () {

    IJ jogo;
    iniciaJogo(&jogo);  

    mudaCasaParaMaiuscula (&jogo);
    CU_ASSERT_EQUAL (jogo.Tabuleiro[1][0], '#'); // Verifica se a casa foi alterada para vazio
}



void teste_CoordenadaValida () {

    // Dimensões do tabuleiro
    int linhas = 5;
    int colunas = 5;

    // Casos válidos
    CU_ASSERT_EQUAL (coordenadaValida(1, 'a', linhas, colunas), 1);  
    CU_ASSERT_EQUAL (coordenadaValida(5, 'e', linhas, colunas), 1);  

    // Casos inválidos
    CU_ASSERT_EQUAL (coordenadaValida(0, 'a', linhas, colunas), 0); 
    CU_ASSERT_EQUAL (coordenadaValida(6, 'a', linhas, colunas), 0);  
    CU_ASSERT_EQUAL (coordenadaValida(3, 'z', linhas, colunas), 0);  
}



int main () {

    if (CUE_SUCCESS != CU_initialize_registry ()) return CU_get_error ();

    CU_basic_set_mode (CU_BRM_VERBOSE);

    CU_pSuite pSuite = NULL;
    pSuite = CU_add_suite ("sum_test_suite", 0, 0);

    if (NULL == pSuite) {
        CU_cleanup_registry ();
        return CU_get_error ();
    }

    if (NULL == CU_add_test (pSuite, "testar iniciaJogo", teste_IniciaJogo)) {
        CU_cleanup_registry ();
        return CU_get_error ();
    }

    if (NULL == CU_add_test (pSuite, "testar mudaCasaParaMaiuscula", teste_MudaCasaParaMaiuscula)) {
        CU_cleanup_registry ();
        return CU_get_error ();
    }

    if (NULL == CU_add_test (pSuite, "testar mudaCasaParaVazio", teste_MudaCasaParaMaiuscula)) {
        CU_cleanup_registry ();
        return CU_get_error ();
    }

    if (NULL == CU_add_test (pSuite, "testar coordenadaValida", teste_CoordenadaValida)) {
        CU_cleanup_registry ();
        return CU_get_error ();
    }
    
    CU_basic_run_tests ();
    return CU_get_error ();
}