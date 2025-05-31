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

// Alteração no tabuleiro
typedef struct alt {
    int L;
    char C;
    char cAnt;
} ALT, *Alt;

// Lista de jogadas
typedef struct lJogadas {
    Alt *Jogada;
    int nAlts;
    struct lJogadas *JAnt;
} LJOGADAS, *LJogadas;

// Informação do jogo
typedef struct info {
    bool aCorrer;
    int nTabuleiro, nJogo;
    int pont;
    int dL, dC;
    char **Tabuleiro;
    LJogadas HJogadas;
} INFO, *Info;

// Função dos comandos do jogo
typedef bool (*Comando) (char, char *, char *, Info);





// Funções relativas à interface dos comandos - Comandos.c

// Termina o jogo
bool sair (char, char *, char *, Info);

// Grava uma save de um jogo
bool gravar (char, char *, char *, Info);

// Lê uma save de um jogo
bool ler (char, char *, char *, Info);

// Imprime a pontuação do jogador
bool imprimePont (char, char *, char *, Info);

// Explica o jogo
bool explica (char, char *, char *, Info);

// Explica os comandos do jogo
bool infoComandos (char, char *, char *, Info);

// Cria um jogo novo
bool criarJogo (char, char *, char *, Info);

// Elimina uma save ou um jogo
bool eliminarJogo (char, char *, char *, Info);

// Indica todos os jogos e as respetivas saves que estão guardados
bool indicaJogos (char, char *, char *, Info);

// Pinta uma casa
bool pintarCasa (char, char *, char *, Info);

// Risca uma casa
bool riscarCasa (char, char *, char *, Info);

// Imprime o(s) último(s) tabuleiro(s)
bool visualizarHistorico (char, char *, char *, Info);

// Verifica se existem infrações no tabuleiro
bool verifica (char, char *, char *, Info);

// Ajuda realizando jogadas necessárias na posição
bool ajuda (char, char *, char *, Info);

// Ajuda realizando jogadas necessárias na posição repetidamente
bool ajudaRep (char, char *, char *, Info);

// Desfaz a(s) última(s) jogada(s)
bool desfazerJogadas (char, char *, char *, Info);

// Resolve o jogo
bool resolveJogo (char, char *, char *, Info);

// Mostra a solução do jogo
bool mostrarSolucao (char, char *, char *, Info);

// Dá uma dica ao jogador
bool dica (char, char *, char *, Info);





// Funções relativas às restrições dos comandos - ComandosRestricoes.c

// Verifica as restrições do comando 's'
int restricoesSair (char *);

// Verifica as restrições do comando 'g'
int restricoesGravar (char *, Info);

// Verifica as restrições do comando 'l'
int restricoesLer (char *, char *);

// Verifica as restrições do comando 'p'
int restricoesImprimePont (char *, Info);

// Verifica as restrições do comando 'e'
int restricoesExplica (char *);

// Verifica as restrições do comando 'c'
int restricoesCriarJogo (char *);

// Verifica as restrições do comando 'E'
int restricoesEliminarJogo (char *, char *);

// Verifica as restrições do comando 'j'
int restricoesIndicaJogos (char *);

// Verifica as restrições dos comandos 'b', 'r' e 'D'
int restricoesMudarCasa (char *, Info);

// Verifica as restrições do comando 'V'
int restricoesVisualizarHistorico (char *arg1, Info I);

// Verifica as restrições do comando 'v'
int restricoesVerifica (char *, Info);

// Verifica as restrições do comando 'a'
int restricoesAjuda (char *, Info);

// Verifica as restrições do comando 'A'
int restricoesAjudaRep (char *, Info);

// Verifica as restrições do comando 'd'
int restricoesDesfazerJogadas (char *, Info);

// Verifica as restrições dos comandos 'R' e 'X'
int restricoesSolucaoJogo (char *, Info);





// Funções relativas à lógica dos comandos - ComandosLogica.c

// Realiza a lógica do comando 's'
void logicaSair (Info);

// Realiza a lógica do comando 'g'
int logicaGravar (char *, Info);

