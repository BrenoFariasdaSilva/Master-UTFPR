/*
 * Description: Solves the Integer Partition Problem using recursion.
 *              Counts the number of ways to write n as a sum of positive integers.
 * Author: Breno Farias da Silva.
 * Date: 24/06/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf, scanf

/*
 * Counts the number of ways to partition 'n' using integers up to 'max'.
 * n: the integer to partition.
 * max: the maximum allowed integer in the partition.
 * return: number of possible partitions.
 */
int countPartitions(int n, int max) {
	if (n == 0) {
		return 1; // Found a valid partition
	}
	if (n < 0 || max == 0) {
		return 0; // Invalid partition
	}

	// Include 'max' in the partition or exclude it
	return countPartitions(n - max, max) + countPartitions(n, max - 1);
}

/*
 * Main function of the program.
 * argc: number of arguments passed on program call.
 * argv: array with the arguments passed on program call.
 * return: program execution status (0: no errors, otherwise: error code).
 */
int main(int argc, char *argv[]) {
	int n;

	printf("Enter a positive integer: ");
	scanf("%d", &n);

	if (n <= 0) {
		printf("Invalid input. Please enter a positive integer.\n");
		return 1;
	}

	int result = countPartitions(n, n);

	printf("Number of integer partitions of %d: %d\n", n, result);

	return 0;
}
