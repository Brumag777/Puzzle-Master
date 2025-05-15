#include "../Puzzle.h"

// Imprime um tabuleiro
void imprimeTabuleiro (int dL, int dC, char **Tabuleiro, int nTabuleiro, int flag) {

    // Imprime o número do tabuleiro (ou 'S' caso seja a solução do jogo)
    if (nTabuleiro) { 
        if      (nTabuleiro < 9)  printf ("\n%d   ", nTabuleiro);
        else if (nTabuleiro < 99) printf ("\n%d  ", nTabuleiro);
        else                      printf ("\n%d ", nTabuleiro);
    }
    else printf ("\nA solução do jogo atual é a seguinte:\n\nS   ");

    // Imprime o índice das colunas
    if (dL > 9) putchar (' ');
    for (int j = 0; j < dC; j++) printf ("%c ", 'a' + j);
    printf ("\n    ");

    // Imprime os '-' em baixo dos índices das colunas
    if (dL > 9) putchar (' ');
    for (int j = 0; j < dC; j++) printf ("- ");
    putchar ('\n');

    // Imprime o tabuleiro linha a linha
    for (int i = 0; i < dL; i++) {

        // Imprime o índice das linhas
        if (i < 9 && dL > 9) printf ("%2d | ", i + 1);
        else printf ("%d | ", i + 1);

        // Imprime a linha atual
        for (int j = 0; j < dC; j++)
            if (eMinuscula (Tabuleiro [i][j])) printf (CINZENTO "%c " RESET, Tabuleiro [i][j]);
            else printf ("%c ", Tabuleiro [i][j]);
        
        // Avança para a linha seguinte
        putchar ('\n');
    }

    if (flag) putchar ('\n');
}



// Imprime um tabuleiro destacando as infrações
void destacaInfracoes (int dL, int dC, char **Tabuleiro, int TabInfracoes [dL][dC], int eSolucao) {

    if (eSolucao) printf ("\nA solução do jogo atual é a seguinte:\n\nS   ");
    else printf ("\nI   ");

    // Imprime o índice das colunas
    if (dL > 9) putchar (' ');
    for (int j = 0; j < dC; j++) printf ("%c ", 'a' + j);
    printf ("\n    ");

    // Imprime os '-' em baixo dos índices das colunas
    if (dL > 9) putchar (' ');
    for (int j = 0; j < dC; j++) printf ("- ");
    putchar ('\n');

    // Imprime o tabuleiro linha a linha
    for (int i = 0; i < dL; i++) {

        // Imprime o índice das linhas
        if (i < 9 && dL > 9) printf ("%2d | ", i + 1);
        else printf ("%d | ", i + 1);

        // Imprime a linha atual
        for (int j = 0; j < dC; j++) {
            if (TabInfracoes [i][j] == 2) printf (CINZENTO "%c " RESET, Tabuleiro [i][j]);
            else if (TabInfracoes [i][j] == 1) printf (VERMELHO "%c " RESET, Tabuleiro [i][j]);
            else printf (VERDE "%c " RESET, Tabuleiro [i][j]);
        }
        
        // Avança para a linha seguinte
        putchar ('\n');
    }

    if (eSolucao) putchar ('\n');
}



// Imprime os jogos e as respetivas saves existentes
void imprimeSavesJogos (int savesJogos [100][100], int nSavesJogos [100]) {

    // Avança uma linha
    putchar ('\n');

    // Percorre os jogos
    for (int i = 1; i < 100; i++) {

        // Se existir este jogo, imprime as suas saves
        if (nSavesJogos [i]) {
            printf("O jogo %d possui a(s) seguinte(s) save(s): ", i);

            // Inteiro que indica se é a primeira save ou não
            int primeira = 1;

            // Procura as saves do jogo
            for (int j = 0; j < 100; j++) {
                if (savesJogos[i][j]) {
                    if (primeira == 0) printf(", ");
                    if (j == 0) printf ("Original (0)");
                    else printf("%d", j);
                    primeira = 0;
                }
            }

            // Passa para a linha seguinte
            putchar ('\n');
        }
    }

    // Avança uma linha
    putchar ('\n');
}



