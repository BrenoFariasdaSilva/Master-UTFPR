/*
 * Description: Calculate the sum of the digits of an integer recursively.
 * Author: Breno Farias da Silva.
 * Date: 28/05/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf, scanf
#include <stdlib.h> // abs

/*
 * Recursive function to calculate the sum of the digits of an integer.
 * n: the integer to calculate the sum of digits.
 * return: sum of the digits of n.
 */
int sum_of_digits(int n) {
	n = abs(n); // Handle negative numbers by using absolute value
	if (n < 10)
		return n;
	else
		return (n % 10) + sum_of_digits(n / 10);
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

	printf("Sum of digits of %d is %d\n", number, sum_of_digits(number));

	return 0;
}
