#include "Puzzle.h"

// Função principal
int main () {

    // Lista de comandos do jogo
    COMANDO comandos [] = {sair, ler, criarJogo, eliminarJogo, listarComandos, pintarCasa, riscarCasa, visualizarHistorico, gravar, 
                           verifica, indicaJogos, ajuda, ajudaRep, resolveJogo, imprimePont, desfazerJogada, apagaHistorico,
                           explicaJogo, mostrarSolucao, NULL};

    // Inicializa a informação sobre o jogo
    Info I = inicializaJogo ();

    // Mensagem inicial
    printf ("Bem vindo ao Puzzle Master. Pressione 'h' para ver a lista de comandos.\n");

    // Corre o jogo
    while (I -> aCorrer) {

        // Indica ao usuário que deve usar um comando
        printf ("> ");

        // Recebe o input
        char line [LINE_SIZE] = {0};
        if (fgets (line, LINE_SIZE, stdin)) assert (line [strlen (line) - 1] == '\n');
        else I -> aCorrer = false;

        // Armazena o input
        char cmd = 0;
        char args [2][LINE_SIZE];
        char rest [LINE_SIZE];
        int num_args = sscanf (line, "%c %s %s %[^\n]", &cmd, args [0], args [1], rest);

        // Define o segundo argumento como uma string vazia caso não exista
        if (num_args <= 2) strcpy (args [1], "\0");

        // Verifica se o número de argumentos é válido (0 ou 1 se o comando não for o 'l', 0, 1 ou 2 se o comando for o 'l')
        if (num_args > 3 || (num_args > 2 && cmd != 'E' && cmd != 'l')) fprintf (stderr, VERMELHO "\nErro:" RESET " Comando inválido.\n\n");

        // Verifica se algum dos comandos foi invocado
        else for (int i = 0, flag = 0; flag == 0; i++)
                if (i > 17) {
                    fprintf (stderr, VERMELHO "\nErro:" RESET " Comando inválido.\n\n");
                    flag = 1;
                }
                else flag = comandos [i] (cmd, (num_args > 1) ? args : NULL, I);
    }

    // Liberta a memória alocada para a informação do jogo
    libertaInfo (I);

    return 0;
}