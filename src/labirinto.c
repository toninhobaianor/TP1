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

void inicia_labiririnto( Action *M ){
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if((M->board[i][j]) == 2){
                M->board[i][j] = 5;
                break;
            }
        }
    }

}
void direcoes_possiveis(Action *M){
  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 5; j++){
      if((M->board[i][j]) == 5){
        if(M->board[i + 1][j] == 1 ){
          M->moves[1] = 2;
          M->type = 4;
        }
        if(M->board[i][j + 1] == 1){
          M->moves[2] = 3;
          M->type = 4;
        }
        if(M->board[i - 1][j] == 1){
          M->moves[3] = 4;
          M->type = 4;
        }
        if(M->board[i][j - 1] == 1){
          M->moves[0] = 1;
          M->type = 4;
        }
        break;
      }
    }
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

  if (strcmp(res,"start") == 0) {
		m->type = 0;	
	}

  if (strcmp(res,"right") == 0) {
    	m->type = 1;
      m->moves[1] = 2;	
	}

  if(strcmp(res,"left") == 0){
    m->type = 1;
    m->moves[3] = 4;
  }

  if(strcmp(res,"down") == 0){
    m->type = 1;
    m->moves[2] = 3;
  }

  if(strcmp(res,"up") == 0){
    m->type = 1;
    m->moves[0] = 1;
  }

  if (strcmp(res,"map") == 0) {
		m->type = 2;	
	}

  if (strcmp(res,"hint") == 0) {
		m->type = 3;	
	}

  if (strcmp(res,"reset") == 0) {
		m->type = 6;	
	}
}

void modifica_labirinto(Action *M,Action *dir){
  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 5; j++){
      if(M->board[i][j] == 5){
        if(dir->moves[2] == 3){            
          if(M->board[i + 1][j] == 3){
            M->type = 5;
          }
          if(M->board[i + 1][j] == 0){           
          }
          if(M->board[i + 1][j] == 1){
            M->board[i + 1][j] = 5;
            M->board[i][j] = 1;
            M->type = 4;
          }
                
        }
        else if(dir->moves[1] == 2){
          if(M->board[i][j + 1] == 3){
            M->board[i][j] = 1;
            M->type = 5;
          }
          if(M->board[i][j + 1] == 0){
          }
          if(M->board[i][j + 1] == 1){
            M->board[i][j + 1] = 5;
            M->board[i][j] = 1;
            M->type = 4;
          }
        }
        else if(dir->moves[0] == 1){
          if(M->board[i - 1][j] == 3){
            M->board[i][j] = 1;
            M->type = 5;
          }
          if(M->board[i - 1][j] == 0){
          }
          if(M->board[i - 1][j] == 1){
            M->board[i - 1][j] = 5;
            M->board[i][j] = 1;
            M->type = 4;
          }
        }
        else if(dir->moves[3] == 4){
          if(M->board[i][j - 1] == 3){
            M->board[i][j] = 1;
            M->type = 5;
          }
          if(M->board[i][j - 1] == 0){
          }
          if(M->board[i][j - 1] == 1){
            M->board[i][j - 1] = 5;
            M->board[i][j] = 1;
            M->type = 4;
          }
        }
        break;
      }
    }
  }
}

void revela_labirinto(Action *m){
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
    }
    printf("\n");
  }
}