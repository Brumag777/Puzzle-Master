#include "../Puzzle.h"

// Imprime um tabuleiro
void imprimeTabuleiro (int dL, int dC, char **Tabuleiro, int nTabuleiro, int flag) {

    // Imprime o número do tabuleiro (ou 'S' caso seja a solução do jogo)
    if (nTabuleiro) { 
        if      (nTabuleiro < 10)  printf ("\n%d   ", nTabuleiro);
        else if (nTabuleiro < 100) printf ("\n%d  ", nTabuleiro);
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
        for (int j = 0; j < dC; j++) {
            if (eMinuscula (Tabuleiro [i][j])) printf (CINZENTO);
            else if (Tabuleiro [i][j] == '#') printf (MAGENTA);
            else printf (AZUL);
            printf ("%c " RESET, Tabuleiro [i][j]);
        }
        
        // Avança para a linha seguinte
        putchar ('\n');
    }

    if (flag) putchar ('\n');
}



// Imprime os últimos 'nTabs' tabuleiros
void visualizaUltimosTabuleiros (Info I, int nTabs, int flag) {

    // Imprime a mensagem inicial
    if (flag) {
        if (nTabs == 1) printf ("\nO último tabuleiro é:\n");
        else printf ("\nOs últimos %d tabuleiros são:\n", nTabs);
    }

    // Caso base da recursão
    if (nTabs == 1) {
        imprimeTabuleiro (I -> dL, I -> dL, I -> Tabuleiro, I -> nTabuleiro, 0);
        return;
    }

    // Caso recursivo
    else {

        // Armazena a lista original
        LJogadas Atual = I -> HJogadas;

        // Aloca memória para a reserva
        Alt *Reserva = malloc (Atual -> nAlts * (sizeof (ALT)));

        // Armazena os caracteres originais do tabuleiro
        for (int i = 0; i < Atual -> nAlts; i++) {
            int linha = Atual -> Jogada [i] -> L;
            char coluna = Atual -> Jogada [i] -> C;
            formaJogada (&Reserva [i], linha, coluna, I -> Tabuleiro [linha - 1][coluna - 'a']);
        }

        // Aplica as alterações de uma jogada
        realizaAlteracoesJogada (I -> Tabuleiro, Atual -> Jogada, Atual -> nAlts);

        // Avança na lista de jogadas
        I -> HJogadas = I -> HJogadas -> JAnt;
        I -> nTabuleiro--;

        // Visualiza os tabuleiros anteriores
        visualizaUltimosTabuleiros (I, nTabs - 1, 0);

        // Retorna ao original
        realizaAlteracoesJogada (I -> Tabuleiro, Reserva, Atual -> nAlts);
        I -> nTabuleiro++;
        I -> HJogadas = Atual;

        // Visualiza o tabuleiro atual
        imprimeTabuleiro (I -> dL, I -> dC, I -> Tabuleiro, I -> nTabuleiro, 0);

        // Liberta a memória alocada para a reserva
        libertaJogada (Reserva, Atual -> nAlts);
    }
}



// Imprime um tabuleiro destacando as infrações
void imprimeTabDestacado (int dL, int dC, char **Tabuleiro, int TabInfracoes [dL][dC], int eSolucao, bool aCorrer) {

    // É um teste, a função não é realiza
    if (!aCorrer) return;

    // Imprime a mensagem inicial
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

    // Avança uma linha
    if (eSolucao) putchar ('\n');
}



// Imprime a mensagem inicial
void imprimeMensagemInicial () {
    printf ("\n________________________________________________________________________________________________________________________________________________________________________________________________________\n\n"
            "\n                                         ██████╗ ██╗   ██╗███████╗███████╗██╗     ███████╗    ███╗   ███╗ █████╗ ███████╗████████╗███████╗██████╗ "
            "\n                                         ██╔══██╗██║   ██║╚══███╔╝╚══███╔╝██║     ██╔════╝    ████╗ ████║██╔══██╗██╔════╝╚══██╔══╝██╔════╝██╔══██╗"
            "\n                                         ██████╔╝██║   ██║  ███╔╝   ███╔╝ ██║     █████╗      ██╔████╔██║███████║███████╗   ██║   █████╗  ██████╔╝"
            "\n                                         ██╔═══╝ ██║   ██║ ███╔╝   ███╔╝  ██║     ██╔══╝      ██║╚██╔╝██║██╔══██║╚════██║   ██║   ██╔══╝  ██╔══██╗"
            "\n                                         ██║     ╚██████╔╝███████╗███████╗███████╗███████╗    ██║ ╚═╝ ██║██║  ██║███████║   ██║   ███████╗██║  ██║"
            "\n                                         ╚═╝      ╚═════╝ ╚══════╝╚══════╝╚══════╝╚══════╝    ╚═╝     ╚═╝╚═╝  ╚═╝╚══════╝   ╚═╝   ╚══════╝╚═╝  ╚═╝"
            AZUL "\n\n                                                                       Pressione h para saber a lista de comandos!\n" RESET
            "\n________________________________________________________________________________________________________________________________________________________________________________________________________\n\n");
}



