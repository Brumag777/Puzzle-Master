// Testa a função 'logicaGravar'
void teste_logicaGravar () {

    // Inicializa a informação sobre o jogo
    Info I = inicializaJogo ();
    I -> dL = 3;
    I -> dC = 5;
    I -> nTabuleiro = 0;
    I -> nJogadas = 6;

    // Testa o caso em que não há nenhum tabuleiro
    CU_ASSERT_EQUAL (logicaGravar ("JogoParaTestarGravar", I), 2);

    // Testa o caso em que não é dado um argumento
    CU_ASSERT_EQUAL (logicaGravar (NULL, I), 1);

    // Altera o número do tabuleiro
    I -> nTabuleiro = 1;

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

    // Realiza a função
    CU_ASSERT_EQUAL (logicaGravar ("JogoParaTestarGravar", I), 0);

    // Abre o ficheiro novamente
    FILE *Jogo = fopen ("JogoParaTestarGravar", "r");

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



// Testa a função 'logicaLer'
void teste_logicaLer () {

    // Inicializa a informação sobre o jogo
    Info I = inicializaJogo ();

    // Testa o caso em que o ficheiro é inválido
    CU_ASSERT_EQUAL (logicaLer ("FICHEIROQUENAOEXITE", I), 2);

    // Testa o caso em que não é dado um argumento
    CU_ASSERT_EQUAL (logicaLer (NULL, I), 1);

    // Realiza a função
    CU_ASSERT_EQUAL (logicaLer ("JogoParaTestarLer", I), 0);

    // Testa se foram lidos os valores corretos
    CU_ASSERT_EQUAL (I -> nTabuleiro, 4);
    CU_ASSERT_EQUAL (I -> nJogadas, 6);
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



// Testa a função 'logicaSair'
void teste_logicaSair () {

    // Inicializa a informação sobre o jogo
    Info I = inicializaJogo ();

    // Testa o caso em que é dado um argumento
    CU_ASSERT_EQUAL (logicaSair ("ARGUMENTO", I), 1);

    // Realiza a função
    CU_ASSERT_EQUAL (logicaSair (NULL, I), 0);

    // Testa o resultado da função
    CU_ASSERT_EQUAL (I -> aCorrer, false);

    // Liberta a memória alocada para a informação do jogo
    libertaInfo (I);
}



// Testa a função 'logicaPintarCasa'
void teste_logicaPintarCasa () {

    // Inicializa a informação sobre o jogo
    Info I = inicializaJogo ();
    I -> dL = 3;
    I -> dC = 5;
    I -> nTabuleiro = 1;
    I -> nJogadas = 0;

    // Testa o caso em que não é dado um argumento
    CU_ASSERT_EQUAL (logicaPintarCasa (NULL, I), 1);

    // Altera o número do tabuleiro
    I -> nTabuleiro = 1;

    // Aloca memória para o tabuleiro
    inicializaTabuleiro (I);

    // Inicializa o tabuleiro
    strcpy (I -> Tabuleiro [0], "ec#dc");
    strcpy (I -> Tabuleiro [1], "dcdEc");
    strcpy (I -> Tabuleiro [2], "dfdce");

    // Testa o caso em que é dada uma coordenada inválida
    CU_ASSERT_EQUAL (logicaPintarCasa ("b5", I), 2);

    // Testa o caso em que a casa está riscada
    CU_ASSERT_EQUAL (logicaPintarCasa ("c1", I), 3);

    // Testa o caso em que a casa está pintada
    CU_ASSERT_EQUAL (logicaPintarCasa ("d2", I), 4);

    // Realiza a função
    CU_ASSERT_EQUAL (logicaPintarCasa ("a1", I), 0);

    // Testa o resultado da função
    CU_ASSERT_EQUAL (I -> Tabuleiro [0][0], 'E');
    CU_ASSERT_EQUAL (I -> nJogadas, 1);

    // Liberta a memória alocada para a informação do jogo
    libertaInfo (I);
}



// Testa a função 'logicaRiscarCasa'
void teste_logicaRiscarCasa () {

    // Inicializa a informação sobre o jogo
    Info I = inicializaJogo ();
    I -> dL = 3;
    I -> dC = 5;
    I -> nTabuleiro = 1;
    I -> nJogadas = 0;

    // Testa o caso em que não é dado um argumento
    CU_ASSERT_EQUAL (logicaRiscarCasa (NULL, I), 1);

    // Altera o número do tabuleiro
    I -> nTabuleiro = 1;

    // Aloca memória para o tabuleiro
    inicializaTabuleiro (I);

    // Inicializa o tabuleiro
    strcpy (I -> Tabuleiro [0], "ec#dc");
    strcpy (I -> Tabuleiro [1], "dcdEc");
    strcpy (I -> Tabuleiro [2], "dfdce");

    // Testa o caso em que é dada uma coordenada inválida
    CU_ASSERT_EQUAL (logicaRiscarCasa ("b5", I), 2);

    // Testa o caso em que a casa está riscada
    CU_ASSERT_EQUAL (logicaRiscarCasa ("c1", I), 3);

    // Testa o caso em que a casa está pintada
    CU_ASSERT_EQUAL (logicaRiscarCasa ("d2", I), 4);

    // Realiza a função
    CU_ASSERT_EQUAL (logicaRiscarCasa ("a1", I), 0);

    // Testa o resultado da função
    CU_ASSERT_EQUAL (I -> Tabuleiro [0][0], '#');
    CU_ASSERT_EQUAL (I -> nJogadas, 1);

    // Liberta a memória alocada para a informação do jogo
    libertaInfo (I);
}



// Testa a função 'logicaDesfazerJogada'
void teste_logicaDesfazerJogada () {

    // Inicializa a informação sobre o jogo
    Info I = inicializaJogo ();
    I -> dL = 3;
    I -> dC = 5;
    I -> nTabuleiro = 0;
    I -> nJogadas = 0;

    // Testa o caso em que ainda não foi lido um ficheiro
    CU_ASSERT_EQUAL (logicaDesfazerJogada (NULL, I), 1);

    // Altera o número do tabuleiro
    I -> nTabuleiro = 1;

    // Testa o caso em que ainda não foi feitas alterações
    CU_ASSERT_EQUAL (logicaDesfazerJogada (NULL, I), 1);

    // Altera o número do tabuleiro
    I -> nTabuleiro = 2;
    
    // Testa o caso em que o argumento não é um natural
    CU_ASSERT_EQUAL (logicaDesfazerJogada ("-1", I), 2);

    // Testa o caso em que foi selecionado o tabuleiro atual
    CU_ASSERT_EQUAL (logicaDesfazerJogada ("2", I), 3);

    // Testa o caso em que foi seleciona um tabuleiro que ainda não existe
    CU_ASSERT_EQUAL (logicaDesfazerJogada ("3", I), 4);

    // Altera o número do tabuleiro
    I -> nTabuleiro = 1;

    // Aloca memória para o tabuleiro
    inicializaTabuleiro (I);

    // Inicializa o tabuleiro
    strcpy (I -> Tabuleiro [0], "ecadc");
    strcpy (I -> Tabuleiro [1], "dcdec");
    strcpy (I -> Tabuleiro [2], "bddce");

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

    // Aplica J1, J2 e J3 ao tabuleiro
    realizaAlteracoesJogada (I -> Tabuleiro, J1, 1);
    realizaAlteracoesJogada (I -> Tabuleiro, J2, 1);
    realizaAlteracoesJogada (I -> Tabuleiro, J3, 4);

    // Adiciona as jogadas ao histórico
    addJogada (I, J1, 1);
    addJogada (I, J2, 1);
    addJogada (I, J3, 4);

    // Realiza a função
    CU_ASSERT_EQUAL (logicaDesfazerJogada ("1", I), 0);

    // Testa o resultado da função
    CU_ASSERT_EQUAL (I -> nTabuleiro, 1);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [0], "ecadc"), 0);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [1], "dcdec"), 0);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [2], "bddce"), 0);

    // Liberta a memória alocada para a informação do jogo
    libertaInfo (I);
}



