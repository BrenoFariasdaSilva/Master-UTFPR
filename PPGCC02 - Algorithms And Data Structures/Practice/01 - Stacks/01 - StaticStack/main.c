/*
 * Description: This program shows an implementation of a Stack using Static Memory Allocation.
 * Author: Breno Farias da Silva.
 * Date: 15/05/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf, scanf
#include <stdbool.h> // 'bool', 'true', and 'false' keywords
#include <string.h> // strtok
#include <stdlib.h> // atoi
#include <ctype.h> // isdigit

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
int search(const StaticStack* stack, ElementType element);
int clone(const StaticStack* stack, StaticStack* clone);
int invert(StaticStack* stack);
int is_equal(const StaticStack* stack1, const StaticStack* stack2);
int insert_vector(StaticStack* stack, const ElementType* vector, int size);
bool is_valid(const StaticStack* stack);
int print_stack_attributes(const StaticStack* stack);
int print_stack(const StaticStack* stack);
int validate_parentheses_expression(const char* expression);
int evaluate_postfix_expression(const char* expression, int* result);
int destroy(StaticStack* stack);

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
	if (!is_valid(stack)) {
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
	if (!is_valid(stack) || !pop_element) {
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
	if (!is_valid(stack)) {
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
	if (!is_valid(stack)) {
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
	if (!is_valid(stack) || !top_element) {
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
	if (!is_valid(stack)) {
		return -1;
	}

	stack->quantity = 0;

	return 1;
}

/*
 * Function to search for an element starting from the top of the stack.
 * stack: pointer to the StaticStack instance.
 * element: the element to search for.
 * return: index from the top (0 = top element), or -1 if not found or error.
 */
int search(const StaticStack* stack, ElementType element) {
	if (!is_valid(stack)) {
		return -1;
	}

	for (int i = stack->quantity - 1; i >= 0; i--) {
		if (stack->vector[i] == element) {
			return stack->quantity - 1 - i; // index from top
		}
	}

	return -1; // not found
}

/*
 * Function to clone a stack.
 * stack: pointer to the source StaticStack.
 * clone: pointer to the destination StaticStack.
 * return: status of the operation (1: success, -1: error).
*/
int clone(const StaticStack* stack, StaticStack* clone) {
	if (!is_valid(stack) || !clone) {
		return -1;
	}

	clone->size = stack->size;
	clone->quantity = stack->quantity;

	for (int i = 0; i < stack->quantity; i++) {
		clone->vector[i] = stack->vector[i];
	}

	return 1;
}

/*
 * Function to invert the stack.
 * stack: pointer to the StaticStack instance.
 * return: status of the operation (1: success, -1: error).
*/
int invert(StaticStack* stack) {
	if (!is_valid(stack)) {
		return -1;
	}

	int start = 0;
	int end = stack->quantity - 1;

	while (start < end) {
		ElementType temp = stack->vector[start];
		stack->vector[start] = stack->vector[end];
		stack->vector[end] = temp;
		start++;
		end--;
	}

	return 1;
}

/*
 * Function to check if two stacks are equal.
 * stack1: pointer to the first StaticStack.
 * stack2: pointer to the second StaticStack.
 * return: 1 if equal, 0 if different, -1 if error.
*/
int is_equal(const StaticStack* stack1, const StaticStack* stack2) {
	if (!is_valid(stack1) || !is_valid(stack2)) {
		return -1;
	}

	if (stack1->quantity != stack2->quantity) {
		return 0;
	}

	for (int i = 0; i < stack1->quantity; i++) {
		if (stack1->vector[i] != stack2->vector[i]) {
			return 0;
		}
	}

	return 1;
}

/*
 * Function to insert elements from a vector into the stack.
 * stack: pointer to the StaticStack instance.
 * vector: array of elements to be inserted.
 * size: number of elements in the vector.
 * return: status of the operation (1: success, -1: error).
*/
int insert_vector(StaticStack* stack, const ElementType* vector, int size) {
	if (!is_valid(stack) || !vector || size < 0) {
		return -1;
	}

	if (stack->quantity + size > stack->size) {
		printf("Not enough space in the stack to insert all elements from the vector.\n");
		return -1;
	}

	for (int i = 0; i < size; i++) {
		stack->vector[stack->quantity++] = vector[i];
	}

	return 1;
}

/*
 * Function to check if the stack is valid.
 * stack: pointer to the StaticStack instance.
 * return: true if valid, false otherwise.
*/
bool is_valid(const StaticStack* stack) {
	if (!stack) {
		return false;
	}

	if (stack->size != MAX_SIZE) {
		return false;
	}

	if (stack->quantity < 0 || stack->quantity > stack->size) {
		return false;
	}

	return true;
}

