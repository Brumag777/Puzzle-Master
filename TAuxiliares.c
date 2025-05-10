// Testa a função 'visualizaUltimosTabuleiros'
void teste_visualizaUltimosTabuleiros () {

    // Inicializa a informação sobre o jogo
    Info I = inicializaJogo ();
    I -> dL = 3;
    I -> dC = 5;
    I -> nTabuleiro = 1;
    I -> eJogo = false;

    // Aloca memória para o tabuleiro
    inicializaTabuleiro (I);

    // Inicializa o tabuleiro
    strcpy (I -> Tabuleiro [0], "EcaDc");
    strcpy (I -> Tabuleiro [1], "dcD#C");
    strcpy (I -> Tabuleiro [2], "bdfCe");

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

    // Adiciona as jogadas ao histórico
    addJogada (I, J1, 1);
    addJogada (I, J2, 1);
    addJogada (I, J3, 4);

    // Testa a função
    CU_ASSERT_EQUAL (visualizaUltimosTabuleiros (I, 1, 1), 1);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [0], "EcaDc"), 0);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [1], "dcD#C"), 0);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [2], "bdfCe"), 0);
    CU_ASSERT_EQUAL (visualizaUltimosTabuleiros (I, 2, 1), 2);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [0], "EcaDc"), 0);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [1], "dcD#C"), 0);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [2], "bdfCe"), 0);

    // Liberta a memória alocada para a informação do jogo
    libertaInfo (I);
}



// Testa a função 'realizaAlteracoesJogada'
void teste_realizaAlteracoesJogada () {

    // Aloca memória para o tabuleiro
    char **Tabuleiro = malloc (3 * (sizeof (char *)));
    for (int i = 0; i < 3; i++) Tabuleiro [i] = malloc (6 * sizeof (char));

    // Aloca memória para os arrays de alterações
    Jogada *J1 = malloc (sizeof (JOGADA));
    Jogada *J2 = malloc (sizeof (JOGADA));
    Jogada *J3 = malloc (4 * (sizeof (JOGADA)));

    // Inicializa o tabuleiro
    strcpy (Tabuleiro [0], "EcaDc");
    strcpy (Tabuleiro [1], "dcD#C");
    strcpy (Tabuleiro [2], "bddCe");

    // Inicializa J1
    formaJogada (&J1 [0], 1, 'a', 'e');

    // Inicializa J2
    formaJogada (&J2 [0], 2, 'd', 'e');

    // Inicializa J3
    formaJogada (&J3 [0], 1, 'd', 'd');
    formaJogada (&J3 [1], 2, 'c', 'd');
    formaJogada (&J3 [2], 2, 'e', 'c');
    formaJogada (&J3 [3], 3, 'd', 'c');

    // Aplica J1, J2 e J3 ao tabuleiro
    realizaAlteracoesJogada (Tabuleiro, J1, 1);
    realizaAlteracoesJogada (Tabuleiro, J2, 1);
    realizaAlteracoesJogada (Tabuleiro, J3, 4);

    // Testa o resultado da função
    CU_ASSERT_EQUAL (strcmp (Tabuleiro [0], "ecadc"), 0);
    CU_ASSERT_EQUAL (strcmp (Tabuleiro [1], "dcdec"), 0);
    CU_ASSERT_EQUAL (strcmp (Tabuleiro [2], "bddce"), 0);

    // Liberta a memória alocada para o tabuleiro
    for (int i = 0; i < 3; i++) free (Tabuleiro [i]);
    free (Tabuleiro);

    // Liberta a memória alocada para J1
    free (J1 [0]);
    free (J1);

    // Liberta a memória alocada para J2
    free (J2 [0]);
    free (J2);

    // Liberta a memória alocada para J3
    for (int i = 0; i < 4; i++) free (J3 [i]);
    free (J3);
}



