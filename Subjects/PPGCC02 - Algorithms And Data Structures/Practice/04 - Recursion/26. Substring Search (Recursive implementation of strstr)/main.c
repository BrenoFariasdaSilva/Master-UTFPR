/*
 * Description: Recursive implementation of substring search (strstr).
 * Author: Breno Farias da Silva.
 * Date: 24/06/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf, scanf

/*
 * Helper function to check if needle matches haystack starting at current position.
 */
int startsWith(const char *haystack, const char *needle) {
	if (*needle == '\0') return 1;
	if (*haystack == '\0') return 0;
	if (*haystack != *needle) return 0;
	return startsWith(haystack + 1, needle + 1);
}

/*
 * Recursive strstr implementation.
 * Returns pointer to first occurrence of needle in haystack or NULL if not found.
 */
const char* recursiveStrstr(const char *haystack, const char *needle) {
	if (*needle == '\0') return haystack; // empty needle matches at start
	if (*haystack == '\0') return NULL;   // haystack empty but needle not found

	if (startsWith(haystack, needle))
		return haystack;
	return recursiveStrstr(haystack + 1, needle);
}

/*
 * Main function of the program.
 * argc: number of arguments passed on program call.
 * argv: array with the arguments passed on program call.
 * return: program execution status (0: no errors, otherwise: error code).
 */
int main(int argc, char *argv[]) {
	const char *haystack = "hello world";
	const char *needle = "world";

	const char *result = recursiveStrstr(haystack, needle);
	if (result)
		printf("Found substring at position: %ld\n", result - haystack);
	else
		printf("Substring not found.\n");

	return 0;
}
