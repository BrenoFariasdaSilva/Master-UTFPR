/*
 * Description: Merge Sort implementation using recursion.
 * Author: Breno Farias da Silva.
 * Date: 28/05/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf, scanf

/*
 * Function to merge two sorted subarrays into a single sorted array.
 * arr: original array containing the subarrays.
 * left: starting index of the left subarray.
 * mid: ending index of the left subarray and mid + 1 is start of right subarray.
 * right: ending index of the right subarray.
 */
void merge(int arr[], int left, int mid, int right) {
	int n1 = mid - left + 1;
	int n2 = right - mid;

	int L[n1], R[n2];

	// Copy data to temporary arrays L[] and R[]
	for (int i = 0; i < n1; i++)
		L[i] = arr[left + i];
	for (int j = 0; j < n2; j++)
		R[j] = arr[mid + 1 + j];

	int i = 0, j = 0, k = left;

	// Merge the temporary arrays back into arr[left..right]
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			arr[k] = L[i];
			i++;
		} else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	// Copy remaining elements of L[], if any
	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}

	// Copy remaining elements of R[], if any
	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}
}

/*
 * Recursive Merge Sort function.
 * arr: array to be sorted.
 * left: starting index.
 * right: ending index.
 */
void merge_sort(int arr[], int left, int right) {
	if (left < right) {
		int mid = left + (right - left) / 2;

		merge_sort(arr, left, mid);
		merge_sort(arr, mid + 1, right);

		merge(arr, left, mid, right);
	}
}

/*
 * Main function of the program.
 * argc: number of arguments passed on program call.
 * argv: array with the arguments passed on program call.
 * return: program execution status (0: no errors, otherwise: error code).
 */
int main(int argc, char *argv[]) {
	int arr[] = {12, 11, 13, 5, 6, 7};
	int n = sizeof(arr) / sizeof(arr[0]);

	printf("Original array: ");
	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");

	merge_sort(arr, 0, n - 1);

	printf("Sorted array: ");
	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");

	return 0;
}
