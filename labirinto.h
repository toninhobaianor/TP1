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
void pega_labirinto(int *m, int *n, Action *M,char *nome_arquivo);
void inicializa_action(Action *M);
char *print_direcoes_possiveis(Action *M);
// função para ocultar o labirinto
// função de consulta()
void inicia_labiririnto(Action *M);
void direcoes_possiveis(Action *M);
int modifica_labirinto(Action *M, char *direcao);



#endif