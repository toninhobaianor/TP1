#include "../common.h"
#include "../labirinto.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

//mostrar o modo de uso do cliente
void usage(int argc, char **argv) {
	printf("usage: %s <server IP> <server port>\n", argv[0]);
	printf("example: %s 127.0.0.1 51511\n", argv[0]);
	exit(EXIT_FAILURE);
}

#define BUFSZ 1024

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
	//char number[BUFSZ] = "start\n";
	//memset(number + 6, 0, BUFSZ);
	while(1) {
		printf("mensagem> ");
		fgets(buf, BUFSZ-1, stdin);

		char *res = malloc(sizeof(100));
		for(int i = 0; i <= 3; i++){
			res[i] = buf[i];
		}
		if (strcmp(res,"exit") == 0) {
			break;	
		}

		size_t count = send(s, buf, strlen(buf)+1, 0);
		if (count != strlen(buf)+1) {
			logexit("send");
		}
		memset(buf, 0, BUFSZ);
		count = recv(s, buf, BUFSZ, 0);
		printf("%s",buf);
	}
	close(s);

	printf("received all of bytes\n");
	puts(buf);

	exit(EXIT_SUCCESS);
}