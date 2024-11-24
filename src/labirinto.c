#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../labirinto.h"
#include <ctype.h>

void pega_labirinto(int *m, int *n, int M[10][10], char *nome_arquivo){
  FILE *arq;
  char c;     
  arq = fopen(nome_arquivo, "rt");
  if (arq == NULL) {
    printf("Problemas na abertura do arquivo\n");
    exit(EXIT_FAILURE);
  }
  int i = 0;  
  int j = 0;  

  while (1) {  
    c = fgetc(arq);
    if (c == EOF) {
      *n = i;  
      break; 
    } 
    // Se o caractere não for tabulação ('\t' = ASCII 9) ou nova linha ('\n' = ASCII 10)
    else if (c != 9 && c != 10 && c != 32) {
      M[i][j] = c-48;  // Armazena o caractere na matriz
      j++;          // Avança para a próxima coluna
    } 
    // Se o caractere for uma nova linha ('\n')
    else if (c == 10) {
      *m = j;  // Atualiza o número de colunas da matriz
      i++;     // Avança para a próxima linha
      j = 0;   // Reseta o índice de colunas
    }
    // Exibe o caractere lido na tela
    //printf("%c", c);
  }
    fclose(arq);
}

void inicia_labiririnto(int M[10][10]){
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if((M[i][j]) == 2){
                M[i][j] = 5;
                break;
            }
        }
    }

}
void direcoes_possiveis(int M[10][10], char *direcoes){
  direcoes[0] = '0';
  direcoes[1] = '0';
  direcoes[2] = '0';
  direcoes[3] = '0';
  for(int i = 0; i < 10; i++){
    for(int j = 0; j < 10; j++){
      if((M[i][j]) == 5){
        if(M[i][j + 1] == 1 ){
          direcoes[1] = '2';
        }
        if(M[i + 1][j] == 1){
          direcoes[2] = '3';
        }
        if(M[i][j - 1] == 1){
          direcoes[3] = '4';
        }
        if(M[i - 1][j] == 1){
          direcoes[0] = '1';
        }
        break;
      }
    }
  }
}

int modifica_labirinto(int M[10][10],char* direcao){
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if(M[i][j] == 5){
                if(strcmp(direcao,"down")){
                  if(M[i][j + 1] == 3){
                    M[i][j] = 1;
                    return 1;
                  }
                    M[i][j + 1] = 5;
                    M[i][j] = 1;
                }
                if(strcmp(direcao,"right")){
                    if(M[i + 1][j] == 3){
                      M[i][j] = 1;
                      return 1;
                    }
                    M[i + 1][j] = 5;
                    M[i][j] = 1;
                }
                if(strcmp(direcao,"up")){
                    if(M[i][j - 1] == 3){
                      M[i][j] = 1;
                      return 1;
                    }
                    M[i][j - 1] = 5;
                    M[i][j] = 1;
                }
                if(strcmp(direcao,"left")){
                    if(M[i - 1][j] == 3){
                      M[i][j] = 1;
                      return 1;
                    }
                    M[i - 1][j] = 5;
                    M[i][j] = 1;
                }
                break;
            }
        }
    }
    return 0;
}




  /*
  char **result;
  result = malloc (10 * sizeof (char));
  for (int j = 0; j < 5; j++){
    result[j] = malloc (5 * sizeof (char)) ;
  }
    
  FILE *arq;
  arq = fopen(nome_arquivo, "r");
  if (arq == NULL){
    printf("Problemas na abertura do arquivo\n");
    exit(EXIT_FAILURE);
  }
  int i = 0;
  //int j = 0;
  while (!feof(arq)){
    fgets(Linha, 100, arq);
    printf("%s\n",Linha);
    //result[i] = Linha;
    printf("%s\n",result[i]);
    //Linha = NULL;
    //result[i][j] = c;
    for(int j = 0; j <= 4; j++){
      for (int j = 0; j <= 4; j++){
        result[i][j] = c;
      }
      printf("%s",result[i]);
    }

    //printf("\n%s\n",Linha);
    //printf("\n%i\n",i);
    //for(int j = 0; j <= 4 ;j++){
      //result[i][j] = Linha[j];
    //}
    strcpy(result[i], Linha);
    i++;
    
  }
  fclose(arq);
  return result;
  */