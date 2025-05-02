#include "Puzzle.h"

// Imprime os últimos 'nTabs' tabuleiros
void visualizaUltimosTabuleiros (Info I, int nTabs, int flag) {
    if (flag) {
        if (nTabs == 1) printf ("\nO último tabuleiro é: \n");
        else printf ("\nOs últimos %d tabuleiros são: \n", nTabs);
    }

    if (nTabs == 1) imprimeTabuleiro (I -> Tabuleiro, I -> dL, I -> dC, I -> nTabuleiro);

    else {
        // Armazena a lista original
        LJogadas Atual = I -> HJogadas;

        // Aloca memória para a reserva
        Jogada *Reserva = malloc (Atual -> nAlts * (sizeof (JOGADA)));

        // Armazena os caracteres originais do tabuleiro
        for (int i = 0; i < Atual -> nAlts; i++) {
            int linha = Atual -> Jogadas [i] -> L;
            char coluna = Atual -> Jogadas [i] -> C;
            formaJogada (&Reserva [i], linha, coluna, I -> Tabuleiro [linha - 1][coluna - 'a']);
        }

        // Aplica as alterações de uma jogada
        realizaAlteracoesJogada (I -> Tabuleiro, Atual -> Jogadas, Atual -> nAlts);

        // Avança na lista de jogadas
        I -> HJogadas = I -> HJogadas -> JAnt;
        I -> nTabuleiro--;

        // Visualiza os tabuleiros anteriores
        visualizaUltimosTabuleiros (I, nTabs - 1, 0);

        // Retorna ao original
        realizaAlteracoesJogada (I -> Tabuleiro, Reserva, Atual -> nAlts);
        I -> nTabuleiro++;
        I -> HJogadas = Atual;

        // Visualiza o tabuleiro atual
        imprimeTabuleiro (I -> Tabuleiro, I -> dL, I -> dC, I -> nTabuleiro);

        // Liberta a memória alocada para a reserva
        libertaJogadas (Reserva, Atual -> nAlts);
    }
}



// Imprime um tabuleiro
void imprimeTabuleiro (char **Tabuleiro, int dL, int dC, int nTabuleiro) {

    // Imprime o número do tabuleiro (ou 'S' caso seja a solução do jogo)
    if (nTabuleiro) {
        if      (nTabuleiro < 9)  printf ("\n%d   ", nTabuleiro);
        else if (nTabuleiro < 99) printf ("\n%d  ", nTabuleiro);
        else                      printf ("\n%d ", nTabuleiro);
    }
    else printf ("\nS   ");

    // Imprime o índice das colunas
    if (dL > 9) putchar (' ');
    for (int j = 0; j < dC; j++) printf ("%c ", 'a' + j);
    printf ("\n    ");

    // Imprime os '-' em baixo dos índices das colunas
    if (dL > 9) putchar (' ');
    for (int j = 0; j < dC; j++) printf ("- ");
    putchar ('\n');

    // Imprime o tabuleiro linha a linha
    for (int i = 0; i < dL; i++) {

        // Imprime o índice das linhas
        if (i < 9 && dL > 9) printf ("%2d | ", i + 1);
        else printf ("%d | ", i + 1);

        // Imprime a linha atual
        for (int j = 0; j < dC; j++)
            printf ("%c ", Tabuleiro [i][j]);
        
        // Avança para a linha seguinte
        putchar ('\n');
    }

    putchar ('\n');
}



// Realiza a um tabuleiro as alterações de uma jogada
void realizaAlteracoesJogada (char **Tabuleiro, Jogada *Jogadas, int nAlts) {
    for (int i = 0; i < nAlts; i++)
        Tabuleiro [Jogadas [i] -> L - 1][Jogadas [i] -> C - 'a'] = Jogadas [i] -> cAnterior;
}



// Forma uma jogada
void formaJogada (Jogada *JNova, int linha, char coluna, char c) {
    (*JNova) = malloc (sizeof (JOGADA));

    (*JNova) -> L = linha;
    (*JNova) -> C = coluna;
    (*JNova) -> cAnterior = c;
}



// Verifica se um caractere é uma letra maiúscula
int eMaiuscula (char c) {
    return c >= 'A' && c <= 'Z';
}



// Verifica se um caractere é uma letra minúscula
int eMinuscula (char c) {
    return c >= 'a' && c <= 'z';
}



// Verifica se uma coordenada é válida (isto é, está dentro do tabuleiro)
int coordenadaValida (int l, char c, int linhas, int colunas) {
    return (!(c < 'a' || c > 'a' + colunas - 1 || l <= 0 || l > linhas));
}



// Verifica se um tabuleiro é válido
int tabuleiroValido (Info I) {

    // Verifica se o tabuleiro não é nulo
    if (I -> Tabuleiro == NULL) return 0;

    // Verifica se todas as casas do tabuleiro possuem caracteres válidos
    for (int i = 0; i < I -> dL; i++) {
        for (int j = 0; j < I -> dC; j++) {
            char c = I -> Tabuleiro [i][j];
            if (!(eMinuscula (c) || eMaiuscula (c) || c == '#')) return 0;
        }

        int t = strlen (I -> Tabuleiro [i]);
        if (t != I -> dC) return 0;
    }

    // O tabuleiro é válido
    return 1;
}



// Verifica se as jogadas são válidas
int jogadasValidas (Info I) {

    // Armazena a lista
    LJogadas LJ = I -> HJogadas;

    // Percore a lista
    while (LJ != NULL) {
        
        // Percorre o array de jogadas
        for (int i = 0; i < LJ -> nAlts; i++) {

            // Armazena a linha da alteração
            int linha = LJ -> Jogadas [i] -> L;

            // Armazena a coluna da alteração
            char coluna = LJ -> Jogadas [i] -> C;

            // Armazena o caractere anterior
            char cAnt = LJ -> Jogadas [i] -> cAnterior;

            // Verifica as restrições
            if (!coordenadaValida (linha, coluna, I -> dL, I -> dC) || !eMinuscula (cAnt)) return 0;
        }

        // Avança na lista
        LJ = LJ -> JAnt;
    }

    // As jogadas são válidas
    return 1;
}