// Imprime a mensagem inicial do jogo
void imprimeMensagemInicial () {
    printf ("\n________________________________________________________________________________________________________________________________________________________________________________________________________\n\n"
            "\n                                         ██████╗ ██╗   ██╗███████╗███████╗██╗     ███████╗    ███╗   ███╗ █████╗ ███████╗████████╗███████╗██████╗ "
            "\n                                         ██╔══██╗██║   ██║╚══███╔╝╚══███╔╝██║     ██╔════╝    ████╗ ████║██╔══██╗██╔════╝╚══██╔══╝██╔════╝██╔══██╗"
            "\n                                         ██████╔╝██║   ██║  ███╔╝   ███╔╝ ██║     █████╗      ██╔████╔██║███████║███████╗   ██║   █████╗  ██████╔╝"
            "\n                                         ██╔═══╝ ██║   ██║ ███╔╝   ███╔╝  ██║     ██╔══╝      ██║╚██╔╝██║██╔══██║╚════██║   ██║   ██╔══╝  ██╔══██╗"
            "\n                                         ██║     ╚██████╔╝███████╗███████╗███████╗███████╗    ██║ ╚═╝ ██║██║  ██║███████║   ██║   ███████╗██║  ██║"
            "\n                                         ╚═╝      ╚═════╝ ╚══════╝╚══════╝╚══════╝╚══════╝    ╚═╝     ╚═╝╚═╝  ╚═╝╚══════╝   ╚═╝   ╚══════╝╚═╝  ╚═╝"
            "\n\n                                                                       Pressione h para saber a lista de comandos.\n"
            "\n________________________________________________________________________________________________________________________________________________________________________________________________________\n\n");
}



// Imprime a lista de comandos do jogo
void imprimeListaComandos () {
    printf ("\nOs comandos do jogo são:\n\n"
            "g: Grava o jogo atual numa nova save.\n"
            "l: Abre um jogo previamente guardado numa save.\n"
            "b: Pinta uma casa de branco.\n"
            "r: Risca uma casa.\n"
            "v: Verifica se existem infrações no jogo.\n"
            "V: Revela o(s) último(s) tabuleiro(s).\n"
            "a: Ajuda realizando jogadas necessárias.\n"
            "A: Ajuda realizando jogadas necessárias repetidamente.\n"
            "R: Resolve o jogo.\n"
            "X: Mostra a solução do jogo.\n"
            "d: Desfaz jogadas.\n"
            "D: Apaga o histórico do jogo.\n"
            "p: Revela a pontuação do jogo.\n"
            "c: Permite criar um jogo novo.\n"
            "E: Permite eliminar jogos previamente guardados.\n"
            "s: Termina o jogo.\n"
            "e: Explica o objetivo e as regras do jogo.\n"
            "j: Indica todos os jogos guardados e as respetivas saves.\n"
            "h: Indica e explica comandos do jogo.\n\n"
            "Se pretende saber mais sobre algum comando, use o comando 'h' dando como argumento o comando desejado.\n\n");
}



// Imprime informação acerca de um comando
void imprimeInfoComando (char c) {
    if      (c == 's') imprimeInfoCs ();
    else if (c == 'l') imprimeInfoCl ();
    else if (c == 'c') imprimeInfoCc ();
    else if (c == 'E') imprimeInfoCE ();
    else if (c == 'h') imprimeInfoCh ();
    else if (c == 'b') imprimeInfoCb ();
    else if (c == 'r') imprimeInfoCr ();
    else if (c == 'V') imprimeInfoCV ();
    else if (c == 'g') imprimeInfoCg ();
    else if (c == 'v') imprimeInfoCv ();
    else if (c == 'j') imprimeInfoCj ();
    else if (c == 'a') imprimeInfoCa ();
    else if (c == 'A') imprimeInfoCA ();
    else if (c == 'R') imprimeInfoCR ();
    else if (c == 'p') imprimeInfoCp ();
    else if (c == 'd') imprimeInfoCd ();
    else if (c == 'D') imprimeInfoCD ();
    else if (c == 'e') imprimeInfoCe ();
    else               imprimeInfoCX ();
}



