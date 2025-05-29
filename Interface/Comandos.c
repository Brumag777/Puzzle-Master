#include "../Puzzle.h"

// Grava o jogo num ficheiro
bool gravar (char cmd, char args [2][LINE_SIZE], Info I) {

    if (cmd == 'g') {

        // Realiza a lógica do comando 'g'
        int n = logicaGravar (args [0], I);

        // Avisa se o jogo foi gravado com sucesso
        if (n >= 0) printf (VERDE "\nJogo gravado na save %d do jogo %d.\n\n" RESET, n, I -> nJogo);

        // Avisa se não há nada a guardar
        else if (n == -1) fprintf (stderr, VERMELHO "\nErro:" RESET " Não há nenhum jogo para guardar. Leia um ficheiro para iniciar o jogo.\n\n");

        // Avisa se não foi possível abrir o ficheiro
        else if (n == -2) fprintf (stderr, VERMELHO "\nErro:" RESET " Não foi possível gravar o jogo.\n\n");

        // Avisa se o argumento dado não é um natural
        else if (n == -3) fprintf (stderr, VERMELHO "\nErro:" RESET " O argumento deve ser um número natural.\n\n");

        // Avisa se o argumento dado é superior a 99
        else if (n == -4) fprintf (stderr, VERMELHO "\nErro:" RESET " O índice máximo das saves é 99.\n\n");

        // Avisa se já existem 100 saves desse jogo
        else if (n == -5) fprintf (stderr, VERMELHO "\nErro:" RESET " O limite de saves desse jogo já foi alcançado.\n\n");

        return true;
    }

    return false;
}



// Lê um ficheiro
bool ler (char cmd, char args [2][LINE_SIZE], Info I) {

    if (cmd == 'l') {

        // Realiza a lógica da comando 'l'
        int n = logicaLer (args, I);

        // Caso de sucesso da função
        if (n == 0) {

            // Imprime o tabuleiro atualizado
            imprimeTabuleiro (I -> dL, I -> dC, I -> Tabuleiro, I -> nTabuleiro, 1);

            // Avisa que o ficheiro foi fido com sucesso
            printf (VERDE "Jogo lido com sucesso.\n\n" RESET);
        }

        // Avisa se não foi dado um argumento
        else if (n == 1) fprintf (stderr, VERMELHO "\nErro:" RESET " O comando l precisa de pelo menos um argumento.\n\n");

        // Avisa se o ficheiro não foi aberto corretamente
        else if (n == 2) fprintf (stderr, VERMELHO "\nErro:" RESET " Esse jogo (ou save) não existe.\n\n");

        // Avisa se houve erros a ler o ficheiro
        else if (n == 3) fprintf (stderr, VERMELHO "\nErro:" RESET " Não foi possível abrir o jogo.\n\n");

        // Avisa se o tabuleiro do ficheiro lido é inválido
        else if (n == 4) fprintf (stderr, VERMELHO "\nErro:" RESET " O jogo guardado não é válido.\n\n");

        // Avisa se as alterações do ficheiro lido são inválidas
        else if (n == 5) fprintf (stderr, VERMELHO "\nErro:" RESET " O jogo guardado não é válido.\n\n");

        // Avisa se o(s) argumento(s) dado(s) são válidos
        else if (n == 6) fprintf (stderr, VERMELHO "\nErro:" RESET " Argumento(s) inválido(s).\n\n");

        // Avisa se não foi possível ler o input do jogador
        else if (n == 7) fprintf (stderr, VERMELHO "\nErro:" RESET " Não foi possível ler o input.\n\n");

        // Avisa se algum dos argumentos é superior a 99
        else if (n == 8) fprintf (stderr, VERMELHO "Erro:\n" RESET " O índice máximo dos jogos e das saves é 99.\n\n");

        return true;
    }

    return false;
}



