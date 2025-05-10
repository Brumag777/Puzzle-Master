#include "Puzzle.h"

// Imprime os últimos 'nTabs' tabuleiros
int visualizaUltimosTabuleiros (Info I, int nTabs, int flag) {

    if (I -> eJogo && flag) {
        if (nTabs == 1) printf ("\nO último tabuleiro é:\n");
        else printf ("\nOs últimos %d tabuleiros são:\n", nTabs);
    }

    int n;

    if (nTabs == 1) {
        if (I -> eJogo) imprimeTabuleiro (I -> dL, I -> dL, I -> Tabuleiro, I -> nTabuleiro, 0);
        return 1;
    }

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
        n = 1 + visualizaUltimosTabuleiros (I, nTabs - 1, 0);

        // Retorna ao original
        realizaAlteracoesJogada (I -> Tabuleiro, Reserva, Atual -> nAlts);
        I -> nTabuleiro++;
        I -> HJogadas = Atual;

        // Visualiza o tabuleiro atual
        if (I -> eJogo) imprimeTabuleiro (I -> dL, I -> dC, I -> Tabuleiro, I -> nTabuleiro, 0);

        // Liberta a memória alocada para a reserva
        libertaJogadas (Reserva, Atual -> nAlts);
    }

    return n;
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
int tabuleiroValido (int dL, int dC, char **Tabuleiro) {

    // Verifica se o tabuleiro não é nulo
    if (Tabuleiro == NULL) return 0;

    // Percorre o tabuleiro para verificar a sua validade
    for (int i = 0; i < dL; i++) {

        // Verifica se todas as casas do tabuleiro possuem caracteres válidos
        for (int j = 0; j < dC; j++) {
            char c = Tabuleiro [i][j];
            if (!(eMinuscula (c) || eMaiuscula (c) || c == '#')) return 0;
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



// Verifica se as linhas não possuem casas brancas repetidas
int verificaLinhas (Info I, char c, int linha, int coluna, int flag) {

    // Inteiro representante da validade da linha
    int validade = 1;
    
    // Percorre o resto da linha para procurar infrações
    for (int j = coluna + 1; j < I -> dC; j++)

        if (I -> Tabuleiro [linha][j] == c) {
            if (I -> eJogo && flag) printf ("Infração: Letra '%c' repetida na linha %d (colunas '%c' e '%c').\n", c, linha + 1, coluna + 'a', j + 'a');
            validade = 0;
        }

    return validade;
}



// Verifica se as colunas não possuem casas brancas repetidas
int verificaColunas (Info I, char c, int linha, int coluna, int flag) {

    // Inteiro representante da validade da coluna
    int validade = 1;
    
    // Percorre o resto da coluna para procurar infrações
    for (int i = linha + 1; i < I -> dL; i++)

        if (I -> Tabuleiro [i][coluna] == c) {
            if (I -> eJogo && flag) printf ("Infração: Letra '%c' repetida na coluna '%c' (linhas %d e %d).\n", c, coluna + 'a', linha + 1, i + 1);
            validade = 0;
        }

    return validade;
}



// Verifica se as casas adjacentes às casas vazias não são vazias
int verificaCasaVazia (Info I, int linha, int coluna, int flag) {

    // Inteiro representante da validade da casa
    int validade = 1;

    // Verifica a casa à direita
    if (coordenadaValida (linha + 1, coluna + 'a' + 1, I -> dL, I -> dC))
        if (I -> Tabuleiro [linha][coluna + 1] == '#') {
            if (I -> eJogo && flag) printf ("Infração: As casas vazias %c%d e %c%d estão juntas.\n", coluna + 'a', linha + 1, coluna + 'a' + 1, linha + 1);
            validade = 0;
        }

    // Verifica a casa abaixo
    if (coordenadaValida (linha + 2, coluna + 'a', I -> dL, I -> dC))
        if (I -> Tabuleiro [linha + 1][coluna] == '#') {
            if (I -> eJogo && flag) printf ("Infração: As casas vazias %c%d e %c%d estão juntas.\n", coluna + 'a', linha + 1, coluna + 'a', linha + 2);
            validade = 0;
        }

    return validade;
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

    if (I -> eJogo) putchar ('\n');

    return 0;
}



// Cria e adiciona uma jogada ao histórico comparando dois tabuleiros
void adicionaJogada (Info I, int dL, int dC, char TabuleiroAnterior [dL][dC + 2], int nAlts) {

    // Aloca memória para o novo array de alterações
    Jogada *JNova = malloc (nAlts * (sizeof (JOGADA)));

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



// Risca as casas que deviam ser vazias
int riscaCasasAux (Info I, int linha, int coluna) {

    // Indicador de alterações
    int flag = 0;

    // Percorre a linha
    if (percorreLinha (I, I -> Tabuleiro [linha][coluna], linha, coluna)) flag = 1;

    // Percorre a coluna
    if (percorreColuna (I, I -> Tabuleiro [linha][coluna], linha, coluna)) flag = 1;

    return flag;
}



// Percorre o tabuleiro para riscar casas que não podem ser brancas pela existência de casas brancas iguais na mesma linha ou coluna
int riscaCasas (Info I) {

    // Indica se houve alterações
    int flag = 0;

    for (int i = 0; i < I -> dL; i++)
        for (int j = 0; j < I -> dC; j++)
            if (eMaiuscula (I -> Tabuleiro [i][j]))
                if (riscaCasasAux (I, i, j)) flag = 1;

    return flag;
}



// Percorre a linha para riscar casas que deviam ser vazias
int percorreLinha (Info I, char c, int linha, int coluna) {

    // Indicador de alterações
    int flag = 0;

    // Altera o 'c' para minúscula
    c += 'a' - 'A';

    for (int j = 0; j < I -> dC; j++)
        if (I -> Tabuleiro [linha][j] == c && j != coluna) {
            I -> Tabuleiro [linha][j] = '#';
            I -> nJogadas++;
            flag = 1;
        }

    return flag;
}



// Percorre a coluna para riscar casas que deviam ser vazias
int percorreColuna (Info I, char c, int linha, int coluna) {

    // Indicador de alterações
    int flag = 0;

    // Altera o 'c' para minúscula
    c += 'a' - 'A';

    for (int i = 0; i < I -> dL; i++)
        if (I -> Tabuleiro [i][coluna] == c && i != linha) {
            I -> Tabuleiro [i][coluna] = '#';
            I -> nJogadas++;
            flag = 1;
        }

    return flag;
}



// Pinta as casas à volta das casas vazias de branco
int pintaCasasAux (Info I, int linha, int coluna) {

    // Indicador de alterações
    int flag = 0;

    // Verifica a casa acima
    if (coordenadaValida (linha, coluna + 'a', I -> dL, I -> dC))
        if (eMinuscula (I -> Tabuleiro [linha - 1][coluna])) {
            I -> Tabuleiro [linha - 1][coluna] += 'A' - 'a';
            I -> nJogadas++;
            flag = 1;
        }

    // Verifica a casa abaixo
    if (coordenadaValida (linha + 2, coluna + 'a', I -> dL, I -> dC))
        if (eMinuscula (I -> Tabuleiro [linha + 1][coluna])) {
            I -> Tabuleiro [linha + 1][coluna] += 'A' - 'a';
            I -> nJogadas++;
            flag = 1;
        }

    // Verifica a casa à esquerda
    if (coordenadaValida (linha + 1, coluna + 'a' - 1, I -> dL, I -> dC))
        if (eMinuscula (I -> Tabuleiro [linha][coluna - 1])) {
            I -> Tabuleiro [linha][coluna - 1] += 'A' - 'a';
            I -> nJogadas++;
            flag = 1;
        }

    // Verifica a casa à direita
    if (coordenadaValida (linha + 1, coluna + 'a' + 1, I -> dL, I -> dC))
        if (eMinuscula (I -> Tabuleiro [linha][coluna + 1])) {
            I -> Tabuleiro [linha][coluna + 1] += 'A' - 'a';
            I -> nJogadas++;
            flag = 1;
        }

    return flag;
}



// Percorre o tabuleiro para pintar casas à volta das casas vazias de branco
int pintaCasas (Info I) {

    // Indica se houve alterações
    int flag = 0;

    for (int i = 0; i < I -> dL; i++)
        for (int j = 0; j < I -> dC; j++)
            if (I -> Tabuleiro [i][j] == '#') 
                if (pintaCasasAux (I, i, j)) flag = 1;

    return flag;
}



// Testa as possibilidades de uma casa minúscula
int testaPossibilidadesCasaAux (Info I, int linha, int coluna) {

    // Risca a casa de modo a realizar o teste
    char C = I -> Tabuleiro [linha][coluna];
    I -> Tabuleiro [linha][coluna] = '#';

    // Cria um tabuleiro auxiliar para verificar os caminhos ortogonais
    int aux [I -> dL][I -> dC], nLetras, l, c;

    // No tabuleiro auxiliar, '0' representa as casas vazias e '1' representa as letras (as casas restantes)
    for (int i = nLetras = 0; i < I -> dL; i++)
        for (int j = 0; j < I -> dC; j++)
            if (I -> Tabuleiro [i][j] == '#') aux [i][j] = 0;
            else {
                l = i;
                c = j;
                aux [i][j] = 1;
                nLetras++;
            }

    // Verifica se o tabuleiro possui pelo menos uma letra
    if (nLetras == 0) return 0;

    // Verifica se existe um caminho ortogonal entre todas as letras
    if (nLetras != contaLetrasLigadas (I -> dL, I -> dC, aux, l, c)) {
        I -> Tabuleiro [linha][coluna] = C + 'A' - 'a';
        I -> nJogadas++;
        return 1;
    }
    else I -> Tabuleiro [linha][coluna] = C;

    return 0;
}



// Percorre o tabuleiro para pintar de branco as casas que não podem ser vazias por bloquear letras
int testaPossibilidadesCasa (Info I) {

    // Indica se houve alterações
    int flag = 0;

    for (int i = 0; i < I -> dL; i++)
        for (int j = 0; j < I -> dC; j++)
            if (eMinuscula (I -> Tabuleiro [i][j])) 
                if (testaPossibilidadesCasaAux (I, i, j)) flag = 1;

    return flag;
}



// Procura infrações numa linha do tabuleiro
int procuraInfracoesL (Info I, char c, int linha, int coluna, int TabInfracoes [I -> dL][I -> dC]) {

    // Inteiro representante da validade do tabuleiro
    int validade = 1;
    
    // Percorre o resto da linha para procurar infrações
    for (int j = coluna + 1; j < I -> dC; j++)
        if (I -> Tabuleiro [linha][j] == c) {
            TabInfracoes [linha][coluna] = TabInfracoes [linha][j] = 1;
            if (I -> eJogo) printf ("Infração: Letra '%c' repetida na linha %d (colunas '%c' e '%c').\n", c, linha + 1, coluna + 'a', j + 'a');
            validade = 0;
        }

    return validade;
}



// Procura infrações numa coluna do tabuleiro
int procuraInfracoesC (Info I, char c, int linha, int coluna, int TabInfracoes [I -> dL][I -> dC]) {

    // Inteiro representante da validade do tabuleiro
    int validade = 1;
    
    // Percorre o resto da coluna para procurar infrações
    for (int i = linha + 1; i < I -> dL; i++)
        if (I -> Tabuleiro [i][coluna] == c) {
            TabInfracoes [linha][coluna] = TabInfracoes [i][coluna] = 1;
            if (I -> eJogo) printf ("Infração: Letra '%c' repetida na coluna '%c' (linhas %d e %d).\n", c, coluna + 'a', linha + 1, i + 1);
            validade = 0;
        }

    return validade;
}



// Procura casas vazias adjacentes a outras
int procuraInfracoesV (Info I, int linha, int coluna, int TabInfracoes [I -> dL][I -> dC]) {

    // Inteiro representante da validade do tabuleiro
    int validade = 1;

    // Verifica a casa à direita
    if (coordenadaValida (linha + 1, coluna + 'a' + 1, I -> dL, I -> dC))
        if (I -> Tabuleiro [linha][coluna + 1] == '#') {
            TabInfracoes [linha][coluna] = TabInfracoes [linha][coluna + 1] = 1;
            if (I -> eJogo) printf ("Infração: As casas vazias %c%d e %c%d estão juntas.\n", coluna + 'a', linha + 1, coluna + 'a' + 1, linha + 1);
            validade = 0;
        }

    // Verifica a casa abaixo
    if (coordenadaValida (linha + 2, coluna + 'a', I -> dL, I -> dC))
        if (I -> Tabuleiro [linha + 1][coluna] == '#') {
            TabInfracoes [linha][coluna] = TabInfracoes [linha + 1][coluna] = 1;
            if (I -> eJogo) printf ("Infração: As casas vazias %c%d e %c%d estão juntas.\n", coluna + 'a', linha + 1, coluna + 'a', linha + 2);
            validade = 0;
        }

    return validade;
}