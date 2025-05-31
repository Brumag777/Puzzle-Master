#include "../Puzzle.h"

// Verifica as restrições do comando 's'
int restricoesSair (char *arg1) {

    // Verifica se foi dado um argumento
    if (arg1 [0]) return 1;

    return 0;
}



// Verifica as restrições do comando 'g'
int restricoesGravar (char *arg1, Info I) {

    // Verifica se não existe um tabuleiro para guardar
    if (I -> nTabuleiro == 0) return 1;

    // Verifica se não foi dado um argumento
    if (arg1 [0] == 0) return 0;

    // Torna o primeiro argumento em inteiro
    int nArg1 = atoi (arg1);

    // Verifica se o primeiro argumento é válido
    if (nArg1 < 1) return 2;
    if (nArg1 > 99) return 3;

    return 0;
}



// Verifica as restrições do comando 'l'
int restricoesLer (char *arg1, char *arg2) {

    // Verifica se não foi dado um argumento
    if (arg1 [0] == 0) return 1;

    // Torna o primeiro argumento em inteiro
    int nArg1 = atoi (arg1);

    // Verifica se o primeiro argumento é válido
    if (nArg1 < 1) return 2;
    if (nArg1 > 99) return 3;

    // Testa a validade do segundo argumento, caso exista
    if (arg2 [0]) {

        // Torna o segundo argumento em inteiro
        int nArg2 = atoi (arg2);

        // Verifica se o segundo argumento é válido
        if (nArg2 < 1) return 2;
        if (nArg2 > 99) return 3;
    }

    return 0;
}



// Verifica as restrições do comando 'p'
int restricoesImprimePont (char *arg1, Info I) {

    // Verifica se foi dado um argumento
    if (arg1 [0]) return 1;

    // Verifica se já foi lido um jogo
    if (I -> nTabuleiro == 0) return 2;

    return 0;
}



// Verifica as restrições do comando 'e'
int restricoesExplica (char *arg1) {

    // Verifica se foi dado um argumento
    if (arg1 [0]) return 1;

    return 0;
}



// Verifica as restrições do comando 'c'
int restricoesCriarJogo (char *arg1) {

    // Verifica se foi dado um argumento
    if (arg1 [0]) return 1;

    return 0;
}



// Verifica as restrições do comando 'E'
int restricoesEliminarJogo (char *arg1, char *arg2) {

    // Verifica se não foi dado um argumento
    if (arg1 [0] == 0) return 1;

    // Torna o primeiro argumento em inteiro
    int nArg1 = atoi (arg1);

    // Verifica se o primeiro argumento é válido
    if (nArg1 < 1) return 2;
    if (nArg1 < 5 && arg2 [0] == 0) return 3;
    if (nArg1 > 99) return 4;

    // Testa a validade do segundo argumento, caso exista
    if (arg2 [0]) {

        // Torna o segundo argumento em inteiro
        int nArg2 = atoi (arg2);

        // Verifica se o segundo argumento é válido
        if (nArg2 < 1) return 2;
        if (nArg2 > 99) return 4;
    }

    return 0;
}



// Verifica as restrições do comando 'j'
int restricoesIndicaJogos (char *arg1) {

    // Verifica se foi dado um argumento
    if (arg1 [0]) return 1;

    return 0;
}



// Verifica as restrições dos comandos 'b', 'r' e 'D'
int restricoesMudarCasa (char *arg1, Info I) {

    // Verifica se não foi dado um argumento
    if (arg1 [0] == 0) return 1;

    // Verifica se já foi aberto um jogo
    if (I -> nTabuleiro == 0) return 2;

    // Converte o argumento
    char c = arg1 [0];
    int l = atoi (arg1 + 1);

    // Verifica se o argumento é válido
    if (!eMinuscula (c)) return 3;
    if (l < 1) return 3;

    // Verifica se a coordenada é válida
    if (!coordenadaValida (atoi (arg1 + 1), arg1 [0], I -> dL, I -> dC)) return 4;

    // Verifica se a casa já está pintada de branco
    if (eMaiuscula (I -> Tabuleiro [l - 1][c - 'a'])) return 5;

    // Verifica se a cada já está riscada
    if (I -> Tabuleiro [l - 1][c - 'a'] == '#') return 6;

    return 0;
}



// Verifica as restrições do comando 'V'
int restricoesVisualizarHistorico (char *arg1, Info I) {

    // Verifica se existem tabuleiros para imprimir
    if (I -> nTabuleiro == 0) return 1;

    // Verifica se o primeiro argumento é válido
    if (arg1 [0]) {

        // Converte o argumento em inteiro
        int nTabs = atoi (arg1);

        // Verifica se o argumento é um natural
        if (nTabs < 1) return 2;

        // Verifica se o argumento é excessivo
        if (nTabs > I -> nTabuleiro) return 3;
    }

    return 0;
}



// Verifica as restrições do comando 'v'
int restricoesVerifica (char *arg1, Info I) {

    // Verifica se foi dado um argumento
    if (arg1 [0]) return 1;

    // Verifica se já foi lido um jogo
    if (I -> nTabuleiro == 0) return 2;

    return 0;
}



// Verifica as restrições do comando 'a'
int restricoesAjuda (char *arg1, Info I) {

    // Verifica se já foi lido um jogo
    if (I -> nTabuleiro == 0) return 1;

    // Verifica se o argumento é válido
    if (arg1 [0]) {
        if (arg1 [1]) return 2;
        if (arg1 [0] != 'b' && arg1 [0] != 'r' && arg1 [0] != 'o') return 2;
    }

    return 0;
}



// Verifica as restrições do comando 'A'
int restricoesAjudaRep (char *arg1, Info I) {

    // Verifica se foi dado um argumento
    if (arg1 [0]) return 1;

    // Verifica se já foi lido um jogo
    if (I -> nTabuleiro == 0) return 2;

    return 0;
}



// Verifica as restrições do comando 'd'
int restricoesDesfazerJogadas (char *arg1, Info I) {

    // Verifica se já foi lido um jogo
    if (I -> nTabuleiro == 0) return 1;

    // Verifica se há alguma jogada para desfazer
    if (I -> nTabuleiro == 1) return 2;

    // Testa se o argumento é válido, caso exista
    if (arg1 [0]) {

        // Converte o argumento em inteiro
        int q = atoi (arg1);

        // Verifica se o argumento é natural
        if (q < 1) return 3;

        // Verifica se o tabuleiro selecionado é o atual
        if (q == I -> nTabuleiro) return 4;

        // Verifica se o tabuleiro selecionado existe
        if (q > I -> nTabuleiro) return 5;
    }

    return 0;
}



// Verifica as restrições dos comandos 'R' e 'X'
int restricoesSolucaoJogo (char *arg1, Info I) {

    // Verifica se foi dado um argumento
    if (arg1 [0]) return 1;

    // Verifica se já foi lido um jogo
    if (I -> nTabuleiro == 0) return 2;

    return 0;
}