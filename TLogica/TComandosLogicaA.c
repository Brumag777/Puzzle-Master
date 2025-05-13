// Testa a função 'guardaInfo'
void teste_guardaInfo () {
    
    // Inicializa a informação sobre o jogo
    Info I = inicializaJogo ();
    I -> dL = 3;
    I -> dC = 5;
    I -> nTabuleiro = 1;
    I -> pont = 6;

    // Aloca memória para o tabuleiro
    inicializaTabuleiro (I);

    // Inicializa o tabuleiro
    strcpy (I -> Tabuleiro [0], "ecadc");
    strcpy (I -> Tabuleiro [1], "dcdec");
    strcpy (I -> Tabuleiro [2], "dfdce");

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

    // Abre o ficheiro
    FILE *Jogo = fopen ("Jogos/Testes/JogoParaTestar", "w");

    // Realiza a função
    guardaInfo (Jogo, I);

    // Fecha o ficheiro
    fclose (Jogo);

    // Abre o ficheiro novamente
    Jogo = fopen ("Jogos/Testes/JogoParaTestar", "r");

    // Lê o número de linhas e de colunas
    int nL, nC;
    if (fscanf (Jogo, "%d %d", &nL, &nC) != 2) return;

    // Lê o tabuleiro
    char Tab [3][7];
    for (int i = 0; i < 3; i++) if (fscanf (Jogo, "%s", Tab [i]) != 1) return;

    // Lê o número do tabuleiro e de jogadas
    int nTab, nJ;
    if (fscanf (Jogo, "%d %d", &nTab, &nJ) != 2) return;

    // Lê o número de alterações de J3
    int nA3;
    if (fscanf (Jogo, "%d", &nA3) != 1) return;

    // Lê J3
    int L31, L32, L33, L34;
    char C31, C32, C33, C34, cAnt31, cAnt32, cAnt33, cAnt34;
    if (fscanf (Jogo, " %c%d%c", &C31, &L31, &cAnt31) != 3) return;
    if (fscanf (Jogo, " %c%d%c", &C32, &L32, &cAnt32) != 3) return;
    if (fscanf (Jogo, " %c%d%c", &C33, &L33, &cAnt33) != 3) return;
    if (fscanf (Jogo, " %c%d%c", &C34, &L34, &cAnt34) != 3) return;

    // Lê o número de alterações de J2
    int nA2;
    if (fscanf (Jogo, "%d", &nA2) != 1) return;

    // Lê J2
    int L2;
    char C2, cAnt2;
    if (fscanf (Jogo, " %c%d%c", &C2, &L2, &cAnt2) != 3) return;

    // Lê o número de alterações de J1
    int nA1;
    if (fscanf (Jogo, "%d", &nA1) != 1) return;

    // Lê J1
    int L1;
    char C1, cAnt1;
    if (fscanf (Jogo, " %c%d%c", &C1, &L1, &cAnt1) != 3) return;

    // Testa se foram lidos os valores corretos
    CU_ASSERT_EQUAL (nTab, 4);
    CU_ASSERT_EQUAL (nJ, 6);
    CU_ASSERT_EQUAL (strcmp (Tab [0], "ecadc"), 0);
    CU_ASSERT_EQUAL (strcmp (Tab [1], "dcdec"), 0);
    CU_ASSERT_EQUAL (strcmp (Tab [2], "dfdce"), 0);
    CU_ASSERT_EQUAL (nA1, 1);
    CU_ASSERT_EQUAL (nA2, 1);
    CU_ASSERT_EQUAL (nA3, 4);
    CU_ASSERT_EQUAL (L1, 1);
    CU_ASSERT_EQUAL (C1, 'a');
    CU_ASSERT_EQUAL (cAnt1, 'e');
    CU_ASSERT_EQUAL (L2, 2);
    CU_ASSERT_EQUAL (C2, 'd');
    CU_ASSERT_EQUAL (cAnt2, 'e');
    CU_ASSERT_EQUAL (L31, 1);
    CU_ASSERT_EQUAL (C31, 'd');
    CU_ASSERT_EQUAL (cAnt31, 'd');
    CU_ASSERT_EQUAL (L32, 2);
    CU_ASSERT_EQUAL (C32, 'c');
    CU_ASSERT_EQUAL (cAnt32, 'd');
    CU_ASSERT_EQUAL (L33, 2);
    CU_ASSERT_EQUAL (C33, 'e');
    CU_ASSERT_EQUAL (cAnt33, 'c');
    CU_ASSERT_EQUAL (L34, 3);
    CU_ASSERT_EQUAL (C34, 'd');
    CU_ASSERT_EQUAL (cAnt34, 'c');

    // Fecha o ficheiro novamente
    fclose (Jogo);

    // Liberta a memória alocada para a informação do jogo
    libertaInfo (I);
}