// Sugere ao jogador que grave o jogo
int pretendeGravar (Info I) {

    // Não há nenhum jogo para gravar
    if (I -> nTabuleiro == 0) return 0;

    // Input do jogador
    char input [LINE_SIZE];

    // Confirma se o jogador pretende gravar o jogo
    printf (AMARELO "\nPretende gravar o jogo atual antes de proceder?\n\n" RESET);
    if (scanf ("%s", input) != 1) return 1;

    // Verifica se a resposta do jogador é válida
    while (strcmp ("S", input) && strcmp ("s", input) && strcmp ("N", input) && strcmp ("n", input)) {
            printf (VERMELHO "\nResposta inválida." RESET " Deve responder " VERDE "S" RESET " (sim) ou " VERMELHO "N" RESET " (não).\n\n");
            if (scanf ("%s", input) != 1) return 1;
        }

    // Verifica qual foi a resposta do jogador
    if (strcmp ("S", input) == 0 || strcmp ("s", input) == 0) gravar ('g', "", "", I);

    // Limpa o stdin
    int ch;
    while ((ch = getchar ()) != '\n' && ch != EOF);

    return 0;
}



// Confirma se o jogador pretende proceder
int pretendeProceder () {

    // Input do jogador
    char input [LINE_SIZE];

    // Confirma se o jogador pretende gravar o jogo
    printf (AMARELO "\nTem a certeza de que deseja proceder?\n\n" RESET);
    if (scanf ("%s", input) != 1) return 1;

    // Verifica se a resposta do jogador é válida
    while (strcmp ("S", input) && strcmp ("s", input) && strcmp ("N", input) && strcmp ("n", input)) {
            printf (VERMELHO "\nResposta inválida." RESET " Deve responder " VERDE "S" RESET " (sim) ou " VERMELHO "N" RESET " (não).\n\n");
            if (scanf ("%s", input) != 1) return 1;
        }

    // Limpa o stdin
    int ch;
    while ((ch = getchar ()) != '\n' && ch != EOF);

    // Verifica qual foi a resposta do jogador
    int r = strcmp ("S", input) == 0 || strcmp ("s", input) == 0;

    // Avança uma linha
    if (r == 0) putchar ('\n');

    return r;
}



