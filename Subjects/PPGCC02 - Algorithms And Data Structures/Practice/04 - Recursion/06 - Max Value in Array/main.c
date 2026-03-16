/*
 * Description: Recursive function to find the maximum value in an array.
 * Author: Breno Farias da Silva.
 * Date: 28/05/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf, scanf

/*
 * Recursive function to find the maximum value in an array.
 * arr: array of integers.
 * index: current index being evaluated.
 * size: total number of elements in the array.
 * currentMax: current maximum value found.
 * return: maximum value in the array.
 */
int findMax(int arr[], int index, int size, int currentMax) {
	if (index == size) {
		return currentMax;
	}

	if (arr[index] > currentMax) {
		currentMax = arr[index];
	}

	return findMax(arr, index + 1, size, currentMax);
}

/*
 * Main function of the program.
 * argc: number of arguments passed on program call.
 * argv: array with the arguments passed on program call.
 * return: program execution status (0: no errors, otherwise: error code).
 */
int main(int argc, char *argv[]) {
	int arr[] = {7, 3, 15, 2, 10, 18, 5};
	int size = sizeof(arr) / sizeof(arr[0]);

	int max = findMax(arr, 1, size, arr[0]);

	printf("Maximum value: %d\n", max);

	return 0;
}
