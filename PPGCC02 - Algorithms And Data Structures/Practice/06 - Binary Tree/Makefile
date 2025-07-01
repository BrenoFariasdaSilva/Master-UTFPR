# Makefile to compile and run the binary_tree program

# Source files
SRC = main.c binary_tree.c

# Name of the executable (without extension)
TARGET = $(basename main.c)

# Compiler
CC = gcc

# Compilation flags (optional, can include -Wall for warnings)
CFLAGS = -Wall -O2

# Default rule: compile, run, and delete executable, clearing terminal first
all: $(TARGET)
	clear
	./$(TARGET)
	rm -f $(TARGET)

# Rule to generate the executable
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

# Rule to run the program (clear terminal before running)
run: $(TARGET)
	clear
	./$(TARGET)

# Clean up generated files
clean:
	rm -f $(TARGET)
