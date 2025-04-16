#include <stdio.h>

// Imprime um tabuleiro
void imprimeTabuleiro (char Tabuleiro [5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++)
            printf ("%c ", Tabuleiro [i][j]);
        putchar ('\n');
    }
}



// Verifica se um caractere é uma letra maiúscula
int eMaiuscula (char c) {
    return c >= 'A' && c <= 'Z';
}



// Verifica se uma coordenada é válida (isto é, está dentro do tabuleiro)
int coordenadaValida (int l, char c, int linhas, int colunas) {
    return (!(c < 'a' || c >= 'a' + colunas || l < 0 || l >= linhas));
}



// Verifica se existe um caminho desde uma casa branca a outra
int verificaCaminho (char Tabuleiro [5][5], int l1, int c1, int l2, int c2, int linhas, int colunas) {

    if (Tabuleiro [l2][c2] == '#') return 0;

    if ((l1 - l2) * (l1 - l2) + (c1 - c2) * (c1 - c2) == 1) return 1;

    // Verifica a casa acima
    if (coordenadaValida (l1 - 1, c1 + 'a', linhas, colunas) && eMaiuscula (Tabuleiro [l1 - 1][c1])) {
        Tabuleiro [l1][c1] += 'a' - 'A';
        if (verificaCaminho (Tabuleiro, l1 - 1, c1, l2, c2, linhas, colunas)) {
            Tabuleiro [l1][c1] -= 'a' - 'A';
            return 1;
        }
        Tabuleiro [l1][c1] -= 'a' - 'A';
    }

    // Verifica a casa abaixo
    if (coordenadaValida (l1 + 1, c1 + 'a', linhas, colunas) && eMaiuscula (Tabuleiro [l1 + 1][c1])) {
        Tabuleiro [l1][c1] += 'a' - 'A';
        if (verificaCaminho (Tabuleiro, l1 + 1, c1, l2, c2, linhas, colunas)) {
            Tabuleiro [l1][c1] -= 'a' - 'A';
            return 1;
        }
        Tabuleiro [l1][c1] -= 'a' - 'A';
    }

    // Verifica a casa à esquerda
    if (coordenadaValida (l1, c1 + 'a' - 1, linhas, colunas) && eMaiuscula (Tabuleiro [l1][c1 - 1])) {
        Tabuleiro [l1][c1] += 'a' - 'A';
        if (verificaCaminho (Tabuleiro, l1, c1 - 1, l2, c2, linhas, colunas)) {
            Tabuleiro [l1][c1] -= 'a' - 'A';
            return 1;
        }
        Tabuleiro [l1][c1] -= 'a' - 'A';
    }

    // Verifica a casa à direita
    if (coordenadaValida (l1, c1 + 'a' + 1, linhas, colunas) && eMaiuscula (Tabuleiro [l1][c1 + 1])) {
        Tabuleiro [l1][c1] += 'a' - 'A';
        if (verificaCaminho (Tabuleiro, l1, c1 + 1, l2, c2, linhas, colunas)) {
            Tabuleiro [l1][c1] -= 'a' - 'A';
            return 1;
        }
        Tabuleiro [l1][c1] -= 'a' - 'A';
    }

    return 0;
}



// Função principal
int main () {

    char Tabuleiro [5][5] = {{'E', '#', 'A', 'D', 'C'},
                             {'D', 'C', '#', 'E', '#'},
                             {'B', '#', 'D', 'C', 'E'},
                             {'C', 'D', 'E', '#', 'B'},
                             {'A', '#', 'C', 'B', '#'}};

    imprimeTabuleiro (Tabuleiro);
    putchar ('\n');

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf ("%d ", verificaCaminho (Tabuleiro, 0, 0, i, j, 5, 5));
        }
        putchar ('\n');
    }

    return 0;
}