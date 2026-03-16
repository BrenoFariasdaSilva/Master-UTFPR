/*
 * Description: Implementation of a linked stack with functions to clone,
 * invert, push all elements from an array, and print using a generic print function.
 * Author: Breno Farias da Silva.
 * Date: 16/05/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf, scanf
#include <stdlib.h> // malloc, free
#include <stdbool.h> // bool type

typedef int ElementType;

typedef struct Node {
	ElementType element; // Element stored in the node
	struct Node* next; // Pointer to the next node in the stack
} Node;

typedef struct {
	Node* top; // Pointer to the top node of the stack
} Stack;

/*
 * Creates and initializes an empty stack.
 * s: pointer to the stack to be initialized.
 */
void stack_create(Stack* s) {
	s->top = NULL;
}

/*
 * Checks whether a stack is empty.
 * s: pointer to the stack to be checked.
 * return: true if the stack is empty, false otherwise.
 */
bool stack_is_empty(Stack* s) {
	return s->top == NULL;
}

/*
 * Pushes an element onto the top of the stack.
 * s: pointer to the stack.
 * elem: element to be pushed.
 * return: true if the element was successfully pushed, false otherwise.
 */
bool push(Stack* s, ElementType elem) {
	Node* new_node = (Node*) malloc(sizeof(Node));
	if (!new_node) return false;
	new_node->element = elem;
	new_node->next = s->top;
	s->top = new_node;
	return true;
}

/*
 * Pops the top element from the stack.
 * s: pointer to the stack.
 * elem: pointer to store the popped element.
 * return: true if the element was successfully popped, false otherwise.
 */
bool pop(Stack* s, ElementType* elem) {
	if (stack_is_empty(s)) return false;
	Node* temp = s->top;
	*elem = temp->element;
	s->top = temp->next;
	free(temp);
	return true;
}

/*
 * Creates a deep copy (clone) of a given stack.
 * The cloned stack will contain the same elements in the same order.
 * s: pointer to the original stack to be cloned.
 * return: pointer to a newly allocated stack that is a clone of 's'.
 */
Stack* stack_clone(Stack* s) {
	Stack* clone = (Stack*) malloc(sizeof(Stack));
	stack_create(clone);

	Stack aux1;
	stack_create(&aux1);
	Stack aux2;
	stack_create(&aux2);

	ElementType elem;

	// Step 1: Move elements from original to aux1 (reverse order)
	Node* current = s->top;
	while (current != NULL) {
		push(&aux1, current->element);
		current = current->next;
	}

	// Step 2: Move from aux1 to aux2 (restore original order)
	while (!stack_is_empty(&aux1)) {
		pop(&aux1, &elem);
		push(&aux2, elem);
	}

	// Step 3: Move from aux2 to clone (copy original order)
	while (!stack_is_empty(&aux2)) {
		pop(&aux2, &elem);
		push(clone, elem);
	}

	return clone;
}

/*
 * Reverses the order of elements in a given stack.
 * The top element becomes the bottom, and vice versa.
 * s: pointer to the stack to be reversed.
 */
void stack_invert(Stack* s) {
	Stack aux;
	stack_create(&aux);
	ElementType elem;

	while (!stack_is_empty(s)) {
		pop(s, &elem);
		push(&aux, elem);
	}

	*s = aux;
}

/*
 * Pushes all elements from a given array into a stack.
 * The first element in the array will be at the bottom of the stack.
 * s: pointer to the stack.
 * array: array of elements to be pushed.
 * array_size: number of elements in the array.
 * return: true if all elements were successfully pushed, false otherwise.
 */
bool stack_push_all(Stack* s, ElementType* array, int array_size) {
	for (int i = 0; i < array_size; i++) {
		if (!push(s, array[i])) return false;
	}
	return true;
}

/*
 * Prints the stack elements using a generic print function.
 * s: pointer to the stack.
 * printElement: pointer to a function to print a single element.
 */
void stack_print(Stack* s, void (*printElement)(void*)) {
	Node* current = s->top;
	while (current != NULL) {
		printElement(&(current->element));
		current = current->next;
	}
	printf("\n");
}

/*
 * Sample function to print an integer element.
 * elem: pointer to the element to be printed.
 */
void printInt(void* elem) {
	printf("%d\n", *(int*)elem);
}

/*
 * Main function of the program.
 * argc: number of arguments passed on program call.
 * argv: array with the arguments passed on program call.
 * return: program execution status (0: no errors, otherwise: error code).
 */
int main(int argc, char *argv[]) {
	Stack s;
	stack_create(&s);

	ElementType array[] = {10, 20, 30, 40, 50};
	stack_push_all(&s, array, 5);

	printf("Original stack:\n");
	stack_print(&s, printInt);

	stack_invert(&s);
	printf("\nInverted stack:\n");
	stack_print(&s, printInt);

	Stack* clone = stack_clone(&s);
	printf("\nCloned stack:\n");
	stack_print(clone, printInt);

	// Free cloned stack memory
	ElementType tmp;
	while (pop(clone, &tmp));
	free(clone);

	return 0;
}
