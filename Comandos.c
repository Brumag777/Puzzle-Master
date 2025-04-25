#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "puzzle.h"

// Grava o jogo num ficheiro
bool gravar (char cmd, char *arg, ESTADO *e) {

    if (cmd == 'g') {

        // Realiza a lógica do comando 'g'
        int n = logicaGravar (arg, e);

        // Avisa se o jogo foi gravado com sucesso
        if (n == 0) fprintf (stderr, "\nJogo gravado em '%s'.\n\n", arg);

        // Avisa se não foi dado um argumento
        else if (n == 1) fprintf (stderr, "\nErro: O comando g precisa de um argumento (nome do ficheiro).\n\n");

        // Avisa se não foi possível abrir o ficheiro
        else if (n == 2) fprintf (stderr, "\nErro: Não foi possível abrir o ficheiro.\n\n");

        return true;
    }

    return false;
}



// Lê um ficheiro
bool ler (char cmd, char *arg, ESTADO *e) {

    if (cmd == 'l') {

        // Realiza a lógica da comando 'l'
        int n = logicaLer (arg, e);

        // Se a leitura occoreu corretamente, imprime o tabuleiro novo e avisa do sucesso da leitura
        if (n == 0) fprintf (stderr, "Tabuleiro lido com sucesso.\n\n");

        // Avisa se não foi dado um argumento
        else if (n == 1) fprintf (stderr, "\nErro: O comando l precisa de um argumento (nome do ficheiro).\n\n");

        // Avisa se o ficheiro não foi aberto corretamente
        else if (n == 2) fprintf (stderr, "\nErro: Não foi possível abrir o ficheiro.\n\n");

        // Avisa se houve erros a ler o ficheiro
        else if (n == 3) fprintf (stderr, "\nErro: Não foi possível ler o ficheiro.\n\n");

        // Avisa se o tabuleiro do ficheiro lido é inválido
        else if (n == 4) fprintf (stderr, "\nErro: O tabuleiro é inválido.\n\n");

        return true;
    }

    return false;
}



// Termina o jogo
bool sair (char cmd, char *arg, ESTADO *e) {

    if (cmd == 's') {

        // Realiza a lógica do comando 's'
        int n = logicaSair (arg, e);

        // Avisa se foi dado um argumento
        if (n == 1) fprintf (stderr, "\nErro: O comando s não precisa de um argumento.\n\n");

        return true;
    } 

    return false;
}



// Pinta uma casa de branco
bool pintarCasa (char cmd, char *arg, ESTADO *e) {
    if (cmd == 'b') {

        // Realiza a lógica do comando 'b'
        int n = logicaPintarCasa (arg, e);

        // Avisa se não foi dado um argumento
        if (n == 1) fprintf (stderr, "\nErro: O comando b precisa de um argumento (coordenada).\n\n");

        // Avisa se a coordenada é inválida
        else if (n == 2) fprintf (stderr, "\nErro: A coordenada é inválida.\n\n");

        // Avisa se a casa selecionada está riscada
        else if (n == 3) fprintf (stderr, "\nErro: A casa selecionada está riscada.\n\n");

        // Avisa se a casa selecionada está pintada de branco
        else if (n == 4) fprintf (stderr, "\nErro: A casa selecionada já está pintada de branco.\n\n");

        return true;
    }
    
    return false;
}



// Muda uma casa para vazia
bool riscarCasa (char cmd, char *arg, ESTADO *e) {

    if (cmd == 'r') {

        // Realiza a lógica do comando 'r'
        int n = logicaRiscarCasa (arg, e);

        // Avisa se não foi dado um argumento
        if (n == 1) fprintf (stderr, "\nErro: O comando b precisa de um argumento (coordenada).\n\n");

        // Avisa se a coordenada é inválida
        else if (n == 2) fprintf (stderr, "\nErro: A coordenada é inválida.\n\n");

        // Avisa se a casa selecionada está riscada
        else if (n == 3) fprintf (stderr, "\nErro: A casa selecionada já está riscada.\n\n");

        // Avisa se a casa selecionada está pintada de branco
        else if (n == 4) fprintf (stderr, "\nErro: A casa selecionada está pintada de branco.\n\n");

        return true;
    }
    
    return false;
}



