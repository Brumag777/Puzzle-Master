#include "../Puzzle.h"

// Termina o jogo
bool sair (char cmd, char *arg1, char *arg2, Info I) {

    // Para evitar warnings
    (void) arg2;

    // Verifica se foi invocado o comando
    if (cmd != 's') return false;

    // Verifica se o comando foi invocado corretamente
    int n = restricoesSair (arg1);

    // Foi dado um argumento
    if (n == 1) fprintf (stderr, VERMELHO "\nErro: " RESET "O comando " AZUL "s" RESET " não precisa de um argumento.\n\n");

    // O comando foi invocado corretamente
    else {

        // Sugere ao jogador que grave o jogo atual
        if (pretendeGravar (I)) fprintf (stderr, VERMELHO "\nErro: " RESET "Não foi possível ler o input.\n\n");

        // Realiza a lógica da função
        else logicaSair (I);
    }

    return true;
}



// Grava uma save de um jogo
bool gravar (char cmd, char *arg1, char *arg2, Info I) {

    // Para evitar warnings
    (void) arg2;

    // Verifica se foi invocado o comando
    if (cmd != 'g') return false;

    // Verifica se o comando foi invocado corretamente
    int n = restricoesGravar (arg1, I);

    // Não existe um tabuleiro para guardar
    if (n == 1) fprintf (stderr, VERMELHO "\nErro: " RESET "Não existe um jogo para guardar. Leia uma save para iniciar o jogo.\n\n");

    // O argumento não é natural
    else if (n == 2) fprintf (stderr, VERMELHO "\nErro: " RESET "O argumento deve ser natural.\n\n");

    // O argumento é excessivo
    else if (n == 3) fprintf (stderr, VERMELHO "\nErro: " RESET "O índice máximo das saves é 99.\n\n");

    // O comando foi invocado corretamente
    else {

        // Realiza a lógica do comando
        n = logicaGravar (arg1, I);

        // O jogo foi gravado corretamente
        if (n > 0) printf (VERDE "\nJogo gravado na save %d do jogo %d.\n\n" RESET, n, I -> nJogo);

        // O limite de saves já foi atingido
        else if (n == -1) fprintf (stderr, VERMELHO "\nErro: " RESET "O limite de saves já foi atingido.\n\n");
    }

    return true;
}



// Lê uma save de um jogo
bool ler (char cmd, char *arg1, char *arg2, Info I) {

    // Verifica se foi invocado o comando
    if (cmd != 'l') return false;

    // Verifica se o comando foi invocado corretamente
    int n = restricoesLer (arg1, arg2);

    // Não foi dado um argumento
    if (n == 1) fprintf (stderr, VERMELHO "\nErro: " RESET "O comando " AZUL "l" RESET " precisa de pelo menos um argumento.\n\n");

    // Os argumentos não são naturais
    else if (n == 2) fprintf (stderr, VERMELHO "\nErro: " RESET "Os argumentos devem ser naturais.\n\n");

    // Os argumentos são excessivos
    else if (n == 3) fprintf (stderr, VERMELHO "\nErro: " RESET "O índice máximo dos jogos e das saves é 99.\n\n");

    // O comando foi invocado corretamente
    else {
        
        // Sugere ao jogador que grave o jogo atual
        if (pretendeGravar (I)) fprintf (stderr, VERMELHO "\nErro: " RESET "Não foi possível ler o input.\n\n");

        // Realiza a lógica do comando
        else {
            n = logicaLer (arg1, arg2, I);

            // A save não existe
            if (n == 1) fprintf (stderr, VERMELHO "\nErro: " RESET "Essa save não existe.\n\n");

            // Não foi possível ler o ficheiro
            else if (n == 2) fprintf (stderr, VERMELHO "\nErro: " RESET "Não foi possível ler a save.\n\n");

            // A save guardada é inválida
            else if (n == 3) fprintf (stderr, VERMELHO "\nErro: " RESET "O jogo guardado é inválido.\n\n");

            // O jogo foi lido com sucesso
            else imprimeTabuleiro (I -> dL, I -> dC, I -> Tabuleiro, I -> nTabuleiro, 1);
        }
    }

    return true;
}



