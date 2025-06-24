/*
 * Description: Generates all permutations of an array using recursion and backtracking.
 * Author: Breno Farias da Silva.
 * Date: 24/06/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf, scanf

/*
 * Swaps two integers.
 * a: pointer to first integer.
 * b: pointer to second integer.
 */
void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

/*
 * Recursively generates and prints all permutations of the array.
 * arr: array containing the elements to permute.
 * start: current index to fix.
 * end: total number of elements in the array.
 */
void generatePermutations(int arr[], int start, int end) {
	if (start == end) {
		for (int i = 0; i < end; i++) {
			printf("%d ", arr[i]);
		}
		printf("\n");
		return;
	}

	for (int i = start; i < end; i++) {
		swap(&arr[start], &arr[i]);
		generatePermutations(arr, start + 1, end);
		swap(&arr[start], &arr[i]); // Backtrack
	}
}

/*
 * Main function of the program.
 * argc: number of arguments passed on program call.
 * argv: array with the arguments passed on program call.
 * return: program execution status (0: no errors, otherwise: error code).
 */
int main(int argc, char *argv[]) {
	int n;

	printf("Enter the number of elements: ");
	scanf("%d", &n);

	int arr[n];

	printf("Enter %d elements:\n", n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}

	printf("\nPermutations:\n");
	generatePermutations(arr, 0, n);

	return 0;
}
