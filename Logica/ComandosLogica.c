#include "../Puzzle.h"

// Função que realiza a lógica do comando 'g' (gravar)
int logicaGravar (char *arg, Info I) {

    // Inteiro a devolver no fim
    int nSave = 1;

    // Verifica se existe um tabuleiro para guardar
    if (I -> nTabuleiro == 0) return -1;

    // Declara o nome do ficheiro
    char nomeFicheiro [LINE_SIZE];

    // Caso de testes
    if (!I -> eJogo) strcpy (nomeFicheiro, "Jogos/Testes/JogoParaTestar");
    
    // Se foi dado um argumento o jogo será guardado no ficheiro escolhido
    else if (arg != NULL) {

        // Torna o argumetno num inteiro (para verificar se é válido)
        nSave = atoi (arg);

        // Verifica se o argumento é válido (número natural)
        if (nSave < 1) return -3;
        
        // Define o ficheiro escolhido
        sprintf (nomeFicheiro, "Jogos/J%d/S%d", I -> nJogo, nSave);
    }

    // Caso contrário será guardado na save de menor índice que ainda não existe
    else {

        // Procura, índice a índice, um ficheiro que ainda não existe
        for (int flag = nSave = 1; flag; nSave++) {

            // Altera o índice
            sprintf (nomeFicheiro, "Jogos/J%d/S%d", I -> nJogo, nSave);

            // Tenta abrir o ficheiro
            FILE *Jogo = fopen (nomeFicheiro, "r");

            // Não conseguiu abrir o ficheiro, então não existe
            if (Jogo == NULL) flag = 0;

            // Conseguiu abrir o ficheiro
            else fclose (Jogo);
        }

        // Decrementa nSave
        nSave--;
    }

    // Abre o ficheiro a preencher
    FILE *Jogo = fopen (nomeFicheiro, "w");

    // Verifica se o ficheiro foi aberto corretamente
    if (Jogo == NULL) return -2;

    // Guarda a informação do jogo no ficheiro
    guardaInfo (Jogo, I);

    // Fecha o ficheiro
    fclose (Jogo);

    return nSave;
}



// Função que realiza a lógica do comando 'l' (ler)
int logicaLer (char args [2][LINE_SIZE], Info I) {

    // Verifica se foi recebido um argumento
    if (args == NULL) return 1;

    // Torna os dois argumentos em inteiros (para verificar se são válidos)
    int arg1 = atoi (args [0]), arg2 = 0;
    if (args [1][0]) {
        arg2 = atoi (args [1]);

        // Verifica se os argumentos são válidos
        if (arg1 < 1 || arg2 < 0) return 6;
    }
    
    // Se não foi dado um segundo argumento, é interpretado como 0
    else {
        args [1][0] = '0';
        args [1][1] = 0;
    }

    // Declara o nome do ficheiro (Jogos/Jarg1/Sarg2)
    char nomeFicheiro [LINE_SIZE];

    // Forma o nome do ficheiro
    formaNomeFicheiro (nomeFicheiro, args, I -> eJogo);

    // Abre o ficheiro a ler
    FILE *Jogo = fopen (nomeFicheiro, "r");

    // Verifica se o ficheiro foi lido com sucesso
    if (Jogo == NULL) return 2;

    // Define o número do jogo
    I -> nJogo = arg1;

    // Lê o ficheiro
    return leFicheiro (Jogo, I);
}



// Função que realiza a lógica do comando 's' (sair)
int logicaSair (char *arg, Info I) {

    // Verifica se não foi recebido um argumento
    if (arg != NULL) return 1;

    // Define 'aCorrer' como falso de modo a terminar o ciclo na main
    I -> aCorrer = false;

    return 0;
}



// Função que realiza a lógica do comando 'b' (pintarCasa)
int logicaPintarCasa (char *coordenada, Info I) {

    // Verifica se foi recebido um argumento
    if (coordenada == NULL) return 1;

    // Define a letra e o número correspondentes à coordenada
    char c = coordenada [0];
    int l = atoi (coordenada + 1);

    // Verifica se a coordenada recebida é válida (isto é, está dentro do tabuleiro)
    if (!coordenadaValida (l, c, I -> dL, I -> dC)) return 2;

    // Verifica se a coordenada recebida não está riscada
    if (I -> Tabuleiro [l - 1][c - 'a'] == '#') return 3;
    
    // Verifica se a coordenada recebida não está pintada de branco
    if (eMaiuscula (I -> Tabuleiro [l - 1][c - 'a'])) return 4;

    // Cria uma jogada nova
    Jogada *Jogs = malloc (sizeof (JOGADA));
    formaJogada (&Jogs [0], l, c, I -> Tabuleiro [l - 1][c - 'a']);

    // Adiciona a nova jogada à lista de jogadas
    addJogada (I, Jogs, 1);

    // Contabiliza uma jogada na pontuação
    I -> pont--;

    // Pinta a casa de branco
    I -> Tabuleiro [l - 1][c - 'a'] += 'A' - 'a';

    return 0;
}



