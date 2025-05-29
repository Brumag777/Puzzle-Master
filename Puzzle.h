#include <stdbool.h> 
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "CUnit/Basic.h"

#define LINE_SIZE 1024

#define MAGENTA "\033[38;2;255;0;255m"
#define VERMELHO "\033[38;2;255;0;0m"
#define AZUL "\033[38;2;50;50;255m"
#define VERDE "\033[38;2;0;255;0m"
#define AMARELO "\033[38;2;255;190;0m"
#define CINZENTO "\033[38;2;170;170;170m"
#define RESET "\033[0m"

// Informação acerca de uma alteração
typedef struct jogada {
    int L;          // Linha da alteração
    char C;         // Coluna da alteração
    char cAnterior; // Caractere anterior à alteração
} JOGADA, *Jogada;

// Informação acerca de todas as jogadas
typedef struct lJogadas {
    Jogada *Jogadas;       // Array de alterações de uma jogada
    int nAlts;             // Número de alterações da jogada (tamanho do array)
    struct lJogadas *JAnt; // O resto da lista
} LJOGADAS, *LJogadas;

// Informação sobre os tabuleiros
typedef struct info {
    bool aCorrer;      // Indica se o jogo está ou não a correr
    int nTabuleiro;    // O número do tabuleiro atual
    int pont;          // A pontuação atual
    int dL;            // O número de linhas do tabuleiro
    int dC;            // O número de colunas do tabuleiro
    char **Tabuleiro;  // O tabuleiro do jogo
    LJogadas HJogadas; // A lista de jogadas do jogo
    bool eJogo;        // Indica se é o jogo ou é um teste
    int nJogo;         // Indica o número do jogo que está aberto
} INFO, *Info;

// Função dos comandos do jogo
typedef bool (*COMANDO) (char cmd, char args [2][LINE_SIZE], Info I);





// Funções relativas à interface dos comandos - Comandos.c

// Grava o jogo numa save
bool gravar (char cmd, char args [2][LINE_SIZE], Info I);

// Lê uma save de um jogo
bool ler (char cmd, char args [2][LINE_SIZE], Info I);

// Termina o jogo
bool sair (char cmd, char args [2][LINE_SIZE], Info I);

// Pinta uma casa de branco
bool pintarCasa (char cmd, char args [2][LINE_SIZE], Info I);

// Risca uma casa
bool riscarCasa (char cmd, char args [2][LINE_SIZE], Info I);

// Desfaz a(s) última(s) jogada(s)
bool desfazerJogada (char cmd, char args [2][LINE_SIZE], Info I);

// Imprime o(s) último(s) tabuleiro(s) armazenado(s) no histórico
bool visualizarHistorico (char cmd, char args [2][LINE_SIZE], Info I);

// Verifica se existem infrações no tabuleiro
bool verifica (char cmd, char args [2][LINE_SIZE], Info I);

// Ajuda o jogador realizando jogadas 'obrigatórias' na posição
bool ajuda (char cmd, char args [2][LINE_SIZE], Info I);

// Ajuda o jogador realizando jogadas 'obrigatórias' repetidamente até não haver nada a alterar
bool ajudaRep (char cmd, char args [2][LINE_SIZE], Info I);

// Resolve o jogo
bool resolveJogo (char cmd, char args [2][LINE_SIZE], Info I);

// Revela a solução do jogo
bool mostrarSolucao (char cmd, char args [2][LINE_SIZE], Info I);

// Apaga o histoŕico de jogadas
bool apagaHistorico (char cmd, char args [2][LINE_SIZE], Info I);

// Revela a pontuação atual
bool imprimePont (char cmd, char args [2][LINE_SIZE], Info I);

// Permite ao jogador criar um jogo novo
bool criarJogo (char cmd, char args [2][LINE_SIZE], Info I);

// Permite ao jogador eliminar um jogo ou uma save de um jogo
bool eliminarJogo (char cmd, char args [2][LINE_SIZE], Info I);

// Imprime informação sobre comandos
bool infoComandos (char cmd, char args [2][LINE_SIZE], Info I);

// Explica o objetivo e as regras do jogo
bool explicaJogo (char cmd, char args [2][LINE_SIZE], Info I);

// Revela todos os jogos e as respetivas saves
bool indicaJogos (char cmd, char args [2][LINE_SIZE], Info I);

// Limpa a terminal
bool limpaTerminal (char cmd, char args [2][LINE_SIZE], Info I);





// Funções relativas à lógica dos comandos - ComandosLogica.c

// Função que realiza a lógica do comando 'g' (gravar)
int logicaGravar (char *nomeFicheiro, Info I);

// Função que realiza a lógica do comando 'l' (ler)
int logicaLer (char args [2][LINE_SIZE], Info I);

// Função que realiza a lógica do comando 's' (sair)
int logicaSair (char *arg, Info I);