// Testa a função 'formaJogada'
void teste_formaJogada () {

    // Inicializa as jogadas
    Jogada J1;
    Jogada J2;
    Jogada J3;

    // Forma as jogadas
    formaJogada (&J1, 3, 'b', 'c');
    formaJogada (&J2, 1, 'a', 'f');
    formaJogada (&J3, 4, 'e', 'd');

    // Testa o resultado da função
    CU_ASSERT_EQUAL (J1 -> L, 3);
    CU_ASSERT_EQUAL (J1 -> C, 'b');
    CU_ASSERT_EQUAL (J1 -> cAnterior, 'c');
    CU_ASSERT_EQUAL (J2 -> L, 1);
    CU_ASSERT_EQUAL (J2 -> C, 'a');
    CU_ASSERT_EQUAL (J2 -> cAnterior, 'f');
    CU_ASSERT_EQUAL (J3 -> L, 4);
    CU_ASSERT_EQUAL (J3 -> C, 'e');
    CU_ASSERT_EQUAL (J3 -> cAnterior, 'd');

    // Liberta a memória alocada para as jogadas
    free (J1);
    free (J2);
    free (J3);
}



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

    // Aloca memória para o tabuleiro
    char **Tabuleiro = malloc (3 * (sizeof (char *)));
    for (int i = 0; i < 3; i++) Tabuleiro [i] = malloc (6 * sizeof (char));

    // Inicializa o tabuleiro
    strcpy (Tabuleiro [0], "EcaDc");
    strcpy (Tabuleiro [1], "dcD#C");
    strcpy (Tabuleiro [2], "bddCe");

    // Testa a função para o tabuleiro atual
    CU_ASSERT_EQUAL (tabuleiroValido (3, 5, Tabuleiro), 1);

    // Torna o tabuleiro inválido adicionando um caractere inválido
    Tabuleiro [0][0] = '0';

    // Testa a função para o tabuleiro atual
    CU_ASSERT_EQUAL (tabuleiroValido (3, 5, Tabuleiro), 0);

    // Retorna o tabuleiro ao estado original
    Tabuleiro [0][0] = 'E';

    // Torna o tabuleiro inválido removendo um caractere de uma linha
    Tabuleiro [2][4] = '\0';

    // Testa a função para o tabuleiro atual
    CU_ASSERT_EQUAL (tabuleiroValido (3, 5, Tabuleiro), 0);

    // Liberta a memória alocada para o tabuleiro
    for (int i = 0; i < 3; i++) free (Tabuleiro [i]);
    free (Tabuleiro);
}



// Testa a função 'jogadasValidas'
void teste_jogadasValidas () {

    // Inicializa a informação sobre o jogo
    Info I = inicializaJogo ();
    I -> dL = 3;
    I -> dC = 5;

    // Aloca memória para os arrays de alterações
    Jogada *J1 = malloc (sizeof (JOGADA));
    Jogada *J2 = malloc (sizeof (JOGADA));
    Jogada *J3 = malloc (4 * (sizeof (JOGADA)));
    Jogada *J4 = malloc (sizeof (JOGADA));
    Jogada *J5 = malloc (sizeof (JOGADA));

    // Inicializa J1
    formaJogada (&J1 [0], 1, 'a', 'e');

    // Inicializa J2
    formaJogada (&J2 [0], 2, 'd', 'e');

    // Inicializa J3
    formaJogada (&J3 [0], 1, 'd', 'd');
    formaJogada (&J3 [1], 2, 'c', 'd');
    formaJogada (&J3 [2], 2, 'e', 'c');
    formaJogada (&J3 [3], 3, 'd', 'c');

    // Inicializa J4
    formaJogada (&J4 [0], 1, 'a', 'D');

    // Inicializa J5
    formaJogada (&J5 [0], 1, 'f', 'd');

    // Adiciona J1, J2 e J3 à lista
    addJogada (I, J1, 1);
    addJogada (I, J2, 1);
    addJogada (I, J3, 4);

    // Testa a função para as jogadas J1, J2 e J3
    CU_ASSERT_EQUAL (jogadasValidas (I), 1);

    // Adiciona J4 à lista
    addJogada (I, J4, 1);

    // Testa a função para as jogadas J1, J2, J3 e J4
    CU_ASSERT_EQUAL (jogadasValidas (I), 0);

    // Remove J4 da lista
    remJogada (I);

    // Adiciona J5 à lista
    addJogada (I, J5, 1);

    // Testa a função para as jogadas J1, J2, J3 e J5
    CU_ASSERT_EQUAL (jogadasValidas (I), 0);

    // Liberta a memória alocada para a informação do jogo
    libertaInfo (I);
}



