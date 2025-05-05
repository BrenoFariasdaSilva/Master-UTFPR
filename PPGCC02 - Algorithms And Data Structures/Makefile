# Makefile para compilar e executar o programa de inserção de string em arquivo texto

# Arquivo fonte
SRC = 01.c

# Nome do executável (sem extensão)
TARGET = $(basename $(SRC))

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
