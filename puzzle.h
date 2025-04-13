#include <stdbool.h> 
#include <assert.h>

#define LINE_SIZE 1024



typedef struct infoJogo {
    int linhas;
    int colunas;
    char **Tabuleiro;
    char Jogo [32];
} IJ;



typedef struct estado {
    bool looping;
    IJ *info;
} ESTADO;



typedef bool (*COMANDO) (char cmd, char *arg, ESTADO *e);



int coordenadaValida (int l, char c, int linhas, int colunas);
void visualizarTabuleiro (IJ *InfoJogo);
int tabuleiroValido(IJ *InfoJogo);
void libertarTabuleiro (IJ *InfoJogo);
void iniciarTabuleiro(ESTADO *e);



bool gravar (char cmd, char *arg, ESTADO *e);
bool ler (char cmd, char *arg, ESTADO *e);
bool sair (char cmd, char *arg, ESTADO *e);
bool mudarParaMaiuscula (char cmd, char *arg, ESTADO *e); 
bool mudarParaVazia (char cmd, char *arg, ESTADO *e);
bool listarComandos (char cmd, char *arg, ESTADO *e);



bool auxLer(ESTADO *e, char *arg);