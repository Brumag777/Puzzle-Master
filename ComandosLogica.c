#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "puzzle.h"

// Função que realiza a lógica do comando 'g' (gravar)
int logicaGravar (char *nomeFicheiro, ESTADO *e) {

    // Verifica se foi recebido um argumento
    if (nomeFicheiro == NULL) return 1;

    // Verifica se existe um tabuleiro para guardar
    if (e -> info -> hTabuleiros -> sp == 0) return 2;

    // Abre o ficheiro a preencher
    FILE *Jogo = fopen (nomeFicheiro, "w");

    // Verifica se o ficheiro foi aberto corretamente
    if (Jogo == NULL) return 3;

    // Grava no ficheiro tabuleiro a tabuleiro
    for (int i = 0; i < e -> info -> hTabuleiros -> sp; i++) {

        // Preenche o ficheiro com a quantidade de linhas e de colunas do tabuleiro
        fprintf (Jogo, "%d %d\n", e -> info -> hTabuleiros -> linhas [i], e -> info -> hTabuleiros -> colunas [i]);

        // Preenche o ficheiro com o tabuleiro, linha a linha
        for (int j = 0; j < e -> info -> hTabuleiros -> linhas [i]; j++)
            fprintf (Jogo, "%s", e -> info -> hTabuleiros -> TAnteriores [i][j]);
    }

    // Fecha o ficheiro
    fclose (Jogo);

    // Liberta a memória dos tabuleiros anteriores
    libertaTabuleiro (e -> info, 1);

    // Aloca memória para os tabuleiros novos
    iniciarTabuleiro (e, 1);

    return 0;
}



// Função que realiza a lógica do comando 'l' (ler)
int logicaLer (char *nomeFicheiro, ESTADO *e) {

    // Verifica se foi recebido um argumento
    if (nomeFicheiro == NULL) return 1;

    // Abre o ficheiro a ler
    FILE *Jogo = fopen (nomeFicheiro, "r");

    // Verifica se o ficheiro foi lido com sucesso
    if (Jogo == NULL) return 2;

    int l, c, nTabuleiros = e -> info -> hTabuleiros -> sp, nTabuleirosLidos = 0;

    while (fscanf (Jogo, "%d %d", &l, &c) == 2) {

        // Liberta a memória alocada para o tabuleiro anterior
        libertaTabuleiro (e -> info, 0);

        // Aloca memória para o tabuleiro novo
        iniciarTabuleiro (e, 0);

        // Armazena o número de linhas e de colunas
        e -> info -> linhas = l;
        e -> info -> colunas = c;

        // Ignora o '\n' da primeira linha
        fgetc (Jogo);

        // Aloca memória para o tabuleiro novo
        e -> info -> Tabuleiro = malloc (e -> info -> linhas * sizeof (char *));

        // Aloca memória para cada linha do tabuleiro novo e preenche o mesmo com a informação do ficheiro
        for (int i = 0; i < e -> info -> linhas; i++) {
            e -> info -> Tabuleiro [i] = malloc ((e -> info -> colunas + 2) * sizeof (char));
            if (fgets (e -> info -> Tabuleiro [i], e -> info -> colunas + 2, Jogo) == NULL) return 3;
        }

        // Verifica se o tabuleiro é válido
        if (!tabuleiroValido (e -> info)) {
            while (nTabuleirosLidos > 0) {
                popStack (e -> info -> hTabuleiros);
                nTabuleirosLidos--;
            }
            return 4;
        }

        nTabuleirosLidos++;

        // Adiciona o tabuleiro novo ao histórico de tabuleiros
        pushStack (e -> info -> hTabuleiros, e -> info -> Tabuleiro, e -> info -> linhas, e -> info -> colunas);
    }

    // Fecha o ficheiro
    fclose (Jogo);

    // Verifica se foi lido algum tabuleiro
    if (e -> info -> hTabuleiros -> sp == nTabuleiros) return 3;
    
    return 0;
}



// Função que realiza a lógica do comando 's' (sair)
int logicaSair (char *arg, ESTADO *e) {

    // Verifica se não foi recebido um argumento
    if (arg != NULL) return 1;

    // Define o looping como falso de modo a terminar o ciclo na main
    e -> looping = false;

    return 0;
}



// Função que realiza a lógica do comando 'b' (pintarCasa)
int logicaPintarCasa (char *coordenada, ESTADO *e) {

    // Verifica se foi recebido um argumento
    if (coordenada == NULL) return 1;

    // Define a letra e o número correspondentes à coordenada
    char c = coordenada [0];
    int l = atoi (coordenada + 1);

    // Verifica se a coordenada recebida é válida (isto é, está dentro do tabuleiro)
    if (!coordenadaValida (l, c, e -> info -> linhas, e -> info -> colunas)) return 2;

    // Verifica se a coordenada recebida não está riscada
    if (e -> info -> Tabuleiro [l - 1][c - 'a'] == '#') return 3;
    
    // Verifica se a coordenada recebida não está pintada de branco
    if (eMaiuscula (e -> info -> Tabuleiro [l - 1][c - 'a'])) return 4;

    // Pinta a casa de branco
    e -> info -> Tabuleiro [l - 1][c - 'a'] += 'A' - 'a';

    return 0;
}