// Termina o jogo
bool sair (char cmd, char args [2][LINE_SIZE], Info I) {

    if (cmd == 's') {

        // Realiza a lógica do comando 's'
        int n = logicaSair (args [0], I);

        // Avisa se foi dado um argumento
        if (n == 1) fprintf (stderr, VERMELHO "\nErro:" RESET " O comando s não precisa de um argumento.\n\n" RESET);

        // Avisa se não foi possível ler o input do jogador
        else if (n == 2) fprintf (stderr, VERMELHO "\nErro:" RESET " Não foi possível ler o input.\n\n");

        return true;
    } 

    return false;
}



// Pinta uma casa de branco
bool pintarCasa (char cmd, char args [2][LINE_SIZE], Info I) {
    if (cmd == 'b') {

        // Realiza a lógica do comando 'b'
        int n = logicaPintarCasa (args [0], I);

        // Caso de sucesso da função
        if (n == 0) {
            // Imprime o tabuleiro atualizado
            imprimeTabuleiro (I -> dL, I -> dC, I -> Tabuleiro, I -> nTabuleiro, 1);

            // Garante que a pontuação não é negativa
            if (I -> pont < 0) I -> pont = 0;

            // Se o jogo estiver terminado, indica se o jogador ganhou
            if (testeJogo (I)) imprimeMensagemFim (I);
        }

        // Avisa se não foi dado um argumento
        else if (n == 1) fprintf (stderr, VERMELHO "\nErro:" RESET " O comando b precisa de um argumento (coordenada).\n\n");

        // Avisa se a coordenada é inválida
        else if (n == 2) fprintf (stderr, VERMELHO "\nErro:" RESET " A coordenada é inválida.\n\n");

        // Avisa se a casa selecionada está riscada
        else if (n == 3) fprintf (stderr, VERMELHO "\nErro:" RESET " A casa selecionada está riscada.\n\n");

        // Avisa se a casa selecionada está pintada de branco
        else if (n == 4) fprintf (stderr, VERMELHO "\nErro:" RESET " A casa selecionada já está pintada de branco.\n\n");

        return true;
    }
    
    return false;
}



// Muda uma casa para vazia
bool riscarCasa (char cmd, char args [2][LINE_SIZE], Info I) {

    if (cmd == 'r') {

        // Realiza a lógica do comando 'r'
        int n = logicaRiscarCasa (args [0], I);

        // Caso de sucesso da função
        if (n == 0) {
            // Imprime o tabuleiro atualizado
            imprimeTabuleiro (I -> dL, I -> dC, I -> Tabuleiro, I -> nTabuleiro, 1);

            // Garante que o pontuação não é negativa
            if (I -> pont < 0) I -> pont = 0;

            // Se o jogo estiver terminado, indica se o jogador ganhou
            if (testeJogo (I)) imprimeMensagemFim (I);
        }

        // Avisa se não foi dado um argumento
        else if (n == 1) fprintf (stderr, VERMELHO "\nErro:" RESET " O comando b precisa de um argumento (coordenada).\n\n");

        // Avisa se a coordenada é inválida
        else if (n == 2) fprintf (stderr, VERMELHO "\nErro:" RESET " A coordenada é inválida.\n\n");

        // Avisa se a casa selecionada está riscada
        else if (n == 3) fprintf (stderr, VERMELHO "\nErro:" RESET " A casa selecionada já está riscada.\n\n");

        // Avisa se a casa selecionada está pintada de branco
        else if (n == 4) fprintf (stderr, VERMELHO "\nErro:" RESET " A casa selecionada está pintada de branco.\n\n");

        return true;
    }
    
    return false;
}