// Explica o jogo
void imprimeExplicacaoJogo () {
    printf ("\n"
            AZUL "Puzzle Master" RESET " é um quebra-cabeças no qual o objetivo é terminar um tabuleiro com o máximo de pontuação possível.\n"
            "Um tabuleiro é considerado terminado quando todas as casas estão pintadas de branco ou riscadas e não existe nenhuma infração.\n\n"
            MAGENTA "Nota:" AZUL " Casas brancas são casas com letra maiúscula e casas riscadas são casas com #.\n\n" RESET
            "Um tabuleiro não possui infrações se respeitar as seguintes condições:\n\n"
            AZUL "1." RESET " Não existem casas brancas iguais na mesma linha ou coluna.\n"
            AZUL "2." RESET " Não existem casas riscadas juntas.\n"
            AZUL "3." RESET " Existe um caminho ortogonal entre todas as letras.\n\n"
            "Consideremos o tabuleiro seguinte:\n\n" AZUL
            "e c a d c\n"
            "d c d e c\n"
            "b d d c e\n"
            "c d e e b\n"
            "a c c b b\n\n" RESET
            "Se olharmos para o canto inferior direito do tabuleiro, temos três " AZUL "b" RESET " colados. Como dois " AZUL "B" RESET " não podem estar na mesma linha ou coluna, sabemos que o canto teria que ser um dos seguintes casos:\n\n" AZUL
            "e c a d c    e c a d c\n"
            "d c d e c    d c d e c\n"
            "b d d c e    b d d c e\n"
            "c d e e " VERMELHO "#" AZUL "    c d e e " MAGENTA "B" AZUL "\n"
            "a c c " VERMELHO "#" MAGENTA " B" AZUL "    a c c " MAGENTA "B #\n\n" RESET
            "No primeiro caso, o " AZUL "B" RESET " do canto inferior direito está bloqueado, pelo que a condição " AZUL "3" RESET " não é mantida. Sendo assim, apenas o segundo tabuleiro é válido.\n\n" AZUL
            "e c a d c\n"
            "d c d e c\n"
            "b d d c e\n"
            "c d e e " MAGENTA "B\n" AZUL
            "a c c " MAGENTA "B #\n\n" RESET
            "Na quarta coluna temos as letras " AZUL "e c e." RESET " Se riscarmos a letra " AZUL "c" RESET " que está no meio teríamos:\n\n" AZUL
            "e c a d c\n"
            "d c d e c\n"
            "b d d " MAGENTA "#" AZUL " e\n"
            "c d e e "MAGENTA "B\n" AZUL
            "a c c " MAGENTA "B #\n\n" RESET
            "Pela condição " AZUL "2" RESET " temos:\n\n" AZUL
            "e c a d c\n"
            "d c d " VERMELHO "E " AZUL "c\n"
            "b d " MAGENTA "D # E\n" AZUL
            "c d e " VERMELHO "E " MAGENTA "B\n" AZUL
            "a c c " MAGENTA "B #\n\n" RESET
            "Agora temos que a condição " AZUL "1" RESET " não é respeitada, uma vez que existem dois " AZUL "E" RESET " na mesma coluna, pelo que a casa tinha de ter pintada de branco:\n\n" AZUL
            "e c a d c\n"
            "d c d e c\n"
            "b d d " MAGENTA "C" AZUL " e\n"
            "c d e e " MAGENTA "B\n" AZUL
            "a c c " MAGENTA "B #\n\n" RESET
            "Na segunda coluna, temos três " AZUL "c," RESET " estando dois deles juntos. Se pintarmos o " AZUL "c" RESET " isolado:\n\n" AZUL
            "e c a d c\n"
            "d c d e c\n"
            "b d d " MAGENTA "C" AZUL " e\n"
            "c d e e " MAGENTA "B\n" AZUL
            "a " MAGENTA "C" AZUL " c " MAGENTA "B #\n\n" RESET
            "Pela condição " AZUL "1" RESET ":\n\n" AZUL
            "e" VERMELHO " #" AZUL " a d c\n"
            "d" VERMELHO " #" AZUL " d e c\n"
            "b d d " MAGENTA "C" AZUL " e\n"
            "c d e e " MAGENTA "B\n" AZUL
            "a " MAGENTA "C" AZUL " c " MAGENTA "B #\n\n" RESET
            "Neste caso, a condição " AZUL "2" RESET " não é mantida. Logo o " AZUL "c" RESET " tem de ser riscado:\n\n" AZUL
            "e c a d c\n"
            "d c d e c\n"
            "b d d " MAGENTA "C" AZUL " e\n"
            "c d e e " MAGENTA "B\n" AZUL
            "a " MAGENTA "#" AZUL " c " MAGENTA "B #\n\n" RESET
            "Tendo em atenção estas três condições, é possível progredir até a um tabuleiro finalizado.\n\n"
            MAGENTA "Nota: " AZUL "Jogos podem ou não ter solução e esta pode ou não ser única.\n\n" RESET);
}



// Imprime a lista de comandos do jogo
void imprimeListaComandos () {
    printf (MAGENTA "\nComandos Para Jogar\n\n"
            AZUL "b:" RESET " Pinta uma casa de branco.\n"
            AZUL "r:" RESET " Risca uma casa.\n"
            AZUL "a:" RESET " Ajuda realizando jogadas necessárias.\n"
            AZUL "A:" RESET " Ajuda realizando jogadas necessárias repetidamente.\n"
            AZUL "R:" RESET " Resolve o jogo.\n"
            AZUL "X:" RESET " Revela uma solução do jogo.\n"
            AZUL "D:" RESET " Resolve uma casa do jogo.\n"
            AZUL "d:" RESET " Desfaz jogadas.\n"
            AZUL "v:" RESET " Verifica se existem infrações no jogo.\n"
            AZUL "V:" RESET " Revela o(s) último(s) tabuleiro(s).\n"
            MAGENTA "\nComandos Para Gerenciar Os Jogos\n\n"
            AZUL "g:" RESET " Grava o jogo atual numa save.\n"
            AZUL "l:" RESET " Abre um jogo previamente guardado numa save.\n"
            AZUL "c:" RESET " Permite criar um jogo novo.\n"
            AZUL "E:" RESET " Permite eliminar jogos previamente guardados ou as respetivas saves.\n"
            AZUL "j:" RESET " Indica todos os jogos guardados e as respetivas saves.\n"
            MAGENTA "\nComandos Diversos\n\n"
            AZUL "p:" RESET " Revela a pontuação do jogo.\n"
            AZUL "s:" RESET " Termina o jogo.\n"
            AZUL "e:" RESET " Explica o objetivo e as regras do jogo.\n"
            AZUL "h:" RESET " Indica e explica comandos do jogo.\n"
            MAGENTA "\nNota: " RESET "Se pretende saber mais sobre algum comando, use o comando " AZUL "h" RESET " dando como argumento o comando desejado.\n\n");
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
    else if (c == 'e') imprimeInfoCe ();
    else if (c == 'D') imprimeInfoCD ();
    else               imprimeInfoCX ();
}



// Explica o comando 's'
void imprimeInfoCs () {
    printf ("\nO comando " AZUL "s" RESET " é utilizado para sair do jogo.\n\n"
            "Nota:" VERMELHO " O progresso do jogo que está aberto será perdido.\n\n" RESET);
}



// Explica o comando 'l'
void imprimeInfoCl () {
    printf ("\nO comando " AZUL "l" RESET " é utilizado para abrir jogos previamente salvos. Pode ser usado de duas formas:\n\n"
            AZUL "Com apenas um argumento," RESET " um número natural, para abrir o jogo escolhido na save original.\n"
            AZUL "Com dois argumentos," RESET " ambos números naturais, para abrir o jogo escolhido na save escolhida.\n\n"
            "Exemplos:\n\n"
            AZUL "l 3" RESET " abre o jogo 3 na save original.\n"
            AZUL "l 2 5" RESET " abre o jogo 2 na save 5.\n\n");
}



// Explica o comando 'c'
void imprimeInfoCc () {
    printf ("\nO comando " AZUL "c" RESET " permite ao jogador criar um jogo à sua escolha.\n"
            "Por exemplo, se o jogador pretende criar um tabuleiro personalizado 3x5, pode fazê-lo com o seguinte input:\n\n"
            AZUL "3 5\n\n"
            "abcde\n"
            "fghij\n"
            "klmno\n\n" RESET);
}



// Explica o comando 'E'
void imprimeInfoCE () {
    printf ("\nO comando " AZUL "E" RESET " permite ao jogador eliminar jogos ou saves de jogos. Pode ser usado de duas formas:\n\n"
            AZUL "Com um argumento," RESET " um número natural, para eliminar por completo um jogo.\n"
            AZUL "Com dois argumentos," RESET " ambos números naturais, para eliminar uma save particular de um jogo.\n\n"
            "Exemplos:\n\n"
            AZUL "E 5" RESET " elimina o jogo 5 (elimina todas as saves, incluindo a original).\n"
            AZUL "E 1 2" RESET " elimina a save 2 do jogo 1.\n\n"
            "Nota:" VERMELHO " Eliminar jogos ou as respetivas saves é um processo irreversível.\n\n" RESET);
}



// Explica o comando 'h'
void imprimeInfoCh () {
    printf ("\nO comando " AZUL "h" RESET " tem duas funções:\n\n"
            AZUL "Sem argumento," RESET " lista todos os comandos do jogo, dando uma breve explicação de cada um.\n"
            AZUL "Com um argumento," RESET " o nome de outro comando, explica detalhadamente a função desse comando.\n\n");
}



