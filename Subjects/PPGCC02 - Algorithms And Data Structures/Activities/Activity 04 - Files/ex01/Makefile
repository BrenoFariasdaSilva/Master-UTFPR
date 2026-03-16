# Makefile para compilar o programa 01.c
# Autor: Breno Farias da Silva

# Nome do executável
TARGET = 01

# Arquivo fonte
SRC = 01.c

# Compilador
CC = gcc

# Flags de compilação (opcional, pode incluir -Wall para warnings)
CFLAGS = -Wall -O2

# Regra padrão
all: $(TARGET)

# Regra para gerar o executável
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

# Regra para rodar o programa
run: $(TARGET)
	./$(TARGET)

# Limpeza dos arquivos gerados
clean:
	rm -f $(TARGET)
