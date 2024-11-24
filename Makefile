all:
	gcc -Wall -c src/common.c
	gcc -Wall -c src/labirinto.c
	gcc -Wall src/client.c labirinto.o common.o -o client
	gcc -Wall src/server.c labirinto.o common.o -o server
	gcc -Wall server-mt.c common.o -lpthread -o server-mt

clean:
	rm common.o client server server-mt
