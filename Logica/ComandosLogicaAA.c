#include "../Puzzle.h"

// Guarda o histórico de jogadas numa save
void guardaJogadas (FILE *Save, Info I) {

    // Armazena a lista original
    LJogadas J = I -> HJogadas;

    // Percorre a lista
    while (J) {

        // Guarda o número de alterações de cada jogada
        fprintf (Save, "%d ", J -> nAlts);

        // Percorre o array de alterações
        for (int j = 0; j < J -> nAlts; j++)
            fprintf (Save, "%c%d%c ", J -> Jogada [j] -> C, J -> Jogada [j] -> L, J -> Jogada [j] -> cAnt);

        // Passa para a linha seguinte
        fprintf (Save, "\n");

        // Avança na lista
        J = J -> JAnt;
    }
}



// Lê uma jogada de uma save
int leJogada (FILE *Save, Info I) {

    // Lê a quantidade de alterações
    int nA;
    if (fscanf (Save, "%d", &nA) != 1) return 3;

    // Aloca memória para as alterações
    Alt *Jogs = malloc (nA * (sizeof (ALT)));

    // Lê as jogadas
    for (int k = 0; k < nA; k++) {
        
        // Linha da alteração
        int L;

        // Coluna da alteração
        char C; 
        
        // Caractere anterior à alteração
        char cAnt;

        // Lê a linha, a coluna e o caractere anterior
        if (fscanf (Save, " %c%d%c", &C, &L, &cAnt) != 3) {
            for (int i = 0; i < k; i++) free (Jogs [i]);
            free (Jogs);
            return 3;
        }

        // Forma a jogada
        formaJogada (&Jogs [k], L, C, cAnt);
    }

    // Adiciona a jogada à lista
    addJogada (I, Jogs, nA);

    return 0;
}



// Procura infrações numa linha do tabuleiro
int procuraInfracoesL (Info I, char c, int linha, int coluna, int TabInfracoes [I -> dL][I -> dC]) {

    // Inteiro representante da validade do tabuleiro
    int validade = 1;

    // Percorre o resto da linha para procurar infrações
    for (int j = coluna + 1; j < I -> dC; j++)
        if (I -> Tabuleiro [linha][j] == c) {
            TabInfracoes [linha][coluna] = TabInfracoes [linha][j] = 1;
            avisaInfracaoLinha (I, c, linha + 1, coluna + 'a', j + 'a', 1);
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
            avisaInfracaoColuna (I, c, coluna + 'a', linha + 1, i + 1, 1);
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
            avisaInfracaoCVazias (I, coluna + 'a', linha + 1, coluna + 'a' + 1, linha + 1, 1);
            validade = 0;
        }

    // Verifica a casa abaixo
    if (coordenadaValida (linha + 2, coluna + 'a', I -> dL, I -> dC))
        if (I -> Tabuleiro [linha + 1][coluna] == '#') {
            TabInfracoes [linha][coluna] = TabInfracoes [linha + 1][coluna] = 1;
            avisaInfracaoCVazias (I, coluna + 'a', linha + 1, coluna + 'a', linha + 2, 1);
            validade = 0;
        }

    return validade;
}



// Verifica se as linhas não possuem casas brancas repetidas
int verificaLinhas (Info I, char c, int linha, int coluna, int flag) {

    // Inteiro representante da validade da linha
    int validade = 1;
    
    // Percorre o resto da linha para procurar infrações
    for (int j = coluna + 1; j < I -> dC; j++)
        if (I -> Tabuleiro [linha][j] == c) {
            avisaInfracaoLinha (I, c, linha + 1, coluna + 'a', j + 'a', flag);
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
            avisaInfracaoColuna (I, c, coluna + 'a', linha + 1, i + 1, flag);
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
            avisaInfracaoCVazias (I, coluna + 'a', linha + 1, coluna + 'a' + 1, linha + 1, flag);
            validade = 0;
        }

    // Verifica a casa abaixo
    if (coordenadaValida (linha + 2, coluna + 'a', I -> dL, I -> dC))
        if (I -> Tabuleiro [linha + 1][coluna] == '#') {
            avisaInfracaoCVazias (I, coluna + 'a', linha + 1, coluna + 'a', linha + 2, flag);
            validade = 0;
        }

    return validade;
}



// Risca as casas que deviam ser vazias
int riscaCasasAux (Info I, int linha, int coluna) {

    // Indicador de alterações
    int flag = 0;

    // Percorre a linha
    if (percorreLinha (I, I -> Tabuleiro [linha][coluna], linha)) flag = 1;

    // Percorre a coluna
    if (percorreColuna (I, I -> Tabuleiro [linha][coluna], coluna)) flag = 1;

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



// Pinta as casas à volta das casas vazias de branco
int pintaCasasAux (Info I, int linha, int coluna) {

    // Indicador de alterações
    int flag = 0;

    // Verifica a casa acima
    if (coordenadaValida (linha, coluna + 'a', I -> dL, I -> dC))
        if (eMinuscula (I -> Tabuleiro [linha - 1][coluna])) {
            I -> Tabuleiro [linha - 1][coluna] += 'A' - 'a';
            I -> pont--;
            flag = 1;
        }

    // Verifica a casa abaixo
    if (coordenadaValida (linha + 2, coluna + 'a', I -> dL, I -> dC))
        if (eMinuscula (I -> Tabuleiro [linha + 1][coluna])) {
            I -> Tabuleiro [linha + 1][coluna] += 'A' - 'a';
            I -> pont--;
            flag = 1;
        }

    // Verifica a casa à esquerda
    if (coordenadaValida (linha + 1, coluna + 'a' - 1, I -> dL, I -> dC))
        if (eMinuscula (I -> Tabuleiro [linha][coluna - 1])) {
            I -> Tabuleiro [linha][coluna - 1] += 'A' - 'a';
            I -> pont--;
            flag = 1;
        }

    // Verifica a casa à direita
    if (coordenadaValida (linha + 1, coluna + 'a' + 1, I -> dL, I -> dC))
        if (eMinuscula (I -> Tabuleiro [linha][coluna + 1])) {
            I -> Tabuleiro [linha][coluna + 1] += 'A' - 'a';
            I -> pont--;
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
    if (nLetras == 0) {
        I -> Tabuleiro [linha][coluna] = C;
        return 0;
    }

    // Verifica se existe um caminho ortogonal entre todas as letras
    if (nLetras != contaLetrasLigadas (I -> dL, I -> dC, aux, l, c)) {
        I -> Tabuleiro [linha][coluna] = C + 'A' - 'a';
        I -> pont--;
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