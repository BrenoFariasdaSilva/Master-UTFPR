/*
 * Description: Implementation of utility functions for stack manipulation:
 * - Cloning a stack.
 * - Reversing a stack.
 * - Pushing an entire array into a stack.
 * Author: Breno Farias da Silva.
 * Date: 16/05/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf, scanf
#include <stdlib.h> // malloc, free
#include <stdbool.h> // bool type

#define MAX 100

typedef int ElementType;

typedef struct {
	ElementType elements[MAX];
	int top;
} Stack;

/*
 * Creates and initializes an empty stack.
 * p: pointer to the stack to be initialized.
 */
void stack_create(Stack* p) {
	p->top = -1;
}

/*
 * Checks whether a stack is empty.
 * p: pointer to the stack to be checked.
 * return: true if the stack is empty, false otherwise.
 */
bool stack_is_empty(Stack* p) {
	return p->top == -1;
}

/*
 * Checks whether a stack is full.
 * p: pointer to the stack to be checked.
 * return: true if the stack is full, false otherwise.
 */
bool stack_is_full(Stack* p) {
	return p->top == MAX - 1;
}

/*
 * Pushes an element onto the top of the stack.
 * p: pointer to the stack.
 * elem: element to be pushed.
 * return: true if the element was successfully pushed, false if the stack is full.
 */
bool push(Stack* p, ElementType elem) {
	if (stack_is_full(p)) return false;
	p->elements[++(p->top)] = elem;
	return true;
}

/*
 * Pops the top element from the stack.
 * p: pointer to the stack.
 * output: pointer to store the popped element.
 * return: true if the element was successfully popped, false if the stack is empty.
 */
bool pop(Stack* p, ElementType* output) {
	if (stack_is_empty(p)) return false;
	*output = p->elements[(p->top)--];
	return true;
}

/*
 * Creates a deep copy (clone) of a given stack.
 * The cloned stack will contain the same elements in the same order.
 * p: pointer to the original stack to be cloned.
 * return: pointer to a newly allocated stack that is a clone of 'p'.
 */
Stack* stack_clone(Stack* p) {
	Stack* clone = (Stack*) malloc(sizeof(Stack));
	stack_create(clone);

	Stack temp;
	stack_create(&temp);

	ElementType elem;

	// Step 1: Reverse original stack into temp
	for (int i = 0; i <= p->top; i++) {
		push(&temp, p->elements[i]);
	}

	// Step 2: Rebuild original order into clone
	while (!stack_is_empty(&temp)) {
		pop(&temp, &elem);
		push(clone, elem);
	}

	return clone;
}

/*
 * Reverses the order of elements in a given stack.
 * The top element becomes the bottom, and vice versa.
 * p: pointer to the stack to be reversed.
 */
void stack_reverse(Stack* p) {
	Stack aux;
	stack_create(&aux);
	ElementType elem;

	while (!stack_is_empty(p)) {
		pop(p, &elem);
		push(&aux, elem);
	}

	// Copy elements back to original stack
	*p = aux;
}

/*
 * Pushes all elements from a given array into a stack.
 * The first element in the array will be at the bottom of the stack.
 * p: pointer to the stack.
 * array: array of elements to be pushed.
 * arraySize: number of elements in the array.
 * return: true if all elements were successfully pushed, false otherwise.
 */
bool stack_pushAll(Stack* p, ElementType* array, int arraySize) {
	for (int i = 0; i < arraySize; i++) {
		if (!push(p, array[i])) return false;
	}
	return true;
}

/*
 * Main function of the program.
 * argc: number of arguments passed on program call.
 * argv: array with the arguments passed.
 * return: execution status (0: success, otherwise: error code).
 */
int main(int argc, char *argv[]) {
	Stack p;
	stack_create(&p);

	ElementType arr[] = {1, 2, 3, 4, 5};
	stack_pushAll(&p, arr, 5);

	printf("Original stack (top to bottom):\n");
	for (int i = p.top; i >= 0; i--) {
		printf("%d\n", p.elements[i]);
	}

	stack_reverse(&p);
	printf("\nReversed stack (top to bottom):\n");
	for (int i = p.top; i >= 0; i--) {
		printf("%d\n", p.elements[i]);
	}

	Stack* cloned = stack_clone(&p);
	printf("\nCloned stack (top to bottom):\n");
	for (int i = cloned->top; i >= 0; i--) {
		printf("%d\n", cloned->elements[i]);
	}

	free(cloned);
	return 0;
}