// Explica o comando 's'
void imprimeInfoCs () {
    printf ("\nO comando 's' é utilizado para sair do jogo. Ao ser utilizado, o jogo que está aberto será perdido.\n\n");
}



// Explica o comando 'l'
void imprimeInfoCl () {
    printf ("\nO comando 'l' é utilizado para abrir jogos previamente salvos. Pode ser usado de duas formas:\n"
            "Com apenas um argumento, um número natural, para abrir o jogo escolhido na save original.\n"
            "Com dois argumentos, ambos números naturais, para abrir o jogo escolhido na save escolhida.\n\n"
            "Exemplos:\n\n"
            "'l 3' abre o jogo 3 na save original, caso exista.\n"
            "'l 2 5' abre o jogo 2 na save 5, caso exista.\n\n");
}



// Explica o comando 'c'
void imprimeInfoCc () {
    printf ("\nO comando 'c' permite ao jogador criar um jogo à sua escolha.\n"
            "Por exemplo, se for usado o comando e, de seguida, o jogador escrever:\n\n"
            "3 3\n"
            "abc\n"
            "def\n"
            "ghi\n\n"
            "É criado um jogo novo com o tabuleiro dado.\n\n");
}



// Explica o comando 'E'
void imprimeInfoCE () {
    printf ("\nO comando 'E' permite ao jogador eliminar jogos ou saves de jogos.\n\n"
            "Exemplos:\n\n"
            "'E 5' elimina o jogo 5 (elimina todas as saves, incluindo a original).\n"
            "'E 1 2' elimina a save 2 do jogo 1.\n\n");
}



// Explica o comando 'h'
void imprimeInfoCh () {
    printf ("\nO comando 'h' tem duas funções:\n"
            "Se for usado sem argumento, lista todos os comandos do jogo, dando uma breve explicação de cada um.\n"
            "Se for usado com um argumento, o nome de outro comando, explica detalhadamente a função desse comando.\n\n");
}



// Explica o comando 'b'
void imprimeInfoCb () {
    printf ("\nO comando 'b' pinta uma casa de branco. Casas brancas ou riscadas não podem ser pintadas.\n"
            "Este comando decrementa a pontuação.\n\n");
}



// Explica o comando 'r'
void imprimeInfoCr () {
    printf ("\nO comando 'r' risca uma casa. Casas brancas ou riscadas não podem ser riscadas.\n"
            "Este comando decrementa a pontuação.\n\n");
}



// Explica o comando 'V'
void imprimeInfoCV () {
    printf ("\nO comando 'V' permite ao jogador ver os últimos tabuleiros do jogo. Pode ser utilizado de duas formas:\n"
            "Sem argumento, de modo a revelar apenas o último tabuleiro do jogo.\n"
            "Com um argumento, um número natural, de modo a revelar os últimos tabuleiros do jogo até ao dado como argumento.\n\n"
            "Exemplos:\n\n"
            "'V' revela o último tabuleiro.\n"
            "'V 3' revela os últimos três tabuleiros.\n\n");
}



// Explica o comando 'g'
void imprimeInfoCg () {
    printf ("\nO comando 'g' é utilizado para guardar jogos numa save. Pode ser utilizado de duas formas:\n"
            "Sem argumento, guardando automaticamente o jogo numa nova save.\n"
            "Com um argumento, um número natural, que indica a save em que o jogador pretende guardar o jogo.\n\n"
            "Exemplos:\n\n"
            "'g' guarda o jogo numa save nova.\n"
            "'g 4' guarda o jogo na save 4.\n\n"
            "Nota: Se já existir a save dada como argumento, esta será substituída. Caso contrário será gerada uma nova save.\n\n");
}



