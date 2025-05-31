// Testa a função 'formaNomeFicheiro'
void teste_formaNomeFicheiro () {
    
    // Nome do ficheiro
    char nomeFicheiro [23] = {0};

    // Realiza a função
    formaNomeFicheiro (nomeFicheiro, "1", "1");

    // Testa o resultado da função
    CU_ASSERT_EQUAL (strcmp (nomeFicheiro, "Jogos/J1/S1"), 0);
}



// Testa a função 'tabuleiroValido'
void teste_tabuleiroValido () {

    // Aloca memória para o tabuleiro
    char **Tabuleiro = malloc (3 * sizeof (char *));
    Tabuleiro [0] = malloc (7 * sizeof (char));
    Tabuleiro [1] = malloc (6 * sizeof (char));
    Tabuleiro [2] = malloc (6 * sizeof (char));

    // Define o tabuleiro
    strcpy (Tabuleiro [0], "ecadc");
    strcpy (Tabuleiro [1], "dC#ec");
    strcpy (Tabuleiro [2], "dfce");

    // Testa a função
    CU_ASSERT_EQUAL (tabuleiroValido (0, 0, NULL), 0);
    CU_ASSERT_EQUAL (tabuleiroValido (3, 5, Tabuleiro), 0);

    // Altera o tabuleiro
    Tabuleiro [0][5] = 'e';
    Tabuleiro [0][6] = 0;

    // Testa a função
    CU_ASSERT_EQUAL (tabuleiroValido (3, 5, Tabuleiro), 0);

    // Altera o tabuleiro
    Tabuleiro [0][5] = 0;
    Tabuleiro [2][4] = '?';
    Tabuleiro [2][5] = 0;

    // Testa a função
    CU_ASSERT_EQUAL (tabuleiroValido (3, 5, Tabuleiro), 0);

    // Altera o tabuleiro
    Tabuleiro [2][4] = 'e';

    // Testa a função
    CU_ASSERT_EQUAL (tabuleiroValido (3, 5, Tabuleiro), 1);

    // Liberta a memória alocada para o tabuleiro
    free (Tabuleiro [0]);
    free (Tabuleiro [1]);
    free (Tabuleiro [2]);
    free (Tabuleiro);
}



// Testa a função 'jogadasValidas'
void teste_jogadasValidas () {

    // Inicializa a informação
    Info I = inicializaInfo ();

    // Define as dimensões do tabuleiro
    I -> dL = 3;
    I -> dC = 5;

    // Aloca memória para os arrays de alterações
    Alt *J1 = malloc (sizeof (ALT));
    Alt *J2 = malloc (sizeof (ALT));
    Alt *J3 = malloc (sizeof (ALT));
    Alt *J4 = malloc (sizeof (ALT));

    // Inicializa J1
    formaJogada (&J1 [0], 1, 'a', 'e');

    // Inicializa J2
    formaJogada (&J2 [0], 2, 'd', 'e');

    // Adiciona J1 e J2 ao histórico
    addJogada (I, J1, 1);
    addJogada (I, J2, 1);

    // Testa a função
    CU_ASSERT_EQUAL (jogadasValidas (I), 1);

    // Inicializa J3
    formaJogada (&J3 [0], 2, 'g', 'e');

    // Adiciona J3 ao histórico
    addJogada (I, J3, 1);

    // Testa a função
    CU_ASSERT_EQUAL (jogadasValidas (I), 0);

    // Remove J3 do histórico
    remJogada (I);

    // Inicializa J4
    formaJogada (&J4 [0], 2, 'd', 'A');

    // Adiciona J4 ao histórico
    addJogada (I, J4, 1);

    // Testa a função
    CU_ASSERT_EQUAL (jogadasValidas (I), 0);

    // Liberta a informação do jogo
    libertaInfo (I);
}



// Testa a função 'eMaiuscula'
void teste_eMaiuscula () {
    CU_ASSERT_EQUAL (eMaiuscula ('A'), 1);
    CU_ASSERT_EQUAL (eMaiuscula ('A' - 1), 0);
    CU_ASSERT_EQUAL (eMaiuscula ('Z' + 1), 0);
}



// Testa a função 'eMinuscula'
void teste_eMinuscula () {
    CU_ASSERT_EQUAL (eMinuscula ('a'), 1);
    CU_ASSERT_EQUAL (eMinuscula ('a' - 1), 0);
    CU_ASSERT_EQUAL (eMinuscula ('z' + 1), 0);
}



