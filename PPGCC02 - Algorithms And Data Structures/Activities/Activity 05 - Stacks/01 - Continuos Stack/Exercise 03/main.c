/*
 * Description: This program reads an arithmetic expression from a text file
 *              and checks whether it has correctly matched parentheses (),
 *              brackets [], and braces {} using a stack.
 * Author: Breno Farias da Silva.
 * Date: 27/03/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf, fopen, fclose, fgetc
#include <stdlib.h> // exit
#define MAX 1000 // Maximum stack size

/*
 * Stack structure for characters.
 * data: array to hold characters.
 * top: index of the top element.
 */
typedef struct {
	char data[MAX];
	int top;
} Stack;

/*
 * Initializes the stack by setting top to -1.
 */
void create_stack(Stack* s) {
	s->top = -1;
}

/*
 * Checks if the stack is empty.
 * Returns 1 if empty, 0 otherwise.
 */
int is_empty(Stack* s) {
	return s->top == -1;
}

/*
 * Pushes a character onto the stack.
 * Returns 1 if successful, 0 if stack is full.
 */
int push(Stack* s, char c) {
	if (s->top == MAX - 1) return 0;
	s->data[++(s->top)] = c;
	return 1;
}

/*
 * Pops a character from the stack.
 * Returns 1 if successful, 0 if stack is empty.
 */
int pop(Stack* s, char* c) {
	if (is_empty(s)) return 0;
	*c = s->data[(s->top)--];
	return 1;
}

/*
 * Returns 1 if the pair of characters is a matching open-close symbol.
 */
int is_matching_pair(char open, char close) {
	return (open == '(' && close == ')') ||
	       (open == '[' && close == ']') ||
	       (open == '{' && close == '}');
}

/*
 * Checks if the expression has balanced symbols.
 * filename: name of the file containing the expression.
 * Returns 1 if balanced, 0 otherwise.
 */
int check_balance(const char* filename) {
	FILE* file = fopen(filename, "r");

	if (file == NULL) {
		printf("Error: Could not open file '%s'\n", filename);
		return 0;
	}

	Stack s;
	create_stack(&s);
	char ch, top;

		while ((ch = fgetc(file)) != EOF) {
			if (ch == '(' || ch == '[' || ch == '{') {
				push(&s, ch);
			} else if (ch == ')' || ch == ']' || ch == '}') {
				if (!pop(&s, &top) || !is_matching_pair(top, ch)) {
					fclose(file);
					return 0; // Mismatch or extra closing symbol
				}
			}
		}

	fclose(file);
	return is_empty(&s); // If stack is empty, all symbols matched
}

/*
 * Main function of the program.
 * argc: number of arguments passed to the program.
 * argv: array of arguments passed to the program.
 * return: execution status (0: no errors, otherwise, error code).
 */
int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Usage: %s <filename>\n", argv[0]);
		return 1;
	}

	if (check_balance(argv[1])) {
		printf("The expression has correct parenthesis matching.\n");
	} else {
		printf("The expression has incorrect parenthesis matching.\n");
	}

	return 0;
}
