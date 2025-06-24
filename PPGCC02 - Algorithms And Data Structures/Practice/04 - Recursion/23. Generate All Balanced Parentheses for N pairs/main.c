/*
 * Description: Generates all balanced parentheses combinations for N pairs using recursion.
 * Author: Breno Farias da Silva.
 * Date: 24/06/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf, scanf

/*
 * Recursive function to generate all balanced parentheses.
 * str: current string being built.
 * pos: current position in the string.
 * n: total number of pairs.
 * open: number of open parentheses used.
 * close: number of close parentheses used.
 */
void generateParentheses(char str[], int pos, int n, int open, int close) {
	if (close == n) {
		str[pos] = '\0';
		printf("%s\n", str);
		return;
	}

	if (open < n) {
		str[pos] = '(';
		generateParentheses(str, pos + 1, n, open + 1, close);
	}

	if (close < open) {
		str[pos] = ')';
		generateParentheses(str, pos + 1, n, open, close + 1);
	}
}

/*
 * Main function of the program.
 * argc: number of arguments passed on program call.
 * argv: array with the arguments passed on program call.
 * return: program execution status (0: no errors, otherwise: error code).
 */
int main(int argc, char *argv[]) {
	int n;

	printf("Enter the number of pairs of parentheses: ");
	scanf("%d", &n);

	if (n < 0) {
		printf("Invalid input. Please enter a non-negative integer.\n");
		return 1;
	}

	char str[2 * n + 1]; // To hold the parentheses string (+1 for '\0')

	printf("All balanced parentheses combinations for %d pairs:\n", n);
	generateParentheses(str, 0, n, 0, 0);

	return 0;
}
