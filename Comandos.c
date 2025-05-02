#include "Puzzle.h"

// Grava o jogo num ficheiro
bool gravar (char cmd, char *arg, Info I) {

    if (cmd == 'g') {

        // Realiza a lógica do comando 'g'
        int n = logicaGravar (arg, I);

        // Avisa se o jogo foi gravado com sucesso
        if (n == 0) fprintf (stderr, "\nJogo gravado em '%s'.\n\n", arg);

        // Avisa se não foi dado um argumento
        else if (n == 1) fprintf (stderr, "\nErro: O comando g precisa de um argumento (nome do ficheiro).\n\n");

        // Avisa se não há nada a guardar
        else if (n == 2) fprintf (stderr, "\nErro: Não há nenhum tabuleiro para guardar. Leia um ficheiro para iniciar o jogo.\n\n");

        // Avisa se não foi possível abrir o ficheiro
        else if (n == 3) fprintf (stderr, "\nErro: Não foi possível abrir o ficheiro.\n\n");

        return true;
    }

    return false;
}



// Lê um ficheiro
bool ler (char cmd, char *arg, Info I) {

    if (cmd == 'l') {

        // Realiza a lógica da comando 'l'
        int n = logicaLer (arg, I);

        // Caso de sucesso da função
        if (n == 0) {
            // Imprime o tabuleiro atualizado
            imprimeTabuleiro (I -> Tabuleiro, I -> dL, I -> dC, I -> nTabuleiro);

            // Avisa que o ficheiro foi fido com sucesso
            fprintf (stderr, "Tabuleiro lido com sucesso.\n\n");
        }

        // Avisa se não foi dado um argumento
        else if (n == 1) fprintf (stderr, "\nErro: O comando l precisa de um argumento (nome do ficheiro).\n\n");

        // Avisa se o ficheiro não foi aberto corretamente
        else if (n == 2) fprintf (stderr, "\nErro: Não foi possível abrir o ficheiro.\n\n");

        // Avisa se houve erros a ler o ficheiro
        else if (n == 3) fprintf (stderr, "\nErro: Não foi possível ler o ficheiro.\n\n");

        // Avisa se o tabuleiro do ficheiro lido é inválido
        else if (n == 4) fprintf (stderr, "\nErro: O tabuleiro não é válido.\n\n");

        // Avisa se as alterações do ficheiro lido são inválidas
        else if (n == 5) fprintf (stderr, "\nErro: As alterações são inválidas.\n\n");

        return true;
    }

    return false;
}



// Termina o jogo
bool sair (char cmd, char *arg, Info I) {

    if (cmd == 's') {

        // Realiza a lógica do comando 's'
        int n = logicaSair (arg, I);

        // Avisa se foi dado um argumento
        if (n == 1) fprintf (stderr, "\nErro: O comando s não precisa de um argumento.\n\n");

        return true;
    } 

    return false;
}



// Pinta uma casa de branco
bool pintarCasa (char cmd, char *arg, Info I) {
    if (cmd == 'b') {

        // Realiza a lógica do comando 'b'
        int n = logicaPintarCasa (arg, I);

        // Caso de sucesso da função
        if (n == 0) {
            // Imprime o tabuleiro atualizado
            imprimeTabuleiro (I -> Tabuleiro, I -> dL, I -> dC, I -> nTabuleiro);

            // Se o jogo estiver terminado, indica se o jogador ganhou
            // if (testeJogo (I)) printf ("Parabéns! Conseguiste resolver o puzzle!\n\n");
        }

        // Avisa se não foi dado um argumento
        else if (n == 1) fprintf (stderr, "\nErro: O comando b precisa de um argumento (coordenada).\n\n");

        // Avisa se a coordenada é inválida
        else if (n == 2) fprintf (stderr, "\nErro: A coordenada é inválida.\n\n");

        // Avisa se a casa selecionada está riscada
        else if (n == 3) fprintf (stderr, "\nErro: A casa selecionada está riscada.\n\n");

        // Avisa se a casa selecionada está pintada de branco
        else if (n == 4) fprintf (stderr, "\nErro: A casa selecionada já está pintada de branco.\n\n");

        return true;
    }
    
    return false;
}



