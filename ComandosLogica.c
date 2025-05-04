#include "Puzzle.h"

// Função que realiza a lógica do comando 'g' (gravar)
int logicaGravar (char *nomeFicheiro, Info I) {

    // Verifica se foi recebido um argumento
    if (nomeFicheiro == NULL) return 1;

    // Verifica se existe um tabuleiro para guardar
    if (I -> nTabuleiro == 0) return 2;

    // Abre o ficheiro a preencher
    FILE *Jogo = fopen (nomeFicheiro, "w");

    // Verifica se o ficheiro foi aberto corretamente
    if (Jogo == NULL) return 3;

    // Guarda a informação do jogo no ficheiro
    guardaInfo (Jogo, I);

    // Fecha o ficheiro
    fclose (Jogo);

    return 0;
}



// Função que realiza a lógica do comando 'l' (ler)
int logicaLer (char *nomeFicheiro, Info I) {

    // Verifica se foi recebido um argumento
    if (nomeFicheiro == NULL) return 1;

    // Abre o ficheiro a ler
    FILE *Jogo = fopen (nomeFicheiro, "r");

    // Verifica se o ficheiro foi lido com sucesso
    if (Jogo == NULL) return 2;

    // Lê o ficheiro
    return leFicheiro (Jogo, I);
}



// Função que realiza a lógica do comando 'p' (preview)
int logicaPreview (char *nomeFicheiro) {

    // Verifica se foi recebido um argumento
    if (nomeFicheiro == NULL) return 1;

    // Abre o ficheiro a ler
    FILE *Jogo = fopen (nomeFicheiro, "r");

    // Verifica se o ficheiro foi lido com sucesso
    if (Jogo == NULL) return 2;

    // Lê o tabuleiro
    return leTabuleiro (Jogo);
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

    // Conta uma jogada
    I -> nJogadas++;

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

    // Conta uma jogada
    I -> nJogadas++;

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

    // Conta uma jogada
    I -> nJogadas++;

    return 0;
}



// Função que realiza a lógica do comando 'V' (vizualizarHistorico)
int logicaVizualizarHistorico (char *nTab, Info I) {

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

    putchar ('\n');

    // Inteiro representante da validade do tabuleiro
    int validade = 1;

    // Procura infrações em relação à existência de casas riscadas juntas e de casa brancas na mesma linha ou coluna
    if (!verificaInfracoes (I, 1)) validade = 0;

    // Procura infrações em relação à existência de um caminho ortogonal entre todas as letras
    if (!verificaCaminhoOrtogonal (I, 1)) validade = 0;

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

            // Armazena o tabuleiro atual e o número de jogadas
            char TPreAlteracoes [I -> dL][I -> dC + 2];
            int nJogadasAnterior = I -> nJogadas;
            
            // Copia o tabuleiro atual
            for (int i = 0; i < I -> dL; i++) strcpy (TPreAlteracoes [i], I -> Tabuleiro [i]);

            // Comando foi invocado como 'a'
            if (versaoComando == 1) {
                if (ajudaUmaVez (I) == 0) return 2;
            }

            // Comando foi invocado como 'a b'
            else if (versaoComando == 2) {
                if (pintaCasas (I) == 0) return 2;
            }

            // Comando foi invocado como 'a r'
            else if (versaoComando == 3) {
                if (riscaCasas (I) == 0) return 2;
            }

            // Comando foi invocado como 'a o'
            else if (testaPossibilidadesCasa (I) == 0) return 2;

            // Adiciona a jogada ao histórico
            adicionaJogada (I, I -> dL, I -> dC, TPreAlteracoes, I -> nJogadas - nJogadasAnterior);
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
    if (!verificaInfracoes (I, 0)) validade = 0;

    // Procura infrações em relação à existência de um caminho ortogonal entre todas as letras
    if (!verificaCaminhoOrtogonal (I, 0)) validade = 0;

    // Avisa que o tabuleiro possui infrações
    if (validade == 0) return 3;

    // Armazena o tabuleiro atual e o número de jogadas
    char TPreAlteracoes [I -> dL][I -> dC + 2];
    int nJogadasAnterior = I -> nJogadas;
            
    // Copia o tabuleiro atual
    for (int i = 0; i < I -> dL; i++) strcpy (TPreAlteracoes [i], I -> Tabuleiro [i]);

    // Realiza as alterações necessárias
    if (ajudaUmaVez (I) == 0) return 2;

    // Repete o processo até não haver nada a alterar
    while (ajudaUmaVez (I));

    // Adiciona a jogada ao histórico
    adicionaJogada (I, I -> dL, I -> dC, TPreAlteracoes, I -> nJogadas - nJogadasAnterior);

    return 0;
}



// Função que realiza a lógica dos comandos 'R' e 'X'
int logicaResolveJogo (char *arg, Info I, int flag) {

    // Verifica se não foi recebido um argumento
    if (arg != NULL) return 1;

    // Verifica se existe um jogo para resolver
    if (I -> nTabuleiro == 0) return 2;

    // Armazena o tabuleiro atual e o número de jogadas
    char TPreAlteracoes [I -> dL][I -> dC + 2];
    int nJogadasAnterior = I -> nJogadas;

    // Copia o tabuleiro atual
    for (int i = 0; i < I -> dL; i++) strcpy (TPreAlteracoes [i], I -> Tabuleiro [i]);

    // Resolve o jogo (se possível)
    if (!resolve (I, I -> dL, I -> dC, TPreAlteracoes)) return 3;

    // Foi invocado o comando 'R'
    if (flag) adicionaJogada (I, I -> dL, I -> dC, TPreAlteracoes, I -> nJogadas - nJogadasAnterior);

    // Foi invocado o comando 'X'
    else {
        imprimeTabuleiro (I -> dL, I -> dC, I -> Tabuleiro, 0, 1);
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



// Função que realiza a lógica do comando 'j' (imprimeNJogadas)
int logicaImprimeNJogadas (char *arg, Info I) {

    // Verifica se não foi recebido um argumento
    if (arg != NULL) return 1;

    // Verifica se já foi lido um tabuleiro
    if (I -> nTabuleiro == 0) return 2;

    return 0;
}



// Função que realiza a lógica dos comandos 'h' (listarComandos) e 'e' (explicaJogo)
int logicaListarInfo (char *arg) {

    // Verifica se não foi recebido um argumento
    if (arg != NULL) return 1;

    return 0;
}