/*
 * Description: Generates all anagrams (permutations) of a given string using recursion.
 * Author: Breno Farias da Silva.
 * Date: 24/06/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf, scanf
#include <string.h> // strlen

/*
 * Swaps two characters in a string.
 */
void swap(char *x, char *y) {
	char temp = *x;
	*x = *y;
	*y = temp;
}

/*
 * Recursive function to generate all permutations of the string.
 * str: the string to permute.
 * start: starting index for permutation.
 * end: ending index for permutation.
 */
void generateAnagrams(char str[], int start, int end) {
	if (start == end) {
		printf("%s\n", str);
		return;
	}
	for (int i = start; i <= end; i++) {
		swap(&str[start], &str[i]);
		generateAnagrams(str, start + 1, end);
		swap(&str[start], &str[i]); // backtrack
	}
}

/*
 * Main function of the program.
 * argc: number of arguments passed on program call.
 * argv: array with the arguments passed on program call.
 * return: program execution status (0: no errors, otherwise: error code).
 */
int main(int argc, char *argv[]) {
	char str[100];

	printf("Enter a string: ");
	scanf("%99s", str);

	generateAnagrams(str, 0, strlen(str) - 1);

	return 0;
}
