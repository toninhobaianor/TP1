#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../labirinto.h"
#include <ctype.h>

#define MAX_SIZE 10
#define BUFSZ 1024

void remove_espacos( char * out, const char * in ){
    const char * p = in;
    int i = 0;

    while( *p ){
        if( !isspace(*p) ){
          out[i++] = *p;
        }
        p++;
    }
    out[i] = 0;
    //return out;
}

void inicializa_action(Action *M){
  M->moves[0] = 0;
  M->moves[1] = 0;
  M->moves[2] = 0;
  M->moves[3] = 0;
  for(int i = 0; i < 10; i++){
    for(int j = 0; j < 10; j++){
      M->board[i][j] = 0;
    }
  }
}


void pega_labirinto(int *m, int *n, Action *M, char *nome_arquivo){
  FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(EXIT_FAILURE); // Erro ao abrir arquivo
    }

    // Ler o labirinto no formato de matriz 10x10
    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < 5; j++) {
            char c;
            fscanf(arquivo, " %c", &c);  // Lê um caractere, o espaço antes de %c ignora espaços em branco
            M->board[i][j] = (int) c - 48; // Converte o caractere em seu valor ASCII
        }
    }

    // Fechar o arquivo
    fclose(arquivo);
}

int *inicia_labiririntos(Action *M,Action *N){
  int encontrei = 0;
  int aux;
  int *posi = malloc(10 * sizeof(int)); 
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if((M->board[i][j]) == 2){
              encontrei = 1;

              M->board[i][j] = 5;
              N->board[i][j] = 5;

              N->board[i + 1][j] = M->board[i + 1][j];
              N->board[i][j + 1] = M->board[i][j + 1];
              N->board[i - 1][j] = M->board[i - 1][j];
              N->board[i][j - 1] = M->board[i][j - 1];

              posi[0] = i;
              posi[1] = j;

              if(encontrei == 1){
                j = j + 2;
                aux = i + 1;
              }
            }
            if(aux == i){
              j = j + 1;
              aux = -1;
            }
            else{
              N->board[i][j] = 4;
            }
        }
    }
  return posi;
}
void direcoes_possiveis(Action *M, int *posi){
  int i = posi[0];
  int j = posi[1];
  if(M->board[i - 1][j] == 1 || M->board[i - 1][j] == 2 || M->board[i - 1][j] == 3){ // up
    M->moves[0] = 1;
    M->type = 4;
  }
  if(M->board[i][j - 1] == 1 || M->board[i][j - 1] == 2 || M->board[i][j - 1] == 3){ // left
    M->moves[3] = 4;
    M->type = 4;
  }
  if(M->board[i + 1][j] == 1 || M->board[i + 1][j] == 2 || M->board[i + 1][j] == 3){  //down
    M->moves[2] = 3;
    M->type = 4;
  }
  if(M->board[i][j + 1] == 1 || M->board[i][j + 1] == 2 || M->board[i][j + 1] == 3){ //right
    M->moves[1] = 2;
    M->type = 4;
  }
}

char *print_direcoes_possiveis(Action *M){
  char *direcoes = malloc(100* sizeof(char));
  if(M->moves[0] == 1){
    direcoes = strcat(direcoes,"Up,");
    //direcoes = "Up,";
  }
  if(M->moves[1] == 2){
    direcoes = strcat(direcoes,"Right,");
    //direcoes = direcoes + "Right,";
  }
  if(M->moves[2] == 3){
    direcoes = strcat(direcoes,"Down,");
   // direcoes += "Down,";
  }
  if(M->moves[3] == 4){
    direcoes = strcat(direcoes,"Left,");
    //direcoes += "Left,";
  }
  return direcoes;
}

void modifica_tipo(Action *m,char *buffer){
  char *res = malloc(10*sizeof(char));
  for(int i = 0; buffer[i] != '\n'; i++){
      res[i] = buffer[i];
  }

  if (strcmp(res,"exit") == 0) {
		m->type = 7;	
	}

  else if (strcmp(res,"start") == 0) {
		m->type = 0;	
	}

  else if (strcmp(res,"right") == 0) {
    m->type = 1;
    m->moves[1] = 2;	
	}

  else if(strcmp(res,"left") == 0){
    m->type = 1;
    m->moves[3] = 4;
  }

  else if(strcmp(res,"down") == 0){
    m->type = 1;
    m->moves[2] = 3;
  }

  else if(strcmp(res,"up") == 0){
    m->type = 1;
    m->moves[0] = 1;
  }

  else if(strcmp(res,"map") == 0) {
		m->type = 2;	
	}

  else if(strcmp(res,"hint") == 0) {
		m->type = 3;	
	}

  else if (strcmp(res,"reset") == 0) {
		m->type = 6;	
	}
}

