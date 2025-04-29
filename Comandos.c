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

        // Avisa se não há nada a guardar
        else if (n == 2) fprintf (stderr, "\nErro: Não há nada a guardar. Use o comando l para iniciar um jogo.\n\n");

        // Avisa se não foi possível abrir o ficheiro
        else if (n == 3) fprintf (stderr, "\nErro: Não foi possível abrir o ficheiro.\n\n");

        return true;
    }

    return false;
}



// Lê um ficheiro
bool ler (char cmd, char *arg, ESTADO *e) {

    if (cmd == 'l') {

        // Realiza a lógica da comando 'l'
        int n = logicaLer (arg, e);

        // Caso de sucesso da função
        if (n == 0) {
            // Imprime o tabuleiro atualizado
            visualizaUltimosTabuleiros (e -> info -> hTabuleiros, 1, 0, 0);

            // Avisa que o ficheiro foi fido com sucesso
            fprintf (stderr, "Tabuleiro lido com sucesso.\n\n");
        }

        // Avisa se não foi dado um argumento
        else if (n == 1) fprintf (stderr, "\nErro: O comando l precisa de um argumento (nome do ficheiro).\n\n");

        // Avisa se o ficheiro não foi aberto corretamente
        else if (n == 2) fprintf (stderr, "\nErro: Não foi possível abrir o ficheiro.\n\n");

        // Avisa se houve erros a ler o ficheiro
        else if (n == 3) fprintf (stderr, "\nErro: Não foi possível ler o ficheiro.\n\n");

        // Avisa se o tabuleiro do ficheiro lido é inválido
        else if (n == 4) fprintf (stderr, "\nErro: Os tabuleiros não são válidos.\n\n");

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

        // Caso de sucesso da função
        if (n == 0) {
            // Adiciona o tabuleiro resultante ao histórico de tabuleiros
            pushStack (e -> info -> hTabuleiros, e -> info -> Tabuleiro, e -> info -> linhas, e -> info -> colunas);

            // Imprime o tabuleiro atualizado
            visualizaUltimosTabuleiros (e -> info -> hTabuleiros, 1, 0, 0);

            // Se o jogo estiver terminado, indica se o jogador ganhou
            if (testeJogo (e -> info)) printf ("Parabéns! Conseguiste resolver o puzzle!\n\n");
        }

        // Avisa se não foi dado um argumento
        else if (n == 1) fprintf (stderr, "\nErro: O comando b precisa de um argumento (coordenada).\n\n");

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

        // Caso de sucesso da função
        if (n == 0) {
            // Adiciona o tabuleiro resultante ao histórico de tabuleiros
            pushStack (e -> info -> hTabuleiros, e -> info -> Tabuleiro, e -> info -> linhas, e -> info -> colunas);

            // Imprime o tabuleiro resultante
            visualizaUltimosTabuleiros (e -> info -> hTabuleiros, 1, 0, 0);

            // Se o jogo estiver terminado, indica se o jogador ganhou
            if (testeJogo (e -> info)) printf ("Parabéns! Conseguiste resolver o puzzle!\n\n");
        }

        // Avisa se não foi dado um argumento
        else if (n == 1) fprintf (stderr, "\nErro: O comando b precisa de um argumento (coordenada).\n\n");

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
        int n = logicaListarComandos (arg, e);

        // Caso de sucesso da função
        if (n == 0) {
            // Imprime os comandos do jogo
            printf ("\nOs comandos do jogo são:\n"
                    "g <ficheiro>: Grava o tabuleiro num ficheiro.\n"
                    "l <ficheiro>: Lê um tabuleiro de um ficheiro.\n"
                    "b <coordenada>: Pinta a casa selecinada de branco (caso possível).\n"
                    "r <coordenada>: Torna a casa selecionada vazia (caso possível).\n"
                    "v: Verifica se existem infrações na posição atual.\n"
                    "V: Permite ver o último tabuleiro.\n"
                    "V <natural>: Permite ver os tabuleiros anteriores.\n"
                    "a: Ajuda realizando todas as jogadas necessárias na posição atual.\n"
                    "a b: Ajuda pintando de branco as casas à volta de casas riscadas.\n"
                    "a r: Ajuda riscando as casas na mesma linha ou coluna que casas brancas com a mesma letra.\n"
                    "a o: Ajuda pintando de branco as casas que se fossem riscadas não permitiam um caminho ortogonal entre todas as letras.\n"
                    "A: Ajuda realizando todas as jogadas necessárias na posição até não haver mais nenhuma a realizar.\n"
                    "R: Resolve o jogo (se for possível).\n"
                    "X: Mostra a solução do tabuleiro atual (caso exista).\n"
                    "d: Desfaz a última jogada.\n"
                    "d <natural>: Desfaz as últimas jogadas até ao tabuleiro selecinado.\n"
                    "s: Termina o jogo.\n"
                    "h: Lista todos os comandos do jogo.\n\n");
            if (e -> info -> hTabuleiros -> sp) {
                printf ("As coordenadas devem estar compreendidas entre a1 e %c%d \n", e -> info -> colunas + 'a' - 1, e -> info -> linhas);
                printf ("Os números naturais devem ser iguais ou inferiores a %d\n\n", e -> info -> hTabuleiros -> sp);
            }
            else printf ("Leia um ficheiro para usar os comandos.\n\n");
        }

        // Avisa se foi dado um argumento
        else if (n == 1) fprintf (stderr, "\nErro: O comando h não precisa de um argumento.\n\n");

        return true;
    }

    return false;
}