// Realiza a lógica do comando 'l'
int logicaLer (char *, char *, Info);

// Função que realiza a lógica do comando 'h' (infoComandos)
int logicaInfoComandos (char *);

// Função que realiza a lógica do comando 'b' (pintarCasa)
void logicaPintarCasa (char *, Info);

// Função que realiza a lógica do comando 'r' (riscarCasa)
void logicaRiscarCasa (char *, Info);

// Função que realiza a lógica do comando 'v' (verifica)
int logicaVerifica (Info);

// Função que realiza a lógica do comando 'a' (ajuda)
int logicaAjuda (char *, Info);

// Função que realiza a lógica do comando 'A' (ajudaRep)
int logicaAjudaRep (Info);

// Função que realiza a lógica do comando 'd' (desfazerJogadas)
void logicaDesfazerJogadas (char *, Info);

// Função que realiza a lógica dos comando 'R' e 'X' (resolveJogo e mostrarSolucao)
int logicaSolucaoJogo (Info, int);

// Função que realiza a lógica do comando 'D' (dica)
int logicaDica (char *, Info);





// Funções auxiliares à lógica dos comandos - ComandosLogicaA.c

// Guarda a informação do jogo numa save
void guardaInfo (FILE *, Info);

// Lê a informação de uma save
int leSave (FILE *, Info);

// Procura infrações em relação à existência de casas riscadas juntas e de casa brancas na mesma linha ou coluna
int verificaInfracoes (Info, int);

// Procura infrações em relação à existência de um caminho ortogonal entre todas as letras
int verificaCaminhoOrtogonal (Info, int);

// Procura infrações no tabuleiro para preencher o tabuleiro de infrações
int preencheTabInfracoes (Info I, int [I -> dL][I -> dC]);

// Realiza alterações necessárias na posição atual
int ajudaUmaVez (Info, int);

// Resolve o jogo (se possível)
int resolve (Info, int dL, int dC, char [dL][dC + 2]);





// Funções auxiliares às auxiliares à lógica dos comandos ComandosLogicaAA.c

// Guarda o histórico de jogadas numa save
void guardaJogadas (FILE *, Info);

// Lê uma jogada de uma save
int leJogada (FILE *, Info);

// Procura infrações numa linha do tabuleiro
int procuraInfracoesL (Info I, char, int, int, int [I -> dL][I -> dC]);

// Procura infrações numa coluna do tabuleiro
int procuraInfracoesC (Info I, char, int, int, int [I -> dL][I -> dC]);

// Procura casas vazias adjacentes a outras
int procuraInfracoesV (Info I, int, int, int [I -> dL][I -> dC]);

// Verifica se as linhas não possuem casas brancas repetidas
int verificaLinhas (Info, char, int, int, int);

// Verifica se as colunas não possuem casas brancas repetidas
int verificaColunas (Info, char, int, int, int);

// Verifica se as casas adjacentes às casas vazias não são vazias
int verificaCasaVazia (Info, int, int, int);

// Risca as casas que deviam ser vazias
int riscaCasasAux (Info, int, int);

// Percorre o tabuleiro para riscar casas que não podem ser brancas pela existência de casas brancas iguais na mesma linha ou coluna
int riscaCasas (Info);

// Pinta as casas à volta das casas vazias de branco
int pintaCasasAux (Info, int, int);

// Percorre o tabuleiro para pintar casas à volta das casas vazias de branco
int pintaCasas (Info);

// Testa as possibilidades de uma casa minúscula
int testaPossibilidadesCasaAux (Info, int, int);

// Percorre o tabuleiro para pintar de branco as casas que não podem ser vazias por bloquear letras
int testaPossibilidadesCasa (Info);





// Funções auxiliares - Auxiliares.c

// Forma o nome de um ficheiro
void formaNomeFicheiro (char *, char *, char *);

// Verifica se um tabuleiro é válido
int tabuleiroValido (int, int, char **);

// Verifica se as jogadas são válidas
int jogadasValidas (Info);

// Verifica se um caractere é uma letra maiúscula
int eMaiuscula (char);

// Verifica se um caractere é uma letra minúscula
int eMinuscula (char);

