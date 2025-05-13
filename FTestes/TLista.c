// Testa a função 'addJogada'
void teste_addJogada () {

    // Inicializa a informação sobre o jogo
    Info I = inicializaJogo ();
    I -> nTabuleiro = 1;

    // Aloca memória para os arrays de alterações
    Jogada *J1 = malloc (sizeof (JOGADA));
    Jogada *J2 = malloc (sizeof (JOGADA));
    Jogada *J3 = malloc (4 * (sizeof (JOGADA)));

    // Inicializa J1
    formaJogada (&J1 [0], 1, 'a', 'e');

    // Inicializa J2
    formaJogada (&J2 [0], 2, 'd', 'e');

    // Inicializa J3
    formaJogada (&J3 [0], 1, 'd', 'd');
    formaJogada (&J3 [1], 2, 'c', 'd');
    formaJogada (&J3 [2], 2, 'e', 'c');
    formaJogada (&J3 [3], 3, 'd', 'c');

    // Realiza a função
    CU_ASSERT_EQUAL (addJogada (I, J1, 1), 0);
    CU_ASSERT_EQUAL (addJogada (I, J2, 1), 0);
    CU_ASSERT_EQUAL (addJogada (I, J3, 4), 0);

    // Testa o resultado da função
    CU_ASSERT_EQUAL (I -> nTabuleiro, 4);
    CU_ASSERT_EQUAL (I -> HJogadas -> JAnt -> JAnt -> nAlts, 1);
    CU_ASSERT_EQUAL (I -> HJogadas -> JAnt -> nAlts, 1);
    CU_ASSERT_EQUAL (I -> HJogadas -> nAlts, 4);
    CU_ASSERT_EQUAL (I -> HJogadas -> JAnt -> JAnt -> Jogadas [0] -> L, 1);
    CU_ASSERT_EQUAL (I -> HJogadas -> JAnt -> JAnt -> Jogadas [0] -> C, 'a');
    CU_ASSERT_EQUAL (I -> HJogadas -> JAnt -> JAnt -> Jogadas [0] -> cAnterior, 'e');
    CU_ASSERT_EQUAL (I -> HJogadas -> JAnt -> Jogadas [0] -> L, 2);
    CU_ASSERT_EQUAL (I -> HJogadas -> JAnt -> Jogadas [0] -> C, 'd');
    CU_ASSERT_EQUAL (I -> HJogadas -> JAnt -> Jogadas [0] -> cAnterior, 'e');
    CU_ASSERT_EQUAL (I -> HJogadas -> Jogadas [0] -> L, 1);
    CU_ASSERT_EQUAL (I -> HJogadas -> Jogadas [0] -> C, 'd');
    CU_ASSERT_EQUAL (I -> HJogadas -> Jogadas [0] -> cAnterior, 'd');
    CU_ASSERT_EQUAL (I -> HJogadas -> Jogadas [1] -> L, 2);
    CU_ASSERT_EQUAL (I -> HJogadas -> Jogadas [1] -> C, 'c');
    CU_ASSERT_EQUAL (I -> HJogadas -> Jogadas [1] -> cAnterior, 'd');
    CU_ASSERT_EQUAL (I -> HJogadas -> Jogadas [2] -> L, 2);
    CU_ASSERT_EQUAL (I -> HJogadas -> Jogadas [2] -> C, 'e');
    CU_ASSERT_EQUAL (I -> HJogadas -> Jogadas [2] -> cAnterior, 'c');
    CU_ASSERT_EQUAL (I -> HJogadas -> Jogadas [3] -> L, 3);
    CU_ASSERT_EQUAL (I -> HJogadas -> Jogadas [3] -> C, 'd');
    CU_ASSERT_EQUAL (I -> HJogadas -> Jogadas [3] -> cAnterior, 'c');

    // Liberta a memória alocada para a informação do jogo
    libertaInfo (I);
}



// Testa a função 'remJogada'
void teste_remJogada () {

    // Inicializa a informação sobre o jogo
    Info I = inicializaJogo ();
    I -> nTabuleiro = 1;

    // Aloca memória para os arrays de alterações
    Jogada *J1 = malloc (sizeof (JOGADA));
    Jogada *J2 = malloc (sizeof (JOGADA));
    Jogada *J3 = malloc (4 * (sizeof (JOGADA)));

    // Inicializa J1
    formaJogada (&J1 [0], 1, 'a', 'e');

    // Inicializa J2
    formaJogada (&J2 [0], 2, 'd', 'e');

    // Inicializa J3
    formaJogada (&J3 [0], 1, 'd', 'd');
    formaJogada (&J3 [1], 2, 'c', 'd');
    formaJogada (&J3 [2], 2, 'e', 'c');
    formaJogada (&J3 [3], 3, 'd', 'c');

    // Adiciona as jogadas à lista
    addJogada (I, J1, 1);
    addJogada (I, J2, 1);
    addJogada (I, J3, 4);

    // Realiza a função
    remJogada (I);
    remJogada (I);

    // Testa o resultado da função
    CU_ASSERT_EQUAL (I -> nTabuleiro, 2);
    CU_ASSERT_EQUAL (I -> HJogadas -> nAlts, 1);
    CU_ASSERT_EQUAL (I -> HJogadas -> Jogadas [0] -> L, 1);
    CU_ASSERT_EQUAL (I -> HJogadas -> Jogadas [0] -> C, 'a');
    CU_ASSERT_EQUAL (I -> HJogadas -> Jogadas [0] -> cAnterior, 'e');
    
    // Liberta a memória alocada para a informação do jogo
    libertaInfo (I);
}



