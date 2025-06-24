/*
 * Description: Calculates the number of ways to climb a staircase with n steps.
 * Each time, you can climb either 1 or 2 steps.
 * The recurrence relation is f(n) = f(n-1) + f(n-2).
 * Author: Breno Farias da Silva.
 * Date: 24/06/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf, scanf

/*
 * Calculates the number of ways to climb n steps.
 * Each time, you can climb either 1 or 2 steps.
 * n: total number of steps.
 * return: number of ways to climb the stairs.
 */
int countWays(int n) {
	if (n == 0 || n == 1) {
		return 1;
	}

	return countWays(n - 1) + countWays(n - 2);
}

/*
 * Main function of the program.
 * argc: number of arguments passed on program call.
 * argv: array with the arguments passed on program call.
 * return: program execution status (0: no errors, otherwise: error code).
 */
int main(int argc, char *argv[]) {
	int n;

	printf("Enter the number of steps: ");
	scanf("%d", &n);

	int ways = countWays(n);

	printf("Number of ways to climb %d steps: %d\n", n, ways);

	return 0;
}
