#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogo.h"

int main () {

    IJ InfoJogo;

    // Inicia o jogo
    if (iniciaJogo (&InfoJogo)) return 1;

    // Corre o jogo
    char c = 0;

    while (c != 's') {

        vizualizaTabuleiro (InfoJogo); 

        if (scanf (" %c", &c) != 1) return 1;

        if (c == 'b') mudaCasaParaMaiuscula (&InfoJogo);

        else if (c == 'r') mudaCasaParaVazio (&InfoJogo);

        else if (c == 'h') listaComandos ();

        else if (c != 's') printf ("\nComando inválido\n");
        
        if (c != 's') printf ("\n");
    }

    // Liberta a memória alocada
    for (int i = 0; i < InfoJogo.linhas; i++) free (InfoJogo.Tabuleiro [i]);
    free (InfoJogo.Tabuleiro);
    
    return 0;
}