#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "puzzle.h"

// Grava o jogo num ficheiro
bool gravar (char cmd, char *arg, ESTADO *e) {

    if (cmd == 'g') {

        // Verifica se foi recebido um argumento (nome do ficheiro)
        if (arg == NULL) {
            fprintf (stderr, "\nErro: O comando g precisa de um argumento (nome do ficheiro).\n\n");
            return true;
        }

        // Abre o ficheiro a preencher
        FILE *f = fopen (arg, "w");

        // Verifica se o ficheiro foi aberto corretamente
        if (f == NULL) {
            fprintf (stderr, "\nErro: Não foi possível abrir o ficheiro.\n\n");
            return true;
        }

        // Preenche o ficheiro com a quantidade de linhas e de colunas, assim como o tabuleiro atual
        IJ *info = e -> info;
        fprintf (f, "%d %d\n", info -> linhas, info -> colunas);
        for (int i = 0; i < info -> linhas; i++)
            fprintf(f, "%s", info -> Tabuleiro [i]);

        // Fecha o ficheiro
        fclose (f);
        fprintf (stderr, "\nJogo gravado em '%s'.\n\n", arg);

        return true;
    }

    return false;
}



// Lê um ficheiro
bool ler (char cmd, char *arg, ESTADO *e) {

    if (cmd == 'l') {

        // Verifica se foi recebido um argumento (nome do ficheiro)
        if (arg == NULL) {
            fprintf (stderr, "\nErro: O comando l precisa de um argumento (nome do ficheiro).\n\n");
            return true;
        }

        // Lê o ficheiro
        auxLer (e, arg);

        return true;
    }

    return false;
}



// Termina o jogo
bool sair (char cmd, char *arg, ESTADO *e) {

    if (cmd == 's') {

        // Verifica se não foi recebido um argumento
        if (arg != NULL) {
            fprintf (stderr, "\nErro: O comando s não precisa de um argumento.\n\n");
            return true;
        }

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
            fprintf (stderr, "\nErro: O comando b precisa de um argumento (coordenada).\n\n");
            return true;
        }

        // Define a letra e o número correspondentes à coordenada
        char c = arg [0];
        int l = atoi (arg + 1);

        // Verifica se a coordenada recebida é válida (isto é, está dentro do tabuleiro)
        if (!coordenadaValida (l, c, e -> info -> linhas, e -> info -> colunas)) {
            fprintf (stderr, "\nErro: A coordenada é inválida.\n\n");
            return true;
        }

        // Verifica se a coordenada recebida é uma letra minúscula
        if (!eMinuscula (e -> info -> Tabuleiro [l - 1][c - 'a'])) {
            fprintf (stderr, "\nErro: A casa %c%d não contém uma letra minúscula.\n\n", c, l);
            return true;
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
            fprintf (stderr, "\nErro: O comando r precisa de um argumento (coordenada).\n\n");
            return true;
        }

        // Define a letra e o número correspondentes à coordenada
        char c = arg [0];
        int l = atoi (arg + 1);

        // Verifica se a coordenada recebida é válida (isto é, está dentro do tabuleiro)
        if (!coordenadaValida (l, c, e -> info -> linhas, e -> info -> colunas)) {
            fprintf (stderr, "\nErro: A coordenada é inválida.\n\n");
            return true;
        }

        // Verifica se a coordenada recebida não está vazia
        if (e -> info -> Tabuleiro [l - 1][c - 'a'] == '#') {
            fprintf (stderr, "\nErro: A casa %c%d já é vazia.\n\n", c, l);
            return true;
        }

        // Verifica se a coordenada recebida não está pintada de branco
        if (eMaiuscula (e -> info -> Tabuleiro [l - 1][c - 'a'])) {
            fprintf (stderr, "\nErro: A casa %c%d está pintada de branco.\n\n", c, l);
            return true;
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
            fprintf (stderr, "\nErro: O comando h não precisa de um argumento.\n\n");
            return true;
        }

        // Imprime os comandos do jogo
        printf ("\nOs comandos do jogo são:\n"
                "g <ficheiro>: Grava o tabuleiro num ficheiro.\n"
                "l <ficheiro>: Lê um tabuleiro de um ficheiro.\n"
                "b <coordenada>: Pinta a casa selecinada de branco (caso possível).\n"
                "r <coordenada>: Torna a casa selecionada vazia (caso possível).\n"
                "v: Verifica se existem infrações na posição atual.\n"
                "V <natural>: Permite ver os tabuleiros anteriores.\n"
                "a: Ajuda realizando todas as jogadas necessárias na posição atual.\n"
                "A: Ajuda realizando todas as jogadas necessárias na posição até não haver mais nenhuma a realizar.\n"
                "R: Resolve o jogo (se for possível).\n"
                "d <natural>: Desfaz as últimas jogadas até ao tabuleiro selecinado.\n"
                "s: Termina o jogo.\n"
                "h: Lista todos os comandos do jogo.\n\n");

        return true;
    }

    return false;
}



