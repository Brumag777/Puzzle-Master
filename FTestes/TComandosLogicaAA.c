// Testa a função 'guardaJogadas'
void teste_guardaJogadas () {

    // Inicializa a informação
    Info I = inicializaInfo ();

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
    FILE *Save = fopen ("Jogos/Testes/JogoParaTestarJogadas", "w");

    // Realiza a função
    guardaJogadas (Save, I);

    // Fecha o ficheiro
    fclose (Save);

    // Liberta a informação do jogo
    libertaInfo (I);
}



// Testa a função 'leJogada'
void teste_leJogada () {

    // Inicializa a informação
    Info I = inicializaInfo ();

    // Abre o ficheiro
    FILE *Save = fopen ("Jogos/Testes/JogoParaTestarJogadas", "r");

    // Realiza a função
    CU_ASSERT_EQUAL (leJogada (Save, I), 0);

    // Fecha o ficheiro
    fclose (Save);

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

    // Abre outro ficheiro
    Save = fopen ("Jogos/Testes/JogoVazio", "r");

    // Realiza a função
    CU_ASSERT_EQUAL (leJogada (Save, I), 3);

    // Fecha o ficheiro
    fclose (Save);

    // Abre outro ficheiro
    Save = fopen ("Jogos/Testes/JogoJogada", "r");

    // Realiza a função
    CU_ASSERT_EQUAL (leJogada (Save, I), 3);

    // Fecha o ficheiro
    fclose (Save);

    // Liberta a informação do jogo
    libertaInfo (I);
}



// Testa a função 'procuraInfracoesL'
void teste_procuraInfracoesL () {

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
    strcpy (I -> Tabuleiro [0], "e#adc");
    strcpy (I -> Tabuleiro [1], "D#dec");
    strcpy (I -> Tabuleiro [2], "Dfdce");

    // Cria o tabuleiro de infrações
    int TabInfracoes [3][5] = {0};

    // Testa a função
    CU_ASSERT_EQUAL (procuraInfracoesL (I, 'D', 1, 0, TabInfracoes), 1);

    // Altera o tabuleiro
    I -> Tabuleiro [1][2] = 'D';

    // Testa a função
    CU_ASSERT_EQUAL (procuraInfracoesL (I, 'D', 1, 0, TabInfracoes), 0);

    // Liberta a informação do jogo
    libertaInfo (I);
}



// Testa a função 'procuraInfracoesC'
void teste_procuraInfracoesC () {

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
    strcpy (I -> Tabuleiro [0], "e#adc");
    strcpy (I -> Tabuleiro [1], "D#Dec");
    strcpy (I -> Tabuleiro [2], "dfdce");

    // Cria o tabuleiro de infrações
    int TabInfracoes [3][5] = {0};

    // Testa a função
    CU_ASSERT_EQUAL (procuraInfracoesC (I, 'D', 1, 0, TabInfracoes), 1);

    // Altera o tabuleiro
    I -> Tabuleiro [2][0] = 'D';

    // Testa a função
    CU_ASSERT_EQUAL (procuraInfracoesC (I, 'D', 1, 0, TabInfracoes), 0);

    // Liberta a informação do jogo
    libertaInfo (I);
}



// Testa a função 'procuraInfracoesV'
void teste_procuraInfracoesV () {

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
    strcpy (I -> Tabuleiro [0], "e#adc");
    strcpy (I -> Tabuleiro [1], "DcDec");
    strcpy (I -> Tabuleiro [2], "dfdce");

    // Cria o tabuleiro de infrações
    int TabInfracoes [3][5] = {0};

    // Testa a função
    CU_ASSERT_EQUAL (procuraInfracoesV (I, 0, 1, TabInfracoes), 1);

    // Altera o tabuleiro
    I -> Tabuleiro [1][1] = '#';
    I -> Tabuleiro [0][2] = '#';

    // Testa a função
    CU_ASSERT_EQUAL (procuraInfracoesV (I, 0, 1, TabInfracoes), 0);
    CU_ASSERT_EQUAL (procuraInfracoesV (I, 2, 4, TabInfracoes), 1);

    // Liberta a informação do jogo
    libertaInfo (I);
}



// Testa a função 'verificaLinhas'
void teste_verificaLinhas () {

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
    strcpy (I -> Tabuleiro [0], "e#adc");
    strcpy (I -> Tabuleiro [1], "D#dec");
    strcpy (I -> Tabuleiro [2], "Dfdce");

    // Testa a função
    CU_ASSERT_EQUAL (verificaLinhas (I, 'D', 1, 0, 1), 1);

    // Altera o tabuleiro
    I -> Tabuleiro [1][2] = 'D';

    // Testa a função
    CU_ASSERT_EQUAL (verificaLinhas (I, 'D', 1, 0, 1), 0);

    // Liberta a informação do jogo
    libertaInfo (I);
}



