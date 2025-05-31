// Testa a função 'restricoesSair'
void teste_restricoesSair () {

    // Argumento
    char arg [23] = {0};

    // Testa a função
    CU_ASSERT_EQUAL (restricoesSair (arg), 0);

    // Altera o argumento
    strcpy (arg, "ARGUMENTO");

    // Testa a função
    CU_ASSERT_EQUAL (restricoesSair (arg), 1);
}



// Testa a função 'restricoesGravar'
void teste_restricoesGravar () {

    // Argumento
    char arg [23] = {0};

    // Inicializa a informação
    Info I = inicializaInfo ();

    // Testa a função
    CU_ASSERT_EQUAL (restricoesGravar (arg, I), 1);

    // Altera o número do tabuleiro
    I -> nTabuleiro = 1;

    // Testa a função
    CU_ASSERT_EQUAL (restricoesGravar (arg, I), 0);

    // Altera o argumento
    arg [0] = '0';

    // Testa a função
    CU_ASSERT_EQUAL (restricoesGravar (arg, I), 2);

    // Altera o argumento
    arg [0] = '1';
    arg [1] = '0';
    arg [2] = '0';

    // Testa a função
    CU_ASSERT_EQUAL (restricoesGravar (arg, I), 3);

    // Altera o argumento
    arg [1] = 0;

    // Testa a função
    CU_ASSERT_EQUAL (restricoesGravar (arg, I), 0);

    // Liberta a informação
    libertaInfo (I);
}



// Testa a função 'restricoesLer'
void teste_restricoesLer () {

    // Argumentos
    char arg1 [23] = {0}, arg2 [23] = {0};

    // Testa a função
    CU_ASSERT_EQUAL (restricoesLer (arg1, arg2), 1);

    // Altera o primeiro argumento
    arg1 [0] = '0';

    // Testa a função
    CU_ASSERT_EQUAL (restricoesLer (arg1, arg2), 2);

    // Altera o primeiro argumento
    arg1 [0] = '1';
    arg1 [1] = '0';
    arg1 [2] = '0';

    // Testa a função
    CU_ASSERT_EQUAL (restricoesLer (arg1, arg2), 3);

    // Altera o primeiro argumento
    arg1 [1] = 0;

    // Testa a função
    CU_ASSERT_EQUAL (restricoesLer (arg1, arg2), 0);

    // Altera o segundo argumento
    arg2 [0] = '0';

    // Testa a função
    CU_ASSERT_EQUAL (restricoesLer (arg1, arg2), 2);

    // Altera o segundo argumento
    arg2 [0] = '1';
    arg2 [1] = '0';
    arg2 [2] = '0';

    // Testa a função
    CU_ASSERT_EQUAL (restricoesLer (arg1, arg2), 3);

    // Altera o segundo argumento
    arg2 [1] = 0;

    // Testa a função
    CU_ASSERT_EQUAL (restricoesLer (arg1, arg2), 0);
}



// Testa a função 'restricoesImprimePont'
void teste_restricoesImprimePont () {

    // Argumento
    char arg [23] = "1";

    // Inicializa a informação
    Info I = inicializaInfo ();

    // Testa a função
    CU_ASSERT_EQUAL (restricoesImprimePont (arg, I), 1);

    // Altera o argumento
    arg [0] = 0;

    // Testa a função
    CU_ASSERT_EQUAL (restricoesImprimePont (arg, I), 2);

    // Altera o número do tabuleiro
    I -> nTabuleiro = 1;

    // Testa a função
    CU_ASSERT_EQUAL (restricoesImprimePont (arg, I), 0);

    // Liberta a informação
    libertaInfo (I);
}



// Testa a função 'restricoesExplica'
void teste_restricoesExplica () {

    // Argumento
    char arg [23] = {0};

    // Testa a função
    CU_ASSERT_EQUAL (restricoesExplica (arg), 0);

    // Altera o argumento
    strcpy (arg, "ARGUMENTO");

    // Testa a função
    CU_ASSERT_EQUAL (restricoesExplica (arg), 1);
}



