# Makefile para compilar o programa 04.c
# Autor: Breno Farias da Silva

# Nome do executável
EXEC = 04

# Fonte do código
SRC = 04.c

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# Alvo padrão: compilar
all: $(EXEC)

# Regra de compilação
$(EXEC): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(EXEC)

# Alvo para executar o programa
run: $(EXEC)
	./$(EXEC) 04.gif

# Alvo para limpar arquivos gerados
clean:
	rm -f $(EXEC)
