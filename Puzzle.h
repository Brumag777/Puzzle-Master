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

// Desfaz a últimas jogadas
bool desfazerJogada (char cmd, char *arg, Info I);

// Imprime os últimos tabuleiros armazenados no histórico
bool visualizarHistorico (char cmd, char *arg, Info I);

// Verifica se existem infrações no tabuleiro
bool verifica (char cmd, char *arg, Info I);

// Ajuda o jogador realizando jogadas 'obrigatórias' na posição
bool ajuda (char cmd, char *arg, Info I);

// Ajuda o jogador realizando jogadas 'obrigatórias' repetidamente até não haver nada a alterar
bool ajudaRep (char cmd, char *arg, Info I);

// Resolve o jogo automaticamente
bool resolveJogo (char cmd, char *arg, Info I);

// Mostra o número de jogadas atual
bool imprimeNJogadas (char cmd, char *arg, Info I);

// Lista os comandos do jogo
bool listarComandos (char cmd, char *arg, Info I);

// Mostra a solução do jogo (caso exista)
bool mostrarSolucao (char cmd, char *arg, Info I);





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

// Função que realiza a lógica do comando 'd' (desfazerJogada)
int logicaDesfazerJogada (char *nTab, Info I);

// Função que realiza a lógica do comando 'V' (vizualizarHistorico)
int logicaVizualizarHistorico (char *nTab, Info I);

// Função que realiza a lógica do comando 'v' (verifica)
int logicaVerifica (char *arg, Info I);

// Função que realiza a lógica do comando 'a' (ajuda)
int logicaAjuda (char *arg, Info I);

// Função que realiza a lógica do comando 'A' (ajudaRep)
int logicaAjudaRep (char *arg, Info I);

// Função que realiza a lógica do comando 'R'
int logicaResolveJogo (char *arg, Info I, int flag);

// Função que realiza a lógica do comando 'j' (imprimeNJogadas)
int logicaImprimeNJogadas (char *arg, Info I);

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

// Procura infrações em relação à existência de casas riscadas juntas e de casa brancas na mesma linha ou coluna
int verificaInfracoes (Info I, int flag);

// Procura infrações em relação à existência de um caminho ortogonal entre todas as letras
int verificaCaminhoOrtogonal (Info I, int flag);

// Realiza alterações necessárias na posição atual
int ajudaUmaVez (Info I);

// Resolve o jogo (se possível)
int resolve (Info I, int dL, int dC, char TabuleiroOriginal [dL][dC + 2]);





// Funções auxiliares (gerais) - Auxiliares.c

// Imprime os últimos 'nTabs' tabuleiros
void visualizaUltimosTabuleiros (Info I, int nTabs, int flag);

// Imprime um tabuleiro
void imprimeTabuleiro (char **Tabuleiro, int dL, int dC, int nTabuleiro, int flag);

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