// Função que realiza a lógica do comando 'r' (riscarCasa)
int logicaRiscarCasa (char *coordenada, Info I) {

    // Verifica se foi recebido um argumento
    if (coordenada == NULL) return 1;

    // Define a letra e o número correspondentes à coordenada
    char c = coordenada [0];
    int l = atoi (coordenada + 1);

    // Verifica se a coordenada recebida é válida (isto é, está dentro do tabuleiro)
    if (!coordenadaValida (l, c, I -> dL, I -> dC)) return 2;

    // Verifica se a coordenada recebida não está riscada
    if (I -> Tabuleiro [l - 1][c - 'a'] == '#') return 3;
    
    // Verifica se a coordenada recebida não está pintada de branco
    if (eMaiuscula (I -> Tabuleiro [l - 1][c - 'a'])) return 4;

    // Cria uma jogada nova
    Jogada *Jogs = malloc (sizeof (JOGADA));
    formaJogada (&Jogs [0], l, c, I -> Tabuleiro [l - 1][c - 'a']);

    // Adiciona a nova jogada à lista de jogadas
    addJogada (I, Jogs, 1);

    // Contabiliza uma jogada na pontuação
    I -> pont--;

    // Muda a casa para vazia
    I -> Tabuleiro [l - 1][c - 'a'] = '#';

    return 0;
}



// Função que realiza a lógica do comando 'd' (desfazerJogada)
int logicaDesfazerJogada (char *nTab, Info I) {

    // Verifica se existem tabuleiros anteriores
    if (I -> nTabuleiro == 0 || I -> nTabuleiro == 1) return 1;

    // Índice do tabuleiro para o qual o jogador pretende retornar
    int q;

    // Armazena o número do tabuleiro original
    int nTabOriginal = I -> nTabuleiro;

    // Verifica se o jogador pretende desfazer múltiplas jogadas
    if (nTab == NULL) q = I -> nTabuleiro - 1;

    // Caso em que o jogador pretende desfazer múltiplas jogadas
    else {
        // Desfaz as últimas jogadas até ao tabuleiro q
        q = atoi (nTab);

        // Verifica se o argumento é um número natural
        if (q < 1) return 2;

        // Verifica se o argumento não é igual ao tabuleiro atual
        if (q == I -> nTabuleiro) return 3;

        // Verifica se o tabuleiro desejado existe
        if (q > I -> nTabuleiro) return 4;
    }

    // Desfaz as últimas jogadas até ao tabuleiro anterior ao desejado
    while (I -> nTabuleiro > q) {
        realizaAlteracoesJogada (I -> Tabuleiro, I -> HJogadas -> Jogadas, I -> HJogadas -> nAlts);
        remJogada (I);
    }

    // Contabiliza uma jogada na pontuação
    I -> pont += I -> nTabuleiro - nTabOriginal;

    return 0;
}



// Função que realiza a lógica do comando 'V' (visualizarHistorico)
int logicaVisualizarHistorico (char *nTab, Info I) {

    // Define a quantidade de tabuleiros a imprimir
    int nTabs;

    if (nTab == NULL) nTabs = 1;
    else nTabs = atoi (nTab);

    // Verifica se o argumento é um número natural
    if (nTabs < 1) return -1;

    // Verifica se existem tabuleiros para imprimir
    if (I -> nTabuleiro == 0) return -2;

    // Verifica se existem tabuleiros suficientes para imprimir
    if (nTabs > I -> nTabuleiro) return -3;

    return nTabs;
}



// Função que realiza a lógica do comando 'v' (verifica)
int logicaVerifica (char *arg, Info I) {

    // Verifica se não foi recebido um argumento
    if (arg != NULL) return -1;

    if (I -> eJogo) putchar ('\n');

    // Inteiro representante da validade do tabuleiro
    int validade = 1;

    // Cria o tabuleiro de infrações
    int TabInfracoes [I -> dL][I -> dC];

    // Preenche o tabuleiro de infrações
    for (int i = 0; i < I -> dL; i++) 
        for (int j = 0; j < I -> dC; j++) {
            if (eMinuscula (I -> Tabuleiro [i][j])) TabInfracoes [i][j] = 2;
            else TabInfracoes [i][j] = 0;
        }

    // Preenche o tabuleiro de infrações com uns onde possui infrações
    validade = preencheTabInfracoes (I, TabInfracoes);

    // Imprime o tabuleiro do jogo indicando as infrações
    if (validade == 0 && I -> eJogo) destacaInfracoes (I -> dL, I -> dC, I -> Tabuleiro, TabInfracoes, 0);

    return validade;
}