// Testa a função 'coordenadaValida'
void teste_coordenadaValida () {
    CU_ASSERT_EQUAL (coordenadaValida (1, 'a', 3, 5), 1);
    CU_ASSERT_EQUAL (coordenadaValida (0, 'a', 3, 5), 0);
    CU_ASSERT_EQUAL (coordenadaValida (4, 'a', 3, 5), 0);
    CU_ASSERT_EQUAL (coordenadaValida (1, 'a' - 1, 3, 5), 0);
    CU_ASSERT_EQUAL (coordenadaValida (1, 'f', 3, 5), 0);
}



// Testa a função 'formaJogada'
void teste_formaJogada () {

    // Inicializa as jogadas
    Alt J1;
    Alt J2;
    Alt J3;

    // Forma as jogadas
    formaJogada (&J1, 3, 'b', 'c');
    formaJogada (&J2, 1, 'a', 'f');
    formaJogada (&J3, 4, 'e', 'd');

    // Testa o resultado da função
    CU_ASSERT_EQUAL (J1 -> L, 3);
    CU_ASSERT_EQUAL (J1 -> C, 'b');
    CU_ASSERT_EQUAL (J1 -> cAnt, 'c');
    CU_ASSERT_EQUAL (J2 -> L, 1);
    CU_ASSERT_EQUAL (J2 -> C, 'a');
    CU_ASSERT_EQUAL (J2 -> cAnt, 'f');
    CU_ASSERT_EQUAL (J3 -> L, 4);
    CU_ASSERT_EQUAL (J3 -> C, 'e');
    CU_ASSERT_EQUAL (J3 -> cAnt, 'd');

    // Liberta a memória alocada para as jogadas
    free (J1);
    free (J2);
    free (J3);
}



// Testa a função 'valorPont'
void teste_valorPont () {
    CU_ASSERT_EQUAL (valorPont (5, 5, 60), 1);
    CU_ASSERT_EQUAL (valorPont (5, 5, 40), 2);
    CU_ASSERT_EQUAL (valorPont (5, 5, 20), 3);
}



// Testa a função 'realizaAlteracoesJogada'
void teste_realizaAlteracoesJogada () {

    // Inicializa a informação
    Info I = inicializaInfo ();

    // Declara o tabuleiro
    I -> dL = 3;
    I -> dC = 5;
    I -> nTabuleiro = 1;
    inicializaTabuleiro (I);

    // Define o tabuleiro
    strcpy (I -> Tabuleiro [0], "#caDc");
    strcpy (I -> Tabuleiro [1], "dcD#C");
    strcpy (I -> Tabuleiro [2], "dfdCe");

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

    // Realiza a função
    realizaAlteracoesJogada (I -> Tabuleiro, J3, 4);

    // Testa o resultado da função
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [0], "#cadc"), 0);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [1], "dcd#c"), 0);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [2], "dfdce"), 0);

    // Liberta a informação do jogo
    libertaInfo (I);
}



// Testa a função 'contaLetrasLigadas'
void teste_contaLetrasLigadas () {
    
    // Define o tabuleiro
    int Tabuleiro [3][5] = {{1, 1, 1, 0, 1},
                            {1, 1, 0, 1, 0},
                            {1, 1, 1, 1, 1}};

    // Testa a função
    CU_ASSERT_EQUAL (contaLetrasLigadas (3, 5, Tabuleiro, 0, 0), 11);
    CU_ASSERT_EQUAL (contaLetrasLigadas (3, 5, Tabuleiro, 0, 4), 1);
}



// Testa a função 'percorreLinha'
void teste_percorreLinha () {

    // Inicializa a informação
    Info I = inicializaInfo ();

    // Declara o tabuleiro
    I -> dL = 3;
    I -> dC = 5;
    I -> nTabuleiro = 1;
    inicializaTabuleiro (I);

    // Define o tabuleiro
    strcpy (I -> Tabuleiro [0], "#caDc");
    strcpy (I -> Tabuleiro [1], "dcD#C");
    strcpy (I -> Tabuleiro [2], "dfdCe");

    // Testa a função
    CU_ASSERT_EQUAL (percorreLinha (I, 'D', 0), 0);
    CU_ASSERT_EQUAL (percorreLinha (I, 'D', 1), 1);

    // Liberta a informação do jogo
    libertaInfo (I);
}



