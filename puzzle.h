#include <stdbool.h> 
#include <assert.h>

#define LINE_SIZE 1024





// Histórico de tabuleiros do jogo
typedef struct hist {
    int sp;              // Quantos tabuleiros são considerados (os primeiros sp)
    int cap;             // Capacidade do struct (possui capacidade para cap tabuleiros)
    char ***TAnteriores; // Array de tabuleiros que armazena os tabuleiros anteriores às jogadas (para o comando d)
} HIST, *Hist;





// Informação principal sobre o jogo
typedef struct infoJogo {
    int linhas;       // Quantidade de linhas do tabuleiro
    int colunas;      // Quantidade de colunas do tabuleiro
    char **Tabuleiro; // Tabuleiro atual do jogo
    Hist hTabuleiros; // Histórico de tabuleiros do jogo
} IJ;





// Estado do jogo
typedef struct estado {
    bool looping; // Se o jogo deve ou não continuar a correr
    IJ *info;     // Informação principal sobre o jogo
} ESTADO;





// Função dos comandos do jogo
typedef bool (*COMANDO) (char cmd, char *arg, ESTADO *e);





// Funções auxiliares - auxiliares.c

// Verifica se um caractere é uma letra maiúscula
int eMaiuscula (char c);

// Verifica se um caractere é uma letra minúscula
int eMinuscula (char c);

// Verifica se uma coordenada é válida (isto é, está dentro do tabuleiro)
int coordenadaValida (int l, char c, int linhas, int colunas);

// Imprime o tabuleiro atual do jogo
void visualizarTabuleiro (IJ *InfoJogo);

// Verifica se um tabuleiro é válido
int tabuleiroValido(IJ *InfoJogo);

// Liberta a memória alocada para os tabuleiros
void libertaTabuleiro (IJ *InfoJogo);

// Inicializa os tabuleiros
void iniciarTabuleiro (ESTADO *e);

// Verifica se as linhas não possuem casas brancas repetidas
int verificaLinhas (IJ *InfoJogo, char c, int linha, int coluna);

// Verifica se as colunas não possuem casas brancas repetidas
int verificaColunas (IJ *InfoJogo, char c, int linha, int coluna);

// Verifica se as casas adjacentes às casas vazias são brancas
int verificaHashtag (IJ *InfoJogo, int linha, int coluna);

// Verifica se existe um caminho desde uma casa branca a outra
int verificaCaminho (IJ *IJ, int l1, int c1, int l2, int c2);

// Função auxiliar ao comando 'l'
bool auxLer (ESTADO *e, char *arg);





// Comandos do jogo - comandos.c

// Grava o jogo num ficheiro
bool gravar (char cmd, char *arg, ESTADO *e);

// Lê um ficheiro
bool ler (char cmd, char *arg, ESTADO *e);

// Termina o jogo
bool sair (char cmd, char *arg, ESTADO *e);

// Pinta uma casa de branco
bool mudarParaMaiuscula (char cmd, char *arg, ESTADO *e);

// Muda uma casa para vazia
bool mudarParaVazia (char cmd, char *arg, ESTADO *e);

// Lista os comandos do jogo
bool listarComandos (char cmd, char *arg, ESTADO *e);

// Desfaz a última jogada
bool desfazerJogada (char cmd, char *arg, ESTADO *e);

// Imprime os últimos tabuleiros armazenados no histórico
bool vizualizarStack (char cmd, char *arg, ESTADO *e);

// Verifica se existem infrações no tabuleiro
bool verifica (char cmd, char *arg, ESTADO *e);





// Funções relativas ao histórico de tabuleiros - Stack.c

// Imprime os últimos q tabuleiros armazenados no histórico
void vizualizaUltimosTabuleiros (Hist h, int linhas, int colunas, int q);

// Inicializa o histórico
void inicializaStack (Hist h);

// Adiciona um tabuleiro ao histórico
void pushStack (Hist h, char **novoTabuleiro, int linhas);

// Remove um tabuleiro do histórico
void popStack (Hist h, int linhas);

// Liberta a memória alocada para o histórico
void libertaStack (Hist h, int linhas);