// Explica o comando 'v'
void imprimeInfoCv () {
    printf ("\nO comando 'v' avisa o jogador se existirem infrações no estado atual do jogo, destacando-as no tabuleiro.\n\n");
}



// Explica o comando 'j'
void imprimeInfoCj () {
    printf ("\nO comando 'j' revela todos os jogos e as respetivas saves que estão guardados.\n\n");
}



// Explica o comando 'a'
void imprimeInfoCa () {
    printf ("\nO comando 'a' ajuda realizando, uma única vez, jogadas que são necesárias no estado atual do jogo, isto é:\n\n"
            "1. Pinta casas à volta de casas riscadas.\n"
            "2. Risca casas cuja letra (como minúscula) é repetida (como maiúscula) na mesma linha ou coluna.\n"
            "3. Pinta casas que, se fossem riscas, não permitiram um caminho ortogonal entre todas as letras.\n\n"
            "Este comando pode ser usado de quatro formas diferentes:\n\n"
            "'a' realiza os processos 1, 2 e 3.\n"
            "'a b' realiza apenas o processo 1.\n"
            "'a r' realiza apenas o processo 2.\n"
            "'a o' realiza apenas o processo 3.\n\n"
            "Cada alteração que este comando faz decrementa a pontuação.\n\n");
}



// Explica o comando 'A'
void imprimeInfoCA () {
    printf ("\nO comando 'A' ajuda realizando, repetidamente (até não haver nada alterar), jogadas que são necesárias no estado atual do jogo, isto é:\n\n"
            "1. Pinta casas à volta de casas riscadas.\n"
            "2. Risca casas cuja letra (minúscula) é repetida (como maiúscula) na mesma linha ou coluna.\n"
            "3. Pinta casas que, se fossem riscas, não permitiram um caminho ortogonal entre todas as letras.\n\n"
            "Cada alteração que este comando faz decrementa a pontuação.\n\n");
}



// Explica o comando 'R'
void imprimeInfoCR () {
    printf ("\nO comando 'R' resolve o jogo.\n"
            "Se este comando for utilizado, a pontuação do jogador será 0.\n\n");
}



// Explica o comando 'p'
void imprimeInfoCp () {
    printf ("\nO comando 'p' revela a pontuação atual do jogo. Esta irá surgir como:\n\n"
            "Verde se for alta, isto é, acima de dois terços da pontuação máxima.\n"
            "Amarela se for média, isto é, entre um e dois terços da pontuação máxima.\n"
            "Vermelha se for baixa, isto é, abaixo de um terço da pontuação máxima.\n\n");
}



// Explica o comando 'd'
void imprimeInfoCd () {
    printf ("\nO comando 'd' permite ao jogador desfazer jogadas. Pode ser usado de duas formas:\n"
            "Sem argumento, de modo a desfazer uma única jogada.\n"
            "Com um argumento, um número natural, que indica o tabuleiro para o qual o jogador pretende retornar.\n\n."
            "Cada jogada desfeita decrementa a pontuação.\n"
            "Exemplos:\n\n"
            "'d' desfaz a última jogada.\n"
            "'d 3' retorna ao tabuleiro três.\n\n");
}



// Explica o comando 'D'
void imprimeInfoCD () {
    printf ("\nO comando 'D' apaga todo o histórico guardado no jogo atual.\n\n");
}



// Explica o comando 'e'
void imprimeInfoCe () {
    printf ("\nO comando 'e' explica detalhadamente o objetivo e as regras do jogo e ensina como jogar.\n\n");
}



// Explica o comando 'X'
void imprimeInfoCX () {
    printf ("\nO comando 'X' revela uma solução do jogo (jogos podem ou não ter solução e esta pode ou não ser única).\n"
            "Se este comando for utilizado, a pontuação do jogador será 0.\n\n");
}