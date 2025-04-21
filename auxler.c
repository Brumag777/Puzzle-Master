#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "puzzle.h"

// Função auxiliar ao comando 'l'
bool auxLer (ESTADO *e, char *arg) {                                                            
    
    // Abre o ficheiro a ler
    FILE *Jogo = fopen (arg, "r");

    // Verifica se o ficheiro foi lido com sucesso
    if (Jogo == NULL) {
        fprintf (stderr, "\nErro: Ficheiro inválido.\n\n");
        return true;
    }

    // Liberta a memória do tabuleiro relativo ao ficheiro anterior
    libertaTabuleiro (e -> info, 0);

    // Inicializa o tabuleiro novo
    iniciarTabuleiro (e, 0);

    // Lê as linhas e as colunas do ficheiro
    if (fscanf (Jogo, "%d %d", &e -> info -> linhas, &e -> info -> colunas) != 2) {
        fclose (Jogo);
        return true;
    }

    // Ignora o '\n' da primeira linha
    fgetc (Jogo);

    // Aloca memória para o tabuleiro novo
    e -> info -> Tabuleiro = malloc (e -> info -> linhas * sizeof (char *));

    // Aloca memória para cada linha do tabuleiro novo e preenche o mesmo com a informação do ficheiro
    for (int i = 0; i < e -> info -> linhas; i++) {
        e -> info -> Tabuleiro [i] = malloc ((e -> info -> colunas + 2) * sizeof (char));
        if (fgets (e -> info -> Tabuleiro [i], e -> info -> colunas + 2, Jogo) == NULL) return true;
    }

    // Fecha o ficheiro
    fclose (Jogo); 

    // Verifica se o tabuleiro é válido
    if (!tabuleiroValido (e -> info)) {
        fprintf (stderr, "\nErro: Tabuleiro inválido.\n\n");
        return true;
    }

    // Adiciona o tabuleiro novo ao histórico de tabuleiros
    pushStack (e -> info -> hTabuleiros, e -> info -> Tabuleiro, e -> info -> linhas, e -> info -> colunas);

    // Imprime o tabuleiro novo
    visualizarTabuleiro (e -> info);

    // Avisa do sucesso da leitura
    fprintf (stderr, "\nTabuleiro lido com sucesso.\n\n");
    
    return true;
}