// Imprime a pontuação do jogador
bool imprimePont (char cmd, char *arg1, char *arg2, Info I) {

    // Para evitar warnings
    (void) arg2;

    // Verifica se foi invocado o comando
    if (cmd != 'p') return false;

    // Verifica se o comando foi invocado corretamente
    int n = restricoesImprimePont (arg1, I);

    // Foi dado um argumento
    if (n == 1) fprintf (stderr, VERMELHO "\nErro: " RESET "O comando " AZUL "p" RESET " não precisa de um argumento.\n\n");

    // Ainda não foi lido nenhum jogo
    else if (n == 2) fprintf (stderr, VERMELHO "\nErro: " RESET "Ainda não foi lido nenhum jogo.\n\n");

    // O comando foi invocado corretamente
    else {
        n = valorPont (I -> dL, I -> dC, I -> pont);

        // Imprime a pontuação
        if (n == 1) printf ("\nA pontuação atual é " VERDE "%d / %d" RESET ".\n\n", I -> pont, 3 * I -> dL * I -> dC);
        else if (n == 2) printf ("\nA pontuação atual é " AMARELO "%d / %d" RESET ".\n\n", I -> pont, 3 * I -> dL * I -> dC);
        else if (n == 3) printf ("\nA pontuação atual é " VERMELHO "%d / %d" RESET ".\n\n", I -> pont, 3 * I -> dL * I -> dC);
    }

    return true;
}



// Explica o jogo
bool explica (char cmd, char *arg1, char *arg2, Info I) {

    // Para evitar warnings
    (void) arg2;
    (void) I;

    // Verifica se foi invocado o comando
    if (cmd != 'e') return false;

    // Verifica as restrições do comando
    int n = restricoesExplica (arg1);

    // Foi dado um argumento
    if (n == 1) fprintf (stderr, VERMELHO "\nErro: " RESET "O comando " AZUL "e" RESET " não precisa de um argumento.\n\n");

    // O comando foi invocado corretamente
    else imprimeExplicacaoJogo ();

    return true;
}



// Explica os comandos do jogo
bool infoComandos (char cmd, char *arg1, char *arg2, Info I) {

    // Para evitar warnings
    (void) arg2;
    (void) I;

    // Verifica se foi invocado o comando
    if (cmd != 'h') return false;

    // O comando foi invocado sem argumento
    if (arg1 [0] == 0) imprimeListaComandos ();

    // O comando foi invocado com argumento
    else {
        int n = logicaInfoComandos (arg1);

        // O comando não existe
        if (n == -1) fprintf (stderr, VERMELHO "\nErro: " RESET "Esse comando não existe.\n\n");

        // Imprime a informação acerca do comando desejado
        else imprimeInfoComando (n);
    }

    return true;
}