// Desfaz a últimas jogadas
bool desfazerJogada (char cmd, char *arg, ESTADO *e) {

    if (cmd == 'd') {

        // Realiza a lógica do comando 'd'
        int n = logicaDesfazerJogada (arg, e);

        // Caso de sucesso da função
        if (n == 0) {
            // Remove o tabuleiro antigo do histórico de tabuleiros
            popStack (e -> info -> hTabuleiros);

            // Imprime o tabuleiro atualizado
            visualizaUltimosTabuleiros (e -> info -> hTabuleiros, 1, 0, 0);
        }

        // Avisa se não há um tabuleiro anterior
        else if (n == 1) fprintf (stderr, "\nErro: Não existem tabuleiros para desfazer.\n\n");

        // Avisa se o argumento não é um número natural
        else if (n == 2) fprintf (stderr, "\nErro: O argumento deve ser um número natural.\n\n");

        // Avisa se foi selecionado o tabuleiro atual
        else if (n == 3) fprintf (stderr, "\nErro: Esse é o tabuleiro atual.\n\n");

        // Avisa se não existe o tabuleiro desejado
        else if (n == 4) fprintf (stderr, "\nErro: O argumento é maior que o número de tabuleiros (%d).\n\n", e -> info -> hTabuleiros -> sp);

        // Caso em que existe apenas um tabuleiro
        else if (n == 5) {
            // Remove o tabuleiro antigo do histórico de tabuleiros
            popStack (e -> info -> hTabuleiros);

            // Avisa que não existem mais tabuleiros
            printf ("\nNão existem mais tabuleiros. Leia um ficheiro para iniciar um jogo.\n\n");
        }

        return true;
    }

    return false;
}



// Imprime os últimos tabuleiros armazenados no histórico
bool visualizarHistorico (char cmd, char *arg, ESTADO *e) {

    if (cmd == 'V') {

        // Realiza a lógica do comando 'V'
        int n = logicaVizualizarHistorico (arg, e);

        // Caso de sucesso da função
        if (n > 0) visualizaUltimosTabuleiros (e -> info -> hTabuleiros, n, 1, 0);

        // Avisa se o argumento não é um número natural
        else if (n == -1) fprintf (stderr, "\nErro: O argumento deve ser um número natural.\n\n");

        // Avisa se não existem tabuleiros para imprimir
        else if (n == -2) fprintf (stderr, "\nErro: Não existem tabuleiros para imprimir.\n\n");

        // Avisa se não existem tabuleiros suficientes para imprimir
        else if (n == -3) fprintf (stderr, "\nErro: O argumento é maior que o número de tabuleiros (%d).\n\n", e -> info -> hTabuleiros -> sp);

        return true;
    }

    return false;
}



// Verifica se existem infrações no tabuleiro
bool verifica (char cmd, char *arg, ESTADO *e) {

    if (cmd == 'v') {

        // Realiza a lógica do comando 'v'
        int n = logicaVerifica (arg, e);

        // Casos de sucesso da função
        if (n == 0) putchar ('\n');
        if (n == 1) {
            printf ("Não há nenhuma infração.\n");
            putchar ('\n');
        }

        // Avisa se foi dado um argumento
        else if (n == -1) fprintf (stderr, "\nErro: O comando v não precisa de um argumento.\n\n");

        return true;
    }

    return false;
}



