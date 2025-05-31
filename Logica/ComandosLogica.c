#include "../Puzzle.h"

// Realiza a lógica do comando 's'
void logicaSair (Info I) {
    I -> aCorrer = false;
}



// Realiza a lógica do comando 'g'
int logicaGravar (char *arg1, Info I) {

    // Inteiro a devolver no fim
    int nSave = 1;

    // Declara o nome do ficheiro
    char nomeFicheiro [LINE_SIZE];

    // Foi dado um argumento, logo o jogo será guardado na save escolhida
    if (arg1 [0]) {
        nSave = atoi (arg1);
        sprintf (nomeFicheiro, "Jogos/J%d/S%s", I -> nJogo, arg1);
    }

    // Não foi dado um argumento, logo o jogo será guardado na menor save que ainda não existe
    else {

        // Procura, índice a índice, um ficheiro que ainda não existe
        for (int flag = 1; flag; nSave++) {

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

    // O limite de saves do jogo já foi atingido
    if (nSave > 99) return -1;

    // Altera o nome do ficheiro se o jogo não está a correr
    if (!I -> aCorrer) strcpy (nomeFicheiro, "Jogos/Testes/Gravar");

    // Abre o ficheiro a preencher
    FILE *Save = fopen (nomeFicheiro, "w");

    // Guarda a informação do jogo no ficheiro
    guardaInfo (Save, I);

    // Fecha o ficheiro
    fclose (Save);

    return nSave;
}



// Realiza a lógica do comando 'l'
int logicaLer (char *arg1, char *arg2, Info I) {

    // Se não foi dado um segundo argumento, este é interpretado como 0
    if (arg2 [0] == 0) arg2 [0] = '0';

    // Declara o nome do ficheiro
    char nomeFicheiro [LINE_SIZE];

    // Forma o nome do ficheiro
    formaNomeFicheiro (nomeFicheiro, arg1, arg2);

    // Abre o ficheiro a ler
    FILE *Save = fopen (nomeFicheiro, "r");

    // Verifica se o ficheiro foi lido com sucesso
    if (Save == NULL) return 1;

    // Atualiza o número do jogo
    I -> nJogo = atoi (arg1);

    // Lê a informação da save
    return leSave (Save, I);
}



// Função que realiza a lógica do comando 'h' (infoComandos)
int logicaInfoComandos (char *arg1) {

    // Verifica se o argumento é válido
    if (strlen (arg1) > 1) return -1;

    // Procura qual dos comandos o jogador pretende explorar
    if (arg1 [0] == 's' || arg1 [0] == 'l' || arg1 [0] == 'c' || arg1 [0] == 'E' || arg1 [0] == 'h' || arg1 [0] == 'b' || arg1 [0] == 'r' || arg1 [0] == 'V' ||
        arg1 [0] == 'g' || arg1 [0] == 'v' || arg1 [0] == 'j' || arg1 [0] == 'a' || arg1 [0] == 'A' || arg1 [0] == 'R' || arg1 [0] == 'p' || arg1 [0] == 'd' ||
        arg1 [0] == 'e' || arg1 [0] == 'D' || arg1 [0] == 'X') return arg1 [0];

    // O argumento não é válido
    return -1;
}



// Função que realiza a lógica do comando 'b' (pintarCasa)
void logicaPintarCasa (char *arg1, Info I) {

    // Converte o argumento
    char c = arg1 [0];
    int l = atoi (arg1 + 1);

    // Cria uma jogada nova
    Alt *JogadaNova = malloc (sizeof (ALT));
    formaJogada (&JogadaNova [0], l, c, I -> Tabuleiro [l - 1][c - 'a']);

    // Adiciona a jogada nova ao histórico
    addJogada (I, JogadaNova, 1);

    // Pinta a casa de branco
    I -> Tabuleiro [l - 1][c - 'a'] += -32;

    // Decrementa a pontuação
    if (I -> pont) I -> pont--;
}



// Função que realiza a lógica do comando 'r' (riscarCasa)
void logicaRiscarCasa (char *arg1, Info I) {

    // Converte o argumento
    char c = arg1 [0];
    int l = atoi (arg1 + 1);

    // Cria uma jogada nova
    Alt *JogadaNova = malloc (sizeof (ALT));
    formaJogada (&JogadaNova [0], l, c, I -> Tabuleiro [l - 1][c - 'a']);

    // Adiciona a jogada nova ao histórico
    addJogada (I, JogadaNova, 1);

    // Pinta a casa de branco
    I -> Tabuleiro [l - 1][c - 'a'] = '#';

    // Decrementa a pontuação
    if (I -> pont) I -> pont--;
}



// Função que realiza a lógica do comando 'v' (verifica)
int logicaVerifica (Info I) {
    
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
    if (validade == 0) imprimeTabDestacado (I -> dL, I -> dC, I -> Tabuleiro, TabInfracoes, 0, I -> aCorrer);

    return validade;
}



// Função que realiza a lógica do comando 'a' (ajuda)
int logicaAjuda (char *arg1, Info I) {

    // Indica qual das versões do comando foi invocada
    int versaoComando = 1;

    // Verifica qual é o argumento
    if (arg1 [0] == 'b') versaoComando = 2;
    else if (arg1 [0] == 'r') versaoComando = 3;
    else if (arg1 [0] == 'o') versaoComando = 4;

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
        if (!ajudaUmaVez (I, versaoComando)) return 1;

        // Adiciona a jogada ao histórico
        adicionaJogada (I, I -> dL, I -> dC, TPreAlteracoes, pontAnterior - I -> pont);
    }

    // Avisa que o tabuleiro possui infrações
    else return 2;

    return 0;
}



// Função que realiza a lógica do comando 'A' (ajudaRep)
int logicaAjudaRep (Info I) {

    // Verifica se o tabuleiro atual não possui infrações
    int validade = 1;

    // Procura infrações em relação à existência de casas riscadas juntas e de casa brancas na mesma linha ou coluna
    if (!verificaInfracoes (I, 0)) validade = 0;

    // Procura infrações em relação à existência de um caminho ortogonal entre todas as letras
    if (!verificaCaminhoOrtogonal (I, 0)) validade = 0;

    // Avisa que o tabuleiro possui infrações
    if (validade == 0) return 2;

    // Armazena o tabuleiro atual e a pontuação
    char TPreAlteracoes [I -> dL][I -> dC + 2];
    int pontAnterior = I -> pont;
            
    // Copia o tabuleiro atual
    for (int i = 0; i < I -> dL; i++) strcpy (TPreAlteracoes [i], I -> Tabuleiro [i]);

    // Realiza as alterações necessárias
    if (ajudaUmaVez (I, 1) == 0) return 1;

    // Repete o processo até não haver nada a alterar
    while (ajudaUmaVez (I, 1));

    // Adiciona a jogada ao histórico
    adicionaJogada (I, I -> dL, I -> dC, TPreAlteracoes, pontAnterior - I -> pont);

    return 0;
}



// Função que realiza a lógica do comando 'd' (desfazerJogadas)
void logicaDesfazerJogadas (char *arg1, Info I) {

    // Armazena o número do tabuleiro original
    int nTabOriginal = I -> nTabuleiro;

    // Tabuleiro a retornar
    int q = I -> nTabuleiro - 1;
    
    // Se existe argumento, é o tabuleiro a retornar
    if (arg1 [0]) q = atoi (arg1);

    // Desfaz as últimas jogadas
    while (I -> nTabuleiro > q) {
        realizaAlteracoesJogada (I -> Tabuleiro, I -> HJogadas -> Jogada, I -> HJogadas -> nAlts);
        remJogada (I);
    }

    // Contabiliza na pontuação
    I -> pont += I -> nTabuleiro - nTabOriginal;
}



// Função que realiza a lógica dos comandos 'R' e 'X' (resolveJogo e mostrarSolucao)
int logicaSolucaoJogo (Info I, int flag) {
    
    // Armazena o tabuleiro atual e a pontuação
    char TPreAlteracoes [I -> dL][I -> dC + 2];
    int pontAnterior = I -> pont;

    // Copia o tabuleiro atual
    for (int i = 0; i < I -> dL; i++) strcpy (TPreAlteracoes [i], I -> Tabuleiro [i]);

    // Resolve o jogo (se possível)
    if (!resolve (I, I -> dL, I -> dC, TPreAlteracoes)) return 1;

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
                else TabInfracoes [i][j] = 0;
            }

        // Imprime o tabuleiro
        imprimeTabDestacado (I -> dL, I -> dC, I -> Tabuleiro, TabInfracoes, 1, I -> aCorrer);

        // Retorna ao tabuleiro original
        for (int i = 0; i < I -> dL; i++) strcpy (I -> Tabuleiro [i], TPreAlteracoes [i]);
    }

    // Foi possível resolver o jogo
    return 0;
}



// Função que realiza a lógica do comando 'D' (dica)
int logicaDica (char *arg1, Info I) {

    // Converte o argumento
    char c = arg1 [0];
    int l = atoi (arg1 + 1);

    // Armazena o tabuleiro atual e a pontuação
    char TPreAlteracoes [I -> dL][I -> dC + 2];

    // Copia o tabuleiro atual
    for (int i = 0; i < I -> dL; i++) strcpy (TPreAlteracoes [i], I -> Tabuleiro [i]);

    // Resolve o jogo (se possível)
    if (!resolve (I, I -> dL, I -> dC, TPreAlteracoes)) return 1;

    // Caractere resultante
    char r = I -> Tabuleiro [l - 1][c - 'a'];

    // Retorna ao tabuleiro original
    for (int i = 0; i < I -> dL; i++) strcpy (I -> Tabuleiro [i], TPreAlteracoes [i]);

    // Altera o caractere
    I -> Tabuleiro [l - 1][c - 'a'] = r;

    // Foi possível chegar à dica
    return 0;
}