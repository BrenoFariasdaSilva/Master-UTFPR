/*
 * Description: Converts an infix expression to its postfix form (reverse Polish notation).
 * Author: Breno Farias da Silva.
 * Date: 22/05/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// Simple stack for characters (operators)
typedef struct {
	char data[MAX];
	int top;
} Stack;

// Initialize the stack
void init(Stack *s) {
	s->top = -1;
}

// Check if the stack is empty
int isEmpty(Stack *s) {
	return s->top == -1;
}

// Push operation
void push(Stack *s, char c) {
	if (s->top < MAX - 1) {
		s->data[++(s->top)] = c;
	}
}

// Pop operation
char pop(Stack *s) {
	if (!isEmpty(s)) {
		return s->data[(s->top)--];
	}
	return '\0'; // invalid return if empty
}

// Return the top element without popping
char peek(Stack *s) {
	if (!isEmpty(s)) {
		return s->data[s->top];
	}
	return '\0';
}

// Return the precedence of the operator
int precedence(char op) {
	switch(op) {
		case '+':
		case '-': return 1;
		case '*':
		case '/': return 2;
		case '^': return 3;
	}
	return 0;
}

// Check if character is a valid operator
int isOperator(char c) {
	return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

/*
 * Converts infix expression to postfix and prints the result.
 * Considers left associativity for +, -, *, / and right associativity for ^.
 */
void infix_to_postfix(const char *infix) {
	Stack s;
	init(&s);

	int i, len = strlen(infix);
	for (i = 0; i < len; i++) {
		char c = infix[i];

		if (isspace(c)) continue; // ignore spaces

		if (isalnum(c)) {
			// Operand: print directly
			printf("%c", c);
		}
		else if (c == '(') {
			push(&s, c);
		}
		else if (c == ')') {
			// Pop until '('
			while (!isEmpty(&s) && peek(&s) != '(') {
				printf("%c", pop(&s));
			}
			if (!isEmpty(&s) && peek(&s) == '(') {
				pop(&s); // remove '(' from stack
			} else {
				// Closing parenthesis without matching opening
				printf("\nError: unbalanced parentheses.\n");
				return;
			}
		}
		else if (isOperator(c)) {
			// Pop operators while precedence and associativity condition holds

			while (!isEmpty(&s) && isOperator(peek(&s))) {
				char topOp = peek(&s);
				int precTop = precedence(topOp);
				int precCur = precedence(c);

				// Associativity:
				// For operators with the same precedence:
				// - left associativity: pop the top
				// - right associativity (^): do not pop top if same precedence

				if ((precTop > precCur) || 
					(precTop == precCur && c != '^')) {
					printf("%c", pop(&s));
				} else {
					break;
				}
			}
			push(&s, c);
		}
		else {
			// Invalid character
			printf("\nError: invalid character '%c'.\n", c);
			return;
		}
	}

	// Pop remaining operators
	while (!isEmpty(&s)) {
		if (peek(&s) == '(') {
			printf("\nError: unbalanced parentheses.\n");
			return;
		}
		printf("%c", pop(&s));
	}
	printf("\n");
}

/*
 * Main function of the program.
 * argc: number of arguments passed on program call.
 * argv: array with the arguments passed on program call.
 * return: program execution status (0: no errors, otherwise: error code).
 */
int main(int argc, char *argv[]) {
	printf("Infix to Postfix Conversion\n");
	printf("----------------------------\n");

	// Test examples
	const char *examples[] = {
		"a+b*c",
		"(a+b)*c",
		"a+b*(c^d-e)^(f+g*h)-i",
		"A*(B+C)/D",
		"((a+t)*((b+(a+c))^(c+d)))"
	};

	for (int i = 0; i < sizeof(examples)/sizeof(examples[0]); i++) {
		printf("Infix:    %s\n", examples[i]);
		printf("Postfix:  ");
		infix_to_postfix(examples[i]);
		printf("\n");
	}

	return 0;
}
