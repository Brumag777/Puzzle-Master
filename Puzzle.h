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

#define VERMELHO "\033[38;2;255;0;0m"
#define VERDE "\033[38;2;0;255;0m"
#define AMARELO "\033[38;2;255;190;0m"
#define CINZENTO "\033[38;2;170;170;170m"
#define RESET "\033[0m"

// Informação acerca de uma jogada
typedef struct jogada {
    int L;
    char C;
    char cAnterior;
} JOGADA, *Jogada;

// Informação acerca de todas as jogadas
typedef struct lJogadas {
    Jogada *Jogadas;
    int nAlts;
    struct lJogadas *JAnt;
} LJOGADAS, *LJogadas;

// Informação sobre os tabuleiros
typedef struct info {
    bool aCorrer;
    int nTabuleiro;
    int pont;
    int dL;
    int dC;
    char **Tabuleiro;
    LJogadas HJogadas;
    bool eJogo;
    int nJogo;
} INFO, *Info;

// Função dos comandos do jogo
typedef bool (*COMANDO) (char cmd, char args [2][LINE_SIZE], Info I);





// Funções relativas à interface dos comandos - Comandos.c

// Grava o jogo num ficheiro
bool gravar (char cmd, char args [2][LINE_SIZE], Info I);

// Lê um ficheiro
bool ler (char cmd, char args [2][LINE_SIZE], Info I);

// Termina o jogo
bool sair (char cmd, char args [2][LINE_SIZE], Info I);

// Pinta uma casa de branco
bool pintarCasa (char cmd, char args [2][LINE_SIZE], Info I);

// Muda uma casa para vazia
bool riscarCasa (char cmd, char args [2][LINE_SIZE], Info I);

// Desfaz a últimas jogadas
bool desfazerJogada (char cmd, char args [2][LINE_SIZE], Info I);

// Imprime os últimos tabuleiros armazenados no histórico
bool visualizarHistorico (char cmd, char args [2][LINE_SIZE], Info I);

// Verifica se existem infrações no tabuleiro
bool verifica (char cmd, char args [2][LINE_SIZE], Info I);

// Ajuda o jogador realizando jogadas 'obrigatórias' na posição
bool ajuda (char cmd, char args [2][LINE_SIZE], Info I);

// Ajuda o jogador realizando jogadas 'obrigatórias' repetidamente até não haver nada a alterar
bool ajudaRep (char cmd, char args [2][LINE_SIZE], Info I);

// Resolve o jogo automaticamente
bool resolveJogo (char cmd, char args [2][LINE_SIZE], Info I);

// Mostra a solução do jogo (caso exista)
bool mostrarSolucao (char cmd, char args [2][LINE_SIZE], Info I);

// Apaga o histoŕico de jogadas
bool apagaHistorico (char cmd, char args [2][LINE_SIZE], Info I);

// Revela a pontuação atual
bool imprimePont (char cmd, char args [2][LINE_SIZE], Info I);

// Permite ao jogador criar um jogo novo
bool criarJogo (char cmd, char args [2][LINE_SIZE], Info I);

// Permite ao jogador eliminar um jogo
bool eliminarJogo (char cmd, char args [2][LINE_SIZE], Info I);

// Lista os comandos do jogo
bool listarComandos (char cmd, char args [2][LINE_SIZE], Info I);

// Explica o objetivo e as regras do jogo
bool explicaJogo (char cmd, char args [2][LINE_SIZE], Info I);





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

// Função que realiza a lógica dos comandos 'h' (listarComandos) e 'e' (explicaJogo)
int logicaListarInfo (char *arg);





// Funções auxiliares à lógica dos comandos - ComandosLogicaA.c

// Guarda o tabuleiro num ficheiro
void guardaInfo (FILE *Jogo, Info I);

// Guarda o histórico de jogadas no ficheiro
void guardaJogadas (FILE *Jogo, Info I);

// Lê a informação de um ficheiro
int leFicheiro (FILE *Jogo, Info I);

// Lê a informação de uma linha de jogadas
int leLinhaJogadas (FILE *Jogo, Info I);

// Procura infrações em relação à existência de casas riscadas juntas e de casa brancas na mesma linha ou coluna
int verificaInfracoes (Info I, int flag);

// Procura infrações em relação à existência de um caminho ortogonal entre todas as letras
int verificaCaminhoOrtogonal (Info I, int flag);

// Realiza alterações necessárias na posição atual
int ajudaUmaVez (Info I, int versaoComando);

// Resolve o jogo (se possível)
int resolve (Info I, int dL, int dC, char TabuleiroOriginal [dL][dC + 2]);

// Procura infrações no tabuleiro para preencher o tabuleiro de infrações
int preencheTabInfracoes (Info I, int TabInfracoes [I -> dL][I -> dC]);





// Funções auxiliares (gerais) - Auxiliares.c

// Imprime os últimos 'nTabs' tabuleiros
int visualizaUltimosTabuleiros (Info I, int nTabs, int flag);

// Forma uma jogada
void formaJogada (Jogada *JNova, int linha, char coluna, char c);

// Realiza a um tabuleiro as alterações de uma jogada
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





// Funções para imprimir o tabuleiro - Tab.c

// Imprime um tabuleiro
void imprimeTabuleiro (int dL, int dC, char **Tabuleiro, int nTabuleiro, int flag);

// Imprime um tabuleiro destacando as infrações
void destacaInfracoes (int dL, int dC, char **Tabuleiro, int TabInfracoes [dL][dC], int eSolucao);