// Testa a função 'logicaVisualizarHistorico'
void teste_logicaVisualizarHistorico () {

    // Inicializa a informação sobre o jogo
    Info I = inicializaJogo ();
    I -> dL = 3;
    I -> dC = 5;
    I -> nTabuleiro = 0;
    I -> nJogadas = 0;

    // Testa o caso em que o argumento não é um natural
    CU_ASSERT_EQUAL (logicaVisualizarHistorico ("-1", I), -1);

    // Testa o caso em que ainda não foi lido um ficheiro
    CU_ASSERT_EQUAL (logicaVisualizarHistorico (NULL, I), -2);

    // Altera o número do tabuleiro
    I -> nTabuleiro = 1;

    // Testa o caso em que foi selecionada uma quantidade de tabuleiros superior à existente
    CU_ASSERT_EQUAL (logicaVisualizarHistorico ("2", I), -3);

    // Altera o número do tabuleiro
    I -> nTabuleiro = 2;

    // Testa o caso em que foi selecionado o tabuleiro atual
    CU_ASSERT_EQUAL (logicaVisualizarHistorico ("2", I), 2);

    // Testa o caso em que foi seleciona um tabuleiro que ainda não existe
    CU_ASSERT_EQUAL (logicaVisualizarHistorico ("1", I), 1);

    // Liberta a memória alocada para a informação do jogo
    libertaInfo (I);
}



