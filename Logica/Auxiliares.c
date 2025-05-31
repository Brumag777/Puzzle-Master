#include "../Puzzle.h"

// Forma o nome de um ficheiro
void formaNomeFicheiro (char *nomeFicheiro, char *arg1, char *arg2) {
    sprintf (nomeFicheiro, "Jogos/J%s/S%s", arg1, arg2);
}



// Verifica se um tabuleiro é válido
int tabuleiroValido (int dL, int dC, char **Tabuleiro) {

    // Verifica se o tabuleiro não é nulo
    if (Tabuleiro == NULL) return 0;

    // Percorre o tabuleiro para verificar a sua validade
    for (int i = 0; i < dL; i++) {

        // Verifica se todas as casas do tabuleiro possuem caracteres válidos
        for (int j = 0; j < dC; j++) {
            char c = Tabuleiro [i][j];
            if (!eMinuscula (c) && !eMaiuscula (c) && c != '#') return 0;
        }

        // Verifica se a linha possui o número correto de colunas
        int t = strlen (Tabuleiro [i]);
        if (t != dC) return 0;
    }

    // O tabuleiro é válido
    return 1;
}



// Verifica se as jogadas são válidas
int jogadasValidas (Info I) {

    // Armazena a lista
    LJogadas LJ = I -> HJogadas;

    // Percore a lista
    while (LJ) {

        // Percorre o array de jogadas
        for (int i = 0; i < LJ -> nAlts; i++) {

            // Armazena a linha da alteração
            int linha = LJ -> Jogada [i] -> L;

            // Armazena a coluna da alteração
            char coluna = LJ -> Jogada [i] -> C;

            // Armazena o caractere anterior
            char cAnt = LJ -> Jogada [i] -> cAnt;

            // Verifica as restrições
            if (!coordenadaValida (linha, coluna, I -> dL, I -> dC) || !eMinuscula (cAnt)) return 0;
        }

        // Avança na lista
        LJ = LJ -> JAnt;
    }

    // As jogadas são válidas
    return 1;
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
    return (c >= 'a' && c <= 'a' + colunas - 1 && l >= 1 && l <= linhas);
}



// Forma uma jogada
void formaJogada (Alt *JNova, int linha, char coluna, char c) {
    (*JNova) = malloc (sizeof (ALT));

    (*JNova) -> L = linha;
    (*JNova) -> C = coluna;
    (*JNova) -> cAnt = c;
}



// Calcula o valor de uma pontuação (1 é alto, 2 é médio, 3 é baixo)
int valorPont (int dL, int dC, int pont) {

    // Calcula a percentagem de pontuação máxima
    float pontMaxima = 3 * dL * dC;
    float pontAtual = pont;
    float percentagemPont = pontAtual / pontMaxima;

    // A pontuação é alta
    if (percentagemPont > 0.667) return 1;

    // A pontuação é média
    if (percentagemPont > 0.334) return 2;

    // A pontuação é baixa
    return 3;
}



// Realiza a um tabuleiro as alterações de uma jogada
void realizaAlteracoesJogada (char **Tabuleiro, Alt *Jogadas, int nAlts) {
    for (int i = 0; i < nAlts; i++)
        Tabuleiro [Jogadas [i] -> L - 1][Jogadas [i] -> C - 'a'] = Jogadas [i] -> cAnt;
}



// Calcula quantas letras estão ligadas à letra da posição dada
int contaLetrasLigadas (int linhas, int colunas, int Tabuleiro [linhas][colunas], int l, int c) {
    
    if (l < 0 || l >= linhas || c < 0 || c >= colunas || Tabuleiro [l][c] == 0) return 0;

    Tabuleiro [l][c] = 0;

    return 1 + contaLetrasLigadas (linhas, colunas, Tabuleiro, l + 1, c) +
               contaLetrasLigadas (linhas, colunas, Tabuleiro, l - 1, c) +
               contaLetrasLigadas (linhas, colunas, Tabuleiro, l, c + 1) +
               contaLetrasLigadas (linhas, colunas, Tabuleiro, l, c - 1);
}



// Percorre a linha para riscar casas que deviam ser vazias
int percorreLinha (Info I, char c, int linha) {

    // Indicador de alterações
    int flag = 0;

    // Altera o 'c' para minúscula
    c += 'a' - 'A';

    for (int j = 0; j < I -> dC; j++)
        if (I -> Tabuleiro [linha][j] == c) {
            I -> Tabuleiro [linha][j] = '#';
            I -> pont--;
            flag = 1;
        }

    return flag;
}



// Percorre a coluna para riscar casas que deviam ser vazias
int percorreColuna (Info I, char c, int coluna) {

    // Indicador de alterações
    int flag = 0;

    // Altera o 'c' para minúscula
    c += 'a' - 'A';

    for (int i = 0; i < I -> dL; i++)
        if (I -> Tabuleiro [i][coluna] == c) {
            I -> Tabuleiro [i][coluna] = '#';
            I -> pont--;
            flag = 1;
        }

    return flag;
}



// Cria e adiciona uma jogada ao histórico comparando dois tabuleiros
void adicionaJogada (Info I, int dL, int dC, char TabuleiroAnterior [dL][dC + 2], int nAlts) {

    // Aloca memória para o novo array de alterações
    Alt *JNova = malloc (nAlts * (sizeof (ALT)));

    // Número de alterações já adicionadas ao array
    int nAA;

    // Percorre os tabuleiros para encontrar as alterações
    for (int i = nAA = 0; i < I -> dL; i++)
        for (int j = 0; j < I -> dC; j++)
            if (TabuleiroAnterior [i][j] != I -> Tabuleiro [i][j])
                formaJogada (&JNova [nAA++], i + 1, j + 'a', TabuleiroAnterior [i][j]);

    // Adiciona ao histórico de jogadas
    addJogada (I, JNova, nAA);
}



// Testa se o jogador já ganhou o jogo
int testeJogo (Info I) {

    // Percorre o tabuleiro para procurar minúsculas
    for (int i = 0; i < I -> dL; i++)
        for (int j = 0; j < I -> dC; j++)
            if (eMinuscula (I -> Tabuleiro [i][j])) return 0;

    // Testa se um tabuleiro terminado é válido
    int validade = 1;

    // Procura infrações em relação à existência de casas riscadas juntas e de casa brancas na mesma linha ou coluna
    if (!verificaInfracoes (I, 1)) validade = 0;

    // Procura infrações em relação à existência de um caminho ortogonal entre todas as letras
    if (!verificaCaminhoOrtogonal (I, 1)) validade = 0;

    // Se não existem infrações, o jogador ganhou
    if (validade) return 1;

    return 0;
}