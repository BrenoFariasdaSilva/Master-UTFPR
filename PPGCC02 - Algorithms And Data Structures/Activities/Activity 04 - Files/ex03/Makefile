# Makefile para compilar o programa 03.c
# Autor: Breno Farias da Silva

# Nome do executável
EXEC = 03

# Fonte do código
SRC = 03.c

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
	./$(EXEC)

# Alvo para limpar arquivos gerados
clean:
	rm -f $(EXEC)
