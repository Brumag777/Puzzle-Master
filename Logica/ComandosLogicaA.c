#include "../Puzzle.h"

// Guarda a informação do jogo numa save
void guardaInfo (FILE *Save, Info I) {
    
    // Guarda o número de linhas e de colunas do tabuleiro
    fprintf (Save, "%d %d\n", I -> dL, I -> dC);

    // Guarda o tabuleiro num ficheiro
    for (int i = 0; i < I -> dL; i++) fprintf (Save, "%s\n", I -> Tabuleiro [i]);

    // Guarda o número do tabuleiro e a pontuação
    fprintf (Save, "%d %d\n", I -> nTabuleiro, I -> pont);

    // Guarda o histórico de jogadas no ficheiro
    guardaJogadas (Save, I);
}



// Lê a informação de uma save
int leSave (FILE *Save, Info I) {

    // Liberta a memória alocada para o tabuleiro anterior
    libertaTabuleiro (I);

    // Limpa o histórico
    while (I -> nTabuleiro > 1) remJogada (I);

    // Lê o número de linhas e de colunas
    if (fscanf (Save, "%d %d", &I -> dL, &I -> dC) != 2) {
        I -> dL = I -> dC = I -> nTabuleiro = 0;
        return 2;
    }

    // Atualiza o número do tabuleiro
    I -> nTabuleiro = 1;

    // Aloca memória para o novo tabuleiro
    inicializaTabuleiro (I);

    // Lê o tabuleiro
    for (int i = 0; i < I -> dL; i++) if (fscanf (Save, "%s", I -> Tabuleiro [i]) != 1) {
        libertaTabuleiro (I);
        I -> dL = I -> dC = I -> nTabuleiro = 0;
        return 2;
    }

    // Verifica se o tabuleiro é válido
    if (!tabuleiroValido (I -> dL, I -> dC, I -> Tabuleiro)) {
        libertaTabuleiro (I);
        I -> dL = I -> dC = I -> nTabuleiro = 0;
        return 3;
    }

    // Lê o número do tabuleiro e a pontuação
    int n = fscanf (Save, "%d %d", &I -> nTabuleiro, &I -> pont);

    // Não leu nenhum valor
    if (n == -1) {
        I -> nTabuleiro = 1;
        I -> pont = 4 * (I -> dL * I -> dC);
    }

    // Leu incorretamente os valores
    else if (n != 2) {
        libertaTabuleiro (I);
        I -> dL = I -> dC = I -> nTabuleiro = 0;
        return 2;
    }

    // Lê as jogadas
    for (int i = 0; i < I -> nTabuleiro - 1; i++) {
        if (leJogada (Save, I)) {
            libertaTabuleiro (I);
            libertaLJogadas (I);
            I -> dL = I -> dC = I -> nTabuleiro = 0;
            return 2;
        }
        I -> nTabuleiro--;
    }

    // Verifica se as jogadas são válidas
    if (!jogadasValidas (I)) {
        libertaTabuleiro (I);
        libertaLJogadas (I);
        I -> dL = I -> dC = I -> nTabuleiro = 0;
        return 3;
    }

    // Inverte o histórico de jogadas
    I -> HJogadas = inverteHistorico (I -> HJogadas);

    // Fecha o ficheiro
    fclose (Save);

    return 0;
}



// Procura infrações em relação à existência de casas riscadas juntas e de casa brancas na mesma linha ou coluna
int verificaInfracoes (Info I, int flag) {

    // Inteiro representante da validade do tabuleiro
    int validade = 1;

    // Percorre o tabuleiro para procurar infrações
    for (int i = 0; i < I -> dL; i++)

        // Percorre cada linha do tabuleiro para procurar infrações
        for (int j = 0; j < I -> dC; j++) {
                
            // Verifica se houve infrações relativas a casas brancas
            if (eMaiuscula (I -> Tabuleiro [i][j])) {
                if (!verificaLinhas (I, I -> Tabuleiro [i][j], i, j, flag) ||
                    !verificaColunas (I, I -> Tabuleiro [i][j], i, j, flag)) validade = 0;
            }

            // Verifica se houve infrações relativas a casas vazias
            else if (I -> Tabuleiro [i][j] == '#')
                if (!verificaCasaVazia (I, i, j, flag)) validade = 0;
        }

    return validade;
}



