#include "../Puzzle.h"

// Cria um jogo
int criaJogo () {

    // Inicializa um novo Info
    Info I = inicializaInfo ();

    // Inicializa o número do tabuleiro
    I -> nTabuleiro = 1;

    // Pede ao jogador a informação do jogo novo
    int n = infoJogoNovo (I);

    // Ocorreu um erro
    if (n) {
        libertaInfo (I);
        return n;
    }

    // Atualiza a pontuação
    I -> pont = 4 * I -> dL * I -> dC;

    // Cria o nome do ficheiro
    char nomeFicheiro [LINE_SIZE];

    // Procura o índice mais baixo que ainda não possui jogo
    I -> nJogo = procuraJogoMaisBaixo (nomeFicheiro);

    // Ocorreu um erro
    if (I -> nJogo < 0) {
        libertaInfo (I);
        return -4;
    }

    // Cria o nome da nova diretoria
    char nomeDiretoria [LINE_SIZE];

    // Define o nome da nova diretoria
    sprintf (nomeDiretoria, "Jogos/J%d", I -> nJogo);

    // Cria a nova diretoria para o jogo novo
    if (mkdir (nomeDiretoria, 0777)) {
        libertaInfo (I);
        return -5;
    }

    // Cria o ficheiro novo
    FILE *Jogo = fopen (nomeFicheiro, "w");

    // Verifica se foi possível abrir o ficheiro
    if (Jogo == NULL) {
        libertaInfo (I);
        return -5;
    }

    // Grava o ficheiro novo
    guardaInfo (Jogo, I);

    // Fecha o ficheiro
    fclose (Jogo);

    // Guarda o número do jogo
    int nJogo = I -> nJogo;

    // Liberta a memória alocada
    libertaInfo (I);

    return nJogo;
}



// Pede ao jogador a informação de um jogo novo
int infoJogoNovo (Info I) {

    // Pede ao jogador o número de linhas e de colunas desejados
    printf ("\nDigite o número de linhas e de colunas do jogo desejado.\n\n");

    // Lê o número de linhas e de colunas do tabuleiro
    if (scanf ("%d %d", &I -> dL, &I -> dC) != 2) {
        libertaInfo (I);
        return -1;
    }

    // Verifica se o número de linhas e de colunas é válido
    if (I -> dL < 0 || I -> dC < 0 || I -> dL > 26 || I -> dC > 26) {
        libertaInfo (I);
        return -2;
    }

    // Inicializa o tabuleiro
    inicializaTabuleiro (I);

    // Pede ao jogador o tabuleiro
    printf ("\nDigite o tabuleiro do jogo desejado.\n\n");

    // Lê o tabuleiro
    for (int i = 0; i < I -> dL; i++) {
        char linha [LINE_SIZE];
        if (scanf ("%s", linha) != 1) {
            libertaInfo (I);
            return -1;
        }
        int tam = strlen (linha);
        if (tam > I -> dC) {
            libertaInfo (I);
            return -3;
        }
        strcpy (I -> Tabuleiro [i], linha);
    }

    // Verifica se o tabuleiro é válido
    if (!tabuleiroValido (I -> dL, I -> dC, I -> Tabuleiro)) {
        libertaInfo (I);
        return -3;
    }

    return 0;
}



// Procura o índice mais baixo que ainda não possui jogo
int procuraJogoMaisBaixo (char *nomeFicheiro) {

    // Número do jogo
    int nJogo;

    // Procura, índice a índice, um ficheiro que ainda não existe
    for (int flag = nJogo = 1; flag; nJogo++) {

        // Altera o índice
        sprintf (nomeFicheiro, "Jogos/J%d/S0", nJogo);

        // Tenta abrir o ficheiro
        FILE *Jogo = fopen (nomeFicheiro, "r");

        // Não conseguiu abrir o ficheiro, então não existe
        if (Jogo == NULL) flag = 0;

        // Conseguiu abrir o ficheiro
        else fclose (Jogo);
    }

    // Decrementa o número do jogo
    nJogo--;

    // Verifica se o número do jogo é superior a 99
    if (nJogo > 99) return -4;

    return nJogo;
}



// Elimina um jogo ou uma save
int eliminaJS (char *arg1, char *arg2) {

    // Caso em que foi dado apenas um argumento, isto é, o jogador pretende eliminar uma diretoria
    if (arg2 [0] == 0) {

        // Cria o nome dos ficheiros
        char nomeFicheiro [LINE_SIZE];

        // Elimina todos os jogos
        for (int i = 0; i < 100; i++) {

            // Define o nome do ficheiro
            sprintf (nomeFicheiro, "Jogos/J%s/S%d", arg1, i);

            // Elimina o jogo
            remove (nomeFicheiro);
        }

        // Define o nome da diretoria
        sprintf (nomeFicheiro, "Jogos/J%s", arg1);

        // Elimina a diretoria
        if (rmdir (nomeFicheiro)) return 1;
    }

    // Caso em que foi dado dois argumentos, isto é, o jogador pretender eliminar um único jogo
    else {

        // Cria o nome do ficheiro
        char nomeFicheiro [LINE_SIZE];

        // Define o nome do ficheiro
        sprintf (nomeFicheiro, "Jogos/J%s/S%s", arg1, arg2);

        // Elimina o ficheiro
        if (remove (nomeFicheiro)) return 1;
    }

    return 0;
}



// Imprime todos os jogos e as respetivas saves
void imprimeJogos () {

    // Cria uma matriz que indica os jogos e saves que existem e um array que diz o número de saves de cada jogo
    int savesJogos [100][100], nSavesJogos [100];

    // Procura em todos os jogos que existem as suas saves
    for (int i = 1; i < 100; i++)
        for (int j = nSavesJogos [i] = 0; j < 100; j++) {

            // Cria o nome do ficheiro
            char nomeFicheiro [LINE_SIZE];

            // Preenche o nome do ficheiro
            sprintf (nomeFicheiro, "Jogos/J%d/S%d", i, j);

            // Tenta abrir o ficheiro
            FILE *Jogo = fopen (nomeFicheiro, "r");

            // Verifica se o ficheiro existe
            if (Jogo != NULL) {
                savesJogos [i][j] = 1;
                fclose (Jogo);
                nSavesJogos [i]++;
            }

            // A save não existe
            else savesJogos [i][j] = 0;
    }

    // Imprime os números dos jogos e ficheiros existentes
    imprimeSavesJogos (savesJogos, nSavesJogos);
}



// Imprime os jogos e as respetivas saves existentes
void imprimeSavesJogos (int savesJogos [100][100], int nSavesJogos [100]) {

    // Avança uma linha
    putchar ('\n');

    // Percorre os jogos
    for (int i = 1; i < 100; i++) {

        // Se existir este jogo, imprime as suas saves
        if (nSavesJogos [i]) {
            printf("O jogo %d possui a(s) seguinte(s) save(s): ", i);

            // Inteiro que indica se é a primeira save ou não
            int primeira = 1;

            // Procura as saves do jogo
            for (int j = 0; j < 100; j++) {
                if (savesJogos[i][j]) {
                    if (primeira == 0) printf(", ");
                    if (j == 0) printf ("Original (0)");
                    else printf("%d", j);
                    primeira = 0;
                }
            }

            // Passa para a linha seguinte
            putchar ('\n');
        }
    }

    // Avança uma linha
    putchar ('\n');
}