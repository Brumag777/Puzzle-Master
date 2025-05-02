#include <stdbool.h> 
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_SIZE 1024

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
    int nJogadas;
    int dL;
    int dC;
    char **Tabuleiro;
    LJogadas HJogadas;
} INFO, *Info;

// Função dos comandos do jogo
typedef bool (*COMANDO) (char cmd, char *arg, Info I);





// Funções relativas à interface dos comandos - Comandos.c

// Grava o jogo num ficheiro
bool gravar (char cmd, char *arg, Info I);

// Lê um ficheiro
bool ler (char cmd, char *arg, Info I);

// Termina o jogo
bool sair (char cmd, char *arg, Info I);

// Pinta uma casa de branco
bool pintarCasa (char cmd, char *arg, Info I);

// Muda uma casa para vazia
bool riscarCasa (char cmd, char *arg, Info I);

// Imprime os últimos tabuleiros armazenados no histórico
bool visualizarHistorico (char cmd, char *arg, Info I);

// Lista os comandos do jogo
bool listarComandos (char cmd, char *arg, Info I);





// Funções relativas à lógica dos comandos - ComandosLogica.c

// Função que realiza a lógica do comando 'g' (gravar)
int logicaGravar (char *nomeFicheiro, Info I);

// Função que realiza a lógica do comando 'l' (ler)
int logicaLer (char *nomeFicheiro, Info I);

// Função que realiza a lógica do comando 's' (sair)
int logicaSair (char *arg, Info I);

// Função que realiza a lógica do comando 'b' (pintarCasa)
int logicaPintarCasa (char *coordenada, Info I);

// Função que realiza a lógica do comando 'r' (riscarCasa)
int logicaRiscarCasa (char *coordenada, Info I);

// Função que realiza a lógica do comando 'V' (vizualizarHistorico)
int logicaVizualizarHistorico (char *nTab, Info I);

// Função que realiza a lógia do comando 'h' (listarComandos)
int logicaListarComandos (char *arg, Info I);





// Funções auxiliares à lógica dos comandos - ComandosLogicaAuxiliares.c

// Guarda o tabuleiro num ficheiro
void guardaInfo (FILE *Jogo, Info I);

// Guarda o histórico de jogadas no ficheiro
void guardaJogadas (FILE *Jogo, Info I);

// Lê a informação de um ficheiro
int leFicheiro (FILE *Jogo, Info I);

// Lê a informação de uma linha de jogadas
int leLinhaJogadas (FILE *Jogo, Info I);





// Funções auxiliares (gerais) - Auxiliares.c

// Imprime os últimos 'nTabs' tabuleiros
void visualizaUltimosTabuleiros (Info I, int nTabs, int flag);

// Imprime um tabuleiro
void imprimeTabuleiro (char **Tabuleiro, int dL, int dC, int nTabuleiro);

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
int tabuleiroValido (Info I);

// Verifica se as jogadas são válidas
int jogadasValidas (Info I);





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
void libertaLJogadas (LJogadas *J);

// Liberta a memória alocada para um array de jogadas
void libertaJogadas (Jogada *J, int nJogadas);




// Funções relativas às listas - Lista.c

// Adiciona uma jogada ao histórico
int addJogada (Info I, Jogada *JogadasNovas, int nAlteracoes);

// Remove uma jogada do histórico
void remJogada (Info I);

// Inverte o histórico de jogadas
LJogadas inverteHistorico (LJogadas L);