// Lista os comandos do jogo
bool listarComandos (char cmd, char *arg, ESTADO *e) {

    if (cmd == 'h') {

        // Realiza a lógica do comando 'h'
        int n = logicaListarComando (arg, e);

        // Avisa se foi dado um argumento
        if (n == 1) fprintf (stderr, "\nErro: O comando h não precisa de um argumento.\n\n");

        return true;
    }

    return false;
}



// Desfaz a últimas jogadas
bool desfazerJogada (char cmd, char *arg, ESTADO *e) {

    if (cmd == 'd') {

        // Realiza a lógica do comando 'd'
        int n = logicaDesfazerJogada (arg, e);

        // Avisa se não há um tabuleiro anterior
        if (n == 1) fprintf (stderr, "\nErro: Não existem tabuleiros anteriores.\n\n");

        // Avisa se o argumento não é um número natural
        else if (n == 2) fprintf (stderr, "\nErro: O argumento deve ser um número natural.\n\n");

        // Avisa se foi selecionado o tabuleiro atual
        else if (n == 3) fprintf (stderr, "\nErro: Esse é o tabuleiro atual.\n\n");

        // Avisa se não existe o tabuleiro desejado
        else if (n == 4) fprintf (stderr, "\nErro: O argumento é maior que o número de jogadas (%d).\n\n", e -> info -> hTabuleiros -> sp);

        return true;
    }

    return false;
}



// Imprime os últimos tabuleiros armazenados no histórico
bool visualizarHistorico (char cmd, char *arg, ESTADO *e) {

    if (cmd == 'V') {

        // Realiza a lógica do comando 'V'
        int n = logicaVizualizarHistorico (arg, e);

        // Avisa se o argumento não é um número natural
        if (n == 1) fprintf (stderr, "\nErro: O argumento deve ser um número natural.\n\n");

        // Avisa se não existem tabuleiros para imprimir
        else if (n == 2) fprintf (stderr, "\nErro: Não existem tabuleiros para imprimir.\n\n");

        // Avisa se não existem tabuleiros suficientes para imprimir
        else if (n == 3) fprintf (stderr, "\nErro: O argumento é maior que o número de tabuleiros (%d).\n\n", e -> info -> hTabuleiros -> sp);

        return true;
    }

    return false;
}



// Verifica se existem infrações no tabuleiro
bool verifica (char cmd, char *arg, ESTADO *e) {

    if (cmd == 'v') {

        // Realiza a lógica do comando 'v'
        int n = logicaVerifica (arg, e);

        // Avisa se foi dado um argumento
        if (n == 1) fprintf (stderr, "\nErro: O comando v não precisa de um argumento.\n\n");

        return true;
    }

    return false;
}



// Ajuda o jogador realizando jogadas 'obrigatórias' na posição
bool ajuda (char cmd, char *arg, ESTADO *e) {

    if (cmd == 'a') {

        // Realiza a lógica do comando 'a'
        int n = logicaAjuda (arg, e);

        // Avisa se foi dado um argumento
        if (n == 1) fprintf (stderr, "\nErro: O argumento é inválido.\n\n");

        // Avisa se não há nada a alterar
        if (n == 2) printf ("\nNão há nada a alterar.\n\n");

        return true;
    }

    return false;
}



// Ajuda o jogador realizando jogadas 'obrigatórias' repetidamente até não haver nada a alterar
bool ajudaRep (char cmd, char *arg, ESTADO *e) {

    if (cmd == 'A') {

        // Realiza a lógica do comando 'A'
        int n = logicaAjudaRep (arg, e);

        // Avisa se foi dado um argumento
        if (n == 1) fprintf (stderr, "\nErro: O comando A não precisa de um argumento.\n\n");

        // Avisa se não há nada a alterar
        if (n == 2) printf ("\nNão há nada a alterar.\n\n");

        return true;
    }

    return false;
}



// Resolve o jogo automaticamente
bool resolveJogo (char cmd, char *arg, ESTADO *e) {

    if (cmd == 'R') {

        // Realiza a lógica do comando 'R'
        int n = logicaResolveJogo (arg, e);

        // Avisa se foi dado um argumento
        if (n == 1) fprintf (stderr, "\nErro: O comando R não precisa de um argumento.\n\n");

        // Avisa se não é possível resolver o jogo
        else if (n == 2) fprintf (stderr, "\nAviso: Não é possível resolver o jogo atual.\n\n");

        return true;
    }

    return false;
}