// Desfaz a últimas jogadas
bool desfazerJogada (char cmd, char args [2][LINE_SIZE], Info I) {

    if (cmd == 'd') {

        // Realiza a lógica do comando 'd'
        int n = logicaDesfazerJogada (args [0], I);

        // Caso de sucesso da função
        if (n == 0) {

            // Limpa o stdin
            int ch;
            while ((ch = getchar ()) != '\n' && ch != EOF);

            // Imprime o tabuleiro
            imprimeTabuleiro (I -> dL, I -> dC, I -> Tabuleiro, I -> nTabuleiro, 1);

            // Garante que a pontuação não é negativa
            if (I -> pont < 0) I -> pont = 0;
        }

        // Avisa se não há um tabuleiro anterior
        else if (n == 1) fprintf (stderr, VERMELHO "\nErro:" RESET " Não existem jogadas para desfazer.\n\n");

        // Avisa se o argumento não é um número natural
        else if (n == 2) fprintf (stderr, VERMELHO "\nErro:" RESET " O argumento deve ser um número natural.\n\n");

        // Avisa se foi selecionado o tabuleiro atual
        else if (n == 3) fprintf (stderr, VERMELHO "\nErro:" RESET " Esse é o tabuleiro atual.\n\n");

        // Avisa se não existe o tabuleiro desejado
        else if (n == 4) fprintf (stderr, VERMELHO "\nErro:" RESET " O argumento é maior que o número de jogadas (%d).\n\n", I -> nTabuleiro);

        // Avisa se não foi possível ler o input do jogador
        else if (n == 5) fprintf (stderr, VERMELHO "\nErro:" RESET " Não foi possível ler o input.\n\n");

        return true;
    }

    return false;
}



// Imprime os últimos tabuleiros armazenados no histórico
bool visualizarHistorico (char cmd, char args [2][LINE_SIZE], Info I) {

    if (cmd == 'V') {

        // Realiza a lógica do comando 'V'
        int n = logicaVisualizarHistorico (args [0], I);

        // Caso de sucesso da função
        if (n > 0) {
            visualizaUltimosTabuleiros (I, n, 1);
            putchar ('\n');
        }

        // Avisa se o argumento não é um número natural
        else if (n == -1) fprintf (stderr, VERMELHO "\nErro:" RESET " O argumento deve ser um número natural.\n\n");

        // Avisa se não existem tabuleiros para imprimir
        else if (n == -2) fprintf (stderr, VERMELHO "\nErro:" RESET " Não existem tabuleiros para imprimir.\n\n");

        // Avisa se não existem tabuleiros suficientes para imprimir
        else if (n == -3) fprintf (stderr, VERMELHO "\nErro:" RESET " O argumento é maior que o número de jogadas (%d).\n\n", I -> nTabuleiro);

        return true;
    }

    return false;
}



// Verifica se existem infrações no tabuleiro
bool verifica (char cmd, char args [2][LINE_SIZE], Info I) {

    if (cmd == 'v') {

        // Realiza a lógica do comando 'v'
        int n = logicaVerifica (args [0], I);

        // Casos de sucesso da função
        if (n >= 0) {
            if (n) printf (VERDE "Não há nenhuma infração.\n" RESET);
            putchar ('\n');
        }

        // Avisa se foi dado um argumento
        else if (n == -1) fprintf (stderr, VERMELHO "\nErro:" RESET " O comando v não precisa de um argumento.\n\n");

        return true;
    }

    return false;
}



// Ajuda o jogador realizando jogadas 'obrigatórias' na posição
bool ajuda (char cmd, char args [2][LINE_SIZE], Info I) {

    if (cmd == 'a') {

        // Realiza a lógica do comando 'a'
        int n = logicaAjuda (args [0], I);

        // Caso de sucesso da função
        if (n == 0) {
            // Imprime o tabuleiro resultante
            imprimeTabuleiro (I -> dL, I -> dC, I -> Tabuleiro, I -> nTabuleiro, 1);

            // Garante que a pontuação não é negativa
            if (I -> pont < 0) I -> pont = 0;

            // Se o jogo estiver terminado, indica se o jogador ganhou
            if (testeJogo (I)) imprimeMensagemFim (I);
        }

        // Avisa se foi dado um argumento
        else if (n == 1) fprintf (stderr, VERMELHO "\nErro:" RESET " O argumento é inválido.\n\n");

        // Avisa se não há nada a alterar
        else if (n == 2) printf ("\nNão há nada a alterar.\n\n");

        // Avisa se o tabuleiro possui infrações
        else if (n == 3) printf (VERMELHO "\nO jogo possui infrações.\n\n" RESET);

        return true;
    }

    return false;
}



