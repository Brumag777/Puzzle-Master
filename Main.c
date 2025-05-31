#include "Puzzle.h"

// Função principal
int main () {

    // Array dos comandos do jogo
    Comando Comandos [] = {sair, gravar, ler, imprimePont, explica, infoComandos, criarJogo, eliminarJogo, indicaJogos,
                           pintarCasa, riscarCasa, visualizarHistorico, verifica, ajuda, ajudaRep, desfazerJogadas, resolveJogo, mostrarSolucao, dica, NULL};

    // Inicializa a informação do jogo
    Info I = inicializaInfo ();

    // Imprime a mensagem inicial
    imprimeMensagemInicial ();

    // Corre o jogo
    while (I -> aCorrer) {

        // Indica ao jogador que deve usar um comando
        printf ("> ");

        // Recebe o input
        char input [LINE_SIZE] = {0};
        if (fgets (input, LINE_SIZE, stdin)) assert (input [strlen (input) - 1] == '\n');
        else I -> aCorrer = false;

        // Verifica se o segundo caractere não é um espaço
        if (input [0] != '\n' && input [1] != '\n' && input [1] != ' ')
            fprintf (stderr, VERMELHO "\nErro: " RESET "Os comandos são apenas um caractere.\n\n");

        else {
            // Separa o input
            char cmd = 0, arg1 [LINE_SIZE], arg2 [LINE_SIZE], resto [LINE_SIZE];
            int numArgs = sscanf (input, "%c %s %s %[^\n]", &cmd, arg1, arg2, resto) - 1;

            // Verifica se o número de argumentos é válido
            if (numArgs > 2 || (numArgs > 1 && cmd != 'E' && cmd != 'l'))
                fprintf (stderr, VERMELHO "\nErro: " RESET "Número de argumentos excessivo.\n\n");

            else {
                // Define os argumentos como strings vazias caso não existam
                if (numArgs < 1) arg1 [0] = 0;
                if (numArgs < 2) arg2 [0] = 0;

                // Procura um comando a executar
                int flag = 0;
                for (int i = 0; flag == 0 && Comandos [i]; i++)
                    flag = Comandos [i] (cmd, arg1, arg2, I);
                
                // Verifica se nenhum comando foi executado
                if (flag == 0)
                    fprintf (stderr, VERMELHO "\nErro: " RESET "Comando inválido.\n\n");
            }
        }
    }

    // Liberta a memória alocada para a informação do jogo
    libertaInfo (I);

    return 0;
}