// Testa a função 'guardaJogadas'
void teste_guardaJogadas () {
    
    // Inicializa a informação sobre o jogo
    Info I = inicializaJogo ();
    I -> dL = 3;
    I -> dC = 5;
    I -> nTabuleiro = 1;
    I -> pont = 6;

    // Aloca memória para o tabuleiro
    inicializaTabuleiro (I);

    // Inicializa o tabuleiro
    strcpy (I -> Tabuleiro [0], "ecadc");
    strcpy (I -> Tabuleiro [1], "dcdec");
    strcpy (I -> Tabuleiro [2], "dfdce");

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

    // Abre o ficheiro
    FILE *Jogo = fopen ("Jogos/Testes/JogoParaTestar", "w");
    
    // Guarda o número de linhas e de colunas do tabuleiro
    fprintf (Jogo, "%d %d\n", I -> dL, I -> dC);

    // Guarda o tabuleiro num ficheiro
    for (int i = 0; i < I -> dL; i++) {
        fprintf (Jogo, "%s", I -> Tabuleiro [i]);
        fprintf (Jogo, "\n");
    }

    // Guarda o número do tabuleiro e de jogadas
    fprintf (Jogo, "%d %d\n", I -> nTabuleiro, I -> pont);

    // Realiza a função
    guardaJogadas (Jogo, I);

    // Fecha o ficheiro
    fclose (Jogo);

    // Abre o ficheiro novamente
    Jogo = fopen ("Jogos/Testes/JogoParaTestar", "r");

    // Variáveis para ler partes desnecessárias do ficheiro
    int x; char s [7];

    // Lê o número de linhas e de colunas
    if (fscanf (Jogo, "%d %d", &x, &x) != 2) return;

    // Lê o tabuleiro
    for (int i = 0; i < 3; i++) if (fscanf (Jogo, "%s", s) != 1) return;

    // Lê o número do tabuleiro e de jogadas
    if (fscanf (Jogo, "%d %d", &x, &x) != 2) return;

    // Lê o número de alterações de J3
    int nA3;
    if (fscanf (Jogo, "%d", &nA3) != 1) return;

    // Lê J3
    int L31, L32, L33, L34;
    char C31, C32, C33, C34, cAnt31, cAnt32, cAnt33, cAnt34;
    if (fscanf (Jogo, " %c%d%c", &C31, &L31, &cAnt31) != 3) return;
    if (fscanf (Jogo, " %c%d%c", &C32, &L32, &cAnt32) != 3) return;
    if (fscanf (Jogo, " %c%d%c", &C33, &L33, &cAnt33) != 3) return;
    if (fscanf (Jogo, " %c%d%c", &C34, &L34, &cAnt34) != 3) return;

    // Lê o número de alterações de J2
    int nA2;
    if (fscanf (Jogo, "%d", &nA2) != 1) return;

    // Lê J2
    int L2;
    char C2, cAnt2;
    if (fscanf (Jogo, " %c%d%c", &C2, &L2, &cAnt2) != 3) return;

    // Lê o número de alterações de J1
    int nA1;
    if (fscanf (Jogo, "%d", &nA1) != 1) return;

    // Lê J1
    int L1;
    char C1, cAnt1;
    if (fscanf (Jogo, " %c%d%c", &C1, &L1, &cAnt1) != 3) return;

    // Testa se foram lidos os valores corretos
    CU_ASSERT_EQUAL (nA1, 1);
    CU_ASSERT_EQUAL (nA2, 1);
    CU_ASSERT_EQUAL (nA3, 4);
    CU_ASSERT_EQUAL (L1, 1);
    CU_ASSERT_EQUAL (C1, 'a');
    CU_ASSERT_EQUAL (cAnt1, 'e');
    CU_ASSERT_EQUAL (L2, 2);
    CU_ASSERT_EQUAL (C2, 'd');
    CU_ASSERT_EQUAL (cAnt2, 'e');
    CU_ASSERT_EQUAL (L31, 1);
    CU_ASSERT_EQUAL (C31, 'd');
    CU_ASSERT_EQUAL (cAnt31, 'd');
    CU_ASSERT_EQUAL (L32, 2);
    CU_ASSERT_EQUAL (C32, 'c');
    CU_ASSERT_EQUAL (cAnt32, 'd');
    CU_ASSERT_EQUAL (L33, 2);
    CU_ASSERT_EQUAL (C33, 'e');
    CU_ASSERT_EQUAL (cAnt33, 'c');
    CU_ASSERT_EQUAL (L34, 3);
    CU_ASSERT_EQUAL (C34, 'd');
    CU_ASSERT_EQUAL (cAnt34, 'c');

    // Fecha o ficheiro novamente
    fclose (Jogo);

    // Liberta a memória alocada para a informação do jogo
    libertaInfo (I);
}