int *modifica_labirinto(Action *M,Action *N,Action *direcao,int *posi){
  int *posicao = malloc(10*sizeof(int));
  int i = posi[0];
  int j = posi[1];
  if(direcao->moves[2] == 3){ //down     
    if(M->board[i + 1][j] == 3){
        M->board[i][j] = 1;
        M->type = 5;
    }
    if(M->board[i + 1][j] == 0){           
    }
    if(M->board[i + 1][j] == 1){
      M->board[i + 1][j] = 5;
      M->board[i][j] = 1;

      N->board[i][j] = 1;
      N->board[i + 1][j] = 5;

      N->board[i + 1][j + 1] = M->board[i + 1][j + 1];
      N->board[i + 1][j - 1] = M->board[i + 1][j - 1];
  
      N->board[i + 2][j + 1] = M->board[i + 2][j + 1];
      N->board[i + 2][j] = M->board[i + 2][j];
      N->board[i + 2][j - 1] = M->board[i + 2][j - 1];


      posicao[0] = i + 1;
      posicao[1] = j;
      M->type = 4;
    }           
  }
  if(direcao->moves[1] == 2){ // right
    if(M->board[i][j + 1] == 3){
      M->board[i][j] = 1;
      M->type = 5;
    }
    if(M->board[i][j + 1] == 0){
    }
    if(M->board[i][j + 1] == 1){
      M->board[i][j + 1] = 5;
      M->board[i][j] = 1;

      N->board[i][j] = 1;
      N->board[i][j + 1] = 5;
      
      N->board[i + 1][j + 1] = M->board[i + 1][j + 1];
      N->board[i + 1][j] = M->board[i + 1][j];
      N->board[i + 1][j + 2] = M->board[i + 1][j + 2];
  
      N->board[i - 1][j] = M->board[i - 1][j];
      N->board[i - 1][j + 1] = M->board[i - 1][j + 1];
      N->board[i - 1][j + 2] = M->board[i - 1][j + 2];

      N->board[i][j + 2] = M->board[i][j + 2];

      posicao[0] = i;
      posicao[1] = j + 1;
      M->type = 4;
    }
  }
  if(direcao->moves[0] == 1){ //up
    if(M->board[i - 1][j] == 3){
      M->board[i][j] = 1;
      M->type = 5;
    }
    if(M->board[i - 1][j] == 0){
    }
    if(M->board[i - 1][j] == 1){
      M->board[i - 1][j] = 5;
      M->board[i][j] = 1;

      N->board[i][j] = 1;
      N->board[i - 1][j] = 5;
  
      N->board[i - 1][j + 1] = M->board[i - 1][j + 1];
      N->board[i - 1][j - 1] = M->board[i - 1][j - 1];

      N->board[i - 2][j - 1] = M->board[i - 2][j - 1];
      N->board[i - 2][j] = M->board[i - 2][j];
      N->board[i - 2][j + 1] = M->board[i - 2][j + 1];

      posicao[0] = i - 1;
      posicao[1] = j;
      M->type = 4;
    }
   }
  if(direcao->moves[3] == 4){ // left
    if(M->board[i][j - 1] == 3){
      M->board[i][j] = 1;
      M->type = 5;
    }
    if(M->board[i][j - 1] == 0){
    }
    if(M->board[i][j - 1] == 1){
      M->board[i][j - 1] = 5;
      M->board[i][j] = 1;

      N->board[i][j] = 1;
      N->board[i][j - 1] = 5;

      N->board[i + 1][j - 1] = M->board[i + 1][j - 1];
      N->board[i + 1][j - 2] = M->board[i + 1][j - 2];
  
      N->board[i - 1][j - 1] = M->board[i - 1][j - 1];
      N->board[i - 1][j - 2] = M->board[i - 1][j - 2];

      N->board[i][j + 1] = M->board[i][j + 1];
      N->board[i][j - 2] = M->board[i][j - 2];

      posicao[0] = i;
      posicao[1] = j - 1;
      M->type = 4;
    }
  }
  return posicao;
}

void Mostra_map(Action *m){
  printf("\n");
  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 5; j++){
      if((m->board[i][j]) == 0){
        printf("# ");
      }
      if((m->board[i][j]) == 1){
        printf("_ ");
      }
      if((m->board[i][j]) == 3){
        printf("X ");
      }
      if((m->board[i][j]) == 2){
        printf("> ");
      }
      if((m->board[i][j]) == 4){
        printf("? ");
      }
      if((m->board[i][j]) == 5){
        printf("+ ");
      }
    }
    printf("\n");
  }
}

void Limpa_movimentos(Action *M){
  M->moves[0] = 0;
  M->moves[1] = 0;
  M->moves[2] = 0;
  M->moves[3] = 0;
}