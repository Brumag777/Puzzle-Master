#include <stdbool.h> 
#include <assert.h>

#define LINE_SIZE 1024



typedef struct hist {
    int sp;
    int cap;
    char ***TAnteriores;
} HIST, *Hist;



typedef struct infoJogo {
    int linhas;
    int colunas;
    char **Tabuleiro;
    Hist hTabuleiros;
} IJ;



typedef struct estado {
    bool looping;
    IJ *info;
} ESTADO;



typedef bool (*COMANDO) (char cmd, char *arg, ESTADO *e);



int eMaiuscula (char c);
int coordenadaValida (int l, char c, int linhas, int colunas);
void visualizarTabuleiro (IJ *InfoJogo);
int tabuleiroValido(IJ *InfoJogo);
void libertaTabuleiro (IJ *InfoJogo);
void iniciarTabuleiro (ESTADO *e);
int verificaLinhas (IJ *InfoJogo, char c, int linha, int coluna);
int verificaColunas (IJ *InfoJogo, char c, int linha, int coluna);
int verificaHashtag (IJ *InfoJogo, int linha, int coluna);



bool gravar (char cmd, char *arg, ESTADO *e);
bool ler (char cmd, char *arg, ESTADO *e);
bool sair (char cmd, char *arg, ESTADO *e);
bool mudarParaMaiuscula (char cmd, char *arg, ESTADO *e); 
bool mudarParaVazia (char cmd, char *arg, ESTADO *e);
bool listarComandos (char cmd, char *arg, ESTADO *e);
bool desfazerJogada (char cmd, char *arg, ESTADO *e);
bool vizualizarStack (char cmd, char *arg, ESTADO *e);
bool verifica (char cmd, char *arg, ESTADO *e);



bool auxLer (ESTADO *e, char *arg);



void vizualizaUltimosTabuleiros (Hist h, int linhas, int colunas, int q);
void inicializaStack (Hist h);
void pushStack (Hist h, char **novoTabuleiro, int linhas);
void popStack (Hist h, int linhas);
void libertaStack (Hist h, int linhas);