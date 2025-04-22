#include <stdbool.h> 
#include <assert.h>

#define LINE_SIZE 1024

// Histórico de tabuleiros do jogo
typedef struct hist {
    int sp;              // Quantos tabuleiros são considerados (os primeiros sp)
    int cap;             // Capacidade do struct (possui capacidade para cap tabuleiros)
    char ***TAnteriores; // Array de tabuleiros que armazena os tabuleiros anteriores às jogadas (para o comando d)
    int *linhas;         // Quantidade de linhas dos tabuleiros
    int *colunas;        // Quantidade de colunas dos tabuleiros
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





// Funções auxiliares - Auxiliares.c

// Liberta a memória alocada para os tabuleiros - a flag indica se é ou não para libertar também o histórico de tabuleiros
void libertaTabuleiro (IJ *InfoJogo, int flag);

// Inicializa os tabuleiros - a flag indica se é ou não para alocar memórica também para o histórico de tabuleiros
void iniciarTabuleiro (ESTADO *e, int flag);

// Verifica se um caractere é uma letra maiúscula
int eMaiuscula (char c);

// Verifica se um caractere é uma letra minúscula
int eMinuscula (char c);

// Verifica se uma coordenada é válida (isto é, está dentro do tabuleiro)
int coordenadaValida (int l, char c, int linhas, int colunas);

// Verifica se um tabuleiro é válido
int tabuleiroValido(IJ *InfoJogo);

// Verifica se as linhas não possuem casas brancas repetidas
int verificaLinhas (IJ *InfoJogo, char c, int linha, int coluna, int flag);

// Verifica se as colunas não possuem casas brancas repetidas
int verificaColunas (IJ *InfoJogo, char c, int linha, int coluna, int flag);

// Verifica se as casas adjacentes às casas vazias não são vazias
int verificaCasaVazia (IJ *InfoJogo, int linha, int coluna, int flag);

// Calcula quantas letras estão ligadas à letra da posição dada
int contaLetrasLigadas (int linhas, int colunas, int Tabuleiro [linhas][colunas], int l, int c);

// Pinta as casas à volta das casas vazias de branco
int pintaCasas (IJ *InfoJogo, int linha, int coluna);

// Risca as casas que deviam ser vazias
int riscaCasas (IJ *InfoJogo, int linha, int coluna);

// Testa as possibilidades de uma casa minúscula
int testaPossibilidadesCasa (IJ *InfoJogo, int linha, int coluna);

// Percorre a linha para riscar casas que deviam ser vazias
int percorreLinha (IJ *InfoJogo, char c, int linha, int coluna);

// Percorre a coluna para riscar casas que deviam ser vazias
int percorreColuna (IJ *InfoJogo, char c, int linha, int coluna);

// Testa se o jogador já ganhou o jogo
int testeJogo (IJ *I);





// Comandos do jogo - Comandos.c

// Grava o jogo num ficheiro
bool gravar (char cmd, char *arg, ESTADO *e);

// Lê um ficheiro
bool ler (char cmd, char *arg, ESTADO *e);

// Termina o jogo
bool sair (char cmd, char *arg, ESTADO *e);

// Pinta uma casa de branco
bool pintarCasa (char cmd, char *arg, ESTADO *e);

// Muda uma casa para vazia
bool riscarCasa (char cmd, char *arg, ESTADO *e);

// Lista os comandos do jogo
bool listarComandos (char cmd, char *arg, ESTADO *e);

// Desfaz a última jogada
bool desfazerJogada (char cmd, char *arg, ESTADO *e);

// Imprime os últimos tabuleiros armazenados no histórico
bool visualizarHistorico (char cmd, char *arg, ESTADO *e);

// Verifica se existem infrações no tabuleiro
bool verifica (char cmd, char *arg, ESTADO *e);

// Ajuda o jogador realizando jogadas 'obrigatórias' na posição
bool ajuda (char cmd, char *arg, ESTADO *e);

// Ajuda o jogador realizando jogadas 'obrigatórias' repetidamente até não haver nada a alterar
bool ajudaRep (char cmd, char *arg, ESTADO *e);

// Resolve o jogo automaticamente
bool resolveJogo (char cmd, char *arg, ESTADO *e);





// Lógica dos comandos do jogo - ComandosLogica.c

// Função que realiza a lógica do comando 'g' (gravar)
int logicaGravar (char *nomeFicheiro, ESTADO *e);

// Função que realiza a lógica do comando 'l' (ler)
int logicaLer (char *nomeFicheiro, ESTADO *e);

// Função que realiza a lógica do comando 's' (sair)
int logicaSair (char *arg, ESTADO *e);

// Função que realiza a lógica do comando 'b' (pintarCasa)
int logicaPintarCasa (char *coordenada, ESTADO *e);

// Função que realiza a lógica do comando 'r' (riscarCasa)
int logicaRiscarCasa (char *coordenada, ESTADO *e);

// Função que realiza a lógia do comando 'h' (listarComandos)
int logicaListarComando (char *arg, ESTADO *e);

// Função que realiza a lógica do comando 'd' (desfazerJogada)
int logicaDesfazerJogada (char *nTab, ESTADO *e);

// Função que realiza a lógica do comando 'V' (vizualizarHistorico)
int logicaVizualizarHistorico (char *nTab, ESTADO *e);

// Função que realiza a lógica do comando 'v' (verifica)
int logicaVerifica (char *arg, ESTADO *e);

// Função que realiza a lógica do comando 'a' (ajuda)
int logicaAjuda (char *arg, ESTADO *e);

// Função que realiza a lógica do comando 'A' (ajudaRep)
int logicaAjudaRep (char *arg, ESTADO *e);

// Função que realiza a lógico do comando 'R'
int logicaResolveJogo (char *arg, ESTADO *e);





// Auxiliares à lógica dos comandos - ComandosLogicaAuxiliares.c

// Desfaz a última jogada do jogo
int desfazUmaJogada (ESTADO *e);

// Procura infrações em relação à existência de casas riscadas juntas e de casa brancas na mesma linha ou coluna
int verificaInfracoes (IJ *I, int flag);

// Procura infrações em relação à existência de um caminho ortogonal entre todas as letras
int verificaCaminhoOrtogonal (IJ *I);

// Realiza alterações necessárias na posição atual
int ajudaUmaVez (IJ *I);

// Resolve o jogo (se possível)
int resolve (IJ *I);





// Funções relativas ao histórico de tabuleiros - Stack.c

// Imprime os últimos q tabuleiros armazenados no histórico
void visualizaUltimosTabuleiros (Hist h, int q, int flag);

// Inicializa o histórico
void inicializaStack (Hist h);

// Adiciona um tabuleiro ao histórico
void pushStack (Hist h, char **novoTabuleiro, int linhas, int colunas);

// Remove um tabuleiro do histórico
void popStack (Hist h);

// Liberta a memória alocada para o histórico
void libertaStack (Hist h);