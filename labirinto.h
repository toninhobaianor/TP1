#ifndef _LABIRINTO_H
#define _LABIRINTO_H

// Estrutura que define uma ação no labirinto (usada para sockets)
typedef struct{
    int type;               // Tipo de ação
    int moves[100];         // Vetor de movimentos possíveis
    int board[10][10];      // Matriz representando o labirinto
}Action;


// função para ler do arquivo txt e colocar o labirinto em uma variavel
void pega_labirinto(int *tam, Action *M,char *nome_arquivo);
// função que preenche a matriz(board) e o vetor(moves) com zeros
void inicializa_action(Action *M);
// função para mostrar na tela todas as possiveis direções
void print_direcoes_possiveis(Action *M);
// função que dependendo do que estiver no buffer altera o tipo do struct e também altera o vetor moves
void modifica_tipo(Action *m,char *buffer);
// mostra na tela a matriz com os respectivos caractres ao inves dos numeros
void Mostra_map(Action *M);
// limpa o vetor de movimentos
void Limpa_movimentos(Action *M);
// Coloca o jogador dentro do labirinto e faz uma copia do labirinto escondendo os movimentos possiveis
int *inicia_labiririntos(Action *M,Action *N,int *tam);
// Olha a partir da posição atual para quais direções podemos ir
void direcoes_possiveis(Action *M,int *posi);
// olha os movimentos possiveis,e move o jogador para as proximas possições
int *modifica_labirinto(Action *M, Action *N,Action *dir,int *posi,int init);
//verifica se o movimento recebido e valido
int verifica_moves(Action *manda,int* recebido);

#endif