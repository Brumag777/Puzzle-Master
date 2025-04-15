#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "puzzle.h"

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



// Imprime o tabuleiro atual do jogo
void visualizarTabuleiro (IJ *InfoJogo) {

    int i, j;

    // Imprime a estrutura do tabuleiro
    printf ("\n%d   ", InfoJogo -> hTabuleiros -> sp);
    for (j = 0; j < InfoJogo -> colunas; j++)
        printf ("%c ", 'a' + j);
    printf ("\n    ");
    for (j = 0; j < InfoJogo -> colunas; j++)
        printf ("- ");
    putchar ('\n');

    // Imprime o tabuleiro, percorrendo cada linha do mesmo
    for (i = 0; i < InfoJogo -> linhas; i++) {
        printf ("%d | ", i + 1);
        for (j = 0; j < InfoJogo -> colunas; j++)
            printf ("%c ", InfoJogo -> Tabuleiro [i][j]);
        putchar ('\n');
    }

    putchar ('\n');
}



// Verifica se um tabuleiro é válido
int tabuleiroValido (IJ *InfoJogo) {

    // Verifica se o tabuleiro não é nulo
    if (InfoJogo == NULL || InfoJogo -> Tabuleiro == NULL) return 0;

    char c;

    // Verifica se todas as casas do tabuleiro possuem caracteres válidos
    for (int i = 0; i < InfoJogo -> linhas; i++) {

        for (int j = 0; j < InfoJogo -> colunas; j++) {

            c = InfoJogo -> Tabuleiro [i][j];

            if (!(eMinuscula (c) || eMaiuscula (c) || c == '#')) {
                fprintf (stderr, "Erro: caractere inválido no tabuleiro (na coordenada %c%d)\n\n", j + 1 + 'a', i + 1);
                return 0;
            }
        }
    }

    return 1; 
}



// Verifica se as linhas não possuem casas brancas repetidas
int verificaLinhas (IJ *InfoJogo, char c, int linha, int coluna) {

    // Inteiro representante da validade do tabuleiro
    int r = 1;
    
    // Percorre o resto da linha para procurar infrações
    for (int j = coluna + 1; j < InfoJogo -> colunas; j++)

        if (InfoJogo -> Tabuleiro [linha][j] == c) {
            printf ("Infração: Letra '%c' repetida na linha %d (colunas '%c' e '%c')\n", c, linha + 1, coluna + 'a', j + 'a');
            r = 0;
        }

    return r;
}




int verificaColunas (IJ *InfoJogo, char c, int linha, int coluna) {

    // Inteiro representante da validade do tabuleiro
    int r = 1;
    
    // Percorre o resto da coluna para procurar infrações
    for (int i = linha + 1; i < InfoJogo -> linhas; i++)

        if (InfoJogo -> Tabuleiro [i][coluna] == c) {
            printf ("Infração: Letra '%c' repetida na coluna '%c' (linhas %d e %d)\n", c, coluna + 'a', linha + 1, i + 1);
            r = 0;
        }

    return r;
}



// Verifica se as casas adjacentes às casas vazias são brancas
int verificaHashtag (IJ *InfoJogo, int linha, int coluna) {

    // Inteiro representante da validade do tabuleiro
    int r = 1;

    // Verifica se a casa em cima (se pertencer ao tabuleiro) é vazia
    if (linha && !eMaiuscula (InfoJogo -> Tabuleiro [linha - 1][coluna])) {
        printf ("Infração: A casa %c%d não está pintada de branco\n", coluna + 'a', linha);
        r = 0;
    }

    // Verifica se a casa em baixo (se pertencer ao tabuleiro) é vazia
    if (linha + 1 < InfoJogo -> linhas && !eMaiuscula (InfoJogo -> Tabuleiro [linha + 1][coluna])) {
        printf ("Infração: A casa %c%d não está pintada de branco\n", coluna + 'a', linha + 2);
        r = 0;
    }

    // Verifica se a casa à esquerda (se pertencer ao tabuleiro) é vazia
    if (coluna && !eMaiuscula (InfoJogo -> Tabuleiro [linha][coluna - 1])) {
        printf ("Infração: A casa %c%d não está pintada de branco\n", coluna + 'a' - 1, linha + 1);
        r = 0;
    }

    // Verifica se a casa à direita (se pertencer ao tabuleiro) é vazia
    if (coluna + 1 < InfoJogo -> colunas && !eMaiuscula (InfoJogo -> Tabuleiro [linha][coluna + 1])) {
        printf ("Infração: A casa %c%d não está pintada de branco\n", coluna + 'a' + 1, linha + 1);
        r = 0;
    }

    return r;
}



