/*
 * Description: Recursive factorial calculation.
 * Author: Breno Farias da Silva.
 * Date: 28/05/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf, scanf

/*
 * Recursive function to calculate the factorial of a number.
 * n: non-negative integer whose factorial will be calculated.
 * return: factorial of n.
 */
int factorial(int n) {
	if (n == 0 || n == 1)
		return 1;
	return n * factorial(n - 1);
}

/*
 * Main function of the program.
 * argc: number of arguments passed on program call.
 * argv: array with the arguments passed on program call.
 * return: program execution status (0: no errors, otherwise: error code).
 */
int main(int argc, char *argv[]) {
	int number;

	printf("Enter a non-negative integer: ");
	scanf("%d", &number);

	if (number < 0) {
		printf("Factorial is not defined for negative numbers.\n");
		return 1;
	}

	int result = factorial(number);

	printf("Factorial of %d is %d.\n", number, result);

	return 0;
}