// Cria um jogo novo
bool criarJogo (char cmd, char *arg1, char *arg2, Info I) {

    // Para evitar warnings
    (void) arg2;
    (void) I;

    // Verifica se foi invocado o comando
    if (cmd != 'c') return false;

    // Verifica as restrições do comando
    int n = restricoesCriarJogo (arg1);

    // Foi dado um argumento
    if (n == 1) fprintf (stderr, VERMELHO "\nErro: " RESET "O comando " AZUL "c" RESET " não precisa de um argumento.\n\n");

    // O comando foi invocado corretamente
    else {

        // Cria o jogo
        n = criaJogo ();

        // Limpa o stdin
        int ch;
        while ((ch = getchar ()) != '\n' && ch != EOF);

        // Caso de sucesso na criação do jogo
        if (n >= 0) printf (VERDE "\nJogo %d criado com sucesso.\n\n" RESET, n);

        // Não foi possível ler o input
        else if (n == -1) fprintf (stderr, VERMELHO "\nErro: " RESET "Não foi possível ler o input.\n\n");

        // As dimensões do tabuleiro são inválidas
        else if (n == -2) fprintf (stderr, VERMELHO "\nErro: " RESET "As dimensões do tabuleiro são inválidas.\n\n");

        // O jogo é inválido
        else if (n == -3) fprintf (stderr, VERMELHO "\nErro: " RESET "O jogo é inválido.\n\n");

        // O limite de jogos já foi atingido
        else if (n == -4) fprintf (stderr, VERMELHO "\nErro: " RESET "O limite de jogos já foi atingido.\n\n");

        // Não foi possível criar o jogo
        else if (n == -5) fprintf (stderr, VERMELHO "\nErro: " RESET "Não foi possível criar o jogo.\n\n");
    }

    return true;
}



// Elimina uma save ou um jogo
bool eliminarJogo (char cmd, char *arg1, char *arg2, Info I) {

    // Para evitar warnings
    (void) I;

    // Verifica se foi invocado o comando
    if (cmd != 'E') return false;

    // Verifica as restrições do comando
    int n = restricoesEliminarJogo (arg1, arg2);

    // Não foi dado um argumento
    if (n == 1) fprintf (stderr, VERMELHO "\nErro: " RESET "O comando " AZUL "E" RESET " precisa de pelo menos um argumento.\n\n");

    // Os argumentos não são naturais
    else if (n == 2) fprintf (stderr, VERMELHO "\nErro: " RESET "Os argumentos devem ser naturais.\n\n");

    // O jogador está a tentar os jogos principais
    else if (n == 3) fprintf (stderr, VERMELHO "\nErro: " RESET "Os jogos principais (1 a 4) não podem ser eliminados.\n\n");

    // Os argumentos são excessivos
    else if (n == 4) fprintf (stderr, VERMELHO "\nErro: " RESET "O índice máximo dos jogos e das saves é 99.\n\n");

    // O comando foi invocado corretamente
    else {

        // Pergunta ao jogador se pretende proceder
        if (pretendeProceder ()) {

            // Elimina o jogo
            n = eliminaJS (arg1, arg2);

            // Caso de sucesso na eliminação do jogo ou da save
            if (n == 0) printf (VERDE "\nJogo ou save eliminado(a) com sucesso.\n\n" RESET);

            // Não foi possível eliminar os ficheiros
            else if (n == 1) fprintf (stderr, VERMELHO "\nErro: " RESET "Não foi possível eliminar o jogo ou a save.\n\n");
        }
    }

    return true;
}



// Indica todos os jogos e as respetivas saves que estão guardados
bool indicaJogos (char cmd, char *arg1, char *arg2, Info I) {

    // Para evitar warnings
    (void) arg2;
    (void) I;

    // Verifica se foi invocado o comando
    if (cmd != 'j') return false;

    // Verifica as restrições do comando
    int n = restricoesIndicaJogos (arg1);

    // Foi dado um argumento
    if (n == 1) fprintf (stderr, VERMELHO "\nErro: " RESET "O comando " AZUL "j" RESET " não precisa de um argumento.\n\n");

    // O comando foi invocado corretamente
    else imprimeJogos ();

    return true;
}



