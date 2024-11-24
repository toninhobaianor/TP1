#ifndef _LABIRINTO_H
#define _LABIRINTO_H

// função para ler do arquivo txt e colocar o labirinto em uma variavel
void pega_labirinto(int *m, int *n, int M[10][10],char *nome_arquivo);
// função para ocultar o labirinto
// função de consulta()
void inicia_labiririnto(int M[10][10]);
void direcoes_possiveis(int M[10][10], char *direcoes);
void modifica_labirinto(int M[10][10],char* direcao);

// Estrutura que define uma ação no labirinto (usada para sockets)
struct action {
    int type;               // Tipo de ação
    int moves[100];         // Vetor de movimentos possíveis
    int board[10][10];      // Matriz representando o labirinto
};

#endif