// Testa a função 'restricoesCriarJogo'
void teste_restricoesCriarJogo () {

    // Argumento
    char arg [23] = {0};

    // Testa a função
    CU_ASSERT_EQUAL (restricoesCriarJogo (arg), 0);

    // Altera o argumento
    strcpy (arg, "ARGUMENTO");

    // Testa a função
    CU_ASSERT_EQUAL (restricoesCriarJogo (arg), 1);
}



// Testa a função 'restricoesEliminarJogo'
void teste_restricoesEliminarJogo () {

    // Argumentos
    char arg1 [23] = {0}, arg2 [23] = {0};

    // Testa a função
    CU_ASSERT_EQUAL (restricoesEliminarJogo (arg1, arg2), 1);

    // Altera o primeiro argumento
    arg1 [0] = '0';

    // Testa a função
    CU_ASSERT_EQUAL (restricoesEliminarJogo (arg1, arg2), 2);

    // Altera o primeiro argumento
    arg1 [0] = '3';

    // Testa a função
    CU_ASSERT_EQUAL (restricoesEliminarJogo (arg1, arg2), 3);

    // Altera o primeiro argumento
    arg1 [0] = '5';
    arg1 [1] = '0';
    arg1 [2] = '0';

    // Testa a função
    CU_ASSERT_EQUAL (restricoesEliminarJogo (arg1, arg2), 4);

    // Altera o primeiro argumento
    arg1 [1] = 0;

    // Testa a função
    CU_ASSERT_EQUAL (restricoesEliminarJogo (arg1, arg2), 0);

    // Altera o segundo argumento
    arg2 [0] = '0';

    // Testa a função
    CU_ASSERT_EQUAL (restricoesEliminarJogo (arg1, arg2), 2);

    // Altera o segundo argumento
    arg2 [0] = '5';
    arg2 [1] = '0';
    arg2 [2] = '0';

    // Testa a função
    CU_ASSERT_EQUAL (restricoesEliminarJogo (arg1, arg2), 4);

    // Altera o segundo argumento
    arg2 [1] = 0;

    // Testa a função
    CU_ASSERT_EQUAL (restricoesEliminarJogo (arg1, arg2), 0);

    // Altera o primeiro argumento
    arg1 [0] = '3';

    // Testa a função
    CU_ASSERT_EQUAL (restricoesEliminarJogo (arg1, arg2), 0);
}



// Testa a função 'restricoesIndicaJogos'
void teste_restricoesIndicaJogos () {

    // Argumento
    char arg [23] = {0};

    // Testa a função
    CU_ASSERT_EQUAL (restricoesIndicaJogos (arg), 0);

    // Altera o argumento
    strcpy (arg, "ARGUMENTO");

    // Testa a função
    CU_ASSERT_EQUAL (restricoesIndicaJogos (arg), 1);
}



// Testa a função 'restricoesMudarCasa'
void teste_restricoesMudarCasa () {

    // Argumento
    char arg [23] = {0};

    // Inicializa a informação
    Info I = inicializaInfo ();

    // Testa a função
    CU_ASSERT_EQUAL (restricoesMudarCasa (arg, I), 1);

    // Altera o argumento
    arg [0] = 'A';
    arg [1] = '0';

    // Testa a função
    CU_ASSERT_EQUAL (restricoesMudarCasa (arg, I), 2);

    // Inicializa o tabuleiro
    I -> nTabuleiro = 1;
    I -> dL = I -> dC = 3;
    inicializaTabuleiro (I);
    strcpy (I -> Tabuleiro [0], "A#a");

    // Testa a função
    CU_ASSERT_EQUAL (restricoesMudarCasa (arg, I), 3);

    // Altera o argumento
    arg [0] = 'd';

    // Testa a função
    CU_ASSERT_EQUAL (restricoesMudarCasa (arg, I), 3);

    // Altera o argumento
    arg [1] = '1';

    // Testa a função
    CU_ASSERT_EQUAL (restricoesMudarCasa (arg, I), 4);

    // Altera o argumento
    arg [0] = 'a';

    // Testa a função
    CU_ASSERT_EQUAL (restricoesMudarCasa (arg, I), 5);

    // Altera o argumento
    arg [0] = 'b';

    // Testa a função
    CU_ASSERT_EQUAL (restricoesMudarCasa (arg, I), 6);

    // Altera o argumento
    arg [0] = 'c';

    // Testa a função
    CU_ASSERT_EQUAL (restricoesMudarCasa (arg, I), 0);

    // Liberta a informação
    libertaInfo (I);
}



