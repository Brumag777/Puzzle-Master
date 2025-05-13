#include "../Puzzle.h"

// Grava o jogo num ficheiro
bool gravar (char cmd, char args [2][LINE_SIZE], Info I) {

    if (cmd == 'g') {

        // Realiza a lógica do comando 'g'
        int n = logicaGravar (args [0], I);

        // Avisa se o jogo foi gravado com sucesso
        if (n >= 0) printf (VERDE "\nJogo gravado na save %d do jogo %d.\n\n" RESET, n, I -> nJogo);

        // Avisa se não há nada a guardar
        else if (n == -1) fprintf (stderr, VERMELHO "\nErro:" RESET " Não há nenhum tabuleiro para guardar. Leia um ficheiro para iniciar o jogo.\n\n");

        // Avisa se não foi possível abrir o ficheiro
        else if (n == -2) fprintf (stderr, VERMELHO "\nErro:" RESET " Não foi possível abrir o ficheiro.\n\n");

        // Avisa se o argumento dado não é um natural
        else if (n == -3) fprintf (stderr, VERMELHO "\nErro:" RESET " O argumento deve ser um número natural.\n\n");

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
            printf (VERDE "Tabuleiro lido com sucesso.\n\n" RESET);
        }

        // Avisa se não foi dado um argumento
        else if (n == 1) fprintf (stderr, VERMELHO "\nErro:" RESET " O comando l precisa de um argumento (nome do ficheiro).\n\n");

        // Avisa se o ficheiro não foi aberto corretamente
        else if (n == 2) fprintf (stderr, VERMELHO "\nErro:" RESET " Não foi possível abrir o ficheiro.\n\n");

        // Avisa se houve erros a ler o ficheiro
        else if (n == 3) fprintf (stderr, VERMELHO "\nErro:" RESET " Não foi possível ler o ficheiro.\n\n");

        // Avisa se o tabuleiro do ficheiro lido é inválido
        else if (n == 4) fprintf (stderr, VERMELHO "\nErro:" RESET " O tabuleiro não é válido.\n\n");

        // Avisa se as alterações do ficheiro lido são inválidas
        else if (n == 5) fprintf (stderr, VERMELHO "\nErro:" RESET " As alterações são inválidas.\n\n");

        // Avisa se o(s) argumento(s) dado(s) são válidos
        else if (n == 6) fprintf (stderr, VERMELHO "\nErro:" RESET " Argumento(s) inválido(s).\n\n");

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
            if (testeJogo (I)) printf (VERDE "Parabéns! Conseguiste resolver o puzzle com uma pontuação de %d.\n\n" RESET, I -> pont);
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
            if (testeJogo (I)) printf (VERDE "Parabéns! Conseguiste resolver o puzzle com uma pontuação de %d.\n\n" RESET, I -> pont);
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
            // Imprime o tabuleiro
            imprimeTabuleiro (I -> dL, I -> dC, I -> Tabuleiro, I -> nTabuleiro, 1);

            // Garante que a pontuação não é negativa
            if (I -> pont < 0) I -> pont = 0;
        }

        // Avisa se não há um tabuleiro anterior
        else if (n == 1) fprintf (stderr, VERMELHO "\nErro:" RESET " Não existem tabuleiros para desfazer.\n\n");

        // Avisa se o argumento não é um número natural
        else if (n == 2) fprintf (stderr, VERMELHO "\nErro:" RESET " O argumento deve ser um número natural.\n\n");

        // Avisa se foi selecionado o tabuleiro atual
        else if (n == 3) fprintf (stderr, VERMELHO "\nErro:" RESET " Esse é o tabuleiro atual.\n\n");

        // Avisa se não existe o tabuleiro desejado
        else if (n == 4) fprintf (stderr, VERMELHO "\nErro:" RESET " O argumento é maior que o número de tabuleiros (%d).\n\n", I -> nTabuleiro);

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
        else if (n == -3) fprintf (stderr, VERMELHO "\nErro:" RESET " O argumento é maior que o número de tabuleiros (%d).\n\n", I -> nTabuleiro);

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
            if (testeJogo (I)) printf (VERDE "Parabéns! Conseguiste resolver o puzzle com uma pontuação de %d.\n\n" RESET, I -> pont);
        }

        // Avisa se foi dado um argumento
        else if (n == 1) fprintf (stderr, VERMELHO "\nErro:" RESET " O argumento é inválido.\n\n");

        // Avisa se não há nada a alterar
        else if (n == 2) printf ("\nNão há nada a alterar.\n\n");

        // Avisa se o tabuleiro possui infrações
        else if (n == 3) printf (VERMELHO "\nO tabuleiro possui infrações.\n\n" RESET);

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
            if (testeJogo (I)) printf (VERDE "Parabéns! Conseguiste resolver o puzzle com uma pontuação de %d.\n\n" RESET, I -> pont);
        }

        // Avisa se foi dado um argumento
        else if (n == 1) fprintf (stderr, VERMELHO "\nErro:" RESET " O comando A não precisa de um argumento.\n\n");

        // Avisa se não há nada a alterar
        else if (n == 2) printf ("\nNão há nada a alterar.\n\n");

        // Avisa se o tabuleiro possui infrações
        else if (n == 3) printf (VERMELHO "\nO tabuleiro possui infrações.\n\n" RESET);

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
            printf (VERMELHO "\nAviso: Não é possível resolver o jogo atual.\n\n" RESET);
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
        if (n == 0) printf (VERDE "\nO histórico foi apagado com sucesso.\n\n");

        // Avisa se foi dado um argumento
        else if (n == 1) fprintf (stderr, VERMELHO "\nErro:" RESET " O comando D não precisa de um argumento.\n\n");

        // Avisa se não há nada do histórico
        else if (n == 2) fprintf (stderr, VERMELHO "\nErro:" RESET " O histórico já está vazio.\n\n");

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
        if (n == 1) printf ("\nA pontuação atual é " VERDE "%d" RESET ".\n\n", I -> pont);
        else if (n == 2) printf ("\nA pontuação atual é " AMARELO "%d" RESET ".\n\n", I -> pont);
        else if (n == 3) printf ("\nA pontuação atual é " VERMELHO "%d" RESET ".\n\n", I -> pont);

        // Avisa se foi dado um argumento
        else if (n == -1) fprintf (stderr, VERMELHO "\nErro:" RESET " O comando p não precisa de um argumento.\n\n");

        // Avisa se ainda não foi lido um ficheiro
        else if (n == -2) fprintf (stderr, VERMELHO "\nErro:" RESET " Ainda não foi lido nenhum ficheiro.\n\n");

        return true;
    }

    return false;
}