// Função que realiza a lógica do comando 'r' (riscarCasa)
int logicaRiscarCasa (char *coordenada, ESTADO *e) {

    // Verifica se foi recebido um argumento
    if (coordenada == NULL) return 1;

    // Define a letra e o número correspondentes à coordenada
    char c = coordenada [0];
    int l = atoi (coordenada + 1);

    // Verifica se a coordenada recebida é válida (isto é, está dentro do tabuleiro)
    if (!coordenadaValida (l, c, e -> info -> linhas, e -> info -> colunas)) return 2;

    // Verifica se a coordenada recebida não está riscada
    if (e -> info -> Tabuleiro [l - 1][c - 'a'] == '#') return 3;
    
    // Verifica se a coordenada recebida não está pintada de branco
    if (eMaiuscula (e -> info -> Tabuleiro [l - 1][c - 'a'])) return 4;

    // Muda a casa para vazia
    e -> info -> Tabuleiro [l - 1][c - 'a'] = '#';

    return 0;
}



// Função que realiza a lógica do comando 'd' (desfazerJogada)
int logicaDesfazerJogada (char *nTab, ESTADO *e) {

    // Verifica se o jogador pretende desfazer múltiplas jogadas
    if (nTab != NULL) {

        // Desfaz as últimas jogadas até ao tabuleiro q
        int q = atoi (nTab);

        // Verifica se o argumento é um número natural
        if (q < 1) return 2;

        // Verifica se o argumento não é igual ao tabuleiro atual
        if (q == e -> info -> hTabuleiros -> sp) return 3;

        // Verifica se o tabuleiro desejado existe
        if (q > e -> info -> hTabuleiros -> sp) return 4;

        // Desfaz as últimas jogadas até ao tabuleiro anterior ao desejado
        while (e -> info -> hTabuleiros -> sp > q + 1) popStack (e -> info -> hTabuleiros);
    }

    // Desfaz a última jogada
    return desfazUmaJogada (e);
}



// Função que realiza a lógica do comando 'V' (vizualizarHistorico)
int logicaVizualizarHistorico (char *nTab, ESTADO *e) {

    // Define a quantidade de tabuleiros a imprimir
    int q;

    if (nTab == NULL) q = 1;
    else q = atoi (nTab);

    // Verifica se o argumento é um número natural
    if (q < 1) return -1;

    // Verifica se existem tabuleiros para imprimir
    if (e -> info -> hTabuleiros -> sp == 0) return -2;

    // Verifica se existem tabuleiros suficientes para imprimir
    if (q > e -> info -> hTabuleiros -> sp) return -3;

    return q;
}



// Função que realiza a lógica do comando 'v' (verifica)
int logicaVerifica (char *arg, ESTADO *e) {

    // Verifica se não foi recebido um argumento
    if (arg != NULL) return -1;

    putchar ('\n');

    // Inteiro representante da validade do tabuleiro
    int validade = 1;

    // Procura infrações em relação à existência de casas riscadas juntas e de casa brancas na mesma linha ou coluna
    if (!verificaInfracoes (e -> info, 1)) validade = 0;

    // Procura infrações em relação à existência de um caminho ortogonal entre todas as letras
    if (!verificaCaminhoOrtogonal (e -> info, 1)) validade = 0;

    return validade;
}



// Função que realiza a lógica do comando 'a' (ajuda)
int logicaAjuda (char *arg, ESTADO *e) {

    // Indica se o argumento é NULL
    int eNulo = 1;

    // Verifica se não foi recebido um argumento
    if (arg == NULL) {
        if (ajudaUmaVez (e -> info) == 0) return 2;
        else eNulo = 0;
    }

    if (eNulo) {

        // Verifica se o argumento é 'b'
        if (strcmp (arg, "b") == 0) {
            if (pintaCasas (e -> info) == 0) return 2;
        }

        // Verifica se o argumento é 'r'
        else if (strcmp (arg, "r") == 0) {
            if (riscaCasas (e -> info) == 0) return 2;
        }

        // Verifica se o argumento é 'o'
        else if (strcmp (arg, "o") == 0) {
            if (testaPossibilidadesCasa (e -> info) == 0) return 2;
        }

        // O argumento é inválido
        else return 1;
    }

    return 0;
}



// Função que realiza a lógica do comando 'A' (ajudaRep)
int logicaAjudaRep (char *arg, ESTADO *e) {

    // Verifica se não foi recebido um argumento
    if (arg != NULL) return 1;

    // Realiza as alterações necessárias
    if (ajudaUmaVez (e -> info) == 0) return 2;

    // Repete o processo até não haver nada a alterar
    while (ajudaUmaVez (e -> info));

    return 0;
}



// Função que realiza a lógica do comando 'R'
int logicaResolveJogo (char *arg, ESTADO *e) {

    // Verifica se não foi recebido um argumento
    if (arg != NULL) return 1;

    // Verifica se existe um jogo para resolver
    if (e -> info -> hTabuleiros -> sp == 0) return 2;

    // Resolve o jogo (se possível)
    if (resolve (e -> info)) return 0;

    // Não é possível resolver o jogo
    return 3;
}



// Função que realiza a lógia do comando 'h' (listarComandos)
int logicaListarComandos (char *arg, ESTADO *e) {

    // Para evitar warnings
    (void) e;

    // Verifica se não foi recebido um argumento
    if (arg != NULL) return 1;

    return 0;
}