#include "../common.h"
#include "../labirinto.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUF 8
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
	//conversão do tipo sockaddr_storage para sockaddr
	struct sockaddr *addr = (struct sockaddr *)(&storage);
	if (0 != connect(s, addr, sizeof(storage))) {
		logexit("connect");
	}

	char addrstr[BUFSZ];
	addrtostr(addr, addrstr, BUFSZ);

	printf("connected to %s\n", addrstr);

	char buf[BUFSZ];
	char *dir;
	memset(buf, 0, BUFSZ);
	int init = 0;
	while(1) {
		inicializa_action(&board);

		printf("mensagem> ");
		fgets(buf, BUFSZ, stdin);
		modifica_tipo(&board,buf);

		//exit
		if (board.type == 7) {
			send(s, &board, sizeof(board), 0);
			break;	
		}
		if (board.type == 6) {
			init = 1;
			send(s, &board, sizeof(board), 0);
			recv(s, &board, sizeof(board), 0);
			for(int i = 0; i < 5; i++){
				for(int j = 0; j < 5; j++){
					printf("%i ",board.board[i][j]);
				}
				printf("\n");
			}
			if(board.type == 4){
				dir = print_direcoes_possiveis(&board);
				printf("Possible moves: %s\n", dir);
			}
			else if(board.type == 5){
				printf("You escaped!");
				revela_labirinto(&board);
			}	
		}
		//start
		else if(board.type == 0){
			init = 1;
			send(s, &board, sizeof(board), 0);
			recv(s, &board, sizeof(board), 0);
			for(int i = 0; i < 5; i++){
				for(int j = 0; j < 5; j++){
					printf("%i ",board.board[i][j]);
				}
				printf("\n");
			}
			if(board.type == 4){
				dir = print_direcoes_possiveis(&board);
				printf("Possible moves: %s\n", dir);
			}
			else if(board.type == 5){
				printf("You escaped!");
				revela_labirinto(&board);
			}
		}
		// move
		else if(board.type == 1 && init == 1){
			send(s, &board, sizeof(board), 0);
			recv(s, &board, sizeof(board), 0);
			for(int i = 0; i < 5; i++){
				for(int j = 0; j < 5; j++){
					printf("%i ",board.board[i][j]);
				}
				printf("\n");
			}
			if(board.type == 4){
				dir = print_direcoes_possiveis(&board);
				printf("Possible moves: %s\n", dir);
			}
			else if(board.type == 5){
				printf("You escaped!");
				revela_labirinto(&board);
			}
		}
		//erro
		else if(init == 0 && board.type == 1){
			printf("error: start the game first \n");
		}
		//erro
		else{
			printf("error: command not found \n");
		}
	}
	close(s);
	printf("received all of bytes\n");
	puts(buf);

	exit(EXIT_SUCCESS);
}