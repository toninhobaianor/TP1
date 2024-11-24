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
    int Colunas = 0;
    int Linhas = 0;
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
    size_t count;
    char caddrstr[BUFSZ];
    addrtostr(caddr, caddrstr, BUFSZ);

    while (1) {
        char buf[BUFSZ];
        memset(buf, 0, BUFSZ);
        recv(csock, buf, BUFSZ, 0);
        printf("[msg] Client connected\n");

        char *res = malloc(sizeof(100));
		for(int i = 0; i <= 4; i++){
			res[i] = buf[i];
		}
        if(strcmp(res,"start") == 0){
            pega_labirinto(&Colunas, &Linhas, board ,nome_arquivo);
            /*
            função de verificar movimentos possiveis
            buf == os moviemntos possiveis
            send(csock, buf, strlen(buf) + 1, 0);
            while(1){
            recv(csock, buf, BUFSZ, 0);
            função de andar no labiririnto
            função de verificar moviemntos possiveis
                a função de verificar os moviemntos vai me dizer se cheguei ao fim
            buf == aos moviemntos possiveis
            send(csock, buf, strlen(buf) + 1, 0);
            }*/
            for(int i = 0; i < 5; i++){
                for(int j = 0; j < 5; j++){
                    printf("%d",board[i][j]);
                }
            }
        }
        if(strcmp(res,"exit ") == 0){
            break;
        }

        sprintf(buf, "remote endpoint: %.1000s\n", caddrstr);
        //sprintf(buf, "%s",result);
        count = send(csock, buf, strlen(buf) + 1, 0);
        if (count != strlen(buf) + 1) {
            logexit("send");
        }
        
    }
    close(csock);
    exit(EXIT_SUCCESS);
}