// Permite ao jogador criar um jogo novo
bool criarJogo (char cmd, char args [2][LINE_SIZE], Info I) {

    // Para evitar warnings
    (void) I;

    if (cmd == 'c') {

        // Realiza a lógica do comando 'c'
        int n = logicaCriarJogo (args [0]);

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
        else if (n == -4) fprintf (stderr, VERMELHO "\nErro:" RESET " O tabuleiro é inválido.\n\n");

        // Avisa se não foi possível criar o ficheiro
        else if (n == -5) fprintf (stderr, VERMELHO "\nErro:" RESET " Não foi possível criar o jogo.\n\n");

        return true;
    }

    return false;
}



// Lista os comandos do jogo
bool listarComandos (char cmd, char args [2][LINE_SIZE], Info I) {

    // Para evitar warnings
    (void) I;

    if (cmd == 'h') {

        // Realiza a lógica do comando 'h'
        int n = logicaListarInfo (args [0]);

        // Caso de sucesso da função
        if (n == 0)
            // Imprime os comandos do jogo
            printf ("\nOs comandos do jogo são:\n"
                    "g: Grava o jogo atual numa nova save.\n"
                    "g 'x': Grava o jogo atual na save 'x'. 'x' deve ser um número natural.\n"
                    "l 'x': Abre o jogo 'x' na save original. 'x' Deve ser um número natural.\n"
                    "l 'x' 'y': Abre o jogo 'x' na save 'y'. 'x' e 'y' devem ser números naturais.\n"
                    "b <coordenada>: Pinta a casa selecinada de branco.\n"
                    "r <coordenada>: Torna a casa selecionada vazia.\n"
                    "v: Verifica se existem infrações no jogo atual e avisa das mesmas.\n"
                    "V: Revela o último tabuleiro.\n"
                    "V 'x': Permite ver os últimos 'x' tabuleiros. 'x' deve ser um número natural.\n"
                    "a: Ajuda realizando todas as jogadas necessárias na posição atual.\n"
                    "a b: Ajuda pintando de branco as casas à volta de casas riscadas.\n"
                    "a r: Ajuda riscando as casas na mesma linha ou coluna que casas brancas com a mesma letra.\n"
                    "a o: Ajuda pintando de branco as casas que se fossem riscadas não permitiam um caminho ortogonal entre todas as letras.\n"
                    "A: Ajuda realizando todas as jogadas necessárias na posição repetidamente até não haver mais nada a alterar.\n"
                    "R: Resolve o jogo atual.\n"
                    "X: Mostra a solução do jogo atual.\n"
                    "d: Desfaz a última jogada.\n"
                    "d 'x': Desfaz as últimas jogadas até ao tabuleiro 'x'. 'x' deve ser um número natural.\n"
                    "D: Apaga o histórico do jogo.\n"
                    "p: Revela a pontuação atual.\n"
                    "c: Permite criar um jogo novo.\n"
                    "s: Termina o jogo.\n"
                    "e: Explica o objetivo e as regras do jogo.\n"
                    "h: Lista todos os comandos do jogo.\n\n");

        // Avisa se foi dado um argumento
        else if (n == 1) fprintf (stderr, VERMELHO "\nErro:" RESET " O comando h não precisa de um argumento.\n\n");

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
            printf ("\n...\n\n");
        }

        // Avisa se foi dado um argumento
        else if (n == 1) fprintf (stderr, VERMELHO "\nErro:" RESET " O comando e não precisa de um argumento.\n\n");

        return true;
    }

    return false;
}