// Ajuda o jogador realizando jogadas 'obrigatórias' repetidamente até não haver nada a alterar
bool ajudaRep (char cmd, char args [2][LINE_SIZE], Info I) {

    if (cmd == 'A') {

        // Realiza a lógica do comando 'A'
        int n = logicaAjudaRep (args [0], I);

        // Caso de sucesso da função
        if (n == 0) {
            // Imprime o tabuleiro resultante
            imprimeTabuleiro (I -> dL, I -> dC, I -> Tabuleiro, I -> nTabuleiro, 1);

            // Garante que a pontuação não é negativa
            if (I -> pont < 0) I -> pont = 0;

            // Se o jogo estiver terminado, indica se o jogador ganhou
            if (testeJogo (I)) imprimeMensagemFim (I);
        }

        // Avisa se foi dado um argumento
        else if (n == 1) fprintf (stderr, VERMELHO "\nErro:" RESET " O comando A não precisa de um argumento.\n\n");

        // Avisa se não há nada a alterar
        else if (n == 2) printf ("\nNão há nada a alterar.\n\n");

        // Avisa se o tabuleiro possui infrações
        else if (n == 3) printf (VERMELHO "\nO jogo possui infrações.\n\n" RESET);

        return true;
    }

    return false;
}



// Resolve o jogo automaticamente
bool resolveJogo (char cmd, char args [2][LINE_SIZE], Info I) {

    if (cmd == 'R') {

        // Armazena a pontuação
        int p = I -> pont;

        // Realiza a lógica do comando 'R'
        int n = logicaResolveJogo (args [0], I, 1);

        // Caso de sucesso da função
        if (n == 0) {
            // Imprime o tabuleiro
            imprimeTabuleiro (I -> dL, I -> dC, I -> Tabuleiro, I -> nTabuleiro, 1);

            // Adiciona um penalty por invocar o comando 'R'
            I -> pont = 0;
        }

        // Avisa se foi dado um argumento
        else if (n == 1) fprintf (stderr, VERMELHO "\nErro:" RESET " O comando R não precisa de um argumento.\n\n");

        // Avisa se não há um jogo para resolver
        else if (n == 2) fprintf (stderr, VERMELHO "\nErro:" RESET " Não há um jogo para resolver. Use o comando l para iniciar um jogo.\n\n");

        // Avisa se não é possível resolver o jogo
        else if (n == 3) {
            printf (VERMELHO "\nAviso:" RESET " Não é possível resolver o jogo atual.\n\n");
            I -> pont = p;
        }

        return true;
    }

    return false;
}



// Mostra a solução do jogo (caso exista)
bool mostrarSolucao (char cmd, char args [2][LINE_SIZE], Info I) {

    if (cmd == 'X') {

        // Armazena a pontuação
        int p = I -> pont;

        // Realiza a lógica do comando 'X'
        int n = logicaResolveJogo (args [0], I, 0);

        // Caso de sucesso da função
        if (n == 0) I -> pont = 0;

        // Avisa se foi dado um argumento
        else if (n == 1) fprintf (stderr, VERMELHO "\nErro:" RESET " O comando X não precisa de um argumento.\n\n");

        // Avisa se não há um jogo para encontar solução
        else if (n == 2) fprintf (stderr, VERMELHO "\nErro:" RESET " Não há um jogo para revelar a solução. Use o comando l para iniciar um jogo.\n\n");

        // Avisa se não é possível resolver o jogo
        else if (n == 3) {
            printf (VERMELHO "\nAviso:" RESET " O jogo atual não possui solução.\n\n");
            I -> pont = p;
        }

        return true;
    }

    return false;
}



