// Testa a função 'logicaSair'
void teste_logicaSair () {

    // Inicializa a informação
    Info I = inicializaInfo ();

    // Realiza a função
    logicaSair (I);

    // Testa o resultado da função
    CU_ASSERT_EQUAL (I -> aCorrer, false);

    // Liberta a informação do jogo
    libertaInfo (I);
}



// Testa a função 'logicaGravar'
void teste_logicaGravar () {

    // Inicializa a informação
    Info I = inicializaInfo ();

    // Inicializa o tabuleiro
    I -> dL = 5;
    I -> dC = 5;
    I -> nTabuleiro = 1;
    inicializaTabuleiro (I);

    // Indica que o jogo não está a correr
    I -> aCorrer = false;

    // Indica o número do jogo
    I -> nJogo = 4;

    // Define o tabuleiro
    strcpy (I -> Tabuleiro [0], "bbecc");
    strcpy (I -> Tabuleiro [1], "eccbd");
    strcpy (I -> Tabuleiro [2], "bcdcb");
    strcpy (I -> Tabuleiro [3], "cdbda");
    strcpy (I -> Tabuleiro [4], "abcdb");

    // Aloca memória para os arrays de alterações
    Alt *J1 = malloc (sizeof (ALT));
    Alt *J2 = malloc (sizeof (ALT));
    Alt *J3 = malloc (4 * (sizeof (ALT)));

    // Inicializa J1
    formaJogada (&J1 [0], 1, 'a', 'e');

    // Inicializa J2
    formaJogada (&J2 [0], 2, 'd', 'e');

    // Inicializa J3
    formaJogada (&J3 [0], 1, 'd', 'd');
    formaJogada (&J3 [1], 2, 'c', 'd');
    formaJogada (&J3 [2], 2, 'e', 'c');
    formaJogada (&J3 [3], 3, 'd', 'c');

    // Adiciona as jogadas ao histórico
    addJogada (I, J1, 1);
    addJogada (I, J2, 1);
    addJogada (I, J3, 4);

    // Testa a função
    CU_ASSERT_TRUE (logicaGravar ("", I) >= -1);
    CU_ASSERT_TRUE (logicaGravar ("1", I) >= -1);

    // Altera o número do jogo
    I -> nJogo = 0;

    // Testa a função
    CU_ASSERT_EQUAL (logicaGravar ("", I), -1);

    // Liberta a informação do jogo
    libertaInfo (I);
}



// Testa a função 'logicaLer'
void teste_logicaLer () {

    // Inicializa a informação
    Info I = inicializaInfo ();

    // Segundo argumento
    char arg2 [23] = {0};

    // Testa a função
    CU_ASSERT_EQUAL (logicaLer ("-1", arg2, I), 1);
    CU_ASSERT_EQUAL (logicaLer ("0", "0", I), 0);

    // Liberta a informação do jogo
    libertaInfo (I);
}



// Testa a função 'logicaInfoComandos'
void teste_logicaInfoComandos () {
    CU_ASSERT_EQUAL (logicaInfoComandos ("ARGUMENTOINVALIDO"), -1);
    CU_ASSERT_EQUAL (logicaInfoComandos ("?"), -1);
    CU_ASSERT_EQUAL (logicaInfoComandos ("s"), 's');
    CU_ASSERT_EQUAL (logicaInfoComandos ("l"), 'l');
    CU_ASSERT_EQUAL (logicaInfoComandos ("c"), 'c');
    CU_ASSERT_EQUAL (logicaInfoComandos ("E"), 'E');
    CU_ASSERT_EQUAL (logicaInfoComandos ("h"), 'h');
    CU_ASSERT_EQUAL (logicaInfoComandos ("b"), 'b');
    CU_ASSERT_EQUAL (logicaInfoComandos ("r"), 'r');
    CU_ASSERT_EQUAL (logicaInfoComandos ("V"), 'V');
    CU_ASSERT_EQUAL (logicaInfoComandos ("g"), 'g');
    CU_ASSERT_EQUAL (logicaInfoComandos ("v"), 'v');
    CU_ASSERT_EQUAL (logicaInfoComandos ("j"), 'j');
    CU_ASSERT_EQUAL (logicaInfoComandos ("a"), 'a');
    CU_ASSERT_EQUAL (logicaInfoComandos ("A"), 'A');
    CU_ASSERT_EQUAL (logicaInfoComandos ("R"), 'R');
    CU_ASSERT_EQUAL (logicaInfoComandos ("p"), 'p');
    CU_ASSERT_EQUAL (logicaInfoComandos ("d"), 'd');
    CU_ASSERT_EQUAL (logicaInfoComandos ("e"), 'e');
    CU_ASSERT_EQUAL (logicaInfoComandos ("D"), 'D');
    CU_ASSERT_EQUAL (logicaInfoComandos ("X"), 'X');
}



