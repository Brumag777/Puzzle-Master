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
            imprimeTabuleiro (I -> dL, I -> dC, I -> Tabuleiro, I -> nTabuleiro, 1);

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



// Revela o tabuleiro armazenado num ficheiro
bool preview (char cmd, char *arg, Info I) {

    // Para evitar warnings
    (void) I;

    if (cmd == 'p') {

        // Realiza a lógica da comando 'p'
        int n = logicaPreview (arg);

        // Avisa se não foi dado um argumento
        if (n == 1) fprintf (stderr, "\nErro: O comando p precisa de um argumento (nome do ficheiro).\n\n");

        // Avisa se o ficheiro não foi aberto corretamente
        else if (n == 2) fprintf (stderr, "\nErro: Não foi possível abrir o ficheiro.\n\n");

        // Avisa se houve erros a ler o ficheiro
        else if (n == 3) fprintf (stderr, "\nErro: Não foi possível ler o ficheiro.\n\n");

        // Avisa se o tabuleiro do ficheiro lido é inválido
        else if (n == 4) fprintf (stderr, "\nErro: O tabuleiro não é válido.\n\n");

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
            imprimeTabuleiro (I -> dL, I -> dC, I -> Tabuleiro, I -> nTabuleiro, 1);

            // Se o jogo estiver terminado, indica se o jogador ganhou
            if (testeJogo (I)) printf ("Parabéns! Conseguiste resolver o puzzle em %d jogadas.\n\n", I -> nJogadas);
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
            imprimeTabuleiro (I -> dL, I -> dC, I -> Tabuleiro, I -> nTabuleiro, 1);

            // Se o jogo estiver terminado, indica se o jogador ganhou
            if (testeJogo (I)) printf ("Parabéns! Conseguiste resolver o puzzle em %d jogadas.\n\n", I -> nJogadas);
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



// Desfaz a últimas jogadas
bool desfazerJogada (char cmd, char *arg, Info I) {

    if (cmd == 'd') {

        // Realiza a lógica do comando 'd'
        int n = logicaDesfazerJogada (arg, I);

        // Caso de sucesso da função
        if (n == 0) imprimeTabuleiro (I -> dL, I -> dC, I -> Tabuleiro, I -> nTabuleiro, 1);

        // Avisa se não há um tabuleiro anterior
        else if (n == 1) fprintf (stderr, "\nErro: Não existem tabuleiros para desfazer.\n\n");

        // Avisa se o argumento não é um número natural
        else if (n == 2) fprintf (stderr, "\nErro: O argumento deve ser um número natural.\n\n");

        // Avisa se foi selecionado o tabuleiro atual
        else if (n == 3) fprintf (stderr, "\nErro: Esse é o tabuleiro atual.\n\n");

        // Avisa se não existe o tabuleiro desejado
        else if (n == 4) fprintf (stderr, "\nErro: O argumento é maior que o número de tabuleiros (%d).\n\n", I -> nTabuleiro);

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
        if (n > 0) {
            visualizaUltimosTabuleiros (I, n, 1);
            putchar ('\n');
        }

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



// Verifica se existem infrações no tabuleiro
bool verifica (char cmd, char *arg, Info I) {

    if (cmd == 'v') {

        // Realiza a lógica do comando 'v'
        int n = logicaVerifica (arg, I);

        // Casos de sucesso da função
        if (n == 0) putchar ('\n');
        if (n == 1) {
            printf ("Não há nenhuma infração.\n");
            putchar ('\n');
        }

        // Avisa se foi dado um argumento
        else if (n == -1) fprintf (stderr, "\nErro: O comando v não precisa de um argumento.\n\n");

        return true;
    }

    return false;
}



// Ajuda o jogador realizando jogadas 'obrigatórias' na posição
bool ajuda (char cmd, char *arg, Info I) {

    if (cmd == 'a') {

        // Realiza a lógica do comando 'a'
        int n = logicaAjuda (arg, I);

        // Caso de sucesso da função
        if (n == 0) {
            // Imprime o tabuleiro resultante
            imprimeTabuleiro (I -> dL, I -> dC, I -> Tabuleiro, I -> nTabuleiro, 1);

            // Se o jogo estiver terminado, indica se o jogador ganhou
            if (testeJogo (I)) printf ("Parabéns! Conseguiste resolver o puzzle em %d jogadas.\n\n", I -> nJogadas);
        }

        // Avisa se foi dado um argumento
        else if (n == 1) fprintf (stderr, "\nErro: O argumento é inválido.\n\n");

        // Avisa se não há nada a alterar
        else if (n == 2) printf ("\nNão há nada a alterar.\n\n");

        // Avisa se o tabuleiro possui infrações
        else if (n == 3) printf ("\nO tabuleiro possui infrações.\n\n");

        return true;
    }

    return false;
}



// Ajuda o jogador realizando jogadas 'obrigatórias' repetidamente até não haver nada a alterar
bool ajudaRep (char cmd, char *arg, Info I) {

    if (cmd == 'A') {

        // Realiza a lógica do comando 'A'
        int n = logicaAjudaRep (arg, I);

        // Caso de sucesso da função
        if (n == 0) {
            // Imprime o tabuleiro resultante
            imprimeTabuleiro (I -> dL, I -> dC, I -> Tabuleiro, I -> nTabuleiro, 1);

            // Se o jogo estiver terminado, indica se o jogador ganhou
            if (testeJogo (I)) printf ("Parabéns! Conseguiste resolver o puzzle em %d jogadas.\n\n", I -> nJogadas);
        }

        // Avisa se foi dado um argumento
        else if (n == 1) fprintf (stderr, "\nErro: O comando A não precisa de um argumento.\n\n");

        // Avisa se não há nada a alterar
        else if (n == 2) printf ("\nNão há nada a alterar.\n\n");

        // Avisa se o tabuleiro possui infrações
        else if (n == 3) printf ("\nO tabuleiro possui infrações.\n\n");

        return true;
    }

    return false;
}



// Resolve o jogo automaticamente
bool resolveJogo (char cmd, char *arg, Info I) {

    if (cmd == 'R') {

        // Realiza a lógica do comando 'R'
        int n = logicaResolveJogo (arg, I, 1);

        // Caso de sucesso da função
        if (n == 0) imprimeTabuleiro (I -> dL, I -> dC, I -> Tabuleiro, I -> nTabuleiro, 1);

        // Avisa se foi dado um argumento
        else if (n == 1) fprintf (stderr, "\nErro: O comando R não precisa de um argumento.\n\n");

        // Avisa se não há um jogo para resolver
        else if (n == 2) fprintf (stderr, "\nErro: Não há um jogo para resolver. Use o comando l para iniciar um jogo.\n\n");

        // Avisa se não é possível resolver o jogo
        else if (n == 3) fprintf (stderr, "\nAviso: Não é possível resolver o jogo atual.\n\n");

        // Adiciona um penalty por invocar o comando 'R'
        I -> nJogadas += I -> dL * I -> dL * I -> dC * I -> dC;

        return true;
    }

    return false;
}



// Mostra a solução do jogo (caso exista)
bool mostrarSolucao (char cmd, char *arg, Info I) {

    if (cmd == 'X') {

        // Realiza a lógica do comando 'X'
        int n = logicaResolveJogo (arg, I, 0);

        // Avisa se foi dado um argumento
        if (n == 1) fprintf (stderr, "\nErro: O comando X não precisa de um argumento.\n\n");

        // Avisa se não há um jogo para encontar solução
        if (n == 2) fprintf (stderr, "\nErro: Não há um jogo para revelar a solução. Use o comando l para iniciar um jogo.\n\n");

        // Avisa se não é possível resolver o jogo
        else if (n == 3) fprintf (stderr, "\nAviso: O jogo atual não possui solução.\n\n");

        return true;
    }

    return false;
}



// Apaga o histoŕico de jogadas
bool apagaHistorico (char cmd, char *arg, Info I) {

    if (cmd == 'D') {

        // Realiza a lógica do comando 'D'
        int n = logicaApagaHistorico (arg, I);

        // Caso de sucesso da função
        if (n == 0) printf ("\nO histórico foi apagado.\n\n");

        // Avisa se foi dado um argumento
        else if (n == 1) fprintf (stderr, "\nErro: O comando D não precisa de um argumento.\n\n");

        // Avisa se não há nada do histórico
        else if (n == 2) fprintf (stderr, "\nErro: O histórico já está vazio.\n\n");

        return true;
    }

    return false;
}



// Mostra o número de jogadas atual
bool imprimeNJogadas (char cmd, char *arg, Info I) {

    if (cmd == 'j') {
        
        // Realiza a lógica do comando 'j'
        int n = logicaImprimeNJogadas (arg, I);

        // Caso de sucesso da função
        if (n == 0) printf ("\nO número de jogadas atual é %d.\n\n", I -> nJogadas);

        // Avisa se foi dado um argumento
        else if (n == 1) fprintf (stderr, "\nErro: O comando j não precisa de um argumento.\n\n");

        // Avisa se ainda não foi lido um ficheiro
        else if (n == 2) fprintf (stderr, "\nErro: Ainda não foi lido nenhum ficheiro.\n\n");

        return true;
    }

    return false;
}



// Lista os comandos do jogo
bool listarComandos (char cmd, char *arg, Info I) {

    if (cmd == 'h') {

        // Realiza a lógica do comando 'h'
        int n = logicaListarInfo (arg);

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
                    "D: Apaga o histórico do jogo.\n"
                    "j: Mostra o número de jogadas atual.\n"
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



// Explica o objetivo e as regras do jogo
bool explicaJogo (char cmd, char *arg, Info I) {

    // Para evitar warnings
    (void) I;

    if (cmd == 'e') {

        // Realiza a lógica do comando 'e'
        int n = logicaListarInfo (arg);

        // Caso de sucesso da função
        if (n == 0) {
            // Explica o jogo
            printf ("\nO objetivo do jogo é...\n\n");
        }

        // Avisa se foi dado um argumento
        else if (n == 1) fprintf (stderr, "\nErro: O comando h não precisa de um argumento.\n\n");

        return true;
    }

    return false;
}