// Testa a função 'leFicheiro'
void teste_leFicheiro () {

    // Inicializa a informação sobre o jogo
    Info I = inicializaJogo ();

    // Abre o ficheiro
    FILE *Jogo = fopen ("Jogos/Testes/JogoParaTestar", "r");

    // Realiza a função
    leFicheiro (Jogo, I);

    // Testa se foram lidos os valores corretos
    CU_ASSERT_EQUAL (I -> nTabuleiro, 4);
    CU_ASSERT_EQUAL (I -> pont, 6);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [0], "ecadc"), 0);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [1], "dcdec"), 0);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [2], "dfdce"), 0);
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



// Testa a função 'leLinhaJogadas'
void teste_leLinhasJogadas () {

    // Inicializa a informação sobre o jogo
    Info I = inicializaJogo ();

    // Abre o ficheiro
    FILE *Jogo = fopen ("Jogos/Testes/JogoParaTestar", "r");

    // Liberta a memória alocada para o tabuleiro anterior
    libertaTabuleiro (I);

    // Limpa o histórico
    logicaApagaHistorico (NULL, I);

    // Lê o número de linhas e de colunas
    if (fscanf (Jogo, "%d %d", &I -> dL, &I -> dC) != 2) return;

    // Atualiza o número do tabuleiro
    I -> nTabuleiro = 1;

    // Aloca memória para o tabuleiro novo
    inicializaTabuleiro (I);

    // Lê o tabuleiro
    for (int i = 0; i < I -> dL; i++) if (fscanf (Jogo, "%s", I -> Tabuleiro [i]) != 1) return;

    // Lê o número do tabuleiro e de jogadas
    if (fscanf (Jogo, "%d %d", &I -> nTabuleiro, &I -> pont) != 2) return;

    // Realiza a função
    leLinhaJogadas (Jogo, I);

    // Fecha o ficheiro
    fclose (Jogo);

    // Testa se foram lidos os valores corretos
    CU_ASSERT_EQUAL (I -> HJogadas -> nAlts, 4);
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
    CU_ASSERT_EQUAL (ajudaUmaVez (I, 1), 0);

    // Altera o tabuleiro
    I -> Tabuleiro [1][2] = 'D';
    I -> Tabuleiro [2][3] = '#';

    // Realiza a função
    CU_ASSERT_EQUAL (ajudaUmaVez (I, 1), 1);

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



// Testa a função 'preencheTabInfracoes'
void teste_preencheTabInfracoes () {

    // Inicializa a informação sobre o jogo
    Info I = inicializaJogo ();
    I -> dL = 3;
    I -> dC = 5;
    I -> nTabuleiro = 1;
    I -> pont = 0;
    I -> eJogo = false;

    // Aloca memória para o tabuleiro
    inicializaTabuleiro (I);

    // Inicializa o tabuleiro
    strcpy (I -> Tabuleiro [0], "e#adc");
    strcpy (I -> Tabuleiro [1], "dcDec");
    strcpy (I -> Tabuleiro [2], "bddc#");

    // Cria o tabuleiro de infrações
    int TabInfracoes [3][5];

    // Preenche o tabuleiro de infrações com zeros
    for (int i = 0; i < 3; i++) for (int j = 0; j < 5; j++) TabInfracoes [i][j] = 0;

    // Testa a função para o tabuleiro atual
    CU_ASSERT_EQUAL (preencheTabInfracoes (I, TabInfracoes), 1);

    // Comete uma infração
    I -> Tabuleiro [2][3] = '#';

    // Testa a função para o tabuleiro atual
    CU_ASSERT_EQUAL (preencheTabInfracoes (I, TabInfracoes), 0);
    CU_ASSERT_EQUAL (TabInfracoes [2][3], 1);
    CU_ASSERT_EQUAL (TabInfracoes [2][4], 1);

    // Retorna ao tabuleiro original
    I -> Tabuleiro [2][3] = 'c';

    // Preenche o tabuleiro de infrações com zeros
    for (int i = 0; i < 3; i++) for (int j = 0; j < 5; j++) TabInfracoes [i][j] = 0;

    // Comete uma infração
    I -> Tabuleiro [1][0] = 'D';

    // Testa a função para o tabuleiro atual
    CU_ASSERT_EQUAL (preencheTabInfracoes (I, TabInfracoes), 0);
    CU_ASSERT_EQUAL (TabInfracoes [1][0], 1);
    CU_ASSERT_EQUAL (TabInfracoes [1][2], 1);

    // Preenche o tabuleiro de infrações com zeros
    for (int i = 0; i < 3; i++) for (int j = 0; j < 5; j++) TabInfracoes [i][j] = 0;

    // Comete uma infração
    I -> Tabuleiro [1][0] = '#';

    // Testa a função para o tabuleiro atual
    CU_ASSERT_EQUAL (preencheTabInfracoes (I, TabInfracoes), 0);
    CU_ASSERT_EQUAL (TabInfracoes [0][1], 1);
    CU_ASSERT_EQUAL (TabInfracoes [1][0], 1);
    CU_ASSERT_EQUAL (TabInfracoes [2][4], 1);

    // Liberta a memória alocada para a informação do jogo
    libertaInfo (I);
}