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
    else if (c != 9 && c != 10) {
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
    printf("%c", c);
  }
    fclose(arq);
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