// Testa a função 'verificaLinhas'
void teste_verificaLinhas () {

    // Inicializa a informação sobre o jogo
    Info I = inicializaJogo ();
    I -> dL = 3;
    I -> dC = 5;
    I -> nTabuleiro = 1;

    // Aloca memória para o tabuleiro
    inicializaTabuleiro (I);

    // Inicializa o tabuleiro
    strcpy (I -> Tabuleiro [0], "EcaDc");
    strcpy (I -> Tabuleiro [1], "DcD#C");
    strcpy (I -> Tabuleiro [2], "bddCe");

    // Testa a função
    CU_ASSERT_EQUAL (verificaLinhas (I, 'E', 0, 0, 0), 1);
    CU_ASSERT_EQUAL (verificaLinhas (I, 'D', 1, 0, 0), 0);
    CU_ASSERT_EQUAL (verificaLinhas (I, 'C', 2, 3, 0), 1);

    // Liberta a memória alocada para a informação do jogo
    libertaInfo (I);
}



// Testa a função 'verificaColunas'
void teste_verificaColunas () {

    // Inicializa a informação sobre o jogo
    Info I = inicializaJogo ();
    I -> dL = 3;
    I -> dC = 5;
    I -> nTabuleiro = 1;

    // Aloca memória para o tabuleiro
    inicializaTabuleiro (I);

    // Inicializa o tabuleiro
    strcpy (I -> Tabuleiro [0], "EcaDc");
    strcpy (I -> Tabuleiro [1], "DcD#C");
    strcpy (I -> Tabuleiro [2], "bdDCe");

    // Testa a função
    CU_ASSERT_EQUAL (verificaColunas (I, 'E', 0, 0, 0), 1);
    CU_ASSERT_EQUAL (verificaColunas (I, 'D', 1, 2, 0), 0);
    CU_ASSERT_EQUAL (verificaColunas (I, 'C', 2, 3, 0), 1);

    // Liberta a memória alocada para a informação do jogo
    libertaInfo (I);
}



// Testa a função 'verificaCasaVazia'
void teste_verificaCasaVazia () {

    // Inicializa a informação sobre o jogo
    Info I = inicializaJogo ();
    I -> dL = 3;
    I -> dC = 5;
    I -> nTabuleiro = 1;

    // Aloca memória para o tabuleiro
    inicializaTabuleiro (I);

    // Inicializa o tabuleiro
    strcpy (I -> Tabuleiro [0], "E##Dc");
    strcpy (I -> Tabuleiro [1], "DcD#C");
    strcpy (I -> Tabuleiro [2], "bdDCe");

    // Testa a função
    CU_ASSERT_EQUAL (verificaCasaVazia (I, 0, 1, 0), 0);
    CU_ASSERT_EQUAL (verificaCasaVazia (I, 0, 2, 0), 1);
    CU_ASSERT_EQUAL (verificaCasaVazia (I, 1, 3, 0), 1);

    // Liberta a memória alocada para a informação do jogo
    libertaInfo (I);
}



// Testa a função 'contaLetrasLigadas'
void teste_contaLetrasLigadas () {

    // Inicializa um representante de tabuleiro
    int aux [3][3] = {{1, 1, 1}, {0, 1, 1}, {1, 0, 1}};

    // Testa a função
    CU_ASSERT_EQUAL (contaLetrasLigadas (3, 3, aux, 2, 0), 1);
    CU_ASSERT_EQUAL (contaLetrasLigadas (3, 3, aux, 1, 1), 6);
}



