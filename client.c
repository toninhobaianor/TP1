#include "common.h"
#include "labirinto.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUFSZ 1024

//mostrar o modo de uso do cliente
void usage(int argc, char **argv) {
	printf("usage: %s <server IP> <server port>\n", argv[0]);
	printf("example: %s 127.0.0.1 51511\n", argv[0]);
	exit(EXIT_FAILURE);
}


int main(int argc, char **argv) {
	if (argc < 3) {
		usage(argc, argv);
	}

	struct sockaddr_storage storage;
	if (0 != addrparse(argv[1], argv[2], &storage)) {
		usage(argc, argv);
	}

	int s;
	//AF_inet é um socket da internet
	//SOCK_STREAM e do modelo TCP
	s = socket(storage.ss_family, SOCK_STREAM, 0);
	if (s == -1) {
		logexit("socket");
	}
    Action board;
	Action recebido;
	//conversão do tipo sockaddr_storage para sockaddr
	struct sockaddr *addr = (struct sockaddr *)(&storage);
	if (0 != connect(s, addr, sizeof(storage))) {
		logexit("connect");
	}

	char addrstr[BUFSZ];
	addrtostr(addr, addrstr, BUFSZ);

	printf("connected to %s\n", addrstr);

	char buf[BUFSZ];
	memset(buf, 0, BUFSZ);
	int init = 0;
	int fim = 0;
	int aux;
	while(1) {
		inicializa_action(&board);

		printf("mensagem> ");
		fgets(buf, BUFSZ, stdin);
		modifica_tipo(&board,buf);
	
	
		switch(board.type){
			case 1:
				if(init == 0){
					printf("error: start the game first \n");
					break;
				}
				if(fim == 1){
					break;
				}
				aux = verifica_moves(&board,&recebido);
				if(aux == 1){
					printf("error: you cannot go this way \n");
					break;
				}

			case 6:
				if(fim == 1){
					board.type = 0;
				}
				fim = 0;

			case 0:
				init = 1;
				if(fim == 1){
					break;
				}
				send(s, &board, sizeof(board), 0);
				recv(s, &recebido, sizeof(recebido), 0);
				if(recebido.type == 4){
					print_direcoes_possiveis(&recebido);
				}
				if(recebido.type == 5){
					send(s, &board, sizeof(board), 0);
					recv(s, &recebido, sizeof(recebido), 0);
					printf("You escaped! \n");
					Mostra_map(&recebido);
					fim = 1;
				}
				break;

			case 2:
				if(init == 0){
					printf("error: start the game first \n");
					break;
				}
				send(s, &board, sizeof(board), 0);
				recv(s, &board, sizeof(board), 0);
				Mostra_map(&board);
				break;
			
			case 7:
				send(s, &board, sizeof(board), 0);
				exit(EXIT_SUCCESS);

			case 10:
				printf("error: command not found \n");
				break;
			
			default:
				break;
		}
	}
	close(s);
	printf("received all of bytes\n");
	puts(buf);

	exit(EXIT_SUCCESS);
}