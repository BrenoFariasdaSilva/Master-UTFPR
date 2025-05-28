/*
 * Description: Quick Sort implementation using recursion.
 * Author: Breno Farias da Silva.
 * Date: 28/05/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf, scanf

/*
 * Function to swap two integers.
 * a: pointer to the first integer.
 * b: pointer to the second integer.
 */
void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

/*
 * Partition function for Quick Sort.
 * arr: array to be partitioned.
 * low: starting index of the partition.
 * high: ending index of the partition.
 * return: the partition index.
 */
int partition(int arr[], int low, int high) {
	int pivot = arr[high];
	int i = low - 1;

	for (int j = low; j <= high - 1; j++) {
		if (arr[j] < pivot) {
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return i + 1;
}

/*
 * Recursive Quick Sort function.
 * arr: array to be sorted.
 * low: starting index.
 * high: ending index.
 */
void quick_sort(int arr[], int low, int high) {
	if (low < high) {
		int pi = partition(arr, low, high);

		quick_sort(arr, low, pi - 1);
		quick_sort(arr, pi + 1, high);
	}
}

/*
 * Main function of the program.
 * argc: number of arguments passed on program call.
 * argv: array with the arguments passed on program call.
 * return: program execution status (0: no errors, otherwise: error code).
 */
int main(int argc, char *argv[]) {
	int arr[] = {10, 7, 8, 9, 1, 5};
	int n = sizeof(arr) / sizeof(arr[0]);

	printf("Original array: ");
	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");

	quick_sort(arr, 0, n - 1);

	printf("Sorted array: ");
	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");

	return 0;
}
