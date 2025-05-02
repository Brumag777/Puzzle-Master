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



// Função que realiza a lógia do comando 'h' (listarComandos)
int logicaListarComandos (char *arg, Info I) {

    // Para evitar warnings
    (void) I;

    // Verifica se não foi recebido um argumento
    if (arg != NULL) return 1;

    return 0;
}