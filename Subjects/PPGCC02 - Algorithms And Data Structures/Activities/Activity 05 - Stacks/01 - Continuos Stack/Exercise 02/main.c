/*
 * Description: Program that reverses the letters of each word in a text
 *              ending with a period, preserving the word order.
 * Author: Breno Farias da Silva.
 * Date: 16/05/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // Input and output functions: printf
#include <string.h> // String manipulation (not directly used, but useful for future expansion)
#include <ctype.h> // isalpha function to check if a character is a letter

#define MAX 100 // Defines the maximum size of the stack

/*
 * Structure that represents the contiguous stack.
 * items: array of stored characters.
 * top: index of the top of the stack.
*/
typedef struct {
	char items[MAX];
	int top;
} Stack;

/*
 * Initializes the stack by setting the top to -1, i.e., an empty stack.
 * p: pointer to the stack to be initialized.
*/
void create_stack(Stack* p) {
	p->top = -1;
}

/*
 * Checks if the stack is empty.
 * p: pointer to the stack to be checked.
 * return: 1 if empty, 0 otherwise.
*/
int is_stack_empty(Stack* p) {
	return p->top == -1;
}

/*
 * Pushes a character onto the stack.
 * p: pointer to the stack.
 * elem: character to be pushed.
 * return: 1 if successfully pushed, 0 if the stack is full.
*/
int push(Stack* p, char elem) {
	if (p->top == MAX - 1) return 0; // Stack full
	p->items[++(p->top)] = elem;
	return 1;
}

/*
 * Pops a character from the stack.
 * p: pointer to the stack.
 * elem: pointer to where the popped character will be stored.
 * return: 1 if successfully popped, 0 if the stack is empty.
*/
int pop(Stack* p, char* elem) {
	if (is_stack_empty(p)) return 0; // Stack empty
	*elem = p->items[(p->top)--];
	return 1;
}

/*
 * Function that goes through a text and reverses the letters of each word,
 * keeping the order of the words. Uses a stack to reverse the letters.
 * text: input string, ending with a period.
*/
void reverse_letters_in_words(char* text) {
	Stack p;
	create_stack(&p); // Initializes the stack

	int i = 0;
	char c;

	// Goes through the string character by character
	while (text[i] != '\0') {
		c = text[i];

		if (isalpha(c)) {
			// If it's a letter, push it to reverse later
			push(&p, c);
		} else {
			// If it's not a letter (space or period), pop and print the reversed word
			char letter;
			while (!is_stack_empty(&p)) {
				pop(&p, &letter);
				printf("%c", letter);
			}

			// Print the separator character (space or period)
			printf("%c", c);
		}

		i++; // Move to the next character
	}

	printf("\n"); // New line at the end
}

/*
 * Main function of the program.
 * argc: number of arguments passed to the program.
 * argv: array with the arguments passed to the program.
 * return: execution status (0: no errors, otherwise, error code).
*/
int main(int argc, char* argv[]) {
	char text[] = "MESTRADO EM CIENCIA DA COMPUTACAO."; // Input text
	reverse_letters_in_words(text); // Calls the function to process the text
	return 0; // Return success
}
