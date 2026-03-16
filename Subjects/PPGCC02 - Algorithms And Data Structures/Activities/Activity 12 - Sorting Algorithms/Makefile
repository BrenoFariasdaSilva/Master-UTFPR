# Makefile to compile and run the SRC program

# Source files
SRC = main.c sorting.c

# Name of the executable (without extension)
TARGET = program

# Compiler
CC = gcc

# Compilation flags (optional, can include -Wall for warnings)
CFLAGS = -Wall -O2

# Default rule: compile, run, and delete executable
all: $(TARGET)
	clear
	./$(TARGET)
	rm -f $(TARGET)

# Rule to generate the executable
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

# Rule to run the program
run: $(TARGET)
	./$(TARGET)

# Clean up generated files
clean:
	rm -f $(TARGET)