// Muda uma casa para vazia
bool riscarCasa (char cmd, char *arg, Info I) {

    if (cmd == 'r') {

        // Realiza a lógica do comando 'r'
        int n = logicaRiscarCasa (arg, I);

        // Caso de sucesso da função
        if (n == 0) {
            // Imprime o tabuleiro atualizado
            imprimeTabuleiro (I -> Tabuleiro, I -> dL, I -> dC, I -> nTabuleiro);

            // Se o jogo estiver terminado, indica se o jogador ganhou
            // if (testeJogo (I)) printf ("Parabéns! Conseguiste resolver o puzzle!\n\n");
        }

        // Avisa se não foi dado um argumento
        else if (n == 1) fprintf (stderr, "\nErro: O comando b precisa de um argumento (coordenada).\n\n");

        // Avisa se a coordenada é inválida
        else if (n == 2) fprintf (stderr, "\nErro: A coordenada é inválida.\n\n");

        // Avisa se a casa selecionada está riscada
        else if (n == 3) fprintf (stderr, "\nErro: A casa selecionada já está riscada.\n\n");

        // Avisa se a casa selecionada está pintada de branco
        else if (n == 4) fprintf (stderr, "\nErro: A casa selecionada está pintada de branco.\n\n");

        return true;
    }
    
    return false;
}



// Imprime os últimos tabuleiros armazenados no histórico
bool visualizarHistorico (char cmd, char *arg, Info I) {

    if (cmd == 'V') {

        // Realiza a lógica do comando 'V'
        int n = logicaVizualizarHistorico (arg, I);

        // Caso de sucesso da função
        if (n > 0) visualizaUltimosTabuleiros (I, n, 1);

        // Avisa se o argumento não é um número natural
        else if (n == -1) fprintf (stderr, "\nErro: O argumento deve ser um número natural.\n\n");

        // Avisa se não existem tabuleiros para imprimir
        else if (n == -2) fprintf (stderr, "\nErro: Não existem tabuleiros para imprimir.\n\n");

        // Avisa se não existem tabuleiros suficientes para imprimir
        else if (n == -3) fprintf (stderr, "\nErro: O argumento é maior que o número de tabuleiros (%d).\n\n", I -> nTabuleiro);

        return true;
    }

    return false;
}



// Lista os comandos do jogo
bool listarComandos (char cmd, char *arg, Info I) {

    if (cmd == 'h') {

        // Realiza a lógica do comando 'h'
        int n = logicaListarComandos (arg, I);

        // Caso de sucesso da função
        if (n == 0) {
            // Imprime os comandos do jogo
            printf ("\nOs comandos do jogo são:\n"
                    "g <ficheiro>: Grava o tabuleiro num ficheiro.\n"
                    "l <ficheiro>: Lê um tabuleiro de um ficheiro.\n"
                    "b <coordenada>: Pinta a casa selecinada de branco (caso possível).\n"
                    "r <coordenada>: Torna a casa selecionada vazia (caso possível).\n"
                    "v: Verifica se existem infrações na posição atual.\n"
                    "V: Permite ver o último tabuleiro.\n"
                    "V <natural>: Permite ver os tabuleiros anteriores.\n"
                    "a: Ajuda realizando todas as jogadas necessárias na posição atual.\n"
                    "a b: Ajuda pintando de branco as casas à volta de casas riscadas.\n"
                    "a r: Ajuda riscando as casas na mesma linha ou coluna que casas brancas com a mesma letra.\n"
                    "a o: Ajuda pintando de branco as casas que se fossem riscadas não permitiam um caminho ortogonal entre todas as letras.\n"
                    "A: Ajuda realizando todas as jogadas necessárias na posição até não haver mais nenhuma a realizar.\n"
                    "R: Resolve o jogo (se for possível).\n"
                    "X: Mostra a solução do tabuleiro atual (caso exista).\n"
                    "d: Desfaz a última jogada.\n"
                    "d <natural>: Desfaz as últimas jogadas até ao tabuleiro selecinado.\n"
                    "s: Termina o jogo.\n"
                    "h: Lista todos os comandos do jogo.\n\n");
            if (I -> nTabuleiro) {
                printf ("As coordenadas devem estar compreendidas entre a1 e %c%d \n", I -> dC + 'a' - 1, I -> dL);
                printf ("Os números naturais devem ser iguais ou inferiores a %d\n\n", I -> nTabuleiro);
            }
            else printf ("Leia um ficheiro para usar os comandos.\n\n");
        }

        // Avisa se foi dado um argumento
        else if (n == 1) fprintf (stderr, "\nErro: O comando h não precisa de um argumento.\n\n");

        return true;
    }

    return false;
}