#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "puzzle.h"

// Grava o jogo num ficheiro
bool gravar (char cmd, char *arg, ESTADO *e) {

    if (cmd == 'g') {

        // Verifica se foi recebido um argumento (nome do ficheiro)
        if (arg == NULL) {
            fprintf (stderr, "Erro: o comando g precisa de um argumento\n\n");
            return false;
        }

        // Abre o ficheiro a preencher
        FILE *f = fopen (arg, "w");

        // Verifica se o ficheiro foi aberto corretamente
        if (f == NULL) {
            fprintf (stderr, "Erro ao abrir o ficheiro para escrita\n\n");
            return false;
        }

        // Preenche o ficheiro com a quantidade de linhas e de colunas, assim como o tabuleiro atual
        IJ *info = e -> info;
        fprintf (f, "%d %d\n", info -> linhas, info -> colunas);
        for (int i = 0; i < info -> linhas; i++)
            fprintf(f, "%s", info -> Tabuleiro [i]);

        // Fecha o ficheiro
        fclose (f);
        printf ("Jogo gravado em '%s'\n\n", arg);

        return true;
    }

    return false;
}



// Lê um ficheiro
bool ler (char cmd, char *arg, ESTADO *e) {

    if (cmd == 'l') {

        // Verifica se foi recebido um argumento (nome do ficheiro)
        if (arg == NULL) {
            fprintf (stderr, "Erro: o comando l precisa de um argumento\n\n");
            return false;
        }

        // Lê o ficheiro
        auxLer (e, arg);

        return true;
    }

    return false;
}



// Termina o jogo
bool sair (char cmd, char *arg, ESTADO *e) {

    // Verifica se não foi recebido um argumento
    if (arg == NULL && cmd == 's') {

        // Define o looping como falso de modo a terminar o ciclo na main
        e -> looping = false;

        return true;
    } 
    
    return false;
}



// Pinta uma casa de branco
bool mudarParaMaiuscula (char cmd, char *arg, ESTADO *e) {
    if (cmd == 'b') {

        // Verifica se foi recebido um argumento (coordenada)
        if (arg == NULL) {
            fprintf (stderr, "Erro: o comando b precisa de um argumento (coordenada)\n\n");
            return false;
        }

        // Define a letra e o número correspondentes à coordenada
        char c = arg [0];
        int l = atoi (arg + 1);

        // Verifica se a coordenada recebida é válida (isto é, está dentro do tabuleiro)
        if (!coordenadaValida (l, c, e -> info -> linhas, e -> info -> colunas)) {
            fprintf (stderr, "Erro: a coordenada é inválida\n\n");
            return false;
        }

        // Verifica se a coordenada recebida é uma letra minúscula
        if (!eMinuscula (e -> info -> Tabuleiro [l - 1][c - 'a'])) {
            fprintf (stderr, "Erro: a casa %c%d não contém uma letra minúscula.\n\n", c, l);
            return false;
        }

        // Pinta a casa de branco
        e -> info -> Tabuleiro [l - 1][c - 'a'] -= 'a' - 'A';

        // Adiciona o tabuleiro resultante ao histórico de tabuleiros
        pushStack (e -> info -> hTabuleiros, e -> info -> Tabuleiro, e -> info -> linhas);

        // Imprime o tabuleiro resultante
        visualizarTabuleiro (e -> info);

        return true;
    }
    
    return false;
}



