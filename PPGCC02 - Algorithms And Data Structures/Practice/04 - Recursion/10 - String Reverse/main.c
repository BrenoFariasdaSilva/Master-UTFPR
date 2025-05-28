/*
 * Description: Recursively reverse a string in place.
 * Author: Breno Farias da Silva.
 * Date: 28/05/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf, scanf
#include <string.h> // strlen

/*
 * Recursive function to reverse a string in place.
 * str: the string to reverse.
 * start: starting index for reversal.
 * end: ending index for reversal.
 */
void reverse_string(char *str, int start, int end) {
	if (start >= end) {
		return;
	}

	// Swap characters at start and end
	char temp = str[start];
	str[start] = str[end];
	str[end] = temp;

	// Recursive call moving towards the middle
	reverse_string(str, start + 1, end - 1);
}

/*
 * Main function of the program.
 * argc: number of arguments passed on program call.
 * argv: array with the arguments passed on program call.
 * return: program execution status (0: no errors, otherwise: error code).
 */
int main(int argc, char *argv[]) {
	char str[] = "Hello World!";
	printf("Original string: %s\n", str);

	reverse_string(str, 0, (int)strlen(str) - 1);

	printf("Reversed string: %s\n", str);

	return 0;
}