// Testa a função 'testeJogo'
void teste_testeJogo () {

    // Inicializa a informação sobre o jogo
    Info I = inicializaJogo ();
    I -> eJogo = false;
    I -> dL = 3;
    I -> dC = 5;
    I -> nTabuleiro = 1;

    // Aloca memória para o tabuleiro
    inicializaTabuleiro (I);

    // Inicializa o tabuleiro
    strcpy (I -> Tabuleiro [0], "e#ADC");
    strcpy (I -> Tabuleiro [1], "DC#E#");
    strcpy (I -> Tabuleiro [2], "BDFCE");

    // Testa a função para o tabuleiro atual
    CU_ASSERT_EQUAL (testeJogo (I), 0);

    // Finaliza o jogo
    I -> Tabuleiro [0][0] = 'E';

    // Testa a função para o tabuleiro atual
    CU_ASSERT_EQUAL (testeJogo (I), 1);

    // Comete uma infração no tabuleiro
    I -> Tabuleiro [0][0] = '#';

    // Testa a função para o tabuleiro atual
    CU_ASSERT_EQUAL (testeJogo (I), 0);

    // Liberta a memória alocada para a informação do jogo
    libertaInfo (I);
}



// Testa a função 'adicionaJogada'
void teste_adicionaJogada () {

    // Inicializa a informação sobre o jogo
    Info I = inicializaJogo ();
    I -> dL = 3;
    I -> dC = 5;
    I -> nTabuleiro = 1;

    // Aloca memória para o tabuleiro
    inicializaTabuleiro (I);

    // Inicializa o tabuleiro
    strcpy (I -> Tabuleiro [0], "ecadc\n");
    strcpy (I -> Tabuleiro [1], "dcdEc\n");
    strcpy (I -> Tabuleiro [2], "#dfce\n");

    // Declara o tabuleiro original
    char TabOriginal [3][7];

    // Inicializa o tabuleiro
    strcpy (TabOriginal [0], "ecadc\n");
    strcpy (TabOriginal [1], "dcdec\n");
    strcpy (TabOriginal [2], "bdfce\n");

    // Realiza a função
    adicionaJogada (I, 3, 5, TabOriginal, 2);

    // Testa se a função funcionou corretamente
    CU_ASSERT_EQUAL (I -> HJogadas -> Jogadas [0] -> L, 2);
    CU_ASSERT_EQUAL (I -> HJogadas -> Jogadas [0] -> C, 'd');
    CU_ASSERT_EQUAL (I -> HJogadas -> Jogadas [0] -> cAnterior, 'e');
    CU_ASSERT_EQUAL (I -> HJogadas -> Jogadas [1] -> L, 3);
    CU_ASSERT_EQUAL (I -> HJogadas -> Jogadas [1] -> C, 'a');
    CU_ASSERT_EQUAL (I -> HJogadas -> Jogadas [1] -> cAnterior, 'b');

    // Liberta a memória alocada para a informação do jogo
    libertaInfo (I);
}



// Testa a função 'riscaCasasAux'
void teste_riscaCasasAux () {

    // Inicializa a informação sobre o jogo
    Info I = inicializaJogo ();
    I -> dL = 3;
    I -> dC = 5;
    I -> nTabuleiro = 1;

    // Aloca memória para o tabuleiro
    inicializaTabuleiro (I);

    // Inicializa o tabuleiro
    strcpy (I -> Tabuleiro [0], "ecddc");
    strcpy (I -> Tabuleiro [1], "dcdec");
    strcpy (I -> Tabuleiro [2], "#dFce");

    // Realiza a função
    CU_ASSERT_EQUAL (riscaCasasAux (I, 2, 2), 0);

    // Altera o tabuleiro
    I -> Tabuleiro [1][2] = 'D';

    // Realiza a função
    CU_ASSERT_EQUAL (riscaCasasAux (I, 1, 2), 1);

    // Testa o resultado da função
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [0], "ec#dc"), 0);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [1], "#cDec"), 0);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [2], "#dFce"), 0);

    // Liberta a memória alocada para a informação do jogo
    libertaInfo (I);
}



