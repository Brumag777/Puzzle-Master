#include "Puzzle.h"

// Guarda a informação do jogo num ficheiro
void guardaInfo (FILE *Jogo, Info I) {
    // Guarda o número do tabuleiro e de jogadas
    fprintf (Jogo, "%d %d\n", I -> nTabuleiro, I -> nJogadas);
    
    // Guarda o número de linhas e de colunas do tabuleiro
    fprintf (Jogo, "%d %d\n", I -> dL, I -> dC);

    // Guarda o tabuleiro num ficheiro
    for (int i = 0; i < I -> dL; i++) {
        fprintf (Jogo, "%s", I -> Tabuleiro [i]);
        fprintf (Jogo, "\n");
    }

    // Guarda o histórico de jogadas no ficheiro
    guardaJogadas (Jogo, I);
}



// Guarda o histórico de jogadas no ficheiro
void guardaJogadas (FILE *Jogo, Info I) {

    // Armazena a lista original
    LJogadas J = I -> HJogadas;

    // Percorre a lista
    while (J != NULL) {

        // Guarda o número de alterações de cada jogada
        fprintf (Jogo, "%d ", J -> nAlts);

        // Percorre o array de alterações
        for (int j = 0; j < J -> nAlts; j++)
            fprintf (Jogo, "%c%d%c ", J -> Jogadas [j] -> C, J -> Jogadas [j] -> L, J -> Jogadas [j] -> cAnterior);

        // Passa para a linha seguinte
        fprintf (Jogo, "\n");

        // Avança na lista
        J = J -> JAnt;
    }
}



// Lê a informação de um ficheiro
int leFicheiro (FILE *Jogo, Info I) {

    // Liberta a memória alocada para o tabuleiro anterior
    libertaTabuleiro (I);

    // Lê o número do tabuleiro e de jogadas
    if (fscanf (Jogo, "%d %d", &I -> nTabuleiro, &I -> nJogadas) != 2) return 3;

    // Lê o número de linhas e de colunas
    if (fscanf (Jogo, "%d %d", &I -> dL, &I -> dC) != 2) return 3;

    // Aloca memória para o tabuleiro novo
    inicializaTabuleiro (I);

    // Lê o tabuleiro
    for (int i = 0; i < I -> dL; i++) if (fscanf (Jogo, "%s", I -> Tabuleiro [i]) != 1) return 3;

    // Verifica se o tabuleiro é válido
    if (!tabuleiroValido (I)) {
        libertaTabuleiro (I);
        return 4;
    }

    // Lê as jogadas
    for (int i = 0; i < I -> nTabuleiro - 1; i++) {
        if (leLinhaJogadas (Jogo, I)) return 3;

        I -> nTabuleiro--;
    }

    // Verifica se as jogadas são válidas
    if (!jogadasValidas (I)) {
        libertaTabuleiro (I);
        libertaLJogadas (&I -> HJogadas);
        return 5;
    }

    // Inverte o histórico de jogadas
    I -> HJogadas = inverteHistorico (I -> HJogadas);

    // Fecha o ficheiro
    fclose (Jogo);

    return 0;
}



// Lê a informação de uma linha de jogadas
int leLinhaJogadas (FILE *Jogo, Info I) {

    // Lê a quantidade de alterações
    int nA;
    if (fscanf (Jogo, "%d", &nA) != 1) return 3;

    // Aloca memória para as alterações
    Jogada *Jogs = malloc (nA * (sizeof (JOGADA)));

    // Lê as jogadas
    for (int k = 0; k < nA; k++) {
        
        // Linha da alteração
        int L;

        // Coluna da alteração
        char C; 
        
        // Caractere anterior à alteração
        char cAnt;
        
        // Lê a linha, a coluna e o caractere anterior
        if (fscanf (Jogo, " %c%d%c", &C, &L, &cAnt) != 3) return 3;

        // Forma a jogada
        formaJogada (&Jogs [k], L, C, cAnt);
    }

    // Adiciona a jogada à lista
    addJogada (I, Jogs, nA);

    return 0;
}