// Testa a função 'logicaPintarCasa'
void teste_logicaPintarCasa () {

    // Inicializa a informação
    Info I = inicializaInfo ();

    // Inicializa o tabuleiro
    I -> dL = 3;
    I -> dC = 5;
    I -> nTabuleiro = 1;
    inicializaTabuleiro (I);

    // Define o tabuleiro
    strcpy (I -> Tabuleiro [0], "ecadc");
    strcpy (I -> Tabuleiro [1], "dcdec");
    strcpy (I -> Tabuleiro [2], "dfdce");

    // Define a pontuação
    I -> pont = 1;

    // Realiza a função
    logicaPintarCasa ("a1", I);
    logicaPintarCasa ("b1", I);

    // Testa o resultado da função
    CU_ASSERT_EQUAL (I -> pont, 0);
    CU_ASSERT_EQUAL (I -> Tabuleiro [0][0], 'E');
    CU_ASSERT_EQUAL (I -> Tabuleiro [0][1], 'C');

    // Liberta a informação do jogo
    libertaInfo (I);
}



// Testa a função 'logicaRiscarCasa'
void teste_logicaRiscarCasa () {

    // Inicializa a informação
    Info I = inicializaInfo ();

    // Inicializa o tabuleiro
    I -> dL = 3;
    I -> dC = 5;
    I -> nTabuleiro = 1;
    inicializaTabuleiro (I);

    // Define o tabuleiro
    strcpy (I -> Tabuleiro [0], "ecadc");
    strcpy (I -> Tabuleiro [1], "dcdec");
    strcpy (I -> Tabuleiro [2], "dfdce");

    // Define a pontuação
    I -> pont = 1;

    // Realiza a função
    logicaRiscarCasa ("a1", I);
    logicaRiscarCasa ("b1", I);

    // Testa o resultado da função
    CU_ASSERT_EQUAL (I -> pont, 0);
    CU_ASSERT_EQUAL (I -> Tabuleiro [0][0], '#');
    CU_ASSERT_EQUAL (I -> Tabuleiro [0][1], '#');

    // Liberta a informação do jogo
    libertaInfo (I);
}



// Testa a função 'logicaVerifica'
void teste_logicaVerifica () {

    // Inicializa a informação
    Info I = inicializaInfo ();

    // Inicializa o tabuleiro
    I -> dL = 3;
    I -> dC = 5;
    I -> nTabuleiro = 1;
    inicializaTabuleiro (I);

    // Indica que o jogo não está a correr
    I -> aCorrer = false;

    // Define o tabuleiro
    strcpy (I -> Tabuleiro [0], "ecadc");
    strcpy (I -> Tabuleiro [1], "dcDec");
    strcpy (I -> Tabuleiro [2], "dfdce");

    // Testa a função
    CU_ASSERT_EQUAL (logicaVerifica (I), 1);

    // Altera o tabuleiro
    I -> Tabuleiro [2][2] = 'D';

    // Testa a função
    CU_ASSERT_EQUAL (logicaVerifica (I), 0);

    // Liberta a informação do jogo
    libertaInfo (I);
}



