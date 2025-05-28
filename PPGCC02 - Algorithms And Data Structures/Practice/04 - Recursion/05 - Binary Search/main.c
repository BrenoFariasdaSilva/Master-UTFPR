/*
 * Description: Recursive binary search in a sorted array.
 * Author: Breno Farias da Silva.
 * Date: 28/05/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf, scanf

/*
 * Recursive function to perform binary search in a sorted array.
 * arr: sorted array of integers.
 * left: starting index of the current search range.
 * right: ending index of the current search range.
 * key: value to search for.
 * return: index of the key if found, otherwise -1.
 */
int binarySearch(int arr[], int left, int right, int key) {
	if (left > right) {
		return -1;
	}

	int mid = left + (right - left) / 2;

	if (arr[mid] == key) {
		return mid;
	} else if (key < arr[mid]) {
		return binarySearch(arr, left, mid - 1, key);
	} else {
		return binarySearch(arr, mid + 1, right, key);
	}
}

/*
 * Main function of the program.
 * argc: number of arguments passed on program call.
 * argv: array with the arguments passed on program call.
 * return: program execution status (0: no errors, otherwise: error code).
 */
int main(int argc, char *argv[]) {
	int arr[] = {1, 3, 5, 7, 9, 12, 15, 18};
	int size = sizeof(arr) / sizeof(arr[0]);
	int key, result;

	printf("Enter value to search: ");
	scanf("%d", &key);

	result = binarySearch(arr, 0, size - 1, key);

	if (result != -1) {
		printf("Value found at index %d.\n", result);
	} else {
		printf("Value not found in the array.\n");
	}

	return 0;
}
