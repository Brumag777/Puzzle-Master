#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "puzzle.h"

// Função que realiza a lógica do comando 'g' (gravar)
int logicaGravar (char *nomeFicheiro, ESTADO *e) {

    // Verifica se foi recebido um argumento
    if (nomeFicheiro == NULL) return 1;

    // Abre o ficheiro a preencher
    FILE *Jogo = fopen (nomeFicheiro, "w");

    // Verifica se o ficheiro foi aberto corretamente
    if (Jogo == NULL) return 2;

    // Preenche o ficheiro com a quantidade de linhas e de colunas do tabuleiro
    fprintf (Jogo, "%d %d\n", e -> info -> linhas, e -> info -> colunas);

    // Preenche o ficheiro com o tabuleiro, linha a linha
    for (int i = 0; i < e -> info -> linhas; i++)
        fprintf (Jogo, "%s", e -> info -> Tabuleiro [i]);

    // Fecha o ficheiro
    fclose (Jogo);

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

    // Liberta a memória alocada para o tabuleiro anterior
    libertaTabuleiro (e -> info, 0);

    // Aloca memória para o tabuleiro novo
    iniciarTabuleiro (e, 0);

    // Lê as linhas e as colunas do ficheiro
    if (fscanf (Jogo, "%d %d", &e -> info -> linhas, &e -> info -> colunas) != 2) {
        fclose (Jogo);
        return 3;
    }

    // Ignora o '\n' da primeira linha
    fgetc (Jogo);

    // Aloca memória para o tabuleiro novo
    e -> info -> Tabuleiro = malloc (e -> info -> linhas * sizeof (char *));

    // Aloca memória para cada linha do tabuleiro novo e preenche o mesmo com a informação do ficheiro
    for (int i = 0; i < e -> info -> linhas; i++) {
        e -> info -> Tabuleiro [i] = malloc ((e -> info -> colunas + 2) * sizeof (char));
        if (fgets (e -> info -> Tabuleiro [i], e -> info -> colunas + 2, Jogo) == NULL) return 3;
    }

    // Fecha o ficheiro
    fclose (Jogo); 

    // Verifica se o tabuleiro é válido
    if (!tabuleiroValido (e -> info)) return 4;

    // Adiciona o tabuleiro novo ao histórico de tabuleiros
    pushStack (e -> info -> hTabuleiros, e -> info -> Tabuleiro, e -> info -> linhas, e -> info -> colunas);

    // Imprime o tabuleiro atualizado
    visualizaUltimosTabuleiros (e -> info -> hTabuleiros, 1, 0);
    
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

    // Adiciona o tabuleiro resultante ao histórico de tabuleiros
    pushStack (e -> info -> hTabuleiros, e -> info -> Tabuleiro, e -> info -> linhas, e -> info -> colunas);

    // Imprime o tabuleiro atualizado
    visualizaUltimosTabuleiros (e -> info -> hTabuleiros, 1, 0);

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

    // Adiciona o tabuleiro resultante ao histórico de tabuleiros
    pushStack (e -> info -> hTabuleiros, e -> info -> Tabuleiro, e -> info -> linhas, e -> info -> colunas);

    // Imprime o tabuleiro resultante
    visualizaUltimosTabuleiros (e -> info -> hTabuleiros, 1, 0);

    return 0;
}



// Função que realiza a lógia do comando 'h' (listarComandos)
int logicaListarComando (char *arg, ESTADO *e) {

    // Verifica se não foi recebido um argumento
    if (arg != NULL) return 1;

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
            "d: Desfaz a última jogada.\n"
            "d <natural>: Desfaz as últimas jogadas até ao tabuleiro selecinado.\n"
            "s: Termina o jogo.\n"
            "h: Lista todos os comandos do jogo.\n");
    printf ("As coordenadas devem estar compreendidas entre a1 e %c%d \n", e -> info -> colunas + 'a' - 1, e -> info -> linhas);
    printf ("Os números naturais devem ser iguais ou inferiores a %d\n\n", e -> info -> hTabuleiros -> sp);

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

    // Verifica se foi recebido um argumento
    if (nTab == NULL) return 1;

    // Define a quantidade de tabuleiros a imprimir
    int q = atoi (nTab);

    // Verifica se o argumento é um número natural
    if (q < 1) return 2;

    // Verifica se existem tabuleiros suficientes para imprimir
    if (q > e -> info -> hTabuleiros -> sp) return 3;

    // Imprime os últimos q tabuleiros armazenados no histórico
    visualizaUltimosTabuleiros (e -> info -> hTabuleiros, q, 1);

    return 0;
}



// Função que realiza a lógica do comando 'v' (verifica)
int logicaVerifica (char *arg, ESTADO *e) {

    // Verifica se não foi recebido um argumento
    if (arg != NULL) return 1;

    putchar ('\n');

    // Inteiro representante da validade do tabuleiro
    int validade = 1;

    // Procura infrações em relação à existência de casas riscadas juntas e de casa brancas na mesma linha ou coluna
    if (!verificaInfracoes (e -> info, 1)) validade = 0;

    // Procura infrações em relação à existência de um caminho ortogonal entre todas as letras
    if (!verificaCaminhoOrtogonal (e -> info)) validade = 0;

    // Avisa se o tabuleiro é válido
    if (validade) printf ("Não há nenhuma infração.\n");

    putchar ('\n');

    return 0;
}



// Função que realiza a lógica do comando 'a' (ajuda)
int logicaAjuda (char *arg, ESTADO *e) {

    // Verifica se não foi recebido um argumento
    if (arg != NULL) return 1;
    
    // Realiza as alterações necessárias
    if (ajudaUmaVez (e -> info) == 0) return 2;

    // Atualiza o histórico de tabuleiros
    pushStack (e -> info -> hTabuleiros, e -> info -> Tabuleiro, e -> info -> linhas, e -> info -> colunas);

    // Imprime o tabuleiro resultante
    visualizaUltimosTabuleiros (e -> info -> hTabuleiros, 1, 0);

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

    // Atualiza o histórico de tabuleiros
    pushStack (e -> info -> hTabuleiros, e -> info -> Tabuleiro, e -> info -> linhas, e -> info -> colunas);

    // Imprime o tabuleiro resultante
    visualizaUltimosTabuleiros (e -> info -> hTabuleiros, 1, 0);

    return 0;
}



// Função que realiza a lógico do comando 'R'
int logicaResolveJogo (char *arg, ESTADO *e) {

    // Verifica se não foi recebido um argumento
    if (arg != NULL) return 1;

    // Resolve o jogo (se possível)
    if (resolve (e -> info)) {
        pushStack (e -> info -> hTabuleiros, e -> info -> Tabuleiro, e -> info -> linhas, e -> info -> colunas);
        visualizaUltimosTabuleiros (e -> info -> hTabuleiros, 1, 0);
        return 0;
    }

    // Não é possível resolver o jogo
    return 2;
}