// Função que realiza a lógica do comando 'a' (ajuda)
int logicaAjuda (char *arg, Info I) {

    // Indica qual das versões do comando foi invocada
    int versaoComando = 0;

    // Verifica qual é o argumento
    if (arg == NULL) versaoComando = 1;
    else if (strcmp (arg, "b") == 0) versaoComando = 2;
    else if (strcmp (arg, "r") == 0) versaoComando = 3;
    else if (strcmp (arg, "o") == 0) versaoComando = 4;

    // Executa a lógica da função
    if (versaoComando) {

        // Verifica se o tabuleiro atual não possui infrações
        int validade = 1;

        // Procura infrações em relação à existência de casas riscadas juntas e de casa brancas na mesma linha ou coluna
        if (!verificaInfracoes (I, 0)) validade = 0;

        // Procura infrações em relação à existência de um caminho ortogonal entre todas as letras
        if (!verificaCaminhoOrtogonal (I, 0)) validade = 0;

        // O tabuleiro não possui infrações
        if (validade) {

            // Armazena o tabuleiro atual e a pontuação
            char TPreAlteracoes [I -> dL][I -> dC + 2];
            int pontAnterior = I -> pont;

            // Copia o tabuleiro atual
            for (int i = 0; i < I -> dL; i++) strcpy (TPreAlteracoes [i], I -> Tabuleiro [i]);

            // Realiza o comando
            if (!ajudaUmaVez (I, versaoComando)) return 2;

            // Adiciona a jogada ao histórico
            adicionaJogada (I, I -> dL, I -> dC, TPreAlteracoes, pontAnterior - I -> pont);
        }

        // Avisa que o tabuleiro possui infrações
        else return 3;
    }

    // Avisa que o argumento é inválido
    else return 1;

    return 0;
}



// Função que realiza a lógica do comando 'A' (ajudaRep)
int logicaAjudaRep (char *arg, Info I) {

    // Verifica se não foi recebido um argumento
    if (arg != NULL) return 1;

    // Verifica se o tabuleiro atual não possui infrações
    int validade = 1;

    // Procura infrações em relação à existência de casas riscadas juntas e de casa brancas na mesma linha ou coluna
    if (!verificaInfracoes (I, 1)) validade = 0;

    // Procura infrações em relação à existência de um caminho ortogonal entre todas as letras
    if (!verificaCaminhoOrtogonal (I, 1)) validade = 0;

    // Avisa que o tabuleiro possui infrações
    if (validade == 0) return 3;

    // Armazena o tabuleiro atual e a pontuação
    char TPreAlteracoes [I -> dL][I -> dC + 2];
    int pontAnterior = I -> pont;
            
    // Copia o tabuleiro atual
    for (int i = 0; i < I -> dL; i++) strcpy (TPreAlteracoes [i], I -> Tabuleiro [i]);

    // Realiza as alterações necessárias
    if (ajudaUmaVez (I, 1) == 0) return 2;

    // Repete o processo até não haver nada a alterar
    while (ajudaUmaVez (I, 1));

    // Adiciona a jogada ao histórico
    adicionaJogada (I, I -> dL, I -> dC, TPreAlteracoes, pontAnterior - I -> pont);

    return 0;
}



// Função que realiza a lógica dos comandos 'R' e 'X'
int logicaResolveJogo (char *arg, Info I, int flag) {

    // Verifica se não foi recebido um argumento
    if (arg != NULL) return 1;

    // Verifica se existe um jogo para resolver
    if (I -> nTabuleiro == 0) return 2;

    // Armazena o tabuleiro atual e a pontuação
    char TPreAlteracoes [I -> dL][I -> dC + 2];
    int pontAnterior = I -> pont;

    // Copia o tabuleiro atual
    for (int i = 0; i < I -> dL; i++) strcpy (TPreAlteracoes [i], I -> Tabuleiro [i]);

    // Resolve o jogo (se possível)
    if (!resolve (I, I -> dL, I -> dC, TPreAlteracoes)) return 3;

    // Foi invocado o comando 'R'
    if (flag) adicionaJogada (I, I -> dL, I -> dC, TPreAlteracoes, pontAnterior - I -> pont);

    // Foi invocado o comando 'X'
    else {
        // Cria o tabuleiro de infrações
        int TabInfracoes [I -> dL][I -> dC];

        // Preenche o tabuleiro de infrações
        for (int i = 0; i < I -> dL; i++) 
            for (int j = 0; j < I -> dC; j++) {
                if (eMinuscula (TPreAlteracoes [i][j])) TabInfracoes [i][j] = 2;
                else if (I -> Tabuleiro [i][j] == TPreAlteracoes [i][j]) TabInfracoes [i][j] = 0;
                else TabInfracoes [i][j] = 1;
            }

        // Imprime o tabuleiro
        destacaInfracoes (I -> dL, I -> dC, I -> Tabuleiro, TabInfracoes, 1);

        // Retorna ao tabuleiro original
        for (int i = 0; i < I -> dL; i++) strcpy (I -> Tabuleiro [i], TPreAlteracoes [i]);
    }

    // Foi possível resolver o jogo
    return 0;
}



