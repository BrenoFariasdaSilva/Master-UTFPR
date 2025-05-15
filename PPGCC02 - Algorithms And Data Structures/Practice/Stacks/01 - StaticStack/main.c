/*
 * Description: This program shows an implementation of a Stack using Static Memory Allocation.
 * Author: Breno Farias da Silva.
 * Date: 15/05/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf, scanf

#define ElementType int // Define a macro for the element type in the Stack.
#define MAX_SIZE 100 // Define the Max Size of the Stack.

typedef struct {
	ElementType vector[MAX_SIZE]; // Fixed-size array
	int size; // Maximum size (capacity)
	int quantity; // Current number of elements
} StaticStack;

// Function declarations
StaticStack create_stack();
int push(StaticStack* stack, const ElementType add_element);
int pop(StaticStack* stack, ElementType* pop_element);
int is_empty(StaticStack* stack);
int is_full(StaticStack* stack);
int peek(const StaticStack* stack, ElementType* top_element);
int clear(StaticStack* stack);
int print_stack_attributes(const StaticStack* stack);
int print_stack(const StaticStack* stack);

/*
 * Function to create and initialize the stack.
 * return: The created static stack instance.
*/
StaticStack create_stack() {
	StaticStack stack;
	stack.size = MAX_SIZE;
	stack.quantity = 0;
	return stack;
}

/*
 * Function to push an element onto the stack.
 * stack: pointer to the StaticStack instance.
 * add_element: the element to add to the stack.
 * return: status of the operation (1: success, -1: error).
*/
int push(StaticStack* stack, const ElementType add_element) {
	if (!stack) {
		return -1;
	}

	if (stack->quantity >= stack->size) {
		printf("Stack is full. Can't push another element! \n");
		return -1;
	}

	stack->vector[stack->quantity++] = add_element;

	return 1;
}

/*
 * Function to pop the top element from the stack.
 * stack: pointer to the StaticStack instance.
 * pop_element: pointer to store the popped element.
 * return: status of the operation (1: success, -1: error).
*/
int pop(StaticStack* stack, ElementType* pop_element) {
	if (!stack || !pop_element) {
		return -1;
	}

	if (stack->quantity <= 0) {
		printf("Empty Stack. Unable to pop the element in the top!\n");
		return -1;
	}

	*pop_element = stack->vector[--stack->quantity];

	return 1;
}

/*
 * Function to check if the stack is empty.
 * stack: pointer to the StaticStack instance.
 * return: 1 if empty, 0 if not empty, -1 if error (null pointer).
*/
int is_empty(StaticStack* stack) {
	if (!stack) {
		return -1;
	}

	return (stack->quantity == 0) ? 1 : 0;
}

/*
 * Function to check if the stack is full.
 * stack: pointer to the StaticStack instance.
 * return: 1 if full, 0 if not full, -1 if error (null pointer).
*/
int is_full(StaticStack* stack) {
	if (!stack) {
		return -1;
	}

	return (stack->quantity == stack->size) ? 1 : 0;
}

/*
 * Function to peek at the top element without popping.
 * stack: pointer to the StaticStack instance.
 * top_element: pointer to store the top element.
 * return: status of the operation (1: success, -1: error).
*/
int peek(const StaticStack* stack, ElementType* top_element) {
	if (!stack || !top_element) {
		return -1;
	}

	if (stack->quantity == 0) {
		printf("Empty Stack. Nothing to peek!\n");
		return -1;
	}

	*top_element = stack->vector[stack->quantity - 1];

	return 1;
}

/*
 * Function to clear the stack.
 * stack: pointer to the StaticStack instance.
 * return: status of the operation (1: success, -1: error).
*/
int clear(StaticStack* stack) {
	if (!stack) {
		return -1;
	}

	stack->quantity = 0;

	return 1;
}

/*
 * Function to print stack attributes.
 * stack: pointer to the StaticStack instance.
 * return: status of the operation (1: success, -1: error).
*/
int print_stack_attributes(const StaticStack* stack) {
	if (!stack) {
		return -1;
	}

	print_stack(stack);
	printf("Stack Max Size: %d\n", stack->size);
	printf("Stack Current Size: %d\n\n", stack->quantity);

	return 1;
}

/*
 * Function to print all elements in the stack.
 * stack: pointer to the StaticStack instance.
 * return: status of the operation (1: success, -1: error).
*/
int print_stack(const StaticStack* stack) {
	if (!stack) {
		return -1;
	}

	printf("Static Stack: ");
	for (int i = 0; i < stack->quantity; i++) {
		printf("%d ", stack->vector[i]);
	}
	printf("\n");

	return 1;
}

/*
 * Main function of the program.
 * argc: number of arguments passed when calling the program.
 * argv: array containing the arguments passed to the program.
 * return: program exit status (0: no errors, otherwise, error code).
*/
int main(int argc, char *argv[]) {
	printf("Welcome to the Static Implementation of a Stack Data Structure!\n\n");

	StaticStack stack = create_stack();

	push(&stack, 10);
	push(&stack, 20);

	print_stack_attributes(&stack);

	ElementType popped;
	if (pop(&stack, &popped)) {
		printf("Popped: %d\n", popped);
	}

	print_stack_attributes(&stack);

	printf("Is Stack Empty? %s\n\n", is_empty(&stack) == 1 ? "Yes" : "No");

	ElementType top;
	if (peek(&stack, &top) == 1) {
		printf("Top element (peek): %d\n\n", top);
	} else {
		printf("Failed to peek top element.\n\n");
	}

	printf("Clearing the stack...\n");
	if (clear(&stack) == 1) {
		printf("Stack cleared successfully.\n\n");
	}

	print_stack_attributes(&stack);

	printf("Is Stack Full? %s\n", is_full(&stack) == 1 ? "Yes" : "No");

	return 0;
}
	