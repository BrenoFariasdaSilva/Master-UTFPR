CC = gcc
CFLAGS = -Wall -Wextra -O2

all: main

hash.o: hash.c hash.h
	$(CC) $(CFLAGS) -c hash.c -o hash.o

main.o: main.c hash.h
	$(CC) $(CFLAGS) -c main.c -o main.o

main: main.o hash.o
	$(CC) $(CFLAGS) main.o hash.o -o main

run:
	./main 100 1 # exemplo rodando teste sondagem linear com tabela tamanho 100
	$(MAKE) clean

clean:
	rm -f *.o main