// Testa a função 'percorreLinha'
void teste_percorreLinha () {

    // Inicializa a informação sobre o jogo
    Info I = inicializaJogo ();
    I -> dL = 3;
    I -> dC = 5;
    I -> nTabuleiro = 1;

    // Aloca memória para o tabuleiro
    inicializaTabuleiro (I);

    // Inicializa o tabuleiro
    strcpy (I -> Tabuleiro [0], "ecddc");
    strcpy (I -> Tabuleiro [1], "dcdec");
    strcpy (I -> Tabuleiro [2], "#dFce");

    // Realiza a função
    CU_ASSERT_EQUAL (percorreLinha (I, 'F', 2, 2), 0);

    // Altera o tabuleiro
    I -> Tabuleiro [1][2] = 'D';

    // Realiza a função
    CU_ASSERT_EQUAL (percorreLinha (I, 'D', 1, 2), 1);

    // Testa o resultado da função
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [0], "ecddc"), 0);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [1], "#cDec"), 0);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [2], "#dFce"), 0);

    // Liberta a memória alocada para a informação do jogo
    libertaInfo (I);
}



// Testa a função 'percorreColuna'
void teste_percorreColuna () {

    // Inicializa a informação sobre o jogo
    Info I = inicializaJogo ();
    I -> dL = 3;
    I -> dC = 5;
    I -> nTabuleiro = 1;

    // Aloca memória para o tabuleiro
    inicializaTabuleiro (I);

    // Inicializa o tabuleiro
    strcpy (I -> Tabuleiro [0], "ecddc");
    strcpy (I -> Tabuleiro [1], "dcdec");
    strcpy (I -> Tabuleiro [2], "#dFce");

    // Realiza a função
    CU_ASSERT_EQUAL (percorreColuna (I, 'F', 2, 2), 0);

    // Altera o tabuleiro
    I -> Tabuleiro [1][2] = 'D';

    // Realiza a função
    CU_ASSERT_EQUAL (percorreColuna (I, 'D', 1, 2), 1);

    // Testa o resultado da função
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [0], "ec#dc"), 0);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [1], "dcDec"), 0);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [2], "#dFce"), 0);

    // Liberta a memória alocada para a informação do jogo
    libertaInfo (I);
}



// Testa a função 'riscaCasas'
void teste_riscaCasas () {

    // Inicializa a informação sobre o jogo
    Info I = inicializaJogo ();
    I -> dL = 3;
    I -> dC = 5;
    I -> nTabuleiro = 1;

    // Aloca memória para o tabuleiro
    inicializaTabuleiro (I);

    // Inicializa o tabuleiro
    strcpy (I -> Tabuleiro [0], "ecddc");
    strcpy (I -> Tabuleiro [1], "dcdec");
    strcpy (I -> Tabuleiro [2], "#dFce");

    // Realiza a função
    CU_ASSERT_EQUAL (riscaCasas (I), 0);

    // Altera o tabuleiro
    I -> Tabuleiro [1][2] = 'D';

    // Realiza a função
    CU_ASSERT_EQUAL (riscaCasas (I), 1);

    // Testa o resultado da função
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [0], "ec#dc"), 0);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [1], "#cDec"), 0);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [2], "#dFce"), 0);

    // Liberta a memória alocada para a informação do jogo
    libertaInfo (I);
}



// Testa a função 'pintaCasasAux'
void teste_pintaCasasAux () {

    // Inicializa a informação sobre o jogo
    Info I = inicializaJogo ();
    I -> dL = 3;
    I -> dC = 5;
    I -> nTabuleiro = 1;

    // Aloca memória para o tabuleiro
    inicializaTabuleiro (I);

    // Inicializa o tabuleiro
    strcpy (I -> Tabuleiro [0], "ecdD#");
    strcpy (I -> Tabuleiro [1], "dcDeC");
    strcpy (I -> Tabuleiro [2], "#dFce");

    // Realiza a função
    CU_ASSERT_EQUAL (pintaCasasAux (I, 0, 4), 0);
    
    // Realiza a função
    CU_ASSERT_EQUAL (pintaCasasAux (I, 2, 0), 1);

    // Testa o resultado da função
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [0], "ecdD#"), 0);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [1], "DcDeC"), 0);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [2], "#DFce"), 0);

    // Liberta a memória alocada para a informação do jogo
    libertaInfo (I);
}



