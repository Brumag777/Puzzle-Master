#include "Puzzle.h"

// Adiciona uma jogada ao histórico
int addJogada (Info I, Jogada *JogadasNovas, int nAlteracoes) {
    LJogadas novaCelula = malloc (sizeof (LJOGADAS));
    if (novaCelula == NULL) return 1;

    novaCelula -> Jogadas = JogadasNovas;
    novaCelula -> JAnt = I -> HJogadas;
    I -> HJogadas = novaCelula;

    I -> HJogadas -> nAlts = nAlteracoes;
    I -> nTabuleiro++;

    return 0;
}



// Remove uma jogada do histórico
void remJogada (Info I) {
    LJogadas aRemover = I -> HJogadas;
    I -> HJogadas = I -> HJogadas -> JAnt;

    libertaJogadas (aRemover -> Jogadas, I -> HJogadas -> nAlts);
    free (aRemover);

    I -> nTabuleiro--;
}



// Inverte o histórico de jogadas
LJogadas inverteHistorico (LJogadas L) {
    LJogadas anterior = NULL, proximo;

    while (L != NULL) {
        proximo = L -> JAnt;
        L -> JAnt = anterior;
        anterior = L;
        L = proximo;
    }

    return anterior;
}