// Apaga o histoŕico de jogadas
bool apagaHistorico (char cmd, char args [2][LINE_SIZE], Info I) {

    if (cmd == 'D') {

        // Realiza a lógica do comando 'D'
        int n = logicaApagaHistorico (args [0], I);

        // Caso de sucesso da função
        if (n == 0) printf (VERDE "\nO histórico foi apagado com sucesso.\n\n" RESET);

        // Avisa se foi dado um argumento
        else if (n == 1) fprintf (stderr, VERMELHO "\nErro:" RESET " O comando D não precisa de um argumento.\n\n");

        // Avisa se não há nada do histórico
        else if (n == 2) fprintf (stderr, VERMELHO "\nErro:" RESET " O histórico já está vazio.\n\n");

        // Avisa se não foi possível ler o input
        else if (n == 3) fprintf (stderr, VERMELHO "\nErro:" RESET " Não foi possível ler o input");

        // O jogador não terminou o comando
        else if (n == 4) putchar ('\n');

        return true;
    }

    return false;
}



// Revela a pontuação atual
bool imprimePont (char cmd, char args [2][LINE_SIZE], Info I) {

    if (cmd == 'p') {

        // Realiza a lógica do comando 'p'
        int n = logicaImprimePont (args [0], I);

        // Caso de sucesso da função
        if (n == 1) printf ("\nA pontuação atual é " VERDE "%d / %d" RESET ".\n\n", I -> pont, 3 * I -> dL * I -> dC);
        else if (n == 2) printf ("\nA pontuação atual é " AMARELO "%d / %d" RESET ".\n\n", I -> pont, 3 * I -> dL * I -> dC);
        else if (n == 3) printf ("\nA pontuação atual é " VERMELHO "%d / %d" RESET ".\n\n", I -> pont, 3 * I -> dL * I -> dC);

        // Avisa se foi dado um argumento
        else if (n == -1) fprintf (stderr, VERMELHO "\nErro:" RESET " O comando p não precisa de um argumento.\n\n");

        // Avisa se ainda não foi lido um ficheiro
        else if (n == -2) fprintf (stderr, VERMELHO "\nErro:" RESET " Ainda não foi lido nenhum jogo.\n\n");

        return true;
    }

    return false;
}



// Permite ao jogador criar um jogo novo
bool criarJogo (char cmd, char args [2][LINE_SIZE], Info I) {

    if (cmd == 'c') {

        // Realiza a lógica do comando 'c'
        int n = logicaCriarJogo (args [0], I);

        // Limpa o stdin
        int ch;
        while ((ch = getchar ()) != '\n' && ch != EOF);

        // Caso de sucesso da função
        if (n >= 0) printf (VERDE "\nJogo %d criado com sucesso.\n\n" RESET, n);

        // Avisa se foi dado um argumento
        else if (n == -1) fprintf (stderr, VERMELHO "\nErro:" RESET " O comando c não precisa de um argumento.\n\n");

        // Avisa se não foi possível ler algo
        else if (n == -2) fprintf (stderr, VERMELHO "\nErro:" RESET " Não foi possível ler o input.\n\n");

        // Avisa se o número de linhas e/ou colunas é inválido
        else if (n == -3) fprintf (stderr, VERMELHO "\nErro:" RESET " Os número de linhas e de colunas devem estar entre 1 e 26.\n\n");

        // Avisa se o tabuleiro é inválido
        else if (n == -4) fprintf (stderr, VERMELHO "\nErro:" RESET " O jogo é inválido.\n\n");

        // Avisa se não foi possível criar o ficheiro
        else if (n == -5) fprintf (stderr, VERMELHO "\nErro:" RESET " Não foi possível criar o jogo.\n\n");

        // Avisa se o limite de jogos já foi atingido
        else if (n == -6) fprintf (stderr, VERMELHO "\nErro:" RESET "O limite de jogos (99) já foi atingido.\n\n");

        return true;
    }

    return false;
}



