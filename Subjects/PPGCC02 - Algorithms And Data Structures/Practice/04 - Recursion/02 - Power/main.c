/*
 * Description: Recursive power calculation, including support for negative exponents.
 * Author: Breno Farias da Silva.
 * Date: 28/05/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf, scanf

/*
 * Recursive function to calculate the power of a number.
 * base: the base value (double).
 * exponent: the exponent value (can be negative).
 * return: base raised to the power of exponent (as a double).
 */
double power(double base, int exponent) {
	if (exponent == 0)
		return 1.0;
	else if (exponent < 0)
		return 1.0 / power(base, -exponent);
	else
		return base * power(base, exponent - 1);
}

/*
 * Main function of the program.
 * argc: number of arguments passed on program call.
 * argv: array with the arguments passed on program call.
 * return: program execution status (0: no errors, otherwise: error code).
 */
int main(int argc, char *argv[]) {
	double base;
	int exponent;

	printf("Enter the base: ");
	scanf("%lf", &base);

	printf("Enter the exponent (integer): ");
	scanf("%d", &exponent);

	double result = power(base, exponent);

	printf("%.2lf raised to the power of %d is %.6lf.\n", base, exponent, result);

	return 0;
}
