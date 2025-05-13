#include "../Puzzle.h"

// Inicializa a informação sobre o jogo
Info inicializaJogo () {
    Info I = malloc (sizeof (INFO));
    if (I == NULL) return NULL;
    I -> aCorrer = true;
    I -> nTabuleiro = 0;
    I -> pont = -1;
    I -> dL = I -> dC = 0;
    I -> Tabuleiro = NULL;
    I -> HJogadas = NULL;
    I -> eJogo = true;
    I -> nJogo = 0;
    return I;
}



// Aloca memória para o tabuleiro do jogo
int inicializaTabuleiro (Info I) {
    if (I -> nTabuleiro) {
        I -> Tabuleiro = malloc (I -> dL * sizeof (char *));
        if (I -> Tabuleiro == NULL) return 1;

        for (int i = 0; i < I -> dL; i++) {
            I -> Tabuleiro [i] = malloc ((I -> dC + 2) * sizeof (char));
            if (I -> Tabuleiro [i] == NULL) return 1;
        }

        return 0;
    }

    return 1;
}



// Liberta a memória alocada para a informação do jogo
void libertaInfo (Info I) {
    if (I != NULL) {
        libertaTabuleiro (I);

        libertaLJogadas (I);

        free (I);
    }
}



// Liberta a memória alocada para o tabuleiro do jogo
void libertaTabuleiro (Info I) {
    if (I -> Tabuleiro != NULL) {
        for (int i = 0; i < I -> dL; i++)
            if (I -> Tabuleiro [i] != NULL) free (I -> Tabuleiro [i]);

        free (I -> Tabuleiro);
    }

    I -> Tabuleiro = NULL;
}



// Liberta a lista de jogadas do jogo
void libertaLJogadas (Info I) {
    LJogadas JAux = I -> HJogadas;

    while (JAux != NULL) {
        LJogadas aRemover = JAux;
        JAux = JAux -> JAnt;
        libertaJogadas (aRemover -> Jogadas, aRemover -> nAlts);
        free (aRemover);
    }

    I -> HJogadas = NULL;
}



// Liberta a memória alocada para um array de jogadas
void libertaJogadas (Jogada *J, int nAlts) {
    if (J != NULL) {
        for (int i = 0; i < nAlts; i++) 
            if (J [i] != NULL) free (J [i]);

        free (J);
    }
}