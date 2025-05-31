// Testa a função 'guardaInfo'
void teste_guardaInfo () {

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

    // Abre o ficheiro
    FILE *save = fopen ("Jogos/Testes/JogoParaTestar", "w");

    // Realiza a função
    guardaInfo (save, I);

    // Fecha o ficheiro
    fclose (save);

    // Liberta a informação do jogo
    libertaInfo (I);
}



// Testa a função 'leSave'
void teste_leSave () {

    // Inicializa a informação
    Info I = inicializaInfo ();

    // Abre o ficheiro
    FILE *Save = fopen ("Jogos/Testes/JogoParaTestar", "r");

    // Realiza a função
    CU_ASSERT_EQUAL (leSave (Save, I), 0);

    // Testa se foram lidos os valores corretos
    CU_ASSERT_EQUAL (I -> HJogadas -> nAlts, 4);
    CU_ASSERT_EQUAL (I -> HJogadas -> Jogada [0] -> L, 1);
    CU_ASSERT_EQUAL (I -> HJogadas -> Jogada [0] -> C, 'd');
    CU_ASSERT_EQUAL (I -> HJogadas -> Jogada [0] -> cAnt, 'd');
    CU_ASSERT_EQUAL (I -> HJogadas -> Jogada [1] -> L, 2);
    CU_ASSERT_EQUAL (I -> HJogadas -> Jogada [1] -> C, 'c');
    CU_ASSERT_EQUAL (I -> HJogadas -> Jogada [1] -> cAnt, 'd');
    CU_ASSERT_EQUAL (I -> HJogadas -> Jogada [2] -> L, 2);
    CU_ASSERT_EQUAL (I -> HJogadas -> Jogada [2] -> C, 'e');
    CU_ASSERT_EQUAL (I -> HJogadas -> Jogada [2] -> cAnt, 'c');
    CU_ASSERT_EQUAL (I -> HJogadas -> Jogada [3] -> L, 3);
    CU_ASSERT_EQUAL (I -> HJogadas -> Jogada [3] -> C, 'd');
    CU_ASSERT_EQUAL (I -> HJogadas -> Jogada [3] -> cAnt, 'c');
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [0], "ecadc"), 0);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [1], "dcdec"), 0);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [2], "dfdce"), 0);
    CU_ASSERT_EQUAL (I -> nTabuleiro, 4);
    CU_ASSERT_EQUAL (I -> pont, 0);
    CU_ASSERT_EQUAL (I -> dL, 3);
    CU_ASSERT_EQUAL (I -> dC, 5);

    // Abre outro ficheiro
    Save = fopen ("Jogos/Testes/JogoVazio", "r");

    // Realiza a função
    CU_ASSERT_EQUAL (leSave (Save, I), 2);

    // Abre outro ficheiro
    Save = fopen ("Jogos/Testes/JogoSemTabuleiro", "r");

    // Realiza a função
    CU_ASSERT_EQUAL (leSave (Save, I), 2);

    // Abre outro ficheiro
    Save = fopen ("Jogos/Testes/JogoTabuleiroInvalido", "r");

    // Realiza a função
    CU_ASSERT_EQUAL (leSave (Save, I), 3);

    // Abre outro ficheiro
    Save = fopen ("Jogos/Testes/JogoSemPont", "r");

    // Realiza a função
    CU_ASSERT_EQUAL (leSave (Save, I), 2);

    // Abre outro ficheiro
    Save = fopen ("Jogos/Testes/JogoSemJogadas", "r");

    // Realiza a função
    CU_ASSERT_EQUAL (leSave (Save, I), 2);

    // Abre outro ficheiro
    Save = fopen ("Jogos/Testes/JogoJogadasInvalidas", "r");

    // Realiza a função
    CU_ASSERT_EQUAL (leSave (Save, I), 3);

    // Abre outro ficheiro
    Save = fopen ("Jogos/Testes/JogoApenasTabuleiro", "r");

    // Realiza a função
    CU_ASSERT_EQUAL (leSave(Save, I), 0);

    // Liberta a informação do jogo
    libertaInfo (I);
}



// Testa a função 'verificaInfracoes'
void teste_verificaInfracoes () {

    // Inicializa a informação
    Info I = inicializaInfo ();

    // Indica que o jogo não está a correr
    I -> aCorrer = false;

    // Inicializa o tabuleiro
    I -> dL = 3;
    I -> dC = 5;
    I -> nTabuleiro = 1;
    inicializaTabuleiro (I);

    // Define o tabuleiro
    strcpy (I -> Tabuleiro [0], "ecadc");
    strcpy (I -> Tabuleiro [1], "D#dec");
    strcpy (I -> Tabuleiro [2], "dfdce");

    // Testa a função
    CU_ASSERT_EQUAL (verificaInfracoes (I, 1), 1);

    // Altera o tabuleiro
    I -> Tabuleiro [0][1] = '#';
    I -> Tabuleiro [2][0] = 'D';
    I -> Tabuleiro [1][2] = 'D';

    // Testa a função
    CU_ASSERT_EQUAL (verificaInfracoes (I, 1), 0);

    // Liberta a informação do jogo
    libertaInfo (I);
}