// Testa a função 'percorreColuna'
void teste_percorreColuna () {

    // Inicializa a informação
    Info I = inicializaInfo ();

    // Declara o tabuleiro
    I -> dL = 3;
    I -> dC = 5;
    I -> nTabuleiro = 1;
    inicializaTabuleiro (I);

    // Define o tabuleiro
    strcpy (I -> Tabuleiro [0], "#caDc");
    strcpy (I -> Tabuleiro [1], "dcD#C");
    strcpy (I -> Tabuleiro [2], "dfdCe");

    // Testa a função
    CU_ASSERT_EQUAL (percorreColuna (I, 'D', 3), 0);
    CU_ASSERT_EQUAL (percorreColuna (I, 'D', 2), 1);

    // Liberta a informação do jogo
    libertaInfo (I);
}



// Testa a função 'adicionaJogada'
void teste_adicionaJogada () {

    // Inicializa a informação
    Info I = inicializaInfo ();

    // Declara o tabuleiro
    I -> dL = 3;
    I -> dC = 5;
    I -> nTabuleiro = 1;
    inicializaTabuleiro (I);

    // Define o tabuleiro
    strcpy (I -> Tabuleiro [0], "#caDc");
    strcpy (I -> Tabuleiro [1], "dcD#C");
    strcpy (I -> Tabuleiro [2], "dfdCe");

    // Tabuleiro anteriro às alterações
    char Tab [3][7] = {"ecadc", "dcdec", "dfdce"};

    // Realiza a função
    adicionaJogada (I, 3, 5, Tab, 6);

    // Testa o resultado da função
    CU_ASSERT_EQUAL (I -> HJogadas -> nAlts, 6);

    // Liberta a informação do jogo
    libertaInfo (I);
}



// Testa a função 'testeJogo'
void teste_testeJogo () {

    // Inicializa a informação
    Info I = inicializaInfo ();

    // Indica que o jogo não está a correr
    I -> aCorrer = false;

    // Declara o tabuleiro
    I -> dL = 3;
    I -> dC = 5;
    I -> nTabuleiro = 1;
    inicializaTabuleiro (I);

    // Define o tabuleiro
    strcpy (I -> Tabuleiro [0], "E#ADC");
    strcpy (I -> Tabuleiro [1], "DC#E#");
    strcpy (I -> Tabuleiro [2], "#FDCe");

    // Testa a função
    CU_ASSERT_EQUAL (testeJogo (I), 0);

    // Altera o tabuleiro
    I -> Tabuleiro [2][4] = 'E';

    // Testa a função
    CU_ASSERT_EQUAL (testeJogo (I), 1);

    // Altera o tabuleiro
    I -> Tabuleiro [0][0] = '#';

    // Testa a função
    CU_ASSERT_EQUAL (testeJogo (I), 0);

    // Altera o tabuleiro
    I -> Tabuleiro [0][0] = 'E';
    I -> Tabuleiro [1][0] = '#';

    // Testa a função
    CU_ASSERT_EQUAL (testeJogo (I), 0);

    // Liberta a informação do jogo
    libertaInfo (I);
}



// Função principal
void testesAuxiliares (CU_pSuite suite) {
    CU_add_test (suite, "formaNomeFicheiro", teste_formaNomeFicheiro);
    CU_add_test (suite, "tabuleiroValido", teste_tabuleiroValido);
    CU_add_test (suite, "jogadasValidas", teste_jogadasValidas);
    CU_add_test (suite, "eMaiuscula", teste_eMaiuscula);
    CU_add_test (suite, "eMinuscula", teste_eMinuscula);
    CU_add_test (suite, "coordenadaValida", teste_coordenadaValida);
    CU_add_test (suite, "formaJogada", teste_formaJogada);
    CU_add_test (suite, "valorPont", teste_valorPont);
    CU_add_test (suite, "realizaAlteracoesJogada", teste_realizaAlteracoesJogada);
    CU_add_test (suite, "contaLetrasLigadas", teste_contaLetrasLigadas);
    CU_add_test (suite, "percorreLinha", teste_percorreLinha);
    CU_add_test (suite, "percorreColuna", teste_percorreColuna);
    CU_add_test (suite, "adicionaJogada", teste_adicionaJogada);
    CU_add_test (suite, "testeJogo", teste_testeJogo);
}