// Testa a função 'inverteHistorico'
void teste_inverteHistorico () {

    // Inicializa a informação sobre o jogo
    Info I = inicializaJogo ();
    I -> nTabuleiro = 1;

    // Aloca memória para os arrays de alterações
    Jogada *J1 = malloc (sizeof (JOGADA));
    Jogada *J2 = malloc (sizeof (JOGADA));
    Jogada *J3 = malloc (4 * (sizeof (JOGADA)));

    // Inicializa J1
    formaJogada (&J1 [0], 1, 'a', 'e');

    // Inicializa J2
    formaJogada (&J2 [0], 2, 'd', 'e');

    // Inicializa J3
    formaJogada (&J3 [0], 1, 'd', 'd');
    formaJogada (&J3 [1], 2, 'c', 'd');
    formaJogada (&J3 [2], 2, 'e', 'c');
    formaJogada (&J3 [3], 3, 'd', 'c');

    // Adiciona as jogadas à lista
    addJogada (I, J1, 1);
    addJogada (I, J2, 1);
    addJogada (I, J3, 4);

    // Realiza a função
    I -> HJogadas = inverteHistorico (I -> HJogadas);

    // Testa o resultado da função
    CU_ASSERT_EQUAL (I -> nTabuleiro, 4);
    CU_ASSERT_EQUAL (I -> HJogadas -> nAlts, 1);
    CU_ASSERT_EQUAL (I -> HJogadas -> JAnt -> nAlts, 1);
    CU_ASSERT_EQUAL (I -> HJogadas -> JAnt -> JAnt -> nAlts, 4);
    CU_ASSERT_EQUAL (I -> HJogadas -> Jogadas [0] -> L, 1);
    CU_ASSERT_EQUAL (I -> HJogadas -> Jogadas [0] -> C, 'a');
    CU_ASSERT_EQUAL (I -> HJogadas -> Jogadas [0] -> cAnterior, 'e');
    CU_ASSERT_EQUAL (I -> HJogadas -> JAnt -> Jogadas [0] -> L, 2);
    CU_ASSERT_EQUAL (I -> HJogadas -> JAnt -> Jogadas [0] -> C, 'd');
    CU_ASSERT_EQUAL (I -> HJogadas -> JAnt -> Jogadas [0] -> cAnterior, 'e');
    CU_ASSERT_EQUAL (I -> HJogadas -> JAnt -> JAnt -> Jogadas [0] -> L, 1);
    CU_ASSERT_EQUAL (I -> HJogadas -> JAnt -> JAnt -> Jogadas [0] -> C, 'd');
    CU_ASSERT_EQUAL (I -> HJogadas -> JAnt -> JAnt -> Jogadas [0] -> cAnterior, 'd');
    CU_ASSERT_EQUAL (I -> HJogadas -> JAnt -> JAnt ->Jogadas [1] -> L, 2);
    CU_ASSERT_EQUAL (I -> HJogadas -> JAnt -> JAnt -> Jogadas [1] -> C, 'c');
    CU_ASSERT_EQUAL (I -> HJogadas -> JAnt -> JAnt -> Jogadas [1] -> cAnterior, 'd');
    CU_ASSERT_EQUAL (I -> HJogadas -> JAnt -> JAnt -> Jogadas [2] -> L, 2);
    CU_ASSERT_EQUAL (I -> HJogadas -> JAnt -> JAnt -> Jogadas [2] -> C, 'e');
    CU_ASSERT_EQUAL (I -> HJogadas -> JAnt -> JAnt -> Jogadas [2] -> cAnterior, 'c');
    CU_ASSERT_EQUAL (I -> HJogadas -> JAnt -> JAnt -> Jogadas [3] -> L, 3);
    CU_ASSERT_EQUAL (I -> HJogadas -> JAnt -> JAnt -> Jogadas [3] -> C, 'd');
    CU_ASSERT_EQUAL (I -> HJogadas -> JAnt -> JAnt -> Jogadas [3] -> cAnterior, 'c');

    // Liberta a memória alocada para a informação do jogo
    libertaInfo (I);
}