// Testa a função 'logicaAjuda'
void teste_logicaAjuda () {

    // Inicializa a informação
    Info I = inicializaInfo ();

    // Inicializa o tabuleiro
    I -> dL = 3;
    I -> dC = 5;
    I -> nTabuleiro = 1;
    inicializaTabuleiro (I);

    // Indica que o jogo não está a correr
    I -> aCorrer = false;

    // Define o tabuleiro
    strcpy (I -> Tabuleiro [0], "e#adc");
    strcpy (I -> Tabuleiro [1], "#cDec");
    strcpy (I -> Tabuleiro [2], "dfDce");

    // Testa a função
    CU_ASSERT_EQUAL (logicaAjuda ("r", I), 2);

    // Altera o tabuleiro
    strcpy (I -> Tabuleiro [0], "ecadc");
    strcpy (I -> Tabuleiro [1], "dcDec");
    strcpy (I -> Tabuleiro [2], "dfdce");

    // Testa a função
    CU_ASSERT_EQUAL (logicaAjuda ("o", I), 1);
    CU_ASSERT_EQUAL (logicaAjuda ("b", I), 1);
    CU_ASSERT_EQUAL (logicaAjuda ("", I), 0);

    // Liberta a informação do jogo
    libertaInfo (I);
}



// Testa a função 'logicaAjudaRep'
void teste_logicaAjudaRep () {

    // Inicializa a informação
    Info I = inicializaInfo ();

    // Inicializa o tabuleiro
    I -> dL = 3;
    I -> dC = 5;
    I -> nTabuleiro = 1;
    inicializaTabuleiro (I);

    // Indica que o jogo não está a correr
    I -> aCorrer = false;

    // Define o tabuleiro
    strcpy (I -> Tabuleiro [0], "e#adc");
    strcpy (I -> Tabuleiro [1], "#cDec");
    strcpy (I -> Tabuleiro [2], "dfDce");

    // Testa a função
    CU_ASSERT_EQUAL (logicaAjudaRep (I), 2);

    // Altera o tabuleiro
    strcpy (I -> Tabuleiro [0], "ecadc");
    strcpy (I -> Tabuleiro [1], "dcdec");
    strcpy (I -> Tabuleiro [2], "dfdce");

    // Testa a função
    CU_ASSERT_EQUAL (logicaAjudaRep (I), 1);

    // Altera o tabulerio
    I -> Tabuleiro [1][2] = 'D';

    // Testa a função
    CU_ASSERT_EQUAL (logicaAjudaRep (I), 0);

    // Liberta a informação do jogo
    libertaInfo (I);
}



// Testa a função 'logicaDesfazerJogadas'
void teste_logicaDesfazerJogadas () {

    // Inicializa a informação
    Info I = inicializaInfo ();

    // Inicializa o tabuleiro
    I -> dL = 3;
    I -> dC = 5;
    I -> nTabuleiro = 1;
    inicializaTabuleiro (I);

    // Define o tabuleiro
    strcpy (I -> Tabuleiro [0], "ecadc");
    strcpy (I -> Tabuleiro [1], "dcdec");
    strcpy (I -> Tabuleiro [2], "dfdce");

    // Aloca memória para os arrays de alterações
    Alt *J1 = malloc (sizeof (ALT));
    Alt *J2 = malloc (sizeof (ALT));
    Alt *J3 = malloc (4 * (sizeof (ALT)));

    // Inicializa J1
    formaJogada (&J1 [0], 1, 'a', 'e');

    // Inicializa J2
    formaJogada (&J2 [0], 2, 'd', 'e');

    // Inicializa J3
    formaJogada (&J3 [0], 1, 'd', 'd');
    formaJogada (&J3 [1], 2, 'c', 'd');
    formaJogada (&J3 [2], 2, 'e', 'c');
    formaJogada (&J3 [3], 3, 'd', 'c');

    // Adiciona as jogadas ao histórico
    addJogada (I, J1, 1);
    addJogada (I, J2, 1);
    addJogada (I, J3, 4);

    // Define a pontuação
    I -> pont = 5;

    // Realiza a função
    logicaDesfazerJogadas ("", I);

    // Testa o resultado da função
    CU_ASSERT_EQUAL (I -> pont, 4);

    // Realiza a função
    logicaDesfazerJogadas ("1", I);

    // Testa o resultado da função
    CU_ASSERT_EQUAL (I -> pont, 2);

    // Liberta a informação do jogo
    libertaInfo (I);
}



