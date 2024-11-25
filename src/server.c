#include "../common.h"
#include "../labirinto.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>

#define BUFSZ 1024

void usage(int argc, char **argv) {
    printf("usage: %s <v4|v6> <server port>\n", argv[0]);
    printf("example: %s v4 51511\n", argv[0]);
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
    if (argc < 3) {
        usage(argc, argv);
    }

    struct sockaddr_storage storage;
    if (0 != server_sockaddr_init(argv[1], argv[2], &storage)) {
        usage(argc, argv);
    }

    char nome_arquivo[100] = "input/in.txt";
    //nome_arquivo = (char *)(&argv[4]);
    int Colunas = 10;
    int Linhas = 10;
    int board[10][10];

    int s;
    s = socket(storage.ss_family, SOCK_STREAM, 0);
    if (s == -1) {
        logexit("socket");
    }

    int enable = 1;
    if (0 != setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int))) {
        logexit("setsockopt");
    }

    struct sockaddr *addr = (struct sockaddr *)(&storage);
    if (0 != bind(s, addr, sizeof(storage))) {
        logexit("bind");
    }

    if (0 != listen(s, 10)) {
        logexit("listen");
    }

    char addrstr[BUFSZ];
    addrtostr(addr, addrstr, BUFSZ);
    printf("bound to %s, waiting connections\n", addrstr);

    struct sockaddr_storage cstorage;
    struct sockaddr *caddr = (struct sockaddr *)(&cstorage);
    socklen_t caddrlen = sizeof(cstorage);

    int csock = accept(s, caddr, &caddrlen);
    if (csock == -1) {
        logexit("accept");
    }
    
    char caddrstr[BUFSZ];
    addrtostr(caddr, caddrstr, BUFSZ);
    char *dir = malloc(sizeof(100));
    char *res = malloc(sizeof(100));
    char buf[BUFSZ];

    while (1) {      
        memset(buf, 0, BUFSZ);
        recv(csock, buf, BUFSZ, 0);
        printf("[msg] Client connected\n");

		for(int i = 0; i <= 4; i++){
			res[i] = buf[i];
		}
        if(strcmp(res,"start") == 0){
           init: pega_labirinto(&Colunas, &Linhas, board ,nome_arquivo);
           inicia_labiririnto(board);
           for(int i = 0; i < 5; i++){
                for(int j = 0; j < 5; j++){
                    printf("%i",board[i][j]);
                }
                printf("\n");
            }
           direcoes_possiveis(board,dir);

           sprintf(buf, "Possible moves: %s\n", dir);
           send(csock, buf, strlen(buf) + 1, 0);

           while(1){
                recv(csock, buf, BUFSZ, 0);
                /*for(int i = 0; i < sizeof(buf) + 1; i++){
                    if(buf[i] != ' ' || buf[i] != '\n'){
                        res[i] = buf[i];
                    }  
		        }*/
                remove_espacos(res,buf);
                printf("%s , %li",res, sizeof(res));

                if(strcmp(res,"exit") == 0){
                    exit(EXIT_SUCCESS);
                }
                if(strcmp(res,"reset") == 0){
                    printf("starting new game");
                    goto init;
                }

                int aux = modifica_labirinto(board,res);
                printf("\n");
                for(int i = 0; i < 5; i++){
                    for(int j = 0; j < 5; j++){
                        printf("%i",board[i][j]);
                    }
                    printf("\n");
                }
                if(aux == 1){
                    sprintf(buf, "You escaped!\n");
                    send(csock, buf, strlen(buf) + 1, 0);
                    break;
                }
                if(aux == 2){
                    sprintf(buf, "error: you cannot go this way\n");
                    send(csock, buf, strlen(buf) + 1, 0);
                }
                if(aux == 0){
                    direcoes_possiveis(board,dir);
                    sprintf(buf, "Possible moves: %s\n", dir);
                    send(csock, buf, strlen(buf) + 1, 0);
                } 
           }

        }
        else if(strcmp(res,"exit") == 0){
            break;
        }
        else if(strcmp(res,"reset") == 0){
            printf("starting new game");
            goto init;
        }
       else{
        sprintf(buf,"digite uma algo valido\n");
        send(csock, buf, strlen(buf) + 1, 0);
       }
        
    }
    close(csock);
    free(res);
    free(dir);
    exit(EXIT_SUCCESS);
}