// Muda uma casa para vazia
bool mudarParaVazia (char cmd, char *arg, ESTADO *e) {

    if (cmd == 'r') {

        // Verifica se foi recebido um argumento (coordenada)
        if (arg == NULL) {
            fprintf (stderr, "Erro: o comando r precisa de um argumento (coordenada)\n\n");
            return false;
        }

        // Define a letra e o número correspondentes à coordenada
        char c = arg [0];
        int l = atoi (arg + 1);

        // Verifica se a coordenada recebida é válida (isto é, está dentro do tabuleiro)
        if (!coordenadaValida (l, c, e -> info -> linhas, e -> info -> colunas)) {
            fprintf (stderr, "Erro: a coordenada é inválida\n\n");
            return false;
        }

        // Verifica se a coordenada recebida não está vazia
        if (e -> info -> Tabuleiro [l - 1][c - 'a'] == '#') {
            fprintf (stderr, "Erro: a coordenada %c%d já é vazia\n\n", c, l);
            return false;
        }

        // Muda a casa para vazio
        e -> info -> Tabuleiro [l - 1][c - 'a'] = '#';

        // Adiciona o tabuleiro resultante ao histórico de tabuleiros
        pushStack (e -> info -> hTabuleiros, e -> info -> Tabuleiro, e -> info -> linhas);

        // Imprime o tabuleiro resultante
        visualizarTabuleiro (e -> info);

        return true;
    }
    
    return false;
}



// Lista os comandos do jogo
bool listarComandos (char cmd, char *arg, ESTADO *e) {

    // Ignora o parâmetro e para evitar o warning de "unused parameter"
    (void) e;

    if (cmd == 'h') {

        // Verifica se não foi recebido um argumento
        if (arg != NULL) {
            fprintf (stderr, "Erro: o comando h não precisa de um argumento\n\n");
            return false;
        }

        // Imprime os comandos do jogo
        printf ("\nOs comandos do jogo são:\n"
                "g <ficheiro>: Grava o estado atual do jogo\n"
                "l <ficheiro>: Lê o estado do jogo\n"
                "b <coordenada>: Coloca a letra da casa em maiúsculas\n"
                "r <coordenada>: Coloca a casa vazia\n"
                "v: Verifica o estado do jogo e aponta todas as restrições violadas\n"
                "V <natural>: Permite ver os tabuleiros anteriores\n"
                "a: Ajuda mudando todas as casas que se pode inferir no estado atual do tabuleiro\n"
                "A: Invoca o comando 'a' enquanto o jogo sofre alterações\n"
                "R: Resolve o jogo\n"
                "d <natural>: Desfaz a última jogada\n"
                "s: Termina o jogo\n"
                "h: Lista todos os comandos do jogo\n");
                putchar ('\n');

        return true;
    }

    return false;
}



// Desfaz a últimas jogadas
bool desfazerJogada (char cmd, char *arg, ESTADO *e) {

    if (cmd == 'd') {

        // Verifica se foi recebido um argumento (número natural)
        if (arg == NULL) {
            fprintf (stderr, "Erro: o comando d precisa de um argumento (número natural)\n\n");
            return false;
        }

        // Define o tabuleiro para o qual o jogo vai retornar
        int q = atoi (arg);

        // Verifica se o argumento é um número natural
        if (q < 1) {
            fprintf (stderr, "Erro: o argumento deve ser um número natural\n\n");
            return false;
        }

        // Verifica se o argumento não é igual ao tabuleiro atual
        if (q == e -> info -> hTabuleiros -> sp) {
            fprintf (stderr, "Erro: não há nada a atualizar\n\n");
            return false;
        }

        // Verifica se o tabuleiro desejado existe
        if (q > e -> info -> hTabuleiros -> sp) {
            fprintf (stderr, "Erro: ainda não existe o tabuleiro %d\n\n", q);
            return false;
        }

        // Certificação de que o jogador deseja desfazer a(s) última(s) jogada(s)
        fprintf (stderr, "Tem a certeza de que deseja retornar ao %dº tabuleiro?\n> ", q);
        char c [LINE_SIZE];
        while (1) {

            if (scanf ("%s", c) != 1) return false;

            if (strcmp (c, "sim") && strcmp (c, "Sim") && strcmp (c, "s") && strcmp (c, "S")) {

                if (strcmp (c, "não") && strcmp (c, "Não") && strcmp (c, "n") && strcmp (c, "N"))
                    fprintf (stderr, "Resposta inválida: deve ser 'sim' ou 'não'. Responda novamente.\n> ");

                else {
                    putchar ('\n');
                    return true;
                }
            }
            else break;
        }

        // Desfaz as últimas jogadas até ao tabuleiro anterior ao desejado
        while (e -> info -> hTabuleiros -> sp > q + 1)
            popStack (e -> info -> hTabuleiros, e -> info -> linhas);

        // Atualiza o tabuleiro para o desejado
        for (int i = 0; i < e -> info -> linhas; i++)
            strcpy (e -> info -> Tabuleiro [i], e -> info -> hTabuleiros -> TAnteriores [e -> info -> hTabuleiros -> sp - 2][i]);

        // Remove o último tabuleiro do histórico
        popStack (e -> info -> hTabuleiros, e -> info -> linhas);

        // Imprime o tabuleiro resultante (anterior)
        visualizarTabuleiro (e -> info);

        return true;
    }

    return false;
}