// Testa a função 'restricoesVisualizarHistorico'
void teste_restricoesVisualizarHistorico () {

    // Argumento
    char arg [23] = "0";

    // Inicializa a informação
    Info I = inicializaInfo ();

    // Testa a função
    CU_ASSERT_EQUAL (restricoesVisualizarHistorico (arg, I), 1);

    // Altera o número do tabuleiro
    I -> nTabuleiro = 3;

    // Testa a função
    CU_ASSERT_EQUAL (restricoesVisualizarHistorico (arg, I), 2);

    // Altera o argumento
    arg [0] = '5';

    // Testa a função
    CU_ASSERT_EQUAL (restricoesVisualizarHistorico (arg, I), 3);

    // Altera o argumento
    arg [0] = '1';

    // Testa a função
    CU_ASSERT_EQUAL (restricoesVisualizarHistorico (arg, I), 0);

    // Altera o argumento
    arg [0] = 0;

    // Testa a função
    CU_ASSERT_EQUAL (restricoesVisualizarHistorico (arg, I), 0);

    // Liberta a informação
    libertaInfo (I);
}



// Testa a função 'restricoesVerifica'
void teste_restricoesVerifica () {

    // Argumento
    char arg [23] = {0};

    // Inicializa a informação
    Info I = inicializaInfo ();

    // Testa a função
    CU_ASSERT_EQUAL (restricoesVerifica (arg, I), 2);

    // Altera o argumento
    strcpy (arg, "ARGUMENTO");

    // Testa a função
    CU_ASSERT_EQUAL (restricoesVerifica (arg, I), 1);

    // Altera o argumento
    arg [0] = 0;

    // Altera o número do tabuleiro
    I -> nTabuleiro = 1;

    // Testa a função
    CU_ASSERT_EQUAL (restricoesVerifica (arg, I), 0);

    // Liberta a informação
    libertaInfo (I);
}



// Testa a função 'restricoesAjuda'
void teste_restricoesAjuda () {

    // Argumento
    char arg [23] = {0};

    // Inicializa a informação
    Info I = inicializaInfo ();

    // Testa a função
    CU_ASSERT_EQUAL (restricoesAjuda (arg, I), 1);

    // Altera o número do tabuleiro
    I -> nTabuleiro = 1;

    // Testa a função
    CU_ASSERT_EQUAL (restricoesAjuda (arg, I), 0);

    // Altera o argumento
    arg [0] = '1';
    arg [1] = '1';

    // Testa a função
    CU_ASSERT_EQUAL (restricoesAjuda (arg, I), 2);

    // Altera o argumento
    arg [1] = 0;

    // Testa a função
    CU_ASSERT_EQUAL (restricoesAjuda (arg, I), 2);

    // Altera o argumento
    arg [0] = 'b';

    // Testa a função
    CU_ASSERT_EQUAL (restricoesAjuda (arg, I), 0);

    // Altera o argumento
    arg [0] = 'r';

    // Testa a função
    CU_ASSERT_EQUAL (restricoesAjuda (arg, I), 0);

    // Altera o argumento
    arg [0] = 'o';

    // Testa a função
    CU_ASSERT_EQUAL (restricoesAjuda (arg, I), 0);

    // Liberta a informação
    libertaInfo (I);
}



// Testa a função 'restricoesAjudaRep'
void teste_restricoesAjudaRep () {

    // Argumento
    char arg [23] = {0};

    // Inicializa a informação
    Info I = inicializaInfo ();

    // Testa a função
    CU_ASSERT_EQUAL (restricoesAjudaRep (arg, I), 2);

    // Altera o argumento
    strcpy (arg, "ARGUMENTO");

    // Testa a função
    CU_ASSERT_EQUAL (restricoesAjudaRep (arg, I), 1);

    // Altera o argumento
    arg [0] = 0;

    // Altera o número do tabuleiro
    I -> nTabuleiro = 1;

    // Testa a função
    CU_ASSERT_EQUAL (restricoesAjudaRep (arg, I), 0);

    // Liberta a informação
    libertaInfo (I);
}



