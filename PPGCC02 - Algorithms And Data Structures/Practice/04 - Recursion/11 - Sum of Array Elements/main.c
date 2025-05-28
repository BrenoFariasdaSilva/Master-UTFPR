/*
 * Description: Recursively compute the sum of all elements in an array.
 * Author: Breno Farias da Silva.
 * Date: 28/05/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf, scanf

/*
 * Recursive function to compute the sum of array elements.
 * arr: array of integers.
 * n: number of elements in the array.
 * return: sum of the array elements.
 */
int sum_array(int arr[], int n) {
	if (n == 0) {
		return 0;
	}

	// Sum current element plus sum of remaining elements
	return arr[n - 1] + sum_array(arr, n - 1);
}

/*
 * Main function of the program.
 * argc: number of arguments passed on program call.
 * argv: array with the arguments passed on program call.
 * return: program execution status (0: no errors, otherwise: error code).
 */
int main(int argc, char *argv[]) {
	int arr[] = {1, 2, 3, 4, 5};
	int size = sizeof(arr) / sizeof(arr[0]);

	int total = sum_array(arr, size);
	printf("Sum of array elements: %d\n", total);

	return 0;
}
