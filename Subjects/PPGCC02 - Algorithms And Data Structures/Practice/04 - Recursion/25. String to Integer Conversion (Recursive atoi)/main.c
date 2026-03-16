/*
 * Description: Converts a numeric string to an integer using recursion.
 * Author: Breno Farias da Silva.
 * Date: 24/06/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf, scanf
#include <string.h> // strlen

/*
 * Recursive function to convert string to integer.
 * str: input numeric string.
 * index: current index being processed.
 * length: total length of the string.
 * return: integer value of the string.
 */
int recursiveAtoi(const char *str, int index, int length) {
	if (index == length)
		return 0;
	int digit = str[index] - '0';
	return digit * pow(10, length - index - 1) + recursiveAtoi(str, index + 1, length);
}

/*
 * Main function of the program.
 * argc: number of arguments passed on program call.
 * argv: array with the arguments passed on program call.
 * return: program execution status (0: no errors, otherwise: error code).
 */
int main(int argc, char *argv[]) {
	char str[100];

	printf("Enter a numeric string: ");
	scanf("%99s", str);

	int length = strlen(str);
	int result = recursiveAtoi(str, 0, length);

	printf("Converted integer: %d\n", result);

	return 0;
}

/*
 * Helper function: pow for integer base and exponent.
 * Implemented here to avoid including math.h.
 */
int pow(int base, int exp) {
	int result = 1;
	for (int i = 0; i < exp; i++) {
		result *= base;
	}
	return result;
}
