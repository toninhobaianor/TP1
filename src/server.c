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
    Action board;
    Action res;

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

    while (1) {      
        inicializa_action(&res);
        recv(csock, &res, sizeof(board), 0);
        printf("[msg] Client connected\n");
    
        //start   
        if(res.type == 0){
           inicializa_action(&board);
           pega_labirinto(&Colunas, &Linhas, &board ,nome_arquivo);
           inicia_labiririnto(&board);
           for(int i = 0; i < 5; i++){
                for(int j = 0; j < 5; j++){
                    printf("%i ",board.board[i][j]);
                }
                printf("\n");
            }
           direcoes_possiveis(&board);
           send(csock, &board, sizeof(board), 0);
           
           while(1){
            recv(csock, &res, sizeof(board), 0);
            if(res.type == 1){
                modifica_labirinto(&board,&res);
                send(csock, &board, sizeof(board), 0);
            }
           }
        }
        //exit
        else if(res.type == 7){
            break;
        }
        
    }
    close(csock);
    exit(EXIT_SUCCESS);
}