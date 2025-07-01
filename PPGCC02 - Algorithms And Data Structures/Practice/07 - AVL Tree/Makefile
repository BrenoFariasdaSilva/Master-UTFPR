# Makefile to compile and run the AVL tree program

# Source files
SRC = main.c avl.c

# Executable name
TARGET = main

# Compiler
CC = gcc

# Compilation flags (warnings + optimization)
CFLAGS = -Wall -O2

# Default rule: compile, run, and delete executable
all: $(TARGET)
	clear
	./$(TARGET)
	rm -f $(TARGET)

# Rule to generate executable from source files
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

# Clean generated files
clean:
	rm -f $(TARGET)