// Testa a função 'logicaVerifica'
void teste_logicaVerifica () {

    // Inicializa a informação sobre o jogo
    Info I = inicializaJogo ();
    I -> dL = 3;
    I -> dC = 5;
    I -> nTabuleiro = 0;
    I -> nJogadas = 0;
    I -> eJogo = false;

    // Testa o caso em que é dado um argumento
    CU_ASSERT_EQUAL (logicaVerifica ("ARGUMENTO", I), -1);

    // Altera o número do tabuleiro
    I -> nTabuleiro = 1;

    // Aloca memória para o tabuleiro
    inicializaTabuleiro (I);

    // Inicializa o tabuleiro
    strcpy (I -> Tabuleiro [0], "e#adc");
    strcpy (I -> Tabuleiro [1], "dcDec");
    strcpy (I -> Tabuleiro [2], "bddc#");

    // Testa a função para o tabuleiro atual
    CU_ASSERT_EQUAL (logicaVerifica (NULL, I), 1);

    // Comete uma infração
    I -> Tabuleiro [2][3] = '#';

    // Testa a função para o tabuleiro atual
    CU_ASSERT_EQUAL (logicaVerifica (NULL, I), 0);

    // Retorna ao tabuleiro original
    I -> Tabuleiro [2][3] = 'c';

    // Comete uma infração
    I -> Tabuleiro [1][0] = 'D';

    // Testa a função para o tabuleiro atual
    CU_ASSERT_EQUAL (logicaVerifica (NULL, I), 0);

    // Comete uma infração
    I -> Tabuleiro [1][0] = '#';

    // Testa a função para o tabuleiro atual
    CU_ASSERT_EQUAL (logicaVerifica (NULL, I), 0);

    // Liberta a memória alocada para a informação do jogo
    libertaInfo (I);
}



// Testa a função 'logicaAjuda'
void teste_logicaAjuda () {

    // Inicializa a informação sobre o jogo
    Info I = inicializaJogo ();
    I -> dL = 3;
    I -> dC = 5;
    I -> nTabuleiro = 1;
    I -> nJogadas = 0;
    I -> eJogo = false;

    // Testa a função para um argumento inválido
    CU_ASSERT_EQUAL (logicaAjuda ("ARGUMENTOINVALIDO", I), 1);

    // Aloca memória para o tabuleiro
    inicializaTabuleiro (I);

    // Inicializa o tabuleiro
    strcpy (I -> Tabuleiro [0], "ecadc");
    strcpy (I -> Tabuleiro [1], "dcDec");
    strcpy (I -> Tabuleiro [2], "bdDc#");

    // Testa a função para um tabuleiro inválido
    CU_ASSERT_EQUAL (logicaAjuda (NULL, I), 3);

    // Altera o tabuleiro
    I -> Tabuleiro [2][2] = 'd';

    // Testa a função para um caso em que não realiza nenhuma alteração
    CU_ASSERT_EQUAL (logicaAjuda ("o", I), 2);

    // Altera o tabuleiro
    I -> Tabuleiro [0][1] = '#';

    // Realiza a função
    CU_ASSERT_EQUAL (logicaAjuda (NULL, I), 0);

    // Testa o resultado da função
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [0], "E#ADC"), 0);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [1], "#CDEC"), 0);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [2], "BD#C#"), 0);

    // Liberta a memória alocada para a informação do jogo
    libertaInfo (I);
}



// Testa a função 'logicaAjudaRep'
void teste_logicaAjudaRep () {

    // Inicializa a informação sobre o jogo
    Info I = inicializaJogo ();
    I -> dL = 3;
    I -> dC = 5;
    I -> nTabuleiro = 1;
    I -> nJogadas = 0;
    I -> eJogo = false;

    // Testa a função quando é dado um argumento
    CU_ASSERT_EQUAL (logicaAjudaRep ("ARGUMENTO", I), 1);

    // Aloca memória para o tabuleiro
    inicializaTabuleiro (I);

    // Inicializa o tabuleiro
    strcpy (I -> Tabuleiro [0], "ecadc");
    strcpy (I -> Tabuleiro [1], "dcDec");
    strcpy (I -> Tabuleiro [2], "bdDc#");

    // Testa a função para um tabuleiro inválido
    CU_ASSERT_EQUAL (logicaAjudaRep (NULL, I), 3);

    // Altera o tabuleiro
    I -> Tabuleiro [2][2] = 'd';

    // Realiza a função
    CU_ASSERT_EQUAL (logicaAjudaRep (NULL, I), 0);

    // Testa o resultado da função
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [0], "ECaD#"), 0);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [1], "#CDEC"), 0);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [2], "BD#C#"), 0);

    // Liberta a memória alocada para a informação do jogo
    libertaInfo (I);
}