// Testa a função 'pintaCasas'
void teste_pintaCasas () {

    // Inicializa a informação sobre o jogo
    Info I = inicializaJogo ();
    I -> dL = 3;
    I -> dC = 5;
    I -> nTabuleiro = 1;

    // Aloca memória para o tabuleiro
    inicializaTabuleiro (I);

    // Inicializa o tabuleiro
    strcpy (I -> Tabuleiro [0], "ecddc");
    strcpy (I -> Tabuleiro [1], "dcDec");
    strcpy (I -> Tabuleiro [2], "bdFce");

    // Realiza a função
    CU_ASSERT_EQUAL (pintaCasas (I), 0);

    // Altera o tabuleiro
    I -> Tabuleiro [1][3] = '#';
    
    // Realiza a função
    CU_ASSERT_EQUAL (pintaCasas (I), 1);

    // Testa o resultado da função
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [0], "ecdDc"), 0);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [1], "dcD#C"), 0);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [2], "bdFCe"), 0);

    // Liberta a memória alocada para a informação do jogo
    libertaInfo (I);
}



// Testa a função 'testaPossibilidadesCasaAux'
void teste_testaPossibilidadesCasaAux () {

    // Inicializa a informação sobre o jogo
    Info I = inicializaJogo ();
    I -> dL = 3;
    I -> dC = 5;
    I -> nTabuleiro = 1;

    // Aloca memória para o tabuleiro
    inicializaTabuleiro (I);

    // Inicializa o tabuleiro
    strcpy (I -> Tabuleiro [0], "ecddc");
    strcpy (I -> Tabuleiro [1], "dcDec");
    strcpy (I -> Tabuleiro [2], "bdF#d");

    // Realiza a função
    CU_ASSERT_EQUAL (testaPossibilidadesCasaAux (I, 2, 2), 0);
    
    // Realiza a função
    CU_ASSERT_EQUAL (testaPossibilidadesCasaAux (I, 1, 4), 1);

    // Testa o resultado da função
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [0], "ecddc"), 0);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [1], "dcDeC"), 0);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [2], "bdF#d"), 0);

    // Liberta a memória alocada para a informação do jogo
    libertaInfo (I);
}



// Testa a função 'testaPossibilidadesCasa'
void teste_testaPossibilidadesCasa () {

    // Inicializa a informação sobre o jogo
    Info I = inicializaJogo ();
    I -> dL = 3;
    I -> dC = 5;
    I -> nTabuleiro = 1;

    // Aloca memória para o tabuleiro
    inicializaTabuleiro (I);

    // Inicializa o tabuleiro
    strcpy (I -> Tabuleiro [0], "ecddc");
    strcpy (I -> Tabuleiro [1], "dcDec");
    strcpy (I -> Tabuleiro [2], "bdFc#");

    // Realiza a função
    CU_ASSERT_EQUAL (testaPossibilidadesCasa (I), 0);

    // Altera o tabuleiro
    I -> Tabuleiro [1][3] = '#';
    
    // Realiza a função
    CU_ASSERT_EQUAL (testaPossibilidadesCasa (I), 1);

    // Testa o resultado da função
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [0], "ecDDC"), 0);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [1], "dcD#c"), 0);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [2], "bdFc#"), 0);

    // Liberta a memória alocada para a informação do jogo
    libertaInfo (I);
}



