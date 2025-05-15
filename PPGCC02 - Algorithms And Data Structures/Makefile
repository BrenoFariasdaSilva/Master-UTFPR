# Makefile to compile and run the SRC program

# Source file
SRC = 01.c

# Name of the executable (without extension)
TARGET = $(basename $(SRC))

# Compiler
CC = gcc

# Compilation flags (optional, can include -Wall for warnings)
CFLAGS = -Wall -O2

# Default rule
all: $(TARGET)

# Rule to generate the executable
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

# Rule to run the program
run: $(TARGET)
	./$(TARGET)

# Clean up generated files
clean:
	rm -f $(TARGET)
