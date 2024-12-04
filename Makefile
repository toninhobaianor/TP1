all:
	gcc -Wall -c common.c
	gcc -Wall -c labirinto.c
	gcc -Wall client.c labirinto.o common.o -o bin/client
	gcc -Wall server.c labirinto.o common.o -o bin/server

clean:
	rm common.o bin/client bin/server