// Desfaz a últimas jogadas
bool desfazerJogada (char cmd, char *arg, ESTADO *e) {

    if (cmd == 'd') {

        // Verifica se foi recebido um argumento (número natural)
        if (arg == NULL) {
            fprintf (stderr, "\nErro: O comando d precisa de um argumento (número natural).\n\n");
            return true;
        }

        // Define o tabuleiro para o qual o jogo vai retornar
        int q = atoi (arg);

        // Verifica se o argumento é um número natural
        if (q < 1) {
            fprintf (stderr, "\nErro: O argumento deve ser um número natural.\n\n");
            return true;
        }

        // Verifica se o argumento não é igual ao tabuleiro atual
        if (q == e -> info -> hTabuleiros -> sp) {
            fprintf (stderr, "\nErro: Esse é o tabuleiro atual.\n\n");
            return true;
        }

        // Verifica se o tabuleiro desejado existe
        if (q > e -> info -> hTabuleiros -> sp) {
            fprintf (stderr, "\nErro: Ainda não existe esse tabuleiro (o último é o %dº).\n\n", e -> info -> hTabuleiros -> sp);
            return true;
        }

        // Certificação de que o jogador deseja desfazer a(s) última(s) jogada(s)
        fprintf (stderr, "\nTem a certeza de que deseja retornar ao %dº tabuleiro?\n> ", q);
        char c [LINE_SIZE];
        while (1) {

            if (scanf ("%s", c) != 1) return true;

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
bool visualizarStack (char cmd, char *arg, ESTADO *e) {

    if (cmd == 'V') {

        // Verifica se foi recebido um argumento (número natural)
        if (arg == NULL) {
            fprintf (stderr, "\nErro: O comando V precisa de um argumento (número natural).\n\n");
            return true;
        }

        // Define a quantidade de tabuleiros a imprimir
        int q = atoi (arg);

        // Verifica se o argumento é um número natural
        if (q < 1) {
            fprintf (stderr, "\nErro: O argumento deve ser um número natural.\n\n");
            return true;
        }

        // Verifica se a quantidade de tabuleiros a imprimir é menor ou igual à quantidade de tabuleiros guardados no histórico
        if (q > e -> info -> hTabuleiros -> sp) {
            fprintf (stderr, "\nErro: O argumento é maior que o número de jogadas (%d).\n\n", e -> info -> hTabuleiros -> sp);
            return true;
        }

        // Imprime os últimos q tabuleiros armazenados no histórico
        visualizaUltimosTabuleiros (e -> info -> hTabuleiros, e -> info -> linhas, e -> info -> colunas, q);

        return true;
    }

    return false;
}



// Verifica se existem infrações no tabuleiro
bool verifica (char cmd, char *arg, ESTADO *e) {

    if (cmd == 'v') {

        // Verifica se não foi recebido um argumento
        if (arg != NULL) {
            fprintf (stderr, "\nErro: O comando v não precisa de um argumento.\n\n");
            return true;
        }

        putchar ('\n');

        // Inteiro representante da validade do tabuleiro
        int validade = 1;

        // Percorre o tabuleiro para procurar infrações
        for (int i = 0; i < e -> info -> linhas; i++)

            // Percorre cada linha do tabuleiro para procurar infrações
            for (int j = 0; j < e -> info -> colunas; j++) {
                
                // Verifica se houve infrações relativas a casas brancas
                if (eMaiuscula (e -> info -> Tabuleiro [i][j])) {
                    if (!verificaLinhas (e -> info, e -> info -> Tabuleiro [i][j], i, j) ||
                        !verificaColunas (e -> info, e -> info -> Tabuleiro [i][j], i, j)) validade = 0;
                }

                // Verifica se houve infrações relativas a casas vazias
                else if (e -> info -> Tabuleiro [i][j] == '#')
                    if (!verificaCasaVazia (e -> info, i, j)) validade = 0;
            }



        // Cria um tabuleiro auxiliar para verificar os caminhos ortogonais
        int aux [e -> info -> linhas][e -> info -> colunas], nLetras, l, c;

        // No tabuleiro auxiliar, '0' representa as casas vazias e '1' representa as letras (as casas restantes)
        for (int i = nLetras = 0; i < e -> info -> linhas; i++)
            for (int j = 0; j < e -> info -> colunas; j++)
                if (e -> info -> Tabuleiro [i][j] == '#') aux [i][j] = 0;
                else {
                    l = i;
                    c = j;
                    aux [i][j] = 1;
                    nLetras++;
                }

        // Verifica se o tabuleiro possui pelo menos uma letra
        if (nLetras == 0) {
            fprintf (stderr, "\nInfração: O tabuleiro não possui nenhuma letra.\n\n");
            return true;
        }

        // Verifica se existe um caminho ortogonal entre todas as letras
        if (nLetras != contaLetrasLigadas (e -> info -> linhas, e -> info -> colunas, aux, l, c)) {
            validade = 0;
            fprintf (stderr, "Infração: Não existe um caminho ortogonal entre todas as letras.\n");
        }



        // Avisa se o tabuleiro é válido
        if (validade) printf ("Não há nenhuma infração.\n");

        putchar ('\n');

        return true;
    }

    return false;
}



// Ajuda o jogador realizando jogadas 'obrigatórias' na posição
bool ajuda (char cmd, char *arg, ESTADO *e) {

    if (cmd == 'a') {

        // Verifica se não foi recebido um argumento
        if (arg != NULL) {
            fprintf (stderr, "\nErro: O comando a não precisa de um argumento.\n\n");
            return true;
        }

        // Realiza as alterações necessárias
        if (ajudaAux (e) == 0) {
            fprintf (stderr, "\nNão há nada a alterar.\n\n");
            return true;
        }

        // Atualiza o histórico de tabuleiros
        pushStack (e -> info -> hTabuleiros, e -> info -> Tabuleiro, e -> info -> linhas);

        // Imprime o tabuleiro resultante
        visualizarTabuleiro (e -> info);

        return true;
    }

    return false;
}



// Ajuda o jogador realizando jogadas 'obrigatórias' repetidamente até não haver nada a alterar
bool ajudaRep (char cmd, char *arg, ESTADO *e) {

    if (cmd == 'A') {

        // Verifica se não foi recebido um argumento
        if (arg != NULL) {
            fprintf (stderr, "\nErro: O comando A não precisa de um argumento.\n\n");
            return true;
        }

        // Realiza as alterações necessárias
        if (ajudaAux (e) == 0) {
            fprintf (stderr, "\nNão há nada a alterar.\n\n");
            return true;
        }

        // Repete o processo
        while (ajudaAux (e));

        // Atualiza o histórico de tabuleiros
        pushStack (e -> info -> hTabuleiros, e -> info -> Tabuleiro, e -> info -> linhas);

        // Imprime o tabuleiro resultante
        visualizarTabuleiro (e -> info);

        return true;
    }

    return false;
}