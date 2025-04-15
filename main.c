#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "puzzle.h"

int main () {
    //                     s     l    g       b                   r               h               d               V
    COMANDO comandos [] = {sair, ler, gravar, mudarParaMaiuscula, mudarParaVazia, listarComandos, desfazerJogada, vizualizarStack, 
    //                     v                       
                           verifica, NULL};

    ESTADO estado;
    estado.looping = true;

    iniciarTabuleiro (&estado);

    while (estado.looping) {
        printf ("> ");
        char line [LINE_SIZE] = {0};
        
        if (fgets (line, LINE_SIZE, stdin) != NULL) 
            assert (line [strlen (line) - 1] == '\n');
        else estado.looping = false;

        char cmd = 0;
        char arg [LINE_SIZE];
        char resto [LINE_SIZE];
        int num_args = sscanf (line, "%c %s %[^\n]", &cmd, arg, resto);

        if (num_args > 2) 
            fprintf (stderr, "Erro: comando %c foi invocado com argumentos extra: %s\n\n", cmd, resto);

        else {
            bool ret = false;
            for (int I = 0; !ret && comandos [I] != NULL; I++)
                ret = comandos [I] (cmd, (num_args == 2) ? arg : NULL, &estado);
        }
    }

    if (estado.info != NULL) libertaTabuleiro (estado.info);

    return 0;
}