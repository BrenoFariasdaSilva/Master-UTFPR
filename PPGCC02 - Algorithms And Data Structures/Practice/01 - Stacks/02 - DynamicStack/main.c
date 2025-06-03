/*
 * Description: This program shows an implementation of a Stack using Dynamic Memory Allocation.
 * Author: Breno Farias da Silva.
 * Date: 15/05/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf, scanf
#include <stdlib.h> // malloc, free
#include <stdbool.h> // 'bool', 'true', and 'false' keywords

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
int initialize_stack(DynamicStack *stack);
int push(DynamicStack *stack, const ElementType add_element);
int pop(DynamicStack *stack, ElementType *pop_element);
int peek(const DynamicStack *stack, ElementType *top_element);
int is_empty(const DynamicStack *stack);
int search(const DynamicStack *stack, const ElementType element);
int clone(const DynamicStack *stack, DynamicStack *clone);
int invert(DynamicStack *stack);
bool is_equal(const DynamicStack *stack1, const DynamicStack *stack2);
int insert_vector(DynamicStack *stack, const ElementType *vector, int size);
bool is_valid(const DynamicStack *stack);
int print_stack_attributes(const DynamicStack *stack);
int print_stack(const DynamicStack *stack);
void free_stack(DynamicStack **stack);

/*
 * Function to create a new DynamicStack instance using dynamic memory.
 * return: pointer to a newly allocated DynamicStack (NULL on failure).
 */
DynamicStack* create_stack() {
	DynamicStack *stack = (DynamicStack*) malloc(sizeof(DynamicStack));

	if (!stack) {
		return NULL;
	}

	initialize_stack(stack);

	if (!is_valid(stack)) {
		free(stack);
		return NULL;
	}

	return stack;
}

/*
 * Function to initialize a DynamicStack instance.
 * stack: pointer to the DynamicStack to initialize.
 * return: status of the operation (1: success, -1: error).
 */