// Permite ao jogador eliminar um jogo
bool eliminarJogo (char cmd, char args [2][LINE_SIZE], Info I) {

    if (cmd == 'E') {

        // Realiza a lógica do comando 'E'
        int n = logicaEliminarJogo (args, I);

        // Caso de sucesso da função
        if (n == 0) printf (VERDE "\nJogo(s) eliminado(s) com sucesso.\n\n" RESET);

        // Avisa se não foi dado um argumento
        else if (n == 1) fprintf (stderr, VERMELHO "\nErro:" RESET " O comando E precisa de pelo menos um argumento.\n\n");

        // Avisa se não foi possível remover algum ficheiro (ou a diretoria)
        else if (n == 2) fprintf (stderr, VERMELHO "\nErro:" RESET " Não foi possível remover todos os jogos.\n\n");

        // Avisa se os argumentos são inválidos
        else if (n == 3) fprintf (stderr, VERMELHO "\nErro:" RESET " Os argumentos são inválidos.\n\n");

        // Caso em que o jogador escolheu não presseguir com o comando
        else if (n == 4) putchar ('\n');

        // Avisa se o jogador está a tentar eliminar uma save original
        else if (n == 5) fprintf (stderr, VERMELHO "\nErro:" RESET " Saves originais não podem ser eliminadas (sem eliminar o respetivo jogo).\n\n");

        // Avisa se o jogador está a tentar eliminar um dos quatro jogos principais
        else if (n == 6) fprintf (stderr, VERMELHO "\nErro:" RESET " Os jogos principais (jogos 1 a 4) não podem ser eliminados.\n\n");

        return true;
    }

    return false;
}



// Lista os comandos do jogo
bool infoComandos (char cmd, char args [2][LINE_SIZE], Info I) {

    // Para evitar warnings
    (void) I;

    if (cmd == 'h') {

        // Realiza a lógica do comando 'h'
        int n = logicaInfoComandos (args [0]);

        // Casos de sucesso da função
        if (n >= 0) {
            // Imprime informação sobre o comando desejado
            if (n) imprimeInfoComando (n);

            // Imprime os comandos do jogo
            else imprimeListaComandos ();
        }

        // Avisa se foi dado um argumento
        else if (n == -1) fprintf (stderr, VERMELHO "\nErro:" RESET " Esse comando não existe.\n\n");

        return true;
    }

    return false;
}



// Explica o objetivo e as regras do jogo
bool explicaJogo (char cmd, char args [2][LINE_SIZE], Info I) {

    // Para evitar warnings
    (void) I;

    if (cmd == 'e') {

        // Realiza a lógica do comando 'e'
        int n = logicaListarInfo (args [0]);

        // Caso de sucesso da função
        if (n == 0) {
            // Explica o jogo
            imprimeExplicacaoJogo ();
        }

        // Avisa se foi dado um argumento
        else if (n == 1) fprintf (stderr, VERMELHO "\nErro:" RESET " O comando e não precisa de um argumento.\n\n");

        return true;
    }

    return false;
}



// Revela todos os jogos e saves
bool indicaJogos (char cmd, char args [2][LINE_SIZE], Info I) {

    // Para evitar warnings
    (void) I;

    if (cmd == 'j') {

        // Realiza a lógica do comando 'j'
        int n = logicaListarInfo (args [0]);

        // Caso de sucesso da função
        if (n == 0) {

            // Cria uma matriz que indica os jogos e saves que existem e um array que diz o número de saves de cada jogo
            int savesJogos [100][100], nSavesJogos [100];

            // Procura todos em todos os jogos que existem as suas saves
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

        // Avisa se foi dado um argumento
        else if (n == 1) fprintf (stderr, VERMELHO "\nErro:" RESET " O comando j não precisa de um argumento.\n\n");

        return true;
    }

    return false;
}



// Limpa a terminal
bool limpaTerminal (char cmd, char args [2][LINE_SIZE], Info I) {

    // Para evitar warnings
    (void) I;

    if (cmd == 'C') {

        // Realiza a lógica do comando 'C'
        int n = logicaListarInfo (args [0]);

        // Caso de sucesso da função
        if (n == 0) assert (system ("clear") == 0);

        // Avisa se foi dado um argumento
        else if (n == 1) fprintf (stderr, VERMELHO "\nErro:" RESET " O comando C não precisa de um argumento.\n\n");

        return true;
    }

    return false;
}