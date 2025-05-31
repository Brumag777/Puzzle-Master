#include "../Puzzle.h"

// Inicializa a informação do jogo
Info inicializaInfo () {
    Info I = malloc (sizeof (INFO));
    I -> aCorrer = true;
    I -> nTabuleiro = I -> nJogo = 0;
    I -> pont = 0;
    I -> dL = I -> dC = 0;
    I -> Tabuleiro = NULL;
    I -> HJogadas = NULL;
    return I;
}



// Liberta a memória alocada para a informação do jogo
void libertaInfo (Info I) {
    if (I) {
        libertaTabuleiro (I);
        libertaLJogadas (I);
        free (I);
        I = NULL;
    }
}



// Liberta a memória alocada para o tabuleiro do jogo
void libertaTabuleiro (Info I) {
    if (I -> Tabuleiro) {
        for (int i = 0; i < I -> dL; i++)
            if (I -> Tabuleiro [i]) free (I -> Tabuleiro [i]);
        free (I -> Tabuleiro);
        I -> Tabuleiro = NULL;
    }
}



// Liberta a memória alocada para a lista de jogadas do jogo
void libertaLJogadas (Info I) {
    if (I -> HJogadas) {
        LJogadas L = I -> HJogadas;
        while (L) {
            LJogadas temp = L;
            L = L -> JAnt;
            libertaJogada (temp -> Jogada, temp -> nAlts);
            free (temp);
        }
        I -> HJogadas = NULL;
    }
}



// Liberta a memória alocada para uma jogada
void libertaJogada (Alt *Jogada, int nAlts) {
    if (Jogada) {
        for (int i = 0; i < nAlts; i++)
            if (Jogada [i]) free (Jogada [i]);
        free (Jogada);
    }
}



// Aloca memória para o tabuleiro
void inicializaTabuleiro (Info I) {
    if (I -> nTabuleiro) {
        I -> Tabuleiro = malloc (I -> dL * sizeof (char *));
        for (int i = 0; i < I -> dL; i++)
            I -> Tabuleiro [i] = malloc ((2 + I -> dC) * sizeof (char));
    }
}