int initialize_stack(DynamicStack *stack) {
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
	if (!is_valid(stack)) {
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
int pop(DynamicStack *stack, ElementType *pop_element) {
	if (!is_valid(stack) || !pop_element || is_empty(stack)) {
		return -1; // Invalid input
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
int peek(const DynamicStack *stack, ElementType *top_element) {
	if (!is_valid(stack) || !top_element || is_empty(stack)) {
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
 * Function to search for an element starting from the head of the stack.
 * stack: pointer to the DynamicStack instance.
 * element: element to search for.
 * return: index (0-based from head) if found, -1 if not found or error.
 */
int search(const DynamicStack *stack, const ElementType element) {
	if (!is_valid(stack)) {
		return -1;
	}

	Node* current = stack->head;
	int index = 0;

	while (current) {
		if (current->data == element) {
			return index;
		}
		current = current->below;
		index++;
	}

	return -1;
}

/*
 * Function to clone a stack into another (deep copy).
 * stack: pointer to source stack.
 * clone: pointer to destination stack (must be initialized).
 * return: 1 on success, -1 on error.
 */
int clone(const DynamicStack *stack, DynamicStack *clone) {
	if (!is_valid(stack) || !is_valid(clone) || is_empty(clone)) {
		return -1;
	}

	// Use an array to store elements temporarily for correct order cloning
	ElementType *temp = (ElementType*) malloc(stack->size * sizeof(ElementType));
	if (!temp) {
		return -1;
	}

	Node* current = stack->head;
	int i = 0;
	while (current) {
		temp[i++] = current->data;
		current = current->below;
	}

	// Insert elements from bottom to top (reverse order)
	for (int j = stack->size - 1; j >= 0; j--) {
		if (push(clone, temp[j]) == -1) {
			free(temp);
			return -1;
		}
	}

	free(temp);
	return 1;
}

/*
 * Function to invert the order of elements in the stack.
 * stack: pointer to DynamicStack instance.
 * return: 1 on success, -1 on error.
 */
int invert(DynamicStack *stack) {
	if (!is_valid(stack)) {
		return -1;
	}

	if (is_empty(stack) || stack->size < 2) {
		return 1; // Nothing to invert
	}

	Node *prev = NULL, *current = stack->head, *next = NULL;
	while (current) {
		next = current->below;
		current->below = prev;
		prev = current;
		current = next;
	}
	stack->head = prev;

	return 1;
}

/*
 * Function to check if two stacks are equal (element-wise).
 * stack1, stack2: pointers to stacks.
 * return: 1 if equal, 0 if not equal, -1 on error.
 */
bool is_equal(const DynamicStack *stack1, const DynamicStack *stack2) {
	if (!is_valid(stack1) || !is_valid(stack2)) {
		return -1;
	}

	if (stack1->size != stack2->size) {
		return 0;
	}

	Node* current1 = stack1->head;
	Node* current2 = stack2->head;

	while (current1 && current2) {
		if (current1->data != current2->data) {
			return false;
		}
		current1 = current1->below;
		current2 = current2->below;
	}

	return true;
}

/*
 * Function to insert an array (vector) of elements onto the stack.
 * stack: pointer to the DynamicStack instance.
 * vector: pointer to array of elements.
 * size: number of elements in vector.
 * return: 1 on success, -1 on error.
 */
int insert_vector(DynamicStack *stack, const ElementType *vector, int size) {
	if (!is_valid(stack) || !vector || size < 1) {
		return -1;
	}

	for (int i = 0; i < size; i++) {
		if (push(stack, vector[i]) == -1) {
			return -1;
		}
	}

	return 1;
}

/*
 * Function to validate the stack structure.
 * Checks for consistency like size matching actual nodes.
 * stack: pointer to DynamicStack instance.
 * return: true if valid, false otherwise.
 */
bool is_valid(const DynamicStack *stack) {
	if (!stack) {
		return false;
	}

	int count = 0;

	Node* current = stack->head;
	while (current) {
		count++;
		current = current->below;
	}

	return (count == stack->size);
}

/*
 * Function to print all elements in the stack.
 * stack: pointer to the DynamicStack instance.
 * return: status of the operation (1: success, -1: error).
 */
int print_stack(const DynamicStack *stack) {
	if (!is_valid(stack)) {
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
int print_stack_attributes(const DynamicStack *stack) {
	if (!is_valid(stack)) {
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
void free_stack(DynamicStack **stack) {
	if (!stack || !(*stack)) {
		return;
	}

	Node *current = (*stack)->head;
	while (current) {
		Node *temp = current;
		current = current->below;
		free(temp);
	}

	free(*stack);	// Free the stack structure itself
	*stack = NULL; // Set the original pointer to NULL to avoid dangling pointer
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
	if (!is_valid(stack)) {
		printf("Failed to create stack.\n");
		return 1;
	}

	print_stack_attributes(stack);

	push(stack, 10);
	push(stack, 20);
	push(stack, 30);
	print_stack_attributes(stack);

	// Test search function
	int idx = search(stack, 20);
	printf("Search for 20: %sfound at index %d\n", (idx == -1) ? "Not " : "", idx);

	// Test clone function
	DynamicStack* clone_stack = create_stack();
	if (clone(stack, clone_stack) == 1) {
		printf("Cloned stack:\n");
		print_stack(clone_stack);
	} else {
		printf("Failed to clone stack.\n");
	}

	// Test invert function
	if (invert(stack) == 1) {
		printf("Inverted original stack:\n");
		print_stack(stack);
	} else {
		printf("Failed to invert stack.\n");
	}

	// Test is_equal function
	int eq = is_equal(stack, clone_stack);
	printf("Is original stack equal to cloned stack? %s\n", eq == 1 ? "Yes" : "No");

	// Test insert_vector function
	ElementType vals[] = {40, 50, 60};
	if (insert_vector(stack, vals, 3) == 1) {
		printf("Stack after inserting vector elements:\n");
		print_stack(stack);
	} else {
		printf("Failed to insert vector.\n");
	}

	// Test is_valid function
	printf("Is stack valid? %s\n", is_valid(stack) ? "Yes" : "No");

	ElementType popped_element;
	pop(stack, &popped_element);
	printf("Popped element: %d\n", popped_element);
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

	// Free both stacks
	free_stack(&stack);
	free_stack(&clone_stack);

	return 0;
}
