/*
 * Description: Compute the Greatest Common Divisor (GCD) of two integers using recursion.
 * Author: Breno Farias da Silva.
 * Date: 28/05/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf, scanf

/*
 * Recursive function to calculate the GCD of two integers using Euclid's algorithm.
 * a: first integer.
 * b: second integer.
 * return: greatest common divisor of a and b.
 */
int gcd(int a, int b) {
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

/*
 * Main function of the program.
 * argc: number of arguments passed on program call.
 * argv: array with the arguments passed on program call.
 * return: program execution status (0: no errors, otherwise: error code).
 */
int main(int argc, char *argv[]) {
	int num1 = 56;
	int num2 = 98;
	printf("GCD of %d and %d is %d\n", num1, num2, gcd(num1, num2));

	return 0;
}