// Pinta uma casa
bool pintarCasa (char cmd, char *arg1, char *arg2, Info I) {

    // Para evitar warnings
    (void) arg2;

    // Verifica se foi invocado o comando
    if (cmd != 'b') return false;

    // Verifica as restrições do comando
    int n = restricoesMudarCasa (arg1, I);

    // Não foi dado um argumento
    if (n == 1) fprintf (stderr, VERMELHO "\nErro: " RESET "O comando " AZUL "b" RESET " precisa de um argumento.\n\n");

    // Ainda não foi lido um jogo
    else if (n == 2) fprintf (stderr, VERMELHO "\nErro: " RESET "Ainda não foi aberto um jogo. Leia uma save para iniciar o jogo.\n\n");

    // O argumento é inválido
    else if (n == 3) fprintf (stderr, VERMELHO "\nErro: " RESET "O argumento deve ser uma coordenada.\n\n");

    // A coordenada é inválida
    else if (n == 4) fprintf (stderr, VERMELHO "\nErro: " RESET "A coordenada é inválida.\n\n");

    // A casa já está pintada de branco
    else if (n == 5) fprintf (stderr, VERMELHO "\nErro: " RESET "A casa já está pintada de branco.\n\n");

    // A casa já está riscada
    else if (n == 6) fprintf (stderr, VERMELHO "\nErro: " RESET "A casa já está riscada.\n\n");

    // Realiza a lógica do comando
    else {
        logicaPintarCasa (arg1, I);

        // Imprime o tabuleiro resultante
        imprimeTabuleiro (I -> dL, I -> dC, I -> Tabuleiro, I -> nTabuleiro, 0);

        // Se o jogo estiver terminado, indica se o jogador ganhou
        putchar ('\n');
        if (testeJogo (I)) imprimeMensagemFim (I);
    }

    return true;
}



// Risca uma casa
bool riscarCasa (char cmd, char *arg1, char *arg2, Info I) {

    // Para evitar warnings
    (void) arg2;

    // Verifica se foi invocado o comando
    if (cmd != 'r') return false;

    // Verifica as restrições do comando
    int n = restricoesMudarCasa (arg1, I);

    // Não foi dado um argumento
    if (n == 1) fprintf (stderr, VERMELHO "\nErro: " RESET "O comando " AZUL "r" RESET "precisa de um argumento.\n\n");

    // Ainda não foi lido um jogo
    else if (n == 2) fprintf (stderr, VERMELHO "\nErro: " RESET "Ainda não foi aberto um jogo. Leia uma save para iniciar o jogo.\n\n");

    // O argumento é inválido
    else if (n == 3) fprintf (stderr, VERMELHO "\nErro: " RESET "O argumento deve ser uma coordenada.\n\n");

    // A coordenada é inválida
    else if (n == 4) fprintf (stderr, VERMELHO "\nErro: " RESET "A coordenada é inválida.\n\n");

    // A casa já está pintada de branco
    else if (n == 5) fprintf (stderr, VERMELHO "\nErro: " RESET "A casa já está pintada de branco.\n\n");

    // A casa já está riscada
    else if (n == 6) fprintf (stderr, VERMELHO "\nErro: " RESET "A casa já está riscada.\n\n");

    // Realiza a lógica do comando
    else {
        logicaRiscarCasa (arg1, I);

        // Imprime o tabuleiro resultante
        imprimeTabuleiro (I -> dL, I -> dC, I -> Tabuleiro, I -> nTabuleiro, 0);

        // Se o jogo estiver terminado, indica se o jogador ganhou
        putchar ('\n');
        if (testeJogo (I)) imprimeMensagemFim (I);
    }

    return true;
}



// Imprime o(s) último(s) tabuleiro(s)
bool visualizarHistorico (char cmd, char *arg1, char *arg2, Info I) {

    // Para evitar warnings
    (void) arg2;

    // Verifica se foi invocado o comando
    if (cmd != 'V') return false;

    // Verifica as restrições do comando
    int n = restricoesVisualizarHistorico (arg1, I);

    // Ainda não foi aberto um jogo
    if (n == 1) fprintf (stderr, VERMELHO "\nErro: " RESET "Ainda não foi aberto um jogo. Leia uma save para iniciar o jogo.\n\n");

    // O argumento não é natural
    else if (n == 2) fprintf (stderr, VERMELHO "\nErro: " RESET "O argumento deve ser um natural.\n\n");

    // O argumento é excessivo
    else if (n == 3) fprintf (stderr, VERMELHO "\nErro: " RESET "Não existem tabuleiros suficientes para imprimir.\n\n");

    // O comando foi invocado corretamente
    else {

        // Número de tabuleiro a imprimir
        int nTabs = 1;

        // Define o número de tabuleiros a imprimir como o argumento caso este exista
        if (arg1 [0]) nTabs = atoi (arg1);

        // Imprime os tabuleiros
        visualizaUltimosTabuleiros (I, nTabs, 1);
        putchar ('\n');
    }

    return true;
}