// Testa a função 'logicaResolveJogo'
void teste_logicaResolveJogo () {

    // Inicializa a informação sobre o jogo
    Info I = inicializaJogo ();
    I -> dL = 3;
    I -> dC = 5;
    I -> nTabuleiro = 1;
    I -> nJogadas = 0;
    I -> eJogo = false;

    // Testa a função quando é dado um argumento
    CU_ASSERT_EQUAL (logicaResolveJogo ("ARGUMENTO", I, 1), 1);

    // Aloca memória para o tabuleiro
    inicializaTabuleiro (I);

    // Inicializa o tabuleiro
    strcpy (I -> Tabuleiro [0], "ecadc");
    strcpy (I -> Tabuleiro [1], "dcDec");
    strcpy (I -> Tabuleiro [2], "b#dc#");

    // Testa um caso em que não é possível resolver o jogo
    CU_ASSERT_EQUAL (logicaResolveJogo (NULL, I, 1), 3);

    // Altera o tabuleiro
    I -> Tabuleiro [1][2] = 'd';
    I -> Tabuleiro [2][1] = 'f';
    I -> Tabuleiro [2][4] = 'e';

    // Realiza a função
    CU_ASSERT_EQUAL (logicaResolveJogo (NULL, I, 1), 0);

    // Testa o resultado da função
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [0], "E#ADC"), 0);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [1], "DC#E#"), 0);
    CU_ASSERT_EQUAL (strcmp (I -> Tabuleiro [2], "BFDCE"), 0);

    // Liberta a memória alocada para a informação do jogo
    libertaInfo (I);
}



// Testa a função 'logicaApagaHistorico'
void teste_logicaApagaHistorico () {

    // Inicializa a informação sobre o jogo
    Info I = inicializaJogo ();
    I -> dL = 3;
    I -> dC = 5;
    I -> nTabuleiro = 1;
    I -> nJogadas = 0;
    I -> eJogo = false;

    // Testa a função quando é dado um argumento
    CU_ASSERT_EQUAL (logicaApagaHistorico ("ARGUMENTO", I), 1);

    // Testa o caso em que o histórico já está vazio
    CU_ASSERT_EQUAL (logicaApagaHistorico (NULL, I), 2);

    // Aloca memória para o tabuleiro
    inicializaTabuleiro (I);

    // Inicializa o tabuleiro
    strcpy (I -> Tabuleiro [0], "ecadc");
    strcpy (I -> Tabuleiro [1], "dcDec");
    strcpy (I -> Tabuleiro [2], "b#dc#");

    // Realiza jogadas
    logicaPintarCasa ("a1", I);
    logicaRiscarCasa ("a2", I);
    ajudaUmaVez (I, 1);

    // Realiza a função
    CU_ASSERT_EQUAL (logicaApagaHistorico (NULL, I), 0);

    // Testa o resultado da função
    CU_ASSERT_EQUAL (I -> nTabuleiro, 1);

    // Liberta a memória alocada para a informação do jogo
    libertaInfo (I);
}



// Testa a função 'logicaImprimeNJogadas'
void teste_logicaImprimeNJogadas () {

    // Inicializa a informação sobre o jogo
    Info I = inicializaJogo ();
    I -> dL = 3;
    I -> dC = 5;
    I -> nTabuleiro = 0;
    I -> nJogadas = 0;
    I -> eJogo = false;

    // Testa o caso em que é dado um argumento
    CU_ASSERT_EQUAL (logicaImprimeNJogadas ("ARGUMENTO", I), 1);

    // Testa o caso em que ainda não foi lido um ficheiro
    CU_ASSERT_EQUAL (logicaImprimeNJogadas (NULL, I), 2);

    // Altera o número do tabuleiro
    I -> nTabuleiro = 3;

    // Testa a função
    CU_ASSERT_EQUAL (logicaImprimeNJogadas (NULL, I), 0);

    // Liberta a memória alocada para a informação do jogo
    libertaInfo (I);
}



// Testa a função 'logicaListarInfo'
void teste_logicaListarInfo () {

    // Testa o caso em que é dado um argumento
    CU_ASSERT_EQUAL (logicaListarInfo ("ARGUMENTO"), 1);

    // Testa a função
    CU_ASSERT_EQUAL (logicaListarInfo (NULL), 0);
}