/*
 * Function to print stack attributes.
 * stack: pointer to the StaticStack instance.
 * return: status of the operation (1: success, -1: error).
*/
int print_stack_attributes(const StaticStack* stack) {
	if (!is_valid(stack)) {
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
	if (!is_valid(stack)) {
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
 * Function to validate the use of parentheses in a mathematical expression.
 * expression: string containing the mathematical expression.
 * return: status of the validation (1: balanced, -1: unbalanced).
 */
int validate_parentheses_expression(const char* expression) {
	if (!expression) {
		return -1;
	}

	StaticStack stack = create_stack();

	for (int i = 0; expression[i] != '\0'; i++) {
		char ch = expression[i];

		// Push opening parenthesis to the stack
		if (ch == '(') {
			if (push(&stack, ch) == -1) {
				return -1;
			}
		}

		// On closing parenthesis, check for matching opening
		if (ch == ')') {
			char temp;
			if (pop(&stack, (int*)&temp) == -1) {
				// Stack is empty, so no matching opening parenthesis
				printf("Unmatched closing parenthesis at position %d.\n", i);
				return -1;
			}
		}
	}

	// After full traversal, stack should be empty
	if (stack.quantity != 0) {
		printf("Unmatched opening parenthesis.\n");
		return -1;
	}

	return 1;
}

/*
 * Function to evaluate a postfix (Reverse Polish Notation) expression.
 * expression: string containing the postfix expression, tokens separated by spaces.
 * result: pointer to store the final result of the evaluated expression.
 * return: status of the operation (1: success, -1: error).
 */
int evaluate_postfix_expression(const char* expression, int* result) {
	if (!expression || !result) {
		return -1;
	}

	StaticStack stack = create_stack();
	char expr_copy[256];
	strncpy(expr_copy, expression, sizeof(expr_copy) - 1);
	expr_copy[sizeof(expr_copy) - 1] = '\0';

	char* token = strtok(expr_copy, " ");
	while (token != NULL) {
		// Check if token is a number (positive or negative)
		if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
			int number = atoi(token);
			if (push(&stack, number) == -1) {
				return -1;
			}
		} else {
			// Token is expected to be an operator
			int b, a;

			if (pop(&stack, &b) == -1 || pop(&stack, &a) == -1) {
				printf("Invalid expression: not enough operands.\n");
				return -1;
			}

			int res;
			if (strcmp(token, "+") == 0) {
				res = a + b;
			} else if (strcmp(token, "-") == 0) {
				res = a - b;
			} else if (strcmp(token, "*") == 0) {
				res = a * b;
			} else if (strcmp(token, "/") == 0) {
				if (b == 0) {
					printf("Division by zero.\n");
					return -1;
				}
				res = a / b;
			} else {
				printf("Unknown operator: %s\n", token);
				return -1;
			}

			if (push(&stack, res) == -1) {
				return -1;
			}
		}

		token = strtok(NULL, " ");
	}

	// Final check: only one result should remain on the stack
	if (stack.quantity != 1) {
		printf("Invalid expression: too many operands.\n");
		return -1;
	}

	return pop(&stack, result);
}

/*
 * Function to destroy the stack.
 * stack: pointer to the StaticStack instance to be destroyed.
 * return: status of the operation (1: success, -1: error).
*/
int destroy(StaticStack* stack) {
	if (!is_valid(stack)) {
		return -1;
	}

	stack->size = 0;
	stack->quantity = 0;

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

	// Test is_valid
	printf("Is the stack valid? %s\n\n", is_valid(&stack) ? "Yes" : "No");

	// Test clone
	StaticStack stack_clone;
	if (clone(&stack, &stack_clone) == 1) {
		printf("Clone successful. Cloned stack contents:\n");
		print_stack_attributes(&stack_clone);
	} else {
		printf("Clone failed.\n");
	}

	// Test invert
	printf("Inverting the original stack...\n");
	if (invert(&stack) == 1) {
		printf("Stack inverted successfully.\n");
		print_stack_attributes(&stack);
	} else {
		printf("Failed to invert the stack.\n");
	}

	// Test is_equal
	printf("Are original and clone stacks equal? %s\n\n",
		is_equal(&stack, &stack_clone) == 1 ? "Yes" : "No");

	// Test insert_vector
	ElementType vec_to_insert[] = {30, 40, 50};
	printf("Inserting vector elements into the cloned stack...\n");
	if (insert_vector(&stack_clone, vec_to_insert, 3) == 1) {
		printf("Vector inserted successfully.\n");
		print_stack_attributes(&stack_clone);
	} else {
		printf("Failed to insert vector into stack.\n");
	}

	// Continue with previous tests
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

	print_stack_attributes(&stack_clone);

	// Search for an element
	ElementType search_for = 20;
	int index = search(&stack_clone, search_for);
	if (index != -1) {
		printf("Element %d found at position %d from the top of the stack.\n\n", search_for, index);
	} else {
		printf("Element %d not found in the stack.\n\n", search_for);
	}

	printf("Clearing the stack...\n");
	if (clear(&stack) == 1) {
		printf("Stack cleared successfully.\n\n");
	}

	print_stack_attributes(&stack);

	printf("Is Stack Full? %s\n", is_full(&stack) == 1 ? "Yes" : "No");

	// Evaluate a postfix expression
	const char* expression = "3 4 + 2 * 7 /";
	int eval_result;
	printf("\nEvaluating postfix expression: \"%s\"\n", expression);
	if (evaluate_postfix_expression(expression, &eval_result) == 1) {
		printf("Result of expression: %d\n", eval_result);
	} else {
		printf("Failed to evaluate the postfix expression.\n");
	}

	// Validate parentheses in an infix expression
	const char* infix_expression = "(3 + 4) * (2 - (1 + 1))";
	printf("\nValidating parentheses in expression: \"%s\"\n", infix_expression);
	if (validate_parentheses_expression(infix_expression) == 1) {
		printf("Parentheses are balanced and correctly nested.\n");
	} else {
		printf("Parentheses are not balanced or incorrectly nested.\n");
	}

	// Destroy the stack
	printf("\nDestroying the stack...\n");
	if (destroy(&stack) == 1) {
		printf("Stack destroyed successfully.\n");
	} else {
		printf("Failed to destroy the stack.\n");
	}


	return 0;
}
