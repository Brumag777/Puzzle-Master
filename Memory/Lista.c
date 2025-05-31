#include "../Puzzle.h"

// Adiciona uma jogada ao histórico
void addJogada (Info I, Alt *JogadasNovas, int nAlteracoes) {
    LJogadas novaCelula = malloc (sizeof (LJOGADAS));

    novaCelula -> Jogada = JogadasNovas;
    novaCelula -> JAnt = I -> HJogadas;
    I -> HJogadas = novaCelula;

    I -> HJogadas -> nAlts = nAlteracoes;
    I -> nTabuleiro++;
}



// Remove uma jogada do histórico
void remJogada (Info I) {
    LJogadas aRemover = I -> HJogadas;
    I -> HJogadas = I -> HJogadas -> JAnt;

    libertaJogada (aRemover -> Jogada, aRemover -> nAlts);
    
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