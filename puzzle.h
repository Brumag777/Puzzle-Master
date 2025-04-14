#include <stdbool.h> 
#include <assert.h>

#define LINE_SIZE 1024



typedef struct tabuleiros {
    char ***Tabuleiros;
    int sp;
} Tabuleiros;



typedef struct infoJogo {
    int linhas;
    int colunas;
    char **Tabuleiro;
    Tabuleiros *TAnteriores;
} IJ;



typedef struct estado {
    bool looping;
    IJ *info;
} ESTADO;



typedef bool (*COMANDO) (char cmd, char *arg, ESTADO *e);



int coordenadaValida (int l, char c, int linhas, int colunas);
void visualizarTabuleiro (IJ *InfoJogo);
int tabuleiroValido(IJ *InfoJogo);
void resetaTabuleiro (IJ *InfoJogo);
void iniciarTabuleiro (ESTADO *e);



bool gravar (char cmd, char *arg, ESTADO *e);
bool ler (char cmd, char *arg, ESTADO *e);
bool sair (char cmd, char *arg, ESTADO *e);
bool mudarParaMaiuscula (char cmd, char *arg, ESTADO *e); 
bool mudarParaVazia (char cmd, char *arg, ESTADO *e);
bool listarComandos (char cmd, char *arg, ESTADO *e);



bool auxLer (ESTADO *e, char *arg);