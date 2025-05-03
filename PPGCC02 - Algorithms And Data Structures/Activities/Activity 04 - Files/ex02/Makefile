# Makefile para compilar o programa 02.c
# Autor: Breno Farias da Silva

# Nome do executável
EXEC = 02

# Fonte do código
SRC = 02.c

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
	./$(EXEC) 02.txt --remove-blank-lines --trim-start --replace dolor HelloWorld

# Alvo para limpar arquivos gerados
clean:
	rm -f $(EXEC)