// Verifica se existem infrações no tabuleiro
bool verifica (char cmd, char *arg1, char *arg2, Info I) {

    // Para evitar warnings
    (void) arg2;

    // Verifica se foi invocado o comando
    if (cmd != 'v') return false;

    // Verifica as restrições do comando
    int n = restricoesVerifica (arg1, I);

    // Foi dado um argumento
    if (n == 1) fprintf (stderr, VERMELHO "\nErro: " RESET "O comando " AZUL "v" RESET " não precisa de um argumento.\n\n");

    // Ainda não foi lido um jogo
    else if (n == 2) fprintf (stderr, VERMELHO "\nErro: " RESET "Ainda não foi aberto um jogo. Leia uma save para iniciar o jogo.\n\n");

    // O comando foi invocado corretamente
    else {

        // Avança uma linha
        putchar ('\n');

        // Realiza a lógica do comando
        n = logicaVerifica (I);

        // Não existe nenhuma infração
        if (n) printf (VERDE "Não há nenhuma infração.\n" RESET);

        // Avança uma linha
        putchar ('\n');
    }

    return true;
}



// Ajuda realizando jogadas necessárias na posição
bool ajuda (char cmd, char *arg1, char *arg2, Info I) {

    // Para evitar warnings
    (void) arg2;

    // Verifica se foi invocado o comando
    if (cmd != 'a') return false;

    // Verifica as restrições do comando
    int n = restricoesAjuda (arg1, I);

    // Ainda não foi lido um jogo
    if (n == 1) fprintf (stderr, VERMELHO "\nErro: " RESET "Ainda não foi aberto um jogo. Leia uma save para iniciar o jogo.\n\n");

    // O argumento é inválido
    else if (n == 2) fprintf (stderr, VERMELHO "\nErro: " RESET "O argumento é inválido.\n\n");

    // O comando foi invocado corretamente
    else {

        // Realiza a lógica do comando
        n = logicaAjuda (arg1, I);

        // Não há nada a alterar
        if (n == 1) printf ("\nNão há nada a alterar.\n\n");

        // O tabuleiro possui infrações
        else if (n == 2) printf (VERMELHO "\nO jogo possui infrações.\n\n" RESET);

        // Caso de sucesso da execução do comando
        else {
            // Imprime o tabuleiro resultante
            imprimeTabuleiro (I -> dL, I -> dC, I -> Tabuleiro, I -> nTabuleiro, 0);

            // Garante que a pontuação não é negativa
            if (I -> pont < 0) I -> pont = 0;

            // Se o jogo estiver terminado, indica se o jogador ganhou
            putchar ('\n');
            if (testeJogo (I)) imprimeMensagemFim (I);
        }
    }

    return true;
}