// Testa a função 'verificaColunas'
void teste_verificaColunas () {

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
    strcpy (I -> Tabuleiro [0], "e#adc");
    strcpy (I -> Tabuleiro [1], "D#Dec");
    strcpy (I -> Tabuleiro [2], "dfdce");

    // Testa a função
    CU_ASSERT_EQUAL (verificaColunas (I, 'D', 1, 0, 1), 1);

    // Altera o tabuleiro
    I -> Tabuleiro [2][0] = 'D';

    // Testa a função
    CU_ASSERT_EQUAL (verificaColunas (I, 'D', 1, 0, 1), 0);

    // Liberta a informação do jogo
    libertaInfo (I);
}



// Testa a função 'verificaCasaVazia'
void teste_verificaCasaVazia () {

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
    strcpy (I -> Tabuleiro [0], "e#adc");
    strcpy (I -> Tabuleiro [1], "DcDec");
    strcpy (I -> Tabuleiro [2], "dfdce");

    // Testa a função
    CU_ASSERT_EQUAL (verificaCasaVazia (I, 0, 1, 1), 1);

    // Altera o tabuleiro
    I -> Tabuleiro [1][1] = '#';
    I -> Tabuleiro [0][2] = '#';

    // Testa a função
    CU_ASSERT_EQUAL (verificaCasaVazia (I, 0, 1, 1), 0);
    CU_ASSERT_EQUAL (verificaCasaVazia (I, 2, 4, 1), 1);

    // Liberta a informação do jogo
    libertaInfo (I);
}



// Testa a função 'riscaCasas'
void teste_riscaCasas () {

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
    strcpy (I -> Tabuleiro [0], "E#AdC");
    strcpy (I -> Tabuleiro [1], "dCdeC");
    strcpy (I -> Tabuleiro [2], "dfdce");

    // Testa a função
    CU_ASSERT_EQUAL (riscaCasas (I), 0);

    // Altera o tabuleiro
    I -> Tabuleiro [1][0] = 'D';

    // Testa a função
    CU_ASSERT_EQUAL (riscaCasas (I), 1);

    // Liberta a informação do jogo
    libertaInfo (I);
}



// Testa a função 'pintaCasas'
void teste_pintaCasas () {

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
    strcpy (I -> Tabuleiro [0], "#Cadc");
    strcpy (I -> Tabuleiro [1], "DcdeC");
    strcpy (I -> Tabuleiro [2], "dfdC#");

    // Testa a função
    CU_ASSERT_EQUAL (pintaCasas (I), 0);

    // Altera o tabuleiro
    I -> Tabuleiro [0][4] = I -> Tabuleiro [1][2] = I -> Tabuleiro [2][0] = '#';
    
    // Testa a função
    CU_ASSERT_EQUAL (pintaCasas (I), 1);

    // Liberta a informação do jogo
    libertaInfo (I);
}



// Testa a função 'testaPossibilidadesCasa'
void teste_testaPossibilidadesCasa () {

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
    strcpy (I -> Tabuleiro [1], "##a##");
    strcpy (I -> Tabuleiro [2], "#####");

    // Testa a função
    CU_ASSERT_EQUAL (testaPossibilidadesCasa (I), 0);

    // Define o tabuleiro
    strcpy (I -> Tabuleiro [0], "e#adc");
    strcpy (I -> Tabuleiro [1], "dc#ec");
    strcpy (I -> Tabuleiro [2], "dfdce");

    // Testa a função
    CU_ASSERT_EQUAL (testaPossibilidadesCasa (I), 1);

    // Liberta a informação do jogo
    libertaInfo (I);
}



// Função principal
void testesComandosLogicaAA (CU_pSuite suite) {
    CU_add_test (suite, "guardaJogadas", teste_guardaJogadas);
    CU_add_test (suite, "leJogada", teste_leJogada);
    CU_add_test (suite, "procuraInfracoesL", teste_procuraInfracoesL);
    CU_add_test (suite, "procuraInfracoesC", teste_procuraInfracoesC);
    CU_add_test (suite, "procuraInfracoesV", teste_procuraInfracoesV);
    CU_add_test (suite, "verificaLinhas", teste_verificaLinhas);
    CU_add_test (suite, "verificaColunas", teste_verificaColunas);
    CU_add_test (suite, "verificaCasaVazia", teste_verificaCasaVazia);
    CU_add_test (suite, "riscaCasas", teste_riscaCasas);
    CU_add_test (suite, "pintaCasas", teste_pintaCasas);
    CU_add_test (suite, "testaPossibilidadesCasa", teste_testaPossibilidadesCasa);
}