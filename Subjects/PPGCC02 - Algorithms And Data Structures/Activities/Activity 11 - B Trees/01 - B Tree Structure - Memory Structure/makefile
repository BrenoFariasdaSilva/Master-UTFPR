# Makefile to compile, run and clean the B-Tree program

# Source files
SRC = main.c b_tree.c

# Header files (for dependencies, optional)
HDR = b_tree.h

# Name of the executable
TARGET = main

# Compiler and flags
CC = gcc
CFLAGS = -Wall -O2

# Default rule: compile, run, then clean
all: run clean

# Compile object files and link executable
$(TARGET): $(SRC) $(HDR)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

# Run the program (clear terminal first)
run: $(TARGET)
	@clear
	echo ""
	./$(TARGET)

# Clean generated files, print an empty line before
clean:
	@echo ""
	rm -f $(TARGET) *.o