// Ajuda realizando jogadas necessárias na posição repetidamente
bool ajudaRep (char cmd, char *arg1, char *arg2, Info I) {

    // Para evitar warnings
    (void) arg2;

    // Verifica se o comando foi invocado
    if (cmd != 'A') return false;

    // Verifica as restrições do comando
    int n = restricoesAjudaRep (arg1, I);

    // Foi dado um argumento
    if (n == 1) fprintf (stderr, VERMELHO "\nErro: " RESET "O comando " AZUL "A" RESET " não precisa de um argumento.\n\n");

    // Ainda não foi lido um jogo
    else if (n == 2) fprintf (stderr, VERMELHO "\nErro: " RESET "Ainda não foi aberto um jogo. Leia uma save para iniciar o jogo.\n\n");

    // O comando foi invocado corretamente
    else {

        // Realiza a lógica do comando
        n = logicaAjudaRep (I);

        // Não há nada a alterar
        if (n == 1) printf ("\nNão há nada a alterar.\n\n");

        // O tabuleiro possui infrações
        else if (n == 2) printf (VERMELHO "\nO jogo possui infrações.\n\n" RESET);

        // Caso de sucesso da execução do comando
        else {
            // Imprime o tabuleiro resultante
            imprimeTabuleiro (I -> dL, I -> dC, I -> Tabuleiro, I -> nTabuleiro, 0);

            // Garante que a pontuação não é negativa
            if (I -> pont < 0) I -> pont = 0;

            // Se o jogo estiver terminado, indica se o jogador ganhou
            putchar ('\n');
            if (testeJogo (I)) imprimeMensagemFim (I);
        }
    }

    return true;
}



// Desfaz a(s) última(s) jogada(s)
bool desfazerJogadas (char cmd, char *arg1, char *arg2, Info I) {

    // Para evitar warnings
    (void) arg2;

    // Verifica se foi invocado o comando
    if (cmd != 'd') return false;

    // Verifica as restrições do comando
    int n = restricoesDesfazerJogadas (arg1, I);

    // Ainda não foi lido um jogo
    if (n == 1) fprintf (stderr, VERMELHO "\nErro: " RESET "Ainda não foi aberto um jogo. Leia uma save para iniciar o jogo.\n\n");

    // Não há nenhuma jogada para desfazer
    else if (n == 2) fprintf (stderr, VERMELHO "\nErro: " RESET "Não há nenhuma jogada para desfazer.\n\n");

    // O argumento não é natural
    else if (n == 3) fprintf (stderr, VERMELHO "\nErro: " RESET "O argumento deve ser um natural.\n\n");

    // O tabuleiro selecionado é o atual
    else if (n == 4) fprintf (stderr, VERMELHO "\nErro: " RESET "Esse é o tabuleiro atual.\n\n");

    // O tabuleiro selecionado não existe
    else if (n == 5) fprintf (stderr, VERMELHO "\nErro: " RESET "Esse tabuleiro não existe.\n\n");

    // O comando foi invocado corretamente
    else {

        // Pergunta ao jogador se pretende proceder
        if (pretendeProceder ()) {

            // Realiza a lógica da função
            logicaDesfazerJogadas (arg1, I);

            // Imprime o tabuleiro
            imprimeTabuleiro (I -> dL, I -> dC, I -> Tabuleiro, I -> nTabuleiro, 1);

            // Garante que a pontuação não é negativa
            if (I -> pont < 0) I -> pont = 0;
        }
    }

    return true;
}



// Resolve o jogo
bool resolveJogo (char cmd, char *arg1, char *arg2, Info I) {
    
    // Para evitar warnings
    (void) arg2;

    // Verifica se foi invocado o comando
    if (cmd != 'R') return false;

    // Verifica as restrições do comando
    int n = restricoesSolucaoJogo (arg1, I);

    // Foi dado um argumento
    if (n == 1) fprintf (stderr, VERMELHO "\nErro: " RESET "O comando " AZUL "R" RESET " não precisa de um argumento.\n\n");

    // Ainda não foi lido um jogo
    else if (n == 2) fprintf (stderr, VERMELHO "\nErro: " RESET "Ainda não foi aberto um jogo. Leia uma save para iniciar o jogo.\n\n");

    // O comando foi invocado corretamente
    else {

        // Armazena a pontuação
        int p = I -> pont;

        // Realiza a lógica do comando
        n = logicaSolucaoJogo (I, 1);

        // Não foi possível resolver o jogo
        if (n == 1) {
            fprintf (stderr, VERMELHO "\nAviso: " RESET "Não é possível resolver o jogo atual.\n\n");
            I -> pont = p;
        }

        // Resolveu o jogo
        else {
            // Imprime o tabuleiro
            imprimeTabuleiro (I -> dL, I -> dC, I -> Tabuleiro, I -> nTabuleiro, 1);

            // Adiciona um penalty por invocar o comando 'R'
            I -> pont = 0;
        }
    }

    return true;
}