// Testa a função 'verificaCaminhoOrtogonal'
void teste_verificaCaminhoOrtogonal () {

    // Inicializa a informação
    Info I = inicializaInfo ();

    // Indica que o jogo não está a correr
    I -> aCorrer = false;

    // Inicializa o tabuleiro
    I -> dL = 3;
    I -> dC = 5;
    I -> nTabuleiro = 1;
    inicializaTabuleiro (I);

    // Define o tabuleiro
    strcpy (I -> Tabuleiro [0], "#####");
    strcpy (I -> Tabuleiro [1], "#####");
    strcpy (I -> Tabuleiro [2], "#####");

    // Testa a função
    CU_ASSERT_EQUAL (verificaCaminhoOrtogonal (I, 1), 1);

    // Altera o tabuleiro
    strcpy (I -> Tabuleiro [0], "ecadc");
    strcpy (I -> Tabuleiro [1], "#cdec");
    strcpy (I -> Tabuleiro [2], "dfdce");

    // Testa a função
    CU_ASSERT_EQUAL (verificaCaminhoOrtogonal (I, 1), 1);

    // Altera o tabuleiro
    I -> Tabuleiro [0][1] = '#';

    // Testa a função
    CU_ASSERT_EQUAL (verificaCaminhoOrtogonal (I, 1), 0);

    // Liberta a informação do jogo
    libertaInfo (I);
}



// Testa a função 'preencheTabInfracoes'
void teste_preencheTabInfracoes () {

    // Inicializa a informação
    Info I = inicializaInfo ();

    // Indica que o jogo não está a correr
    I -> aCorrer = false;

    // Inicializa o tabuleiro
    I -> dL = 3;
    I -> dC = 5;
    I -> nTabuleiro = 1;
    inicializaTabuleiro (I);

    // Define o tabuleiro
    strcpy (I -> Tabuleiro [0], "ecadc");
    strcpy (I -> Tabuleiro [1], "#cDec");
    strcpy (I -> Tabuleiro [2], "dfdce");

    // Cria o tabuleiro de infrações
    int Tab [3][5] = {0};

    // Testa a função
    CU_ASSERT_EQUAL (preencheTabInfracoes (I, Tab), 1);

    // Altera o tabuleiro
    I -> Tabuleiro [0][1] = I -> Tabuleiro [0][2] = '#';
    I -> Tabuleiro [2][0] = I -> Tabuleiro [2][2] = 'D';

    // Testa a função
    CU_ASSERT_EQUAL (preencheTabInfracoes (I, Tab), 0);

    // Liberta a informação do jogo
    libertaInfo (I);
}



// Testa a função 'ajudaUmaVez'
void teste_ajudaUmaVez () {

    // Inicializa a informação
    Info I = inicializaInfo ();

    // Indica que o jogo não está a correr
    I -> aCorrer = false;

    // Inicializa o tabuleiro
    I -> dL = 3;
    I -> dC = 5;
    I -> nTabuleiro = 1;
    inicializaTabuleiro (I);

    // Define o tabuleiro
    strcpy (I -> Tabuleiro [0], "ecadc");
    strcpy (I -> Tabuleiro [1], "dc#ec");
    strcpy (I -> Tabuleiro [2], "dfdce");

    // Testa a função
    CU_ASSERT_EQUAL (ajudaUmaVez (I, 0), 0);
    CU_ASSERT_EQUAL (ajudaUmaVez (I, 3), 0);
    CU_ASSERT_EQUAL (ajudaUmaVez (I, 4), 0);
    CU_ASSERT_EQUAL (ajudaUmaVez (I, 2), 1);
    CU_ASSERT_EQUAL (ajudaUmaVez (I, 1), 1);

    // Liberta a informação do jogo
    libertaInfo (I);
}



// Testa a função 'resolve'
void teste_resolve () {

    // Inicializa a informação
    Info I = inicializaInfo ();

    // Indica que o jogo não está a correr
    I -> aCorrer = false;

    // Inicializa o tabuleiro
    I -> dL = 3;
    I -> dC = 5;
    I -> nTabuleiro = 1;
    inicializaTabuleiro (I);

    // Define o tabuleiro
    strcpy (I -> Tabuleiro [0], "e##dc");
    strcpy (I -> Tabuleiro [1], "#cdec");
    strcpy (I -> Tabuleiro [2], "dfdce");

    // Cria o tabuleiro original
    char Tab1 [3][6] = {"ecadc", "dcdec", "dfdce"};

    // Testa a função
    CU_ASSERT_EQUAL (resolve (I, 3, 5, Tab1), 0);

    // Testa a função
    CU_ASSERT_EQUAL (resolve (I, 3, 5, Tab1), 1);

    // Altera o tabuleiro
    strcpy (I -> Tabuleiro [0], "aaaaa");
    strcpy (I -> Tabuleiro [1], "aaaaa");
    strcpy (I -> Tabuleiro [2], "aaaaa");

    // Testa a função
    CU_ASSERT_EQUAL (resolve (I, 3, 5, Tab1), 0);

    // Liberta a informação do jogo
    libertaInfo (I);
}



// Função principal
void testesComandosLogicaA (CU_pSuite suite) {
    CU_add_test (suite, "guardaInfo", teste_guardaInfo);
    CU_add_test (suite, "leSave", teste_leSave);
    CU_add_test (suite, "verificaInfracoes", teste_verificaInfracoes);
    CU_add_test (suite, "verificaCaminhoOrtogonal", teste_verificaCaminhoOrtogonal);
    CU_add_test (suite, "preencheTabInfracoes", teste_preencheTabInfracoes);
    CU_add_test (suite, "ajudaUmaVez", teste_ajudaUmaVez);
    CU_add_test (suite, "resolve", teste_resolve);
}