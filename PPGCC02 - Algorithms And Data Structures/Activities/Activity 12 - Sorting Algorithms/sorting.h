/*
 * Description: Header file containing the function prototypes for various sorting algorithms.
 * Author: Breno Farias da Silva.
 * Date: 14/06/2025.
 */

#ifndef _SORTING_H_
#define _SORTING_H_

/*
 * Sorts an array using the Bubble Sort algorithm.
 * arr: array to be sorted.
 * size: size of the array.
 */
void bubbleSort(int arr[], int size);

/*
 * Sorts an array using the Insertion Sort algorithm.
 * arr: array to be sorted.
 * size: size of the array.
 */
void insertionSort(int arr[], int size);

/*
 * Sorts an array using the Selection Sort algorithm.
 * arr: array to be sorted.
 * size: size of the array.
 */
void selectionSort(int arr[], int size);

/*
 * Sorts an array using the Quick Sort algorithm.
 * arr: array to be sorted.
 * low: starting index.
 * high: ending index.
 */
void quickSort(int arr[], int low, int high);

/*
 * Sorts an array using the Heap Sort algorithm.
 * arr: array to be sorted.
 * size: size of the array.
 */
void heapSort(int arr[], int size);

/*
 * Sorts an array using the Merge Sort algorithm.
 * arr: array to be sorted.
 * left: starting index.
 * right: ending index.
 */
void mergeSort(int arr[], int left, int right);

/*
 * Sorts an array using the Bucket Sort algorithm.
 * arr: array to be sorted.
 * size: size of the array.
 */
void bucketSort(int arr[], int size);

#endif