// Mostra a solução do jogo
bool mostrarSolucao (char cmd, char *arg1, char *arg2, Info I) {

    // Para evitar warnings
    (void) arg2;

    // Verifica se o comando foi invocado
    if (cmd != 'X') return false;

    // Verifica as restrições do comando
    int n = restricoesSolucaoJogo (arg1, I);

    // Foi dado um argumento
    if (n == 1) fprintf (stderr, VERMELHO "\nErro: " RESET "O comando " AZUL "X" RESET " não precisa de um argumento.\n\n");

    // Ainda não foi lido um jogo
    else if (n == 2) fprintf (stderr, VERMELHO "\nErro: " RESET "Ainda não foi aberto um jogo. Leia uma save para iniciar o jogo.\n\n");

    // O comando foi invocado corretamente
    else {

        // Armazena a pontuação
        int p = I -> pont;

        // Realiza a lógica do comando
        n = logicaSolucaoJogo (I, 0);

        // Não foi possível resolver o jogo
        if (n == 1) {
            fprintf (stderr, VERMELHO "\nAviso: " RESET "O jogo atual não possui solução.\n\n");
            I -> pont = p;
        }

        // Resolveu o jogo
        else I -> pont = 0;
    }

    return true;
}



// Dá uma dica ao jogador
bool dica (char cmd, char *arg1, char *arg2, Info I) {

    // Para evitar warnings
    (void) arg2;

    // Verifica se foi invocado o comando
    if (cmd != 'D') return false;

    // Verifica as restrições do comando
    int n = restricoesMudarCasa (arg1, I);

    // Não foi dado um argumento
    if (n == 1) fprintf (stderr, VERMELHO "\nErro: " RESET "O comando " AZUL "D" RESET " precisa de um argumento.\n\n");

    // Ainda não foi lido um jogo
    else if (n == 2) fprintf (stderr, VERMELHO "\nErro: " RESET "Ainda não foi aberto um jogo. Leia uma save para iniciar o jogo.\n\n");

    // O argumento é inválido
    else if (n == 3) fprintf (stderr, VERMELHO "\nErro: " RESET "O argumento deve ser uma coordenada.\n\n");

    // A coordenada é inválida
    else if (n == 4) fprintf (stderr, VERMELHO "\nErro: " RESET "A coordenada é inválida.\n\n");

    // A casa já está pintada de branco
    else if (n == 5) fprintf (stderr, VERMELHO "\nErro: " RESET "A casa já está pintada de branco.\n\n");

    // A casa já está riscada
    else if (n == 6) fprintf (stderr, VERMELHO "\nErro: " RESET "A casa já está riscada.\n\n");

    // O comando foi invocado corretamente
    else {

        // Armazena a pontuação
        int p = I -> pont;

        // Realiza a lógica do comando
        n = logicaDica (arg1, I);

        // Não foi possível resolver o jogo
        if (n == 1) {
            fprintf (stderr, VERMELHO "\nAviso: " RESET "O jogo atual não possui solução.\n\n");
            I -> pont = p;
        }

        // Encontrou a dica
        else {
            // Imprime o tabuleiro
            imprimeTabuleiro (I -> dL, I -> dC, I -> Tabuleiro, I -> nTabuleiro, 1);

            // Contalibiliza na pontuação
            p -= I -> dL * I -> dC / 2;
            if (p < 0) I -> pont = 0;
            else I -> pont = p;
        }
    }

    return true;
}