// Testa a função 'restricoesDesfazerJogadas'
void teste_restricoesDesfazerJogadas () {

    // Argumento
    char arg [23] = {0};

    // Inicializa a informação
    Info I = inicializaInfo ();

    // Testa a função
    CU_ASSERT_EQUAL (restricoesDesfazerJogadas (arg, I), 1);

    // Altera o número do tabuleiro
    I -> nTabuleiro = 1;

    // Testa a função
    CU_ASSERT_EQUAL (restricoesDesfazerJogadas (arg, I), 2);

    // Altera o número do tabuleiro
    I -> nTabuleiro = 3;

    // Testa a função
    CU_ASSERT_EQUAL (restricoesDesfazerJogadas (arg, I), 0);

    // Altera o argumento
    arg [0] = '0';

    // Testa a função
    CU_ASSERT_EQUAL (restricoesDesfazerJogadas (arg, I), 3);

    // Altera o argumento
    arg [0] = '3';

    // Testa a função
    CU_ASSERT_EQUAL (restricoesDesfazerJogadas (arg, I), 4);

    // Altera o argumento
    arg [0] = '4';

    // Testa a função
    CU_ASSERT_EQUAL (restricoesDesfazerJogadas (arg, I), 5);

    // Altera o argumento
    arg [0] = '2';

    // Testa a função
    CU_ASSERT_EQUAL (restricoesDesfazerJogadas (arg, I), 0);

    // Liberta a informação
    libertaInfo (I);
}



// Testa a função 'restricoesSolucaoJogo'
void teste_restricoesSolucaoJogo () {

    // Argumento
    char arg [23] = {0};

    // Inicializa a informação
    Info I = inicializaInfo ();

    // Testa a função
    CU_ASSERT_EQUAL (restricoesSolucaoJogo (arg, I), 2);

    // Altera o argumento
    strcpy (arg, "ARGUMENTO");

    // Testa a função
    CU_ASSERT_EQUAL (restricoesSolucaoJogo (arg, I), 1);

    // Altera o argumento
    arg [0] = 0;

    // Altera o número do tabuleiro
    I -> nTabuleiro = 1;

    // Testa a função
    CU_ASSERT_EQUAL (restricoesSolucaoJogo (arg, I), 0);

    // Liberta a informação
    libertaInfo (I);
}



// Função principal
void testesComandosRestricoes (CU_pSuite suite) {
    CU_add_test (suite, "restricoesSair", teste_restricoesSair);
    CU_add_test (suite, "restricoesGravar", teste_restricoesGravar);
    CU_add_test (suite, "restricoesLer", teste_restricoesLer);
    CU_add_test (suite, "restricoesImprimePont", teste_restricoesImprimePont);
    CU_add_test (suite, "restricoesExplica", teste_restricoesExplica);
    CU_add_test (suite, "restricoesCriarJogo", teste_restricoesCriarJogo);
    CU_add_test (suite, "restricoesEliminarJogo", teste_restricoesEliminarJogo);
    CU_add_test (suite, "restricoesIndicaJogos", teste_restricoesIndicaJogos);
    CU_add_test (suite, "restricoesMudarCasa", teste_restricoesMudarCasa);
    CU_add_test (suite, "restricoesVisualizarHistorico", teste_restricoesVisualizarHistorico);
    CU_add_test (suite, "restricoesVerifica", teste_restricoesVerifica);
    CU_add_test (suite, "restricoesAjuda", teste_restricoesAjuda);
    CU_add_test (suite, "restricoesAjudaRep", teste_restricoesAjudaRep);
    CU_add_test (suite, "restricoesDesfazerJogadas", teste_restricoesDesfazerJogadas);
    CU_add_test (suite, "restricoesSolucaoJogo", teste_restricoesSolucaoJogo);
}