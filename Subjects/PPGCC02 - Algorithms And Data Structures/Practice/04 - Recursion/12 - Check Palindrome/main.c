/*
 * Description: Recursively check if a string is a palindrome.
 * Author: Breno Farias da Silva.
 * Date: 28/05/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf, scanf
#include <string.h> // strlen

/*
 * Recursive function to check if a string is a palindrome.
 * str: the string to check.
 * start: starting index.
 * end: ending index.
 * return: 1 if palindrome, 0 otherwise.
 */
int is_palindrome(const char *str, int start, int end) {
	if (start >= end) {
		return 1; // Base case: all characters matched
	}
	if (str[start] != str[end]) {
		return 0; // Characters don't match, not palindrome
	}
	// Recursive call moving towards the middle
	return is_palindrome(str, start + 1, end - 1);
}

/*
 * Main function of the program.
 * argc: number of arguments passed on program call.
 * argv: array with the arguments passed on program call.
 * return: program execution status (0: no errors, otherwise: error code).
 */
int main(int argc, char *argv[]) {
	const char *test_str = "madam";
	int len = strlen(test_str);

	if (is_palindrome(test_str, 0, len - 1)) {
		printf("\"%s\" is a palindrome.\n", test_str);
	} else {
		printf("\"%s\" is not a palindrome.\n", test_str);
	}

	return 0;
}
