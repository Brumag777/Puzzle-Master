#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "puzzle.h"

// Função principal
int main () {

    // Lista de comandos do jogo: s, l, g, b, r, h, d, V, v
    COMANDO comandos [] = {sair, ler, gravar, mudarParaMaiuscula, mudarParaVazia, listarComandos, desfazerJogada, vizualizarStack,           
                           verifica, ortog, NULL};



    // Inicializa o estado do jogo
    ESTADO estado;
    estado.looping = true;
    iniciarTabuleiro (&estado);



    // Variável para evitar repetições do '>' quanto é invocado o comando 'd'
    int v = 1;



    // Mantém o jogo a correr até ser usado o comando 's'
    while (estado.looping) {

        if (v) printf ("> ");
        v = 1;

        char line [LINE_SIZE] = {0};
        


        // Recebe o input
        if (fgets (line, LINE_SIZE, stdin) != NULL) 
            assert (line [strlen (line) - 1] == '\n');
        else estado.looping = false;



        // Armazena o input
        char cmd = 0;
        char arg [LINE_SIZE];
        char resto [LINE_SIZE];
        int num_args = sscanf (line, "%c %s %[^\n]", &cmd, arg, resto);



        // Verifica se o número de argumentos é válido (0 ou 1)
        if (num_args > 2)
            fprintf (stderr, "Erro: comando %c foi invocado com argumentos extra: %s\n\n", cmd, resto);
            


        // Verifica se algum dos comandos foi invocado
        else {
            bool ret = false;
            for (int I = 0; !ret && comandos [I] != NULL; I++) {
                ret = comandos [I] (cmd, (num_args == 2) ? arg : NULL, &estado);
                if (I == 6 && ret) v = 0;
            }
        }
    }



    // Liberta a memória alocada
    if (estado.info != NULL) libertaTabuleiro (estado.info);

    return 0;
}