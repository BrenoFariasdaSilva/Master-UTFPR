/*
 * Description: Program to test and measure the execution time of different sorting algorithms,
 *              displaying results ordered from fastest to slowest along with their complexity notation.
 * Author: Breno Farias da Silva.
 * Date: 14/06/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf, scanf
#include <stdlib.h> // rand, srand, malloc, free, qsort
#include <time.h> // clock, CLOCKS_PER_SEC
#include <string.h> // memcpy

#include "sorting.h" // Sorting algorithms

#define SIZE 10000 // Size of the array to sort
#define MAX_VALUE 10000 // Maximum random value

/*
 * Generates an array with random integers.
 * arr: array to be filled.
 * size: size of the array.
 */
void generateRandomArray(int arr[], int size) {
	for (int i = 0; i < size; i++) {
		arr[i] = rand() % MAX_VALUE;
	}
}

/*
 * Prints an array.
 * arr: array to be printed.
 * size: size of the array.
 */
void printArray(int arr[], int size) {
	for (int i = 0; i < size; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

typedef struct {
	const char *name;
	const char *complexity;
	double time;
} SortResult;

// Comparison function to sort by time ascending
int compareByTime(const void *a, const void *b) {
	const SortResult *sa = (const SortResult *)a;
	const SortResult *sb = (const SortResult *)b;
	if (sa->time < sb->time) return -1;
	else if (sa->time > sb->time) return 1;
	else return 0;
}

/*
 * Main function of the program.
 */
int main(int argc, char *argv[]) {
	int original[SIZE];
	int arr[SIZE];
	clock_t start, end;
	double time_taken;

	srand(time(NULL)); // Initialize random seed
	generateRandomArray(original, SIZE);

	printf("Sorting %d elements...\n\n", SIZE);

	// Array to hold results
	SortResult results[7];

	// Bubble Sort O(n^2)
	memcpy(arr, original, sizeof(original));
	start = clock();
	bubbleSort(arr, SIZE);
	end = clock();
	time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
	results[0] = (SortResult){"Bubble Sort", "O(n^2)", time_taken};

	// Insertion Sort O(n^2)
	memcpy(arr, original, sizeof(original));
	start = clock();
	insertionSort(arr, SIZE);
	end = clock();
	time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
	results[1] = (SortResult){"Insertion Sort", "O(n^2)", time_taken};

	// Selection Sort O(n^2)
	memcpy(arr, original, sizeof(original));
	start = clock();
	selectionSort(arr, SIZE);
	end = clock();
	time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
	results[2] = (SortResult){"Selection Sort", "O(n^2)", time_taken};

	// Quick Sort O(n log n) average
	memcpy(arr, original, sizeof(original));
	start = clock();
	quickSort(arr, 0, SIZE - 1);
	end = clock();
	time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
	results[3] = (SortResult){"Quick Sort", "O(n log n)", time_taken};

	// Heap Sort O(n log n)
	memcpy(arr, original, sizeof(original));
	start = clock();
	heapSort(arr, SIZE);
	end = clock();
	time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
	results[4] = (SortResult){"Heap Sort", "O(n log n)", time_taken};

	// Merge Sort O(n log n)
	memcpy(arr, original, sizeof(original));
	start = clock();
	mergeSort(arr, 0, SIZE - 1);
	end = clock();
	time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
	results[5] = (SortResult){"Merge Sort", "O(n log n)", time_taken};

	// Bucket Sort O(n + k)
	memcpy(arr, original, sizeof(original));
	start = clock();
	bucketSort(arr, SIZE);
	end = clock();
	time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
	results[6] = (SortResult){"Bucket Sort", "O(n + k)", time_taken};

	// Sort results by execution time
	qsort(results, 7, sizeof(SortResult), compareByTime);

	// Print sorted results
	printf("Execution time from fastest to slowest:\n");
	for (int i = 0; i < 7; i++) {
		printf("%s (%s): %.6f seconds\n", results[i].name, results[i].complexity, results[i].time);
	}

	return 0;
}
