/*
 * Description: Recursive decimal to binary conversion.
 * Author: Breno Farias da Silva.
 * Date: 28/05/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf, scanf

/*
 * Recursive function to print the binary representation of a number.
 * n: the decimal number to be converted to binary.
 * return: void.
 */
void decimalToBinary(int n) {
	if (n == 0) {
		return;
	}
	decimalToBinary(n / 2);
	printf("%d", n % 2);
}

/*
 * Main function of the program.
 * argc: number of arguments passed on program call.
 * argv: array with the arguments passed on program call.
 * return: program execution status (0: no errors, otherwise: error code).
 */
int main(int argc, char *argv[]) {
	int number;

	printf("Enter a positive integer: ");
	scanf("%d", &number);

	if (number == 0) {
		printf("Binary: 0\n");
	} else if (number > 0) {
		printf("Binary: ");
		decimalToBinary(number);
		printf("\n");
	} else {
		printf("Negative numbers are not supported.\n");
	}

	return 0;
}