// Testa a função 'procuraInfracoesL'
void teste_procuraInfracoesL () {

    // Inicializa a informação sobre o jogo
    Info I = inicializaJogo ();
    I -> dL = 3;
    I -> dC = 5;
    I -> nTabuleiro = 1;

    // Aloca memória para o tabuleiro
    inicializaTabuleiro (I);

    // Inicializa o tabuleiro
    strcpy (I -> Tabuleiro [0], "EcaDc");
    strcpy (I -> Tabuleiro [1], "DcD#C");
    strcpy (I -> Tabuleiro [2], "bddCe");

    // Cria o tabuleiro de infrações
    int TabInfracoes [3][5];

    // Preenche o tabuleiro de infrações com zeros
    for (int i = 0; i < 3; i++) for (int j = 0; j < 5; j++) TabInfracoes [i][j] = 0;

    // Testa a função
    CU_ASSERT_EQUAL (procuraInfracoesL (I, 'E', 0, 0, TabInfracoes), 1);
    CU_ASSERT_EQUAL (procuraInfracoesL (I, 'D', 1, 0, TabInfracoes), 0);
    CU_ASSERT_EQUAL (procuraInfracoesL (I, 'C', 2, 3, TabInfracoes), 1);
    CU_ASSERT_EQUAL (TabInfracoes [1][0], 1);
    CU_ASSERT_EQUAL (TabInfracoes [1][2], 1);

    // Liberta a memória alocada para a informação do jogo
    libertaInfo (I);
}



// Testa a função 'procuraInfracoesC'
void teste_procuraInfracoesC () {

    // Inicializa a informação sobre o jogo
    Info I = inicializaJogo ();
    I -> dL = 3;
    I -> dC = 5;
    I -> nTabuleiro = 1;

    // Aloca memória para o tabuleiro
    inicializaTabuleiro (I);

    // Inicializa o tabuleiro
    strcpy (I -> Tabuleiro [0], "EcaDc");
    strcpy (I -> Tabuleiro [1], "DcD#C");
    strcpy (I -> Tabuleiro [2], "bdDCe");

        // Cria o tabuleiro de infrações
    int TabInfracoes [3][5];

    // Preenche o tabuleiro de infrações com zeros
    for (int i = 0; i < 3; i++) for (int j = 0; j < 5; j++) TabInfracoes [i][j] = 0;

    // Testa a função
    CU_ASSERT_EQUAL (procuraInfracoesC (I, 'E', 0, 0, TabInfracoes), 1);
    CU_ASSERT_EQUAL (procuraInfracoesC (I, 'D', 1, 2, TabInfracoes), 0);
    CU_ASSERT_EQUAL (procuraInfracoesC (I, 'C', 2, 3, TabInfracoes), 1);
    CU_ASSERT_EQUAL (TabInfracoes [1][2], 1);
    CU_ASSERT_EQUAL (TabInfracoes [2][2], 1);

    // Liberta a memória alocada para a informação do jogo
    libertaInfo (I);
}



// Testa a função 'procuraInfracoesV'
void teste_procuraInfracoesV () {

    // Inicializa a informação sobre o jogo
    Info I = inicializaJogo ();
    I -> dL = 3;
    I -> dC = 5;
    I -> nTabuleiro = 1;

    // Aloca memória para o tabuleiro
    inicializaTabuleiro (I);

    // Inicializa o tabuleiro
    strcpy (I -> Tabuleiro [0], "E##Dc");
    strcpy (I -> Tabuleiro [1], "DcD#C");
    strcpy (I -> Tabuleiro [2], "bdDCe");

        // Cria o tabuleiro de infrações
    int TabInfracoes [3][5];

    // Preenche o tabuleiro de infrações com zeros
    for (int i = 0; i < 3; i++) for (int j = 0; j < 5; j++) TabInfracoes [i][j] = 0;

    // Testa a função
    CU_ASSERT_EQUAL (procuraInfracoesV (I, 0, 1, TabInfracoes), 0);
    CU_ASSERT_EQUAL (procuraInfracoesV (I, 0, 2, TabInfracoes), 1);
    CU_ASSERT_EQUAL (procuraInfracoesV (I, 1, 3, TabInfracoes), 1);
    CU_ASSERT_EQUAL (TabInfracoes [0][1], 1);
    CU_ASSERT_EQUAL (TabInfracoes [0][2], 1);

    // Liberta a memória alocada para a informação do jogo
    libertaInfo (I);
}