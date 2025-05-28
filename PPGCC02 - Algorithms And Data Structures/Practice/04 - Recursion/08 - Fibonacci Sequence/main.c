/*
 * Description: Calculate the nth Fibonacci number using recursion.
 * Author: Breno Farias da Silva.
 * Date: 28/05/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf, scanf

/*
 * Recursive function to calculate the nth Fibonacci number.
 * n: position in Fibonacci sequence.
 * return: nth Fibonacci number.
 */
int fibonacci(int n) {
	if (n <= 1)
		return n;
	return fibonacci(n - 1) + fibonacci(n - 2);
}

/*
 * Main function of the program.
 * argc: number of arguments passed on program call.
 * argv: array with the arguments passed on program call.
 * return: program execution status (0: no errors, otherwise: error code).
 */
int main(int argc, char *argv[]) {
	int n = 10;
	printf("Fibonacci number at position %d is %d\n", n, fibonacci(n));

	return 0;
}