// Imprime os últimos tabuleiros armazenados no histórico
bool vizualizarStack (char cmd, char *arg, ESTADO *e) {

    if (cmd == 'V') {

        // Verifica se foi recebido um argumento (número natural)
        if (arg == NULL) {
            fprintf (stderr, "Erro: o comando V precisa de um argumento (número natural)\n\n");
            return false;
        }

        // Define a quantidade de tabuleiros a imprimir
        int q = atoi (arg);

        // Verifica se o argumento é um número natural
        if (q < 1) {
            fprintf (stderr, "Erro: o argumento deve ser um número natural\n\n");
            return false;
        }

        // Verifica se a quantidade de tabuleiros a imprimir é menor ou igual à quantidade de tabuleiros guardados no histórico
        if (q > e -> info -> hTabuleiros -> sp) {
            fprintf (stderr, "Erro: o argumento é maior que o número de jogadas (%d)\n\n", e -> info -> hTabuleiros -> sp);
            return false;
        }

        // Imprime os últimos q tabuleiros armazenados no histórico
        vizualizaUltimosTabuleiros (e -> info -> hTabuleiros, e -> info -> linhas, e -> info -> colunas, q);

        return true;
    }

    return false;
}



// Verifica se existem infrações no tabuleiro
bool verifica (char cmd, char *arg, ESTADO *e) {

    if (cmd == 'v') {

        // Verifica se não foi recebido um argumento
        if (arg != NULL) {
            fprintf (stderr, "Erro: o comando v não precisa de um argumento\n\n");
            return false;
        }

        putchar ('\n');

        // Inteiro representante da validade do tabuleiro
        int r = 1;

        // Percorre o tabuleiro para verificar as restrições
        for (int i = 0; i < e -> info -> linhas; i++)

            // Percorre cada linha do tabuleiro para verificar as restrições
            for (int j = 0; j < e -> info -> colunas; j++) {

                // Verifica se não houve restrições relativas a casas vazias
                if (e -> info -> Tabuleiro [i][j] == '#')
                    if (r) r = verificaHashtag (e -> info, i, j);
                    else verificaHashtag (e -> info, i, j);
                
                // Verifica se não houve restrições relativas a casas brancas
                else if (eMaiuscula (e -> info -> Tabuleiro [i][j])) {
                    if (r) r = verificaLinhas (e -> info, e -> info -> Tabuleiro [i][j], i, j);
                    else verificaLinhas (e -> info, e -> info -> Tabuleiro [i][j], i, j);
                    if (r) r = verificaColunas (e -> info, e -> info -> Tabuleiro [i][j], i, j);
                    else verificaColunas (e -> info, e -> info -> Tabuleiro [i][j], i, j);
                }
            }

        // Avisa casa não houve nenhuma infração, isto é, se o tabuleiro é válido
        if (r) printf ("Não há nenhuma infração\n");

        putchar ('\n');

        return true;
    }

    return false;
}