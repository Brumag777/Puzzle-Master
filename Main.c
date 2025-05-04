#include "Puzzle.h"

// Função principal
int main () {

    // Lista de comandos do jogo
    COMANDO comandos [] = {sair, ler, preview, listarComandos, pintarCasa, riscarCasa, visualizarHistorico, gravar, 
                           verifica, ajuda, ajudaRep, resolveJogo, imprimeNJogadas, desfazerJogada, apagaHistorico,
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
        char arg [LINE_SIZE];
        char resto [LINE_SIZE];
        int num_args = sscanf (line, "%c %s %[^\n]", &cmd, arg, resto);

        // Verifica se o número de argumentos é válido (0 ou 1)
        if (num_args > 2) fprintf (stderr, "\nErro: Comando inválido.\n\n");

        // Verifica se algum dos comandos foi invocado
        else for (int i = 0, flag = 0; flag == 0; i++)
                if (i > 16) {
                    fprintf (stderr, "\nErro: Comando inváldio.\n\n");
                    flag = 1;
                }
                else flag = comandos [i] (cmd, (num_args == 2) ? arg : NULL, I);
    }

    // Liberta a memória alocada para a informação do jogo
    libertaInfo (I);

    return 0;
}