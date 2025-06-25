/*
 * Description: Implementation of various sorting algorithms.
 * Author: Breno Farias da Silva.
 * Date: 14/06/2025.
 */

#include <stdio.h> // printf
#include <stdlib.h> // malloc, free
#include <string.h> // memset

#include "sorting.h" // Function prototypes

/*
 * Sorts an array using the Bubble Sort algorithm.
 * arr: array to be sorted.
 * size: size of the array.
 */
void bubbleSort(int arr[], int size) {
	int temp;
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				// Swap arr[j] and arr[j + 1]
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

/*
* Sorts an array using the Insertion Sort algorithm.
* arr: array to be sorted.
* size: size of the array.
*/
void insertionSort(int arr[], int size) {
	int key, j;
	for (int i = 1; i < size; i++) {
		key = arr[i];
		j = i - 1;
		while (j >= 0 && arr[j] > key) {
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
	}
}

/*
* Sorts an array using the Selection Sort algorithm.
* arr: array to be sorted.
* size: size of the array.
*/
void selectionSort(int arr[], int size) {
	int minIdx, temp;
	for (int i = 0; i < size - 1; i++) {
		minIdx = i;
		for (int j = i + 1; j < size; j++) {
			if (arr[j] < arr[minIdx]) {
				minIdx = j;
			}
		}
		// Swap arr[i] and arr[minIdx]
		temp = arr[i];
		arr[i] = arr[minIdx];
		arr[minIdx] = temp;
	}
}

/*
* Helper function for Quick Sort to partition the array.
* arr: array to be partitioned.
* low: starting index.
* high: ending index.
* return: partition index.
*/
int partition(int arr[], int low, int high) {
	int pivot = arr[high];
	int i = low - 1;
	int temp;

	for (int j = low; j < high; j++) {
		if (arr[j] < pivot) {
			i++;
			// Swap arr[i] and arr[j]
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}
	// Swap arr[i + 1] and arr[high] (pivot)
	temp = arr[i + 1];
	arr[i + 1] = arr[high];
	arr[high] = temp;

	return i + 1;
}

/*
* Sorts an array using the Quick Sort algorithm.
* arr: array to be sorted.
* low: starting index.
* high: ending index.
*/
void quickSort(int arr[], int low, int high) {
	if (low < high) {
		int pi = partition(arr, low, high);

		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}

/*
* Helper function for Heap Sort to heapify a subtree.
* arr: array to be heapified.
* size: size of the heap.
* i: root index of the subtree.
*/
void heapify(int arr[], int size, int i) {
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	int temp;

	if (left < size && arr[left] > arr[largest]) {
		largest = left;
	}

	if (right < size && arr[right] > arr[largest]) {
		largest = right;
	}

	if (largest != i) {
		// Swap arr[i] and arr[largest]
		temp = arr[i];
		arr[i] = arr[largest];
		arr[largest] = temp;

		heapify(arr, size, largest);
	}
}

/*
* Sorts an array using the Heap Sort algorithm.
* arr: array to be sorted.
* size: size of the array.
*/
void heapSort(int arr[], int size) {
	// Build max heap
	for (int i = size / 2 - 1; i >= 0; i--) {
		heapify(arr, size, i);
	}

	// Extract elements from heap
	int temp;
	for (int i = size - 1; i > 0; i--) {
		// Swap arr[0] and arr[i]
		temp = arr[0];
		arr[0] = arr[i];
		arr[i] = temp;

		heapify(arr, i, 0);
	}
}

/*
* Helper function for Merge Sort to merge two subarrays.
* arr: array to be merged.
* left: starting index of the first subarray.
* mid: ending index of the first subarray.
* right: ending index of the second subarray.
*/
void merge(int arr[], int left, int mid, int right) {
	int n1 = mid - left + 1;
	int n2 = right - mid;

	// Create temp arrays
	int *L = (int *)malloc(n1 * sizeof(int));
	int *R = (int *)malloc(n2 * sizeof(int));

	// Copy data to temp arrays
	for (int i = 0; i < n1; i++) {
		L[i] = arr[left + i];
	}
	for (int j = 0; j < n2; j++) {
		R[j] = arr[mid + 1 + j];
	}

	// Merge the temp arrays back into arr
	int i = 0, j = 0, k = left;
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			arr[k++] = L[i++];
		} else {
			arr[k++] = R[j++];
		}
	}

	// Copy remaining elements
	while (i < n1) {
		arr[k++] = L[i++];
	}
	while (j < n2) {
		arr[k++] = R[j++];
	}

	free(L);
	free(R);
}

/*
* Sorts an array using the Merge Sort algorithm.
* arr: array to be sorted.
* left: starting index.
* right: ending index.
*/
void mergeSort(int arr[], int left, int right) {
	if (left < right) {
		int mid = left + (right - left) / 2;

		mergeSort(arr, left, mid);
		mergeSort(arr, mid + 1, right);

		merge(arr, left, mid, right);
	}
}

/*
* Sorts an array using the Bucket Sort algorithm.
* arr: array to be sorted.
* size: size of the array.
*/
void bucketSort(int arr[], int size) {
	int max = arr[0];
	int min = arr[0];

	// Find min and max
	for (int i = 1; i < size; i++) {
		if (arr[i] > max) {
			max = arr[i];
		}
		if (arr[i] < min) {
			min = arr[i];
		}
	}

	int bucketCount = (max - min) / size + 1;
	int **buckets = (int **)malloc(bucketCount * sizeof(int *));
	int *bucketSizes = (int *)malloc(bucketCount * sizeof(int));

	for (int i = 0; i < bucketCount; i++) {
		buckets[i] = (int *)malloc(size * sizeof(int));
		bucketSizes[i] = 0;
	}

	// Distribute elements into buckets
	for (int i = 0; i < size; i++) {
		int index = (arr[i] - min) / size;
		buckets[index][bucketSizes[index]++] = arr[i];
	}

	// Sort individual buckets using Insertion Sort
	int idx = 0;
	for (int i = 0; i < bucketCount; i++) {
		insertionSort(buckets[i], bucketSizes[i]);
		for (int j = 0; j < bucketSizes[i]; j++) {
			arr[idx++] = buckets[i][j];
		}
	}

	// Free memory
	for (int i = 0; i < bucketCount; i++) {
		free(buckets[i]);
	}
	free(buckets);
	free(bucketSizes);
}
