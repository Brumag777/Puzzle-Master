#include "Puzzle.h"

// Testa a função 'verificaInfracoes'
void teste_verificaInfracoes () {

    // Inicializa a informação sobre o jogo
    Info I = inicializaJogo ();
    I -> dL = 3;
    I -> dC = 5;
    I -> nTabuleiro = 1;

    // Aloca memória para o tabuleiro
    inicializaTabuleiro (I);

    // Inicializa o tabuleiro
    strcpy (I -> Tabuleiro [0], "E#cDc");
    strcpy (I -> Tabuleiro [1], "dcD#C");
    strcpy (I -> Tabuleiro [2], "bddCe");

    // Testa a função para o tabuleiro atual
    CU_ASSERT_EQUAL (verificaInfracoes (I, 0), 1);

    // Altera o tabuleiro
    I -> Tabuleiro [1][0] = 'D';

    // Testa a função para o tabuleiro atual
    CU_ASSERT_EQUAL (verificaInfracoes (I, 0), 0);

    // Retorna o tabuleiro ao original
    I -> Tabuleiro [1][0] = 'd';

    // Altera o tabuleiro
    I -> Tabuleiro [2][2] = 'D';

    // Testa a função para o tabuleiro atual
    CU_ASSERT_EQUAL (verificaInfracoes (I, 0), 0);

    // Retorna o tabuleiro ao original
    I -> Tabuleiro [2][2] = 'd';

    // Altera o tabuleiro
    I -> Tabuleiro [0][2] = '#';

    // Testa a função para o tabuleiro atual
    CU_ASSERT_EQUAL (verificaInfracoes (I, 0), 0);

    // Liberta a memória alocada para a informação do jogo
    libertaInfo (I);
}



// Testa a função 'verificaCaminhoOrtogonal'
void teste_verificaCaminhoOrtogonal () {

    // Inicializa a informação sobre o jogo
    Info I = inicializaJogo ();
    I -> dL = 3;
    I -> dC = 5;
    I -> nTabuleiro = 1;

    // Aloca memória para o tabuleiro
    inicializaTabuleiro (I);

    // Inicializa o tabuleiro
    strcpy (I -> Tabuleiro [0], "E#cDc");
    strcpy (I -> Tabuleiro [1], "dcD#C");
    strcpy (I -> Tabuleiro [2], "bddCe");

    // Testa a função para o tabuleiro atual
    CU_ASSERT_EQUAL (verificaCaminhoOrtogonal (I, 0), 1);

    // Altera o tabuleiro
    I -> Tabuleiro [1][0] = 'D';

    // Testa a função para o tabuleiro atual
    CU_ASSERT_EQUAL (verificaCaminhoOrtogonal (I, 0), 1);

    // Altera o tabuleiro
    I -> Tabuleiro [1][0] = '#';

    // Testa a função para o tabuleiro atual
    CU_ASSERT_EQUAL (verificaCaminhoOrtogonal (I, 0), 0);

    // Liberta a memória alocada para a informação do jogo
    libertaInfo (I);
}



// Testa a função 'ajudaUmaVez'
void teste_ajudaUmaVez () {

    // Inicializa a informação sobre o jogo
    Info I = inicializaJogo ();
    I -> dL = 3;
    I -> dC = 5;
    I -> nTabuleiro = 1;

    // Aloca memória para o tabuleiro
    inicializaTabuleiro (I);

    // Inicializa o tabuleiro
    strcpy (I -> Tabuleiro [0], "ecadc");
    strcpy (I -> Tabuleiro [1], "dcdec");
    strcpy (I -> Tabuleiro [2], "bfdce");

    // Realiza a função
    CU_ASSERT_EQUAL (ajudaUmaVez (I), 0);

    // Altera o tabuleiro
    I -> Tabuleiro [1][2] = 'D';
    I -> Tabuleiro [2][3] = '#';

    // Realiza a função
    CU_ASSERT_EQUAL (ajudaUmaVez (I), 1);

    // Testa o resultado da função
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [0], "ECadc"), 0);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [1], "#CDEC"), 0);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [2], "BF##E"), 0);

    // Liberta a memória alocada para a informação do jogo
    libertaInfo (I);
}



// Testa a função 'resolve'
void teste_resolve () {

    // Inicializa a informação sobre o jogo
    Info I = inicializaJogo ();
    I -> dL = 3;
    I -> dC = 5;
    I -> nTabuleiro = 1;

    // Aloca memória para o tabuleiro
    inicializaTabuleiro (I);

    // Declara o tabuleiro original
    char TabOriginal [3][7];

    // Inicializa o tabuleiro
    strcpy (I -> Tabuleiro [0], "eCadc");
    strcpy (I -> Tabuleiro [1], "dcdec");
    strcpy (I -> Tabuleiro [2], "bfdce");

    // Inicializa o tabuleiro original
    strcpy (TabOriginal [0], "eCadc");
    strcpy (TabOriginal [1], "dcdec");
    strcpy (TabOriginal [2], "bfdce");

    // Realiza a função
    CU_ASSERT_EQUAL (resolve (I, 3, 5, TabOriginal), 0);

    // Altera os tabuleiros
    I -> Tabuleiro [0][1] = TabOriginal [0][1] = 'c';

    // Realiza a função
    CU_ASSERT_EQUAL (resolve (I, 3, 5, TabOriginal), 1);

    // Testa o resultado da função
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [0], "E#ADC"), 0);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [1], "DC#E#"), 0);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [2], "BFDCE"), 0);

    // Liberta a memória alocada para a informação do jogo
    libertaInfo (I);
}



// Função principal
int main () {

    CU_initialize_registry ();

    CU_pSuite suite = CU_add_suite ("Testes - Auxiliares.c", NULL, NULL);

    CU_add_test (suite, "verificaInfracoes", teste_verificaInfracoes);
    CU_add_test (suite, "verificaCaminhoOrtogonal", teste_verificaCaminhoOrtogonal);
    CU_add_test (suite, "ajudaUmaVez", teste_ajudaUmaVez);
    CU_add_test (suite, "resolve", teste_resolve);

    CU_basic_set_mode (CU_BRM_VERBOSE);
    CU_basic_run_tests ();
    CU_cleanup_registry ();

    return 0;
}