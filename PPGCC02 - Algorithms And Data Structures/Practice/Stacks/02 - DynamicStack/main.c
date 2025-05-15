/*
 * Description: This program shows an implementation of a Stack using Dynamic Memory Allocation.
 * Author: Breno Farias da Silva.
 * Date: 15/05/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf, scanf
#include <stdlib.h> // malloc, free

#define ElementType int // Define a macro for the element type in the Stack.

typedef struct node {
	ElementType data;
	struct node *below;
} Node;

typedef struct {
	Node *head; // Pointer to node in the head of the stack.
	int size; // Size of the stack.
} DynamicStack;

// Function declarations
DynamicStack* create_stack();
int initialize_stack(DynamicStack* stack);
int push(DynamicStack *stack, const ElementType add_element);
int pop(DynamicStack *stack, ElementType* pop_element);
int peek(const DynamicStack *stack, ElementType* top_element);
int is_empty(const DynamicStack *stack);
int print_stack_attributes(const DynamicStack* stack);
int print_stack(const DynamicStack* stack);
void free_stack(DynamicStack* stack);

/*
 * Function to create a new DynamicStack instance using dynamic memory.
 * return: pointer to a newly allocated DynamicStack (NULL on failure).
 */
DynamicStack* create_stack() {
	DynamicStack* stack = (DynamicStack*) malloc(sizeof(DynamicStack));

	if (!stack) {
		return NULL;
	}

	initialize_stack(stack);

	return stack;
}

/*
 * Function to initialize a DynamicStack instance.
 * stack: pointer to the DynamicStack to initialize.
 * return: status of the operation (1: success, -1: error).
 */
int initialize_stack(DynamicStack* stack) {
	if (!stack) {
		return -1;
	}

	stack->head = NULL;
	stack->size = 0;

	return 1;
}

/*
 * Function to push a new element onto the stack.
 * stack: pointer to the DynamicStack instance.
 * add_element: element to be pushed onto the stack.
 * return: status of the operation (1: success, -1: error).
 */
int push(DynamicStack *stack, const ElementType add_element) {
	if (!stack) {
		return -1;
	}

	Node *new_head = (Node*) malloc(sizeof(Node));
	if (!new_head) {
		return -1;
	}

	new_head->data = add_element;
	new_head->below = stack->head;
	stack->head = new_head;
	stack->size++;

	return 1;
}

/*
 * Function to pop the top element from the stack.
 * stack: pointer to the DynamicStack instance.
 * pop_element: pointer to store the popped element.
 * return: status of the operation (1: success, -1: error).
 */
int pop(DynamicStack *stack, ElementType* pop_element) {
	if (!stack || !pop_element) {
		return -1; // Invalid input
	}

	if (!stack->head) {
		return -1; // Stack underflow
	}

	Node* pop_node = stack->head;
	*pop_element = pop_node->data;

	stack->head = pop_node->below;
	stack->size--;

	free(pop_node);

	return 1;
}

/*
 * Function to get the top element of the stack without removing it.
 * stack: pointer to the DynamicStack instance.
 * top_element: pointer to store the top element.
 * return: status of the operation (1: success, -1: error).
 */
int peek(const DynamicStack *stack, ElementType* top_element) {
	if (!stack || !top_element || !stack->head) {
		return -1;
	}

	*top_element = stack->head->data;

	return 1;
}

/*
 * Function to check if the stack is empty.
 * stack: pointer to the DynamicStack instance.
 * return: 1 if empty, 0 if not empty, -1 if invalid input.
 */
int is_empty(const DynamicStack *stack) {
	if (!stack) {
		return -1;
	}
	
	return (stack->size == 0);
}

/*
 * Function to print all elements in the stack.
 * stack: pointer to the DynamicStack instance.
 * return: status of the operation (1: success, -1: error).
 */
int print_stack(const DynamicStack* stack) {
	if (!stack) {
		return -1;
	}

	printf("Dynamic Stack: ");
	Node *node = stack->head;
	for (int i = 0; i < stack->size; i++) {
		printf("%d ", node->data);
		node = node->below;
	}
	printf("\n");

	return 1;
}

/*
 * Function to print stack attributes.
 * stack: pointer to the DynamicStack instance.
 * return: status of the operation (1: success, -1: error).
 */
int print_stack_attributes(const DynamicStack* stack) {
	if (!stack) {
		return -1;
	}

	print_stack(stack);

	if (stack->head) {
		printf("Stack Head: %d\n", stack->head->data);
	} else {
		printf("Stack Head: NULL (Empty Stack)\n");
	}

	printf("Stack Size: %d\n\n", stack->size);

	return 1;
}

/*
 * Function to free all memory associated with the stack.
 * stack: pointer to the DynamicStack instance.
 * return: void.
 */
void free_stack(DynamicStack* stack) {
	if (!stack) {
		return;
	}

	Node* current = stack->head;
	while (current) {
		Node* temp = current;
		current = current->below;
		free(temp);
	}

	free(stack);
}

/*
 * Main function of the program.
 * argc: number of arguments passed when calling the program.
 * argv: array containing the arguments passed to the program.
 * return: program exit status (0: no errors, otherwise, error code).
 */
int main(int argc, char *argv[]) {
	printf("Welcome to the Dynamic Implementation of a Stack Data Structure!\n\n");

	DynamicStack *stack = create_stack();

	print_stack_attributes(stack);

	push(stack, 10);
	push(stack, 20);
	print_stack_attributes(stack);

	ElementType popped_element;
	pop(stack, &popped_element);
	print_stack_attributes(stack);

	ElementType top_element;
	if (peek(stack, &top_element) == 1) {
		printf("Peeked top element: %d\n\n", top_element);
	}

	if (is_empty(stack)) {
		printf("The stack is empty.\n");
	} else {
		printf("The stack is not empty.\n");
	}

	free_stack(stack);

	return 0;
}
