#ifndef _LABIRINTO_H
#define _LABIRINTO_H
// Estrutura que define uma ação no labirinto (usada para sockets)
typedef struct Action{
    int type;               // Tipo de ação
    int moves[100];         // Vetor de movimentos possíveis
    int board[10][10];      // Matriz representando o labirinto
}Action;

void remove_espacos( char * out, const char * in );
// função para ler do arquivo txt e colocar o labirinto em uma variavel
void pega_labirinto(int *tam, Action *M,char *nome_arquivo);
void inicializa_action(Action *M);
void print_direcoes_possiveis(Action *M);
void modifica_tipo(Action *m,char *buffer);
void Mostra_map(Action *M);
void Limpa_movimentos(Action *M);
// função para ocultar o labirinto
// função de consulta()
int *inicia_labiririntos(Action *M,Action *N);
void direcoes_possiveis(Action *M,int *posi);
int *modifica_labirinto(Action *M, Action *N,Action *dir,int *posi,int init);
int verifica_moves(Action *manda,Action*recebido);

#endif