// Verifica se uma coordenada é válida (isto é, está dentro do tabuleiro)
int coordenadaValida (int, char, int, int);

// Forma uma jogada
void formaJogada (Alt *, int, char, char);

// Calcula o valor de uma pontuação (1 é alto, 2 é médio, 3 é baixo)
int valorPont (int, int, int);

// Realiza a um tabuleiro as alterações de uma jogada
void realizaAlteracoesJogada (char **, Alt *, int);

// Calcula quantas letras estão ligadas à letra da posição dada
int contaLetrasLigadas (int linhas, int colunas, int [linhas][colunas], int, int);

// Percorre a linha para riscar casas que deviam ser vazias
int percorreLinha (Info, char, int);

// Percorre a coluna para riscar casas que deviam ser vazias
int percorreColuna (Info, char, int);

// Cria e adiciona uma jogada ao histórico comparando dois tabuleiros
void adicionaJogada (Info I, int dL, int dC, char [dL][dC + 2], int);

// Testa se o jogador já ganhou o jogo
int testeJogo (Info);





// Funções relativas à gestão de memória - MemoryManagement.c

// Inicializa a informação do jogo
Info inicializaInfo ();

// Liberta a memória alocada para a informação do jogo
void libertaInfo (Info);

// Liberta a memória alocada para o tabuleiro do jogo
void libertaTabuleiro (Info);

// Liberta a memória alocada para a lista de jogadas do jogo
void libertaLJogadas (Info);

// Liberta a memória alocada para uma jogada
void libertaJogada (Alt *, int);

// Aloca memória para o tabuleiro
void inicializaTabuleiro (Info);





// Funções relativas às listas - Listas.c

// Adiciona uma jogada ao histórico
void addJogada (Info, Alt *, int);

// Remove uma jogada do histórico
void remJogada (Info);

// Inverte o histórico de jogadas
LJogadas inverteHistorico (LJogadas);





// Funções de interface - Interface.c

// Imprime um tabuleiro
void imprimeTabuleiro (int, int, char **, int, int);

// Imprime os últimos 'nTabs' tabuleiros
void visualizaUltimosTabuleiros (Info, int, int);

// Imprime um tabuleiro destacando as infrações
void imprimeTabDestacado (int dL, int dC, char **, int [dL][dC], int, bool);

// Imprime a mensagem inicial
void imprimeMensagemInicial ();

// Sugere ao jogador que grave o jogo
int pretendeGravar (Info);

// Confirma se o jogador pretende proceder
int pretendeProceder ();

// Explica o jogo
void imprimeExplicacaoJogo ();

// Imprime a lista de comandos do jogo
void imprimeListaComandos ();

// Imprime informação acerca de um comando
void imprimeInfoComando (char);

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

// Explica o comando 'e'
void imprimeInfoCe ();

// Explica o comando 'D'
void imprimeInfoCD ();

// Explica o comando 'X'
void imprimeInfoCX ();

// Imprime uma mensagem que indica que o tabuleiro está finalizado
void imprimeMensagemFim (Info I);

// Avisa de uma infração numa linha
void avisaInfracaoLinha (Info, char, int, char, char, int);

// Avisa de uma infração numa coluna
void avisaInfracaoColuna (Info, char, char, int, int, int);

// Avisa de uma infração de casas vazias juntas
void avisaInfracaoCVazias (Info, char, int, char, int, int);

// Avisa que não existe um caminho ortogonal entre todas as letras
void avisaInfracaoCOrtogonal (Info, int);





// Funções para criar ou eliminar jogos e saves - JogosSaves.c

// Cria um jogo
int criaJogo ();

// Pede ao jogador a informação de um jogo novo
int infoJogoNovo (Info);

// Procura o índice mais baixo que ainda não possui jogo
int procuraJogoMaisBaixo (char *);

// Elimina um jogo ou uma save
int eliminaJS (char *, char *);

// Imprime todos os jogos e as respetivas saves
void imprimeJogos ();

// Imprime os jogos e as respetivas saves existentes
void imprimeSavesJogos (int [100][100], int [100]);