// Procura infrações em relação à existência de um caminho ortogonal entre todas as letras
int verificaCaminhoOrtogonal (Info I, int flag) {

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

    // Verifica se o tabuleiro possui letras
    if (nLetras == 0) return 1;

    // Verifica se o número de letras total é igual ao número de letras ligadas a uma letra do tabuleiro
    if (nLetras == contaLetrasLigadas (I -> dL, I -> dC, aux, l, c)) return 1;

    // Avisa que não existe um caminho ortogonal entre todas as letras
    avisaInfracaoCOrtogonal (I, flag);

    return 0;
}



// Procura infrações no tabuleiro para preencher o tabuleiro de infrações
int preencheTabInfracoes (Info I, int TabInfracoes [I -> dL][I -> dC]) {

    // Inteiro representante da validade do tabuleiro
    int validade = 1;

    // Verifica se existe um caminho ortogonal entre todas as letras
    int validadeCaminho = verificaCaminhoOrtogonal (I, 1);

    // Atualiza a validade
    if (!validadeCaminho) validade = 0;

    // Percorre o tabuleiro para procurar infrações
    for (int i = 0; i < I -> dL; i++)

        // Percorre cada linha do tabuleiro para procurar infrações
        for (int j = 0; j < I -> dC; j++) {

            // Verifica se houve infrações relativas a casas brancas
            if (eMaiuscula (I -> Tabuleiro [i][j])) {
                if (!procuraInfracoesL (I, I -> Tabuleiro [i][j], i, j, TabInfracoes) ||
                    !procuraInfracoesC (I, I -> Tabuleiro [i][j], i, j, TabInfracoes)) validade = 0;
            }

            // Verifica se houve infrações relativas a casas vazias
            else if (I -> Tabuleiro [i][j] == '#') {
                if (validadeCaminho == 0) TabInfracoes [i][j] = 1;
                if (!procuraInfracoesV (I, i, j, TabInfracoes)) validade = 0;
            }
        }

    return validade;
}



// Realiza alterações necessárias na posição atual
int ajudaUmaVez (Info I, int versaoComando) {

    // Indicador de alterações
    int flag = 0;

    // Percorre o tabuleiro para pintar casas à volta das casas vazias de branco
    if (versaoComando == 1 || versaoComando == 2) if (pintaCasas (I)) flag = 1;

    // Percorre o tabuleiro para riscar casas que não podem ser brancas pela existência de casas brancas iguais na mesma linha ou coluna
    if (versaoComando == 1 || versaoComando == 3) if (riscaCasas (I)) flag = 1;

    // Percorre o tabuleiro para pintar de branco as casas que não podem ser vazias por bloquear letras
    if (versaoComando == 1 || versaoComando == 4) if (testaPossibilidadesCasa (I)) flag = 1;

    return flag;
}



// Resolve o jogo (se possível)
int resolve (Info I, int dL, int dC, char TabuleiroOriginal [dL][dC + 2]) {

    // Realiza todas as jogadas necessárias na posição
    while (ajudaUmaVez (I, 1));

    // Inteiro representante da validade do tabuleiro
    int validade = 1;

    // Procura infrações em relação à existência de casas riscadas juntas e de casa brancas na mesma linha ou coluna
    if (!verificaInfracoes (I, 0)) validade = 0;

    // Procura infrações em relação à existência de um caminho ortogonal entre todas as letras
    if (!verificaCaminhoOrtogonal (I, 0)) validade = 0;

    // Verifica se o tabuleiro é válido
    if (validade == 0) {
        for (int i = 0; i < I -> dL; i++)
            strcpy (I -> Tabuleiro [i], TabuleiroOriginal [i]);
        return 0;
    }

    // Percorre o tabuleiro para mudar as letras minúsculas restantes
    for (int i = 0; i < I -> dL; i++)
        for (int j = 0; j < I -> dC; j++) {
            if (eMinuscula (I -> Tabuleiro [i][j])) {
                
                // Decrementa a pontuação
                I -> pont--;

                // Armazena o caractere original
                char c = I -> Tabuleiro [i][j];

                // Testa o caso da casa ser pintada de branco
                I -> Tabuleiro [i][j] += 'A' - 'a';
                if (resolve (I, dL, dC, TabuleiroOriginal)) return 1;

                // Testa o caso da casa ser riscada
                I -> Tabuleiro [i][j] = '#';
                if (resolve (I, dL, dC, TabuleiroOriginal)) return 1;

                // Retorna ao caractere original
                I -> Tabuleiro [i][j] = c;

                // É impossível resolver o jogo
                return 0;
            }
    }

    // Não há minúsculas e o tabuleiro é válido, logo o jogo está resolvido
    return 1;
}