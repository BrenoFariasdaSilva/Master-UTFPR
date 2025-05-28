/*
 * Description: Recursive sequential search in an array.
 * Author: Breno Farias da Silva.
 * Date: 28/05/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf, scanf

/*
 * Recursive function to perform a sequential search in an array.
 * arr: array of integers.
 * size: total number of elements in the array.
 * index: current index being evaluated.
 * key: value to search for.
 * return: index of the key if found, otherwise -1.
 */
int sequentialSearch(int arr[], int size, int index, int key) {
	if (index >= size) {
		return -1;
	}
	if (arr[index] == key) {
		return index;
	}
	return sequentialSearch(arr, size, index + 1, key);
}

/*
 * Main function of the program.
 * argc: number of arguments passed on program call.
 * argv: array with the arguments passed on program call.
 * return: program execution status (0: no errors, otherwise: error code).
 */
int main(int argc, char *argv[]) {
	int arr[] = {5, 12, 7, 20, 3, 9};
	int size = sizeof(arr) / sizeof(arr[0]);
	int key, result;

	printf("Enter value to search: ");
	scanf("%d", &key);

	result = sequentialSearch(arr, size, 0, key);

	if (result != -1) {
		printf("Value found at index %d.\n", result);
	} else {
		printf("Value not found in the array.\n");
	}

	return 0;
}