// Testa a função 'logicaSolucaoJogo'
void teste_logicaSolucaoJogo () {

    // Inicializa a informação
    Info I = inicializaInfo ();

    // Inicializa o tabuleiro
    I -> dL = 2;
    I -> dC = 2;
    I -> nTabuleiro = 1;
    inicializaTabuleiro (I);
    
    // Indica que o jogo não está a correr
    I -> aCorrer = false;

    // Define o tabuleiro
    strcpy (I -> Tabuleiro [0], "a#");
    strcpy (I -> Tabuleiro [1], "#d");

    // Testa a função
    CU_ASSERT_EQUAL (logicaSolucaoJogo (I, 1), 1);

    // Altera o tabuleiro
    I -> Tabuleiro [0][1] = 'c';

    // Testa a função
    CU_ASSERT_EQUAL (logicaSolucaoJogo (I, 0), 0);
    CU_ASSERT_EQUAL (logicaSolucaoJogo (I, 1), 0);

    // Liberta a informação do jogo
    libertaInfo (I);
}



// Testa a função 'logicaDica'
void teste_logicaDica () {

    // Inicializa a informação
    Info I = inicializaInfo ();

    // Inicializa o tabuleiro
    I -> dL = 3;
    I -> dC = 5;
    I -> nTabuleiro = 1;
    inicializaTabuleiro (I);

    // Define o tabuleiro
    strcpy (I -> Tabuleiro [0], "##adc");
    strcpy (I -> Tabuleiro [1], "dcdec");
    strcpy (I -> Tabuleiro [2], "dfdce");

    // Testa a função
    CU_ASSERT_EQUAL (logicaDica ("a3", I), 1);

    // Altera o tabuleiro
    I -> Tabuleiro [0][0] = 'e';

    // Testa a função
    CU_ASSERT_EQUAL (logicaDica ("a1", I), 0);
    CU_ASSERT_EQUAL (I -> Tabuleiro [0][0], 'E');

    // Liberta a informação do jogo
    libertaInfo (I);
}



// Função principal
void testesComandosLogica (CU_pSuite suite) {
    CU_add_test (suite, "logicaSair", teste_logicaSair);
    CU_add_test (suite, "logicaGravar", teste_logicaGravar);
    CU_add_test (suite, "logicaLer", teste_logicaLer);
    CU_add_test (suite, "logicaInfoComandos", teste_logicaInfoComandos);
    CU_add_test (suite, "logicaPintarCasa", teste_logicaPintarCasa);
    CU_add_test (suite, "logicaRiscarCasa", teste_logicaRiscarCasa);
    CU_add_test (suite, "logicaVerifica", teste_logicaVerifica);
    CU_add_test (suite, "logicaAjuda", teste_logicaAjuda);
    CU_add_test (suite, "logicaAjudaRep", teste_logicaAjudaRep);
    CU_add_test (suite, "logicaDesfazerJogadas", teste_logicaDesfazerJogadas);
    CU_add_test (suite, "logicaSolucaoJogo", teste_logicaSolucaoJogo);
    CU_add_test (suite, "logicaDica", teste_logicaDica);
}