// Função auxiliar ao comando 'l'
bool auxLer (ESTADO *e, char *arg) {                                                            
    
    // Abre o ficheiro a ler
    FILE *Jogo = fopen (arg, "r");

    // Verifica se o ficheiro foi lido com sucesso
    if (Jogo == NULL) {
        fprintf (stderr, "Erro: Ficheiro inválido\n");
        return false;
    }

    // Liberta a memória do tabuleiro relativo ao ficheiro anterior
    libertaTabuleiro (e -> info);

    // Inicializa o tabuleiro novo
    iniciarTabuleiro (e);

    // Lê as linhas e as colunas do ficheiro
    if (fscanf (Jogo, "%d %d", &e -> info -> linhas, &e -> info -> colunas) != 2) {
        fclose (Jogo);
        return false;
    }

    // Ignora o '\n' da primeira linha
    fgetc (Jogo);

    // Aloca memória para o tabuleiro novo
    e -> info -> Tabuleiro = malloc (e -> info -> linhas * sizeof (char *));

    // Aloca memória para cada linha do tabuleiro novo e preenche o mesmo com a informação do ficheiro
    for (int i = 0; i < e -> info -> linhas; i++) {
        e -> info -> Tabuleiro [i] = malloc ((e -> info -> colunas + 2) * sizeof (char));
        if (fgets (e -> info -> Tabuleiro [i], e -> info -> colunas + 2, Jogo) == NULL) return false;
    }

    // Fecha o ficheiro
    fclose (Jogo); 

    // Verifica se o tabuleiro é válido
    if (!tabuleiroValido (e -> info)) {
        fprintf (stderr, "Erro: Tabuleiro inválido\n");
        return false;
    }

    // Adiciona o tabuleiro novo ao histórico de tabuleiros
    pushStack (e -> info -> hTabuleiros, e -> info -> Tabuleiro, e -> info -> linhas);

    // Imprime o tabuleiro novo
    visualizarTabuleiro (e -> info);

    // Avisa do sucesso da leitura
    fprintf (stderr, "Ficheiro lido com sucesso\n\n");
    
    return true;
}



// Inicializa os tabuleiros
void iniciarTabuleiro (ESTADO *e) {

    // Inicializa o tabuleiro principal
    e -> info = malloc (sizeof (IJ));
    e -> info -> Tabuleiro = NULL;
    e -> info -> linhas = 0;
    e -> info -> colunas = 0;

    // Inicializa o histórico de tabuleiros
    e -> info -> hTabuleiros = malloc (sizeof (HIST));
    inicializaStack (e -> info -> hTabuleiros);
}



// Liberta a memória alocada para os tabuleiros
void libertaTabuleiro (IJ *InfoJogo) {

    // Verifica se existe informação sobre o jogo
    if (InfoJogo == NULL) return;

    if (InfoJogo -> Tabuleiro != NULL) {

        // Liberta a memória alocada para cada linha do tabuleiro principal
        for (int i = 0; i < InfoJogo -> linhas; i++) 
            free (InfoJogo -> Tabuleiro [i]);

        // Liberta a memória alocada para o tabuleiro principal
        free (InfoJogo -> Tabuleiro);
    }

    // Liberta a memória alocada para o histórico de tabuleiros
    libertaStack (InfoJogo -> hTabuleiros, InfoJogo -> linhas);

    // Liberta a informação sobre o jogo
    free (InfoJogo);
}