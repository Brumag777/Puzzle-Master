#include "Puzzle.h"

// Função principal
int main () {

    // Lista de comandos do jogo
    COMANDO comandos [] = {sair, ler, listarComandos, pintarCasa, riscarCasa, visualizarHistorico, gravar, NULL};



    // Inicializa a informação sobre o jogo
    Info I = inicializaJogo ();
    if (I == NULL) return 1;



    // Corre o jogo
    while (I -> aCorrer) {
        printf ("> ");

        char line [LINE_SIZE] = {0};
        


        // Recebe o input
        if (fgets (line, LINE_SIZE, stdin) != NULL)
            assert (line [strlen (line) - 1] == '\n');
        else I -> aCorrer = false;



        // Armazena o input
        char cmd = 0;
        char arg [LINE_SIZE];
        char resto [LINE_SIZE];
        int num_args = sscanf (line, "%c %s %[^\n]", &cmd, arg, resto);



        // Verifica se o número de argumentos é válido (0 ou 1)
        if (num_args > 2)
            fprintf (stderr, "\nErro: Comando %c foi invocado com argumentos extra: %s.\n\n", cmd, resto);
            


        // Verifica se algum dos comandos foi invocado
        else {
            bool ret = false;
            int i;

            for (i = 0; !ret && comandos [i] != NULL; i++)
                ret = comandos [i] (cmd, (num_args == 2) ? arg : NULL, I);

            if (cmd != 'g' && comandos [i] == NULL) fprintf (stderr, "\nErro: Comando inválido.\n\n");
        }
    }



    // Liberta a memória alocada para a informação do jogo
    libertaInfo (I);



    return 0;
}