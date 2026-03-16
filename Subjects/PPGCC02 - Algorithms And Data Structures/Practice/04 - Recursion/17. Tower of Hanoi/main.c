/*
 * Description: Solves the Tower of Hanoi problem recursively.
 * Moves disks from source to destination using an auxiliary rod.
 * Author: Breno Farias da Silva.
 * Date: 24/06/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf, scanf

/*
 * Solves the Tower of Hanoi problem recursively.
 * n: number of disks to move.
 * source: the name of the source rod.
 * auxiliary: the name of the auxiliary rod.
 * destination: the name of the destination rod.
 */
void hanoi(int n, char source, char auxiliary, char destination) {
	if (n == 1) {
		printf("Move disk 1 from %c to %c\n", source, destination);
		return;
	}

	hanoi(n - 1, source, destination, auxiliary);
	printf("Move disk %d from %c to %c\n", n, source, destination);
	hanoi(n - 1, auxiliary, source, destination);
}

/*
 * Main function of the program.
 * argc: number of arguments passed on program call.
 * argv: array with the arguments passed on program call.
 * return: program execution status (0: no errors, otherwise: error code).
 */
int main(int argc, char *argv[]) {
	int n;

	printf("Enter the number of disks: ");
	scanf("%d", &n);

	printf("\nSteps to solve Tower of Hanoi with %d disks:\n\n", n);
	hanoi(n, 'A', 'B', 'C');

	return 0;
}
