# Variáveis
CC = gcc
CFLAGS = -Wall -Wextra -O2
OBJS = main.o hash.o
EXEC = main

# Alvo padrão
all: $(EXEC)

# Compilação do executável
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)

# Compilação dos arquivos fonte
main.o: main.c hash.h
	$(CC) $(CFLAGS) -c main.c

hash.o: hash.c hash.h
	$(CC) $(CFLAGS) -c hash.c

# Executa o programa e limpa os arquivos depois
run: all
	./$(EXEC)
	make clean

# Limpa arquivos objeto e o executável
clean:
	rm -f *.o $(EXEC)
