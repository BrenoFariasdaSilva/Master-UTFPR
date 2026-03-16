/*
 * Description: Develop a function to transfer elements from a stack P1 to a stack P2.
 *              It is important that P2 contains the same elements in the same order as P1.
 *              This exercise is different from the stack_clone exercise, where you can
 *              directly access the data from the stack.
 * Author: Breno Farias da Silva.
 * Date: 16/06/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // Input/output functions: printf
#include <stdlib.h> // General utilities (not directly used but good for extensions)

#define MAX 100 // Maximum size of the stack

/*
 * Structure that represents a contiguous stack.
 * items: array of stored characters.
 * top: index of the top of the stack.
*/
typedef struct {
	char items[MAX];
	int top;
} Stack;

/*
 * Initializes the stack by setting the top to -1, indicating an empty stack.
 * s: pointer to the stack to be initialized.
*/
void create_stack(Stack* s) {
	s->top = -1;
}

/*
 * Checks if the stack is empty.
 * s: pointer to the stack to be checked.
 * return: 1 if empty, 0 otherwise.
*/
int is_stack_empty(Stack* s) {
	return s->top == -1;
}

/*
 * Pushes a character onto the stack.
 * s: pointer to the stack.
 * elem: character to be pushed.
 * return: 1 if push was successful, 0 if the stack is full.
*/
int push(Stack* s, char elem) {
	if (s->top == MAX - 1) return 0; // Stack full
	s->items[++(s->top)] = elem;
	return 1;
}

/*
 * Pops a character from the stack.
 * s: pointer to the stack.
 * elem: pointer to where the popped character will be stored.
 * return: 1 if pop was successful, 0 if the stack is empty.
*/
int pop(Stack* s, char* elem) {
	if (is_stack_empty(s)) return 0; // Stack empty
	*elem = s->items[(s->top)--];
	return 1;
}

/*
 * Transfers elements from stack P1 to stack P2.
 * P2 must contain the same elements in the same order as P1.
 * Uses an auxiliary stack to preserve the original order.
*/
void transferStack(Stack* P1, Stack* P2) {
	Stack auxiliary;
	create_stack(&auxiliary);

	// Step 1: Pop from P1 and push into the auxiliary stack
	// This reverses the order of the elements
	char elem;
	while (!is_stack_empty(P1)) {
		pop(P1, &elem);
		push(&auxiliary, elem);
	}

	// Step 2: Pop from auxiliary and push into P2
	// This restores the original order of P1 into P2
	while (!is_stack_empty(&auxiliary)) {
		pop(&auxiliary, &elem);
		push(P2, elem);
	}
}

/*
 * Main function of the program.
 * argc: number of arguments passed to the program.
 * argv: array with the arguments passed to the program.
 * return: execution status (0: no errors, otherwise, error code).
*/
int main(int argc, char *argv[]) {
	Stack P1, P2;
	create_stack(&P1);
	create_stack(&P2);

	// Push some example elements into P1
	push(&P1, 'A');
	push(&P1, 'B');
	push(&P1, 'C');

	// Transfer elements from P1 to P2 preserving the order
	transferStack(&P1, &P2);

	// Print the elements in P2 to confirm the order is preserved
	char elem;
	printf("Elements in P2 (from top to bottom):\n");
	while (!is_stack_empty(&P2)) {
		pop(&P2, &elem);
		printf("%c\n", elem);
	}

	return 0;
}
