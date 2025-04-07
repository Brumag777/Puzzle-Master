typedef struct infoJogo {
    int linhas;
    int colunas;
    char **Tabuleiro;
    char Jogo [32];
} IJ;

int iniciaJogo (IJ *InfoJogo);

void mudaCasaParaMaiuscula (IJ *InfoJogo);  
void mudaCasaParaVazio (IJ *InfoJogo);
void listaComandos ();

int coordenadaValida (int l, char c, int linhas, int colunas);

void vizualizaTabuleiro (IJ InfoJogo);