// Ajuda o jogador realizando jogadas 'obrigatórias' na posição
bool ajuda (char cmd, char *arg, ESTADO *e) {

    if (cmd == 'a') {

        // Realiza a lógica do comando 'a'
        int n = logicaAjuda (arg, e);

        // Caso de sucesso da função
        if (n == 0) {
            // Atualiza o histórico de tabuleiros
            pushStack (e -> info -> hTabuleiros, e -> info -> Tabuleiro, e -> info -> linhas, e -> info -> colunas);

            // Imprime o tabuleiro resultante
            visualizaUltimosTabuleiros (e -> info -> hTabuleiros, 1, 0, 0);

            // Se o jogo estiver terminado, indica se o jogador ganhou
            if (testeJogo (e -> info)) printf ("Parabéns! Conseguiste resolver o puzzle!\n\n");
        }

        // Avisa se foi dado um argumento
        else if (n == 1) fprintf (stderr, "\nErro: O argumento é inválido.\n\n");

        // Avisa se não há nada a alterar
        else if (n == 2) printf ("\nNão há nada a alterar.\n\n");

        return true;
    }

    return false;
}



// Ajuda o jogador realizando jogadas 'obrigatórias' repetidamente até não haver nada a alterar
bool ajudaRep (char cmd, char *arg, ESTADO *e) {

    if (cmd == 'A') {

        // Realiza a lógica do comando 'A'
        int n = logicaAjudaRep (arg, e);

        // Caso de sucesso da função
        if (n == 0) {
            // Atualiza o histórico de tabuleiros
            pushStack (e -> info -> hTabuleiros, e -> info -> Tabuleiro, e -> info -> linhas, e -> info -> colunas);

            // Imprime o tabuleiro resultante
            visualizaUltimosTabuleiros (e -> info -> hTabuleiros, 1, 0, 0);

            // Se o jogo estiver terminado, indica se o jogador ganhou
            if (testeJogo (e -> info)) printf ("Parabéns! Conseguiste resolver o puzzle!\n\n");
        }

        // Avisa se foi dado um argumento
        else if (n == 1) fprintf (stderr, "\nErro: O comando A não precisa de um argumento.\n\n");

        // Avisa se não há nada a alterar
        else if (n == 2) printf ("\nNão há nada a alterar.\n\n");

        return true;
    }

    return false;
}



// Resolve o jogo automaticamente
bool resolveJogo (char cmd, char *arg, ESTADO *e) {

    if (cmd == 'R') {

        // Realiza a lógica do comando 'R'
        int n = logicaResolveJogo (arg, e);

        // Caso de sucesso da função
        if (n == 0) {
            // Atualiza o histórico de tabuleiros
            pushStack (e -> info -> hTabuleiros, e -> info -> Tabuleiro, e -> info -> linhas, e -> info -> colunas);

            // Imprime o tabuleiro resultante
            visualizaUltimosTabuleiros (e -> info -> hTabuleiros, 1, 0, 0);
        }

        // Avisa se foi dado um argumento
        if (n == 1) fprintf (stderr, "\nErro: O comando R não precisa de um argumento.\n\n");

        // Avisa se não há um jogo para resolver
        if (n == 2) fprintf (stderr, "\nErro: Não há um jogo para resolver. Use o comando l para iniciar um jogo.\n\n");

        // Avisa se não é possível resolver o jogo
        else if (n == 3) fprintf (stderr, "\nAviso: Não é possível resolver o jogo atual.\n\n");

        return true;
    }

    return false;
}



// Mostra a solução do jogo (caso exista)
bool mostrarSolucao (char cmd, char *arg, ESTADO *e) {

    if (cmd == 'X') {

        // Realiza a lógica do comando 'X'
        int n = logicaResolveJogo (arg, e);

        // Caso de sucesso da função
        if (n == 0) {
            printf ("\nA solução do jogo atual é a seguinte:\n");

            // Adiciona temporariamente o tabuleiro resultante ao histórico de tabuleiros
            pushStack (e -> info -> hTabuleiros, e -> info -> Tabuleiro, e -> info -> linhas, e -> info -> colunas);

            // Imprime o tabuleiro resultante
            visualizaUltimosTabuleiros (e -> info -> hTabuleiros, 1, 0, 1);

            // Remove o tabuleiro resultante do histórico de tabuleiros
            popStack (e -> info -> hTabuleiros);

            // Atualiza o tabuleiro para o anterior à solução
            for (int i = 0; i < e -> info -> linhas; i++)
                strcpy (e -> info -> Tabuleiro [i], e -> info -> hTabuleiros -> TAnteriores [e -> info -> hTabuleiros -> sp - 1][i]);
        }

        // Avisa se foi dado um argumento
        if (n == 1) fprintf (stderr, "\nErro: O comando X não precisa de um argumento.\n\n");

        // Avisa se não há um jogo para encontar solução
        if (n == 2) fprintf (stderr, "\nErro: Não há um jogo para revelar a solução. Use o comando l para iniciar um jogo.\n\n");

        // Avisa se não é possível resolver o jogo
        else if (n == 3) fprintf (stderr, "\nAviso: O jogo atual não possui solução.\n\n");

        return true;
    }

    return false;
}