// Função que realiza a lógica do comando 'D' (apagaHistorico)
int logicaApagaHistorico (char *arg, Info I) {

    // Verifica se não foi recebido um argumento
    if (arg != NULL) return 1;

    // Verifica se o histórico não está vazio
    if (I -> nTabuleiro < 2) return 2;

    // Apaga o histórico
    while (I -> nTabuleiro > 1) remJogada (I);

    return 0;
}



// Função que realiza a lógica do comando 'c' (criarJogo)
int logicaCriarJogo (char *arg) {

    // Verifica se não foi recebido um argumento
    if (arg != NULL) return -1;

    // Inicializa um novo Info
    Info I = inicializaJogo ();

    // Avisa o jogador do que tem de fazer
    printf ("\nDigite o número de linha e de colunas do jogo desejado.\n\n");

    // Lê o número de linhas e de colunas do tabuleiro
    if (scanf ("%d %d", &I -> dL, &I -> dC) != 2) {
        libertaInfo (I);
        return -2;
    }

    // Verifica se o número de linhas e de colunas é válido
    if (I -> dL < 0 || I -> dC < 0 || I -> dL > 26 || I -> dC > 26) {
        libertaInfo (I);
        return -3;
    }

    // Altera o número do tabuleiro
    I -> nTabuleiro = 1;

    // Inicializa o tabuleiro
    inicializaTabuleiro (I);

    // Avisa o jogador do que tem de fazer
    printf ("\nDigite o tabuleiro do jogo desejado.\n\n");

    // Lê o tabuleiro
    for (int i = 0; i < I -> dL; i++) 
        if (scanf ("%s", I -> Tabuleiro [i]) != 1) {
            libertaInfo (I);
            return -2;
        }

    // Verifica se o tabuleiro é válido
    if (!tabuleiroValido (I -> dL, I -> dC, I -> Tabuleiro)) {
        libertaInfo (I);
        return -4;
    }

    // Cria o nome do ficheiro
    char nomeFicheiro [LINE_SIZE];

    // Procura, índice a índice, um ficheiro que ainda não existe
    for (int flag = I -> nJogo = 1; flag; I -> nJogo++) {

        // Altera o índice
        sprintf (nomeFicheiro, "Jogos/J%d/S0", I -> nJogo);

        // Tenta abrir o ficheiro
        FILE *Jogo = fopen (nomeFicheiro, "r");

        // Não conseguiu abrir o ficheiro, então não existe
        if (Jogo == NULL) flag = 0;

        // Conseguiu abrir o ficheiro
        else fclose (Jogo);
    }

    // Decrementa o número do jogo
    I -> nJogo--;

    // Atualiza a pontuação
    I -> pont = 4 * I -> dL * I -> dC;

    // Cria o nome da nova diretoria
    char nomeDiretoria [LINE_SIZE];

    // Define o nome da nova diretoria
    sprintf (nomeDiretoria, "Jogos/J%d", I -> nJogo);

    // Cria a nova diretoria para o jogo novo
    if (mkdir (nomeDiretoria, 0777)) {
        libertaInfo (I);
        return -5;
    }

    // Cria o ficheiro novo
    FILE *Jogo = fopen (nomeFicheiro, "w");

    // Grava o ficheiro novo
    guardaInfo (Jogo, I);

    // Fecha o ficheiro
    fclose (Jogo);

    // Guarda o número do jogo
    int nJogo = I -> nJogo;

    // Liberta a memória alocada
    libertaInfo (I);

    return nJogo;
}



// Função que realiza a lógica do comando 'p' (imprimePont)
int logicaImprimePont (char *arg, Info I) {

    // Verifica se não foi recebido um argumento
    if (arg != NULL) return -1;

    // Verifica se já foi lido um tabuleiro
    if (I -> nTabuleiro == 0) return -2;

    return valorPont (I -> dL, I -> dC, I -> pont);
}



// Função que realiza a lógica dos comandos 'h' (listarComandos) e 'e' (explicaJogo)
int logicaListarInfo (char *arg) {

    // Verifica se não foi recebido um argumento
    if (arg != NULL) return 1;

    return 0;
}