// Função que realiza a lógica do comando 'b' (pintarCasa)
int logicaPintarCasa (char *coordenada, Info I);

// Função que realiza a lógica do comando 'r' (riscarCasa)
int logicaRiscarCasa (char *coordenada, Info I);

// Função que realiza a lógica do comando 'd' (desfazerJogada)
int logicaDesfazerJogada (char *nTab, Info I);

// Função que realiza a lógica do comando 'V' (visualizarHistorico)
int logicaVisualizarHistorico (char *nTab, Info I);

// Função que realiza a lógica do comando 'v' (verifica)
int logicaVerifica (char *arg, Info I);

// Função que realiza a lógica do comando 'a' (ajuda)
int logicaAjuda (char *arg, Info I);

// Função que realiza a lógica do comando 'A' (ajudaRep)
int logicaAjudaRep (char *arg, Info I);

// Função que realiza a lógica do comando 'R'
int logicaResolveJogo (char *arg, Info I, int flag);

// Função que realiza a lógica do comando 'D' (apagaHistorico)
int logicaApagaHistorico (char *arg, Info I);

// Função que realiza a lógica do comando 'c' (criarJogo)
int logicaCriarJogo (char *arg);

// Função que realiza a lógica do comando 'E' (eliminarJogo)
int logicaEliminarJogo (char args [2][LINE_SIZE], Info I);

// Função que realiza a lógica do comando 'p' (imprimePont)
int logicaImprimePont (char *arg, Info I);

// Função que realiza a lógica dos comandos 'e' (explicaJogo) e 'j' (indicaJogos)
int logicaListarInfo (char *arg);

// Função que realiza a lógica do comando 'h' (infoComandos)
int logicaInfoComandos (char *arg);





// Funções auxiliares à lógica dos comandos - ComandosLogicaA.c

// Guarda o tabuleiro numa save
void guardaInfo (FILE *Jogo, Info I);

// Guarda o histórico de jogadas numa save
void guardaJogadas (FILE *Jogo, Info I);

// Lê a informação de uma save de um jogo
int leFicheiro (FILE *Jogo, Info I);

// Lê a informação de uma linha de jogadas de uma save de um jogo
int leLinhaJogadas (FILE *Jogo, Info I);

// Procura infrações em relação à existência de casas riscadas juntas e de casa brancas na mesma linha ou coluna
int verificaInfracoes (Info I, int flag);

// Procura infrações em relação à existência de um caminho ortogonal entre todas as letras
int verificaCaminhoOrtogonal (Info I, int flag);

// Realiza alterações necessárias na posição atual
int ajudaUmaVez (Info I, int versaoComando);

// Resolve o jogo
int resolve (Info I, int dL, int dC, char TabuleiroOriginal [dL][dC + 2]);

// Procura infrações no tabuleiro para preencher o tabuleiro de infrações
int preencheTabInfracoes (Info I, int TabInfracoes [I -> dL][I -> dC]);





// Funções auxiliares (gerais) - Auxiliares.c

// Imprime os últimos 'nTabs' tabuleiros
int visualizaUltimosTabuleiros (Info I, int nTabs, int flag);

// Forma uma jogada
void formaJogada (Jogada *JNova, int linha, char coluna, char c);

// Realiza num tabuleiro as alterações de uma jogada
void realizaAlteracoesJogada (char **Tabuleiro, Jogada *Jogadas, int nAlts);

// Verifica se um caractere é uma letra maiúscula
int eMaiuscula (char c);

// Verifica se um caractere é uma letra minúscula
int eMinuscula (char c);

// Verifica se uma coordenada é válida (isto é, está dentro do tabuleiro)
int coordenadaValida (int l, char c, int linhas, int colunas);

// Verifica se um tabuleiro é válido
int tabuleiroValido (int dL, int dC, char **Tabuleiro);

// Verifica se as jogadas são válidas
int jogadasValidas (Info I);

// Verifica se as linhas não possuem casas brancas repetidas
int verificaLinhas (Info I, char c, int linha, int coluna, int flag);

// Verifica se as colunas não possuem casas brancas repetidas
int verificaColunas (Info I, char c, int linha, int coluna, int flag);

// Verifica se as casas adjacentes às casas vazias não são vazias
int verificaCasaVazia (Info I, int linha, int coluna, int flag);

// Calcula quantas letras estão ligadas à letra da posição dada
int contaLetrasLigadas (int linhas, int colunas, int Tabuleiro [linhas][colunas], int l, int c);

// Testa se o jogador já ganhou o jogo
int testeJogo (Info I);

// Cria e adiciona uma jogada ao histórico comparando dois tabuleiros
void adicionaJogada (Info I, int dL, int dC, char TabuleiroAnterior [dL][dC + 2], int nAlts);

// Risca as casas que deviam ser vazias
int riscaCasasAux (Info I, int linha, int coluna);

// Percorre o tabuleiro para riscar casas que não podem ser brancas pela existência de casas brancas iguais na mesma linha ou coluna
int riscaCasas (Info I);

// Percorre a linha para riscar casas que deviam ser vazias
int percorreLinha (Info I, char c, int linha, int coluna);

// Percorre a coluna para riscar casas que deviam ser vazias
int percorreColuna (Info I, char c, int linha, int coluna);

// Pinta as casas à volta das casas vazias de branco
int pintaCasasAux (Info I, int linha, int coluna);

// Percorre o tabuleiro para pintar casas à volta das casas vazias de branco
int pintaCasas (Info I);

// Testa as possibilidades de uma casa minúscula
int testaPossibilidadesCasaAux (Info I, int linha, int coluna);

// Percorre o tabuleiro para pintar de branco as casas que não podem ser vazias por bloquear letras
int testaPossibilidadesCasa (Info I);

// Procura infrações numa linha do tabuleiro
int procuraInfracoesL (Info I, char c, int linha, int coluna, int TabInfracoes [I -> dL][I -> dC]);

// Procura infrações numa coluna do tabuleiro
int procuraInfracoesC (Info I, char c, int linha, int coluna, int TabInfracoes [I -> dL][I -> dC]);

// Procura casas vazias adjacentes a outras
int procuraInfracoesV (Info I, int linha, int coluna, int TabInfracoes [I -> dL][I -> dC]);

// Forma o nome de um ficheiro
void formaNomeFicheiro (char *nomeFicheiro, char nums [2][LINE_SIZE], bool eJogo);

// Calcula o valor de uma pontuação (1 é alto, 2 é médio, 3 é baixo)
int valorPont (int dL, int dC, int pont);





// Funções relativas à gestão de memória - MemoryManagement.c

// Inicializa a informação sobre o jogo
Info inicializaJogo ();

// Aloca memória para o tabuleiro do jogo
int inicializaTabuleiro (Info I);

// Liberta a memória alocada para a informação do jogo
void libertaInfo (Info I);

// Liberta a memória alocada para o tabuleiro do jogo
void libertaTabuleiro (Info I);

// Liberta a lista de jogadas do jogo
void libertaLJogadas (Info I);

// Liberta a memória alocada para um array de jogadas
void libertaJogadas (Jogada *J, int nJogadas);





// Funções relativas às listas - Lista.c

// Adiciona uma jogada ao histórico
int addJogada (Info I, Jogada *JogadasNovas, int nAlteracoes);

// Remove uma jogada do histórico
void remJogada (Info I);

// Inverte o histórico de jogadas
LJogadas inverteHistorico (LJogadas L);





// Funções para imprimir - Imprime.c

// Imprime um tabuleiro
void imprimeTabuleiro (int dL, int dC, char **Tabuleiro, int nTabuleiro, int flag);

// Imprime um tabuleiro destacando as infrações
void destacaInfracoes (int dL, int dC, char **Tabuleiro, int TabInfracoes [dL][dC], int eSolucao);

// Imprime os jogos e as respetivas saves existentes
void imprimeSavesJogos (int savesJogos [100][100], int nSavesJogos [100]);

// Imprime a mensagem inicial do jogo
void imprimeMensagemInicial ();

// Imprime a lista de comandos do jogo
void imprimeListaComandos ();

// Imprime informação acerca de um comando
void imprimeInfoComando (char c);

// Explica o comando 's'
void imprimeInfoCs ();

// Explica o comando 'l'
void imprimeInfoCl ();

// Explica o comando 'c'
void imprimeInfoCc ();

// Explica o comando 'E'
void imprimeInfoCE ();

// Explica o comando 'h'
void imprimeInfoCh ();

// Explica o comando 'b'
void imprimeInfoCb ();

// Explica o comando 'r'
void imprimeInfoCr ();

// Explica o comando 'V'
void imprimeInfoCV ();

// Explica o comando 'g'
void imprimeInfoCg ();

// Explica o comando 'v'
void imprimeInfoCv ();

// Explica o comando 'j'
void imprimeInfoCj ();

// Explica o comando 'a'
void imprimeInfoCa ();

// Explica o comando 'A'
void imprimeInfoCA ();

// Explica o comando 'R'
void imprimeInfoCR ();

// Explica o comando 'p'
void imprimeInfoCp ();

// Explica o comando 'd'
void imprimeInfoCd ();

// Explica o comando 'D'
void imprimeInfoCD ();

// Explica o comando 'e'
void imprimeInfoCe ();

// Explica o comando 'C'
void imprimeInfoCC ();

// Explica o comando 'X'
void imprimeInfoCX ();

// Explica o jogo
void imprimeExplicacaoJogo ();

// Imprime uma mensagem que indica que o tabuleiro está finalizado
void imprimeMensagemFim (Info I);