/*
 * Description: Recursive function to compute the number of digits in an integer.
 * Author: Breno Farias da Silva.
 * Date: 28/05/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf, scanf
#include <stdlib.h> // abs

/*
 * Recursive function to count the number of digits in an integer.
 * n: the integer to be analyzed.
 * return: the number of digits in n.
 */
int count_digits(int n) {
	if (abs(n) <= 9)
		return 1;
	else
		return 1 + count_digits(n / 10);
}

/*
 * Main function of the program.
 * argc: number of arguments passed on program call.
 * argv: array with the arguments passed on program call.
 * return: program execution status (0: no errors, otherwise: error code).
 */
int main(int argc, char *argv[]) {
	int number;

	printf("Enter an integer: ");
	scanf("%d", &number);

	int result = count_digits(number);

	printf("Number of digits: %d\n", result);

	return 0;
}