// Explica o comando 'b'
void imprimeInfoCb () {
    printf ("\nO comando " AZUL "b" RESET " pinta uma casa de branco. Casas brancas ou riscadas não podem ser pintadas.\n\n"
            "Nota:" VERMELHO " Este comando decrementa a pontuação.\n\n" RESET);
}



// Explica o comando 'r'
void imprimeInfoCr () {
    printf ("\nO comando " AZUL "r" RESET " risca uma casa. Casas brancas ou riscadas não podem ser riscadas.\n\n"
            "Nota:" VERMELHO " Este comando decrementa a pontuação.\n\n" RESET);
}



// Explica o comando 'V'
void imprimeInfoCV () {
    printf ("\nO comando " AZUL "V" RESET " permite ao jogador ver os últimos tabuleiros do jogo. Pode ser utilizado de duas formas:\n\n"
            AZUL "Sem argumento," RESET " de modo a revelar apenas o último tabuleiro do jogo.\n"
            AZUL "Com um argumento," RESET " um número natural, de modo a revelar os últimos tabuleiros do jogo até ao dado como argumento.\n\n"
            "Exemplos:\n\n"
            AZUL "V" RESET " revela o último tabuleiro.\n"
            AZUL "V 3" RESET " revela os últimos três tabuleiros.\n\n");
}



// Explica o comando 'g'
void imprimeInfoCg () {
    printf ("\nO comando " AZUL "g" RESET " é utilizado para guardar jogos numa save. Pode ser utilizado de duas formas:\n\n"
            AZUL "Sem argumento," RESET " guarda automaticamente o jogo numa nova save.\n"
            AZUL "Com um argumento," RESET " um número natural, que indica a save em que o jogador pretende guardar o jogo.\n\n"
            "Exemplos:\n\n"
            AZUL "g" RESET " guarda o jogo numa save nova.\n"
            AZUL "g 4" RESET " guarda o jogo na save 4.\n\n"
            "Nota:" VERMELHO " Se já existir a save dada como argumento, esta será substituída.\n\n" RESET);
}



// Explica o comando 'v'
void imprimeInfoCv () {
    printf ("\nO comando " AZUL "v" RESET " avisa o jogador se existirem infrações no estado atual do jogo, destacando-as no tabuleiro.\n\n");
}



// Explica o comando 'j'
void imprimeInfoCj () {
    printf ("\nO comando " AZUL "j" RESET " revela todos os jogos que estão guardados, assim como as respetivas saves.\n\n");
}



// Explica o comando 'a'
void imprimeInfoCa () {
    printf ("\nO comando " AZUL "a" RESET " ajuda realizando, uma única vez, jogadas que são necesárias no estado atual do jogo, isto é:\n\n"
            AZUL "1." RESET " Pinta casas à volta de casas riscadas.\n"
            AZUL "2." RESET " Risca casas cuja letra (como minúscula) é repetida (como maiúscula) na mesma linha ou coluna.\n"
            AZUL "3." RESET " Pinta casas que, se fossem riscadas, não permitiram um caminho ortogonal entre todas as letras.\n\n"
            "Este comando pode ser usado de quatro formas diferentes:\n\n"
            AZUL "a" RESET " realiza os processos 1, 2 e 3.\n"
            AZUL "a b" RESET " realiza apenas o processo 1.\n"
            AZUL "a r" RESET " realiza apenas o processo 2.\n"
            AZUL "a o" RESET " realiza apenas o processo 3.\n\n"
            "Nota:" VERMELHO " Cada alteração que este comando realiza decrementa a pontuação.\n\n" RESET);
}



// Explica o comando 'A'
void imprimeInfoCA () {
    printf ("\nO comando " AZUL "A" RESET " ajuda realizando, repetidamente (até não haver nada alterar), jogadas que são necesárias no estado atual do jogo, isto é:\n\n"
            AZUL "1." RESET " Pinta casas à volta de casas riscadas.\n"
            AZUL "2." RESET " Risca casas cuja letra (minúscula) é repetida (como maiúscula) na mesma linha ou coluna.\n"
            AZUL "3." RESET " Pinta casas que, se fossem riscadas, não permitiram um caminho ortogonal entre todas as letras.\n\n"
            "Nota:" VERMELHO " Cada alteração que este comando realiza decrementa a pontuação.\n\n" RESET);
}



