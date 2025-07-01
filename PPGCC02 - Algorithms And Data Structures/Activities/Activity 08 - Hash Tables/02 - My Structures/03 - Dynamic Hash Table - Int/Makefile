# Makefile to compile, run and clean the SRC program

# Source file
SRC = main.c

# Name of the executable (without extension)
TARGET = $(basename $(SRC))

# Compiler
CC = gcc

# Compilation flags
CFLAGS = -Wall -O2

# Default rule: compile, run, then clean
all: run clean

# Rule to generate the executable
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

# Rule to run the program (clears terminal first)
run: $(TARGET)
	@clear
	./$(TARGET)

# Clean up generated files with a preceding empty line
clean:
	@echo ""
	rm -f $(TARGET)