// Explica o comando 'R'
void imprimeInfoCR () {
    printf ("\nO comando " AZUL "R" RESET " resolve o jogo.\n\n"
            "Nota: " VERMELHO "Se este comando for utilizado, a pontuação do jogador será 0.\n\n" RESET);
}



// Explica o comando 'p'
void imprimeInfoCp () {
    printf ("\nO comando " AZUL "p" RESET " revela a pontuação atual do jogo. Esta irá surgir como:\n\n"
            VERDE "Verde" RESET " se for alta, isto é, acima de dois terços da pontuação máxima.\n"
            AMARELO "Amarela" RESET " se for média, isto é, entre um e dois terços da pontuação máxima.\n"
            VERMELHO "Vermelha" RESET " se for baixa, isto é, abaixo de um terço da pontuação máxima.\n\n");
}



// Explica o comando 'd'
void imprimeInfoCd () {
    printf ("\nO comando " AZUL "d" RESET " permite ao jogador desfazer jogadas. Pode ser usado de duas formas:\n\n"
            AZUL "Sem argumento," RESET " de modo a desfazer uma única jogada.\n"
            AZUL "Com um argumento," RESET " um número natural, que indica o tabuleiro para o qual o jogador pretende retornar.\n\n"
            "Exemplos:\n\n"
            AZUL "d" RESET " desfaz a última jogada.\n"
            AZUL "d 3" RESET " retorna ao tabuleiro três.\n\n"
            "Nota: " VERMELHO "Cada jogada desfeita decrementa a pontuação.\n\n" RESET);
}



// Explica o comando 'e'
void imprimeInfoCe () {
    printf ("\nO comando " AZUL "e" RESET " explica detalhadamente o objetivo e as regras do jogo e ensina como jogar.\n\n");
}



// Explica o comando 'D'
void imprimeInfoCD () {
    printf ("\nO comando " AZUL "E" RESET " resolve uma casa do tabuleiro, isto é, pinta ou risca a casa conforme o correto para resolver o jogo.\n\n"
            "Nota: " VERMELHO "Este comando diminui a pontuação substancialmente.\n\n" RESET);
}



// Explica o comando 'X'
void imprimeInfoCX () {
    printf ("\nO comando " AZUL "X" RESET " revela uma solução do jogo.\n\n"
            "Nota: " VERMELHO "Se este comando for utilizado, a pontuação do jogador será 0.\n\n" RESET);
}



// Imprime uma mensagem que indica que o tabuleiro está finalizado
void imprimeMensagemFim (Info I) {

    // Calcula o valor da pontuação
    int vPont = valorPont (I -> dL, I -> dC, I -> pont);

    // Imprime a mensagem
    printf (VERDE "Parabéns! ");
    if (vPont == 1) printf (VERDE);
    else if (vPont == 2) printf (AMARELO);
    else printf (VERMELHO);
    printf ("Conseguiste resolver o puzzle com uma pontuação de %d.\n\n" RESET, I -> pont);
}



// Avisa de uma infração numa linha
void avisaInfracaoLinha (Info I, char c, int linha, char coluna1, char coluna2, int flag) {
    if (I -> aCorrer && flag) printf (VERMELHO "Infração:" RESET " Letra '%c' repetida na linha %d (colunas '%c' e '%c').\n", c, linha, coluna1, coluna2);
}



// Avisa de uma infração numa coluna
void avisaInfracaoColuna (Info I, char c, char coluna, int linha1, int linha2, int flag) {
    if (I -> aCorrer && flag) printf (VERMELHO "Infração:" RESET " Letra '%c' repetida na coluna '%c' (linhas %d e %d).\n", c, coluna, linha1, linha2);
}



// Avisa de uma infração de casas vazias juntas
void avisaInfracaoCVazias (Info I, char coluna1, int linha1, char coluna2, int linha2, int flag) {
    if (I -> aCorrer && flag) printf (VERMELHO "Infração:" RESET " As casas vazias %c%d e %c%d estão juntas.\n", coluna1, linha1, coluna2, linha2);
}



// Avisa que não existe um caminho ortogonal entre todas as letras
void avisaInfracaoCOrtogonal (Info I, int flag) {
    if (I -> aCorrer && flag) printf (VERMELHO "Infração:" RESET " Não existe um caminho ortogonal entre todas as letras.\n");
}