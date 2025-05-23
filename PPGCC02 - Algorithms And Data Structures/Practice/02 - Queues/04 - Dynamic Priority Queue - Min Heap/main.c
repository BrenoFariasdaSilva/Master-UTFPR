/*
 * Description: Dynamic Priority Queue - Min Heap.
 * Author: Breno Farias da Silva.
 * Date: 22/05/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf, scanf
#include <stdlib.h> // malloc, realloc, free
#include <stdbool.h> // bool type
#include <limits.h> // INT_MIN
#include <math.h> // log function

/*
 * Structure representing the Min or Max Heap Priority Queue.
 * It stores the capacity, current size, array of elements,
 * and a flag indicating if it is a min heap (true) or max heap (false).
 */
typedef struct {
	int *data; // Array to hold heap elements.
	int size; // Current number of elements in the heap.
	int capacity; // Allocated capacity of the heap.
	bool is_min; // true: MinHeap, false: MaxHeap
} Heap;

// Function declarations
Heap* createHeap(const int capacity);
void swap(int *a, int *b);
void resizeHeap(Heap *heap);
void heapifyUp(Heap *heap, int index);
void heapifyDown(Heap *heap, const int index);
void insert(Heap *heap, const int value);
void insertVector(Heap *heap, const int *values, const int count);
int peekTop(const Heap *heap);
int extractRoot(Heap *heap);
void freeHeap(Heap *heap);
void invertHeap(Heap *heap);
void printHeap(const Heap *heap);
void printHeapAsTree(const Heap *heap);

// Functions Implementation

/*
 * Function to create a new heap with a given capacity and type.
 * capacity: initial capacity of the heap.
 * is_min: true to create a MinHeap, false for MaxHeap.
 * return: pointer to the newly created heap.
 */
Heap* createHeap(const int capacity) {
	Heap *heap = (Heap *) malloc(sizeof(Heap));
	if (heap == NULL) return NULL; // Memory allocation failed

	heap->data = (int *) malloc(sizeof(int) * capacity);
	if (heap->data == NULL) {
		free(heap);
		return NULL; // Memory allocation failed
	}

	heap->size = 0;
	heap->capacity = capacity;
	heap->is_min = true;
	return heap;
}

/*
 * Function to swap two integer values.
 * a, b: pointers to the integers to be swapped.
 */
void swap(int *a, int *b) {
	if (a == NULL || b == NULL) return; // Check for null pointers

	int temp = *a;
	*a = *b;
	*b = temp;
}

/*
 * Function to double the capacity of the heap.
 * heap: pointer to the heap to be resized.
 */
void resizeHeap(Heap *heap) {
	if (heap == NULL) return; // Check for null pointer

	heap->capacity *= 2;
	heap->data = (int *) realloc(heap->data, sizeof(int) * heap->capacity);
}

/*
 * Function to maintain the heap property from bottom to top.
 * heap: pointer to the heap.
 * index: index of the element to heapify up.
 */
void heapifyUp(Heap *heap, int index) {
	if (heap == NULL || index < 0 || index >= heap->size) return; // Check for null pointer and valid index

	while (index > 0) {
		int parent = (index - 1) / 2;
		if ((heap->is_min && heap->data[parent] <= heap->data[index]) ||
			(!heap->is_min && heap->data[parent] >= heap->data[index])) {
			break;
		}
		swap(&heap->data[parent], &heap->data[index]);
		index = parent;
	}
}

/*
 * Function to maintain the heap property from top to bottom.
 * heap: pointer to the heap.
 * index: index of the element to heapify down.
 */
void heapifyDown(Heap *heap, const int index) {
	if (heap == NULL || index < 0 || index >= heap->size) return; // Check for null pointer and valid index

	int selected = index;
	int left = 2 * index + 1;
	int right = 2 * index + 2;

	if (left < heap->size &&
		((heap->is_min && heap->data[left] < heap->data[selected]) ||
		(!heap->is_min && heap->data[left] > heap->data[selected]))) {
		selected = left;
	}

	if (right < heap->size &&
		((heap->is_min && heap->data[right] < heap->data[selected]) ||
		(!heap->is_min && heap->data[right] > heap->data[selected]))) {
		selected = right;
	}

	if (selected != index) {
		swap(&heap->data[index], &heap->data[selected]);
		heapifyDown(heap, selected);
	}
}

/*
 * Function to insert a new value into the heap.
 * heap: pointer to the heap.
 * value: value to be inserted.
 */
void insert(Heap *heap, const int value) {
	if (heap == NULL) return; // Check for null pointer

	if (heap->size == heap->capacity) {
		resizeHeap(heap);
	}
	
	heap->data[heap->size] = value;
	heap->size++;
	heapifyUp(heap, heap->size - 1);
}

/*
 * Function to insert multiple values into the heap from an array.
 * heap: pointer to the heap.
 * values: array of values to be inserted.
 * count: number of values in the array.
 */
void insertVector(Heap *heap, const int *values, const int count) {
	if (heap == NULL || values == NULL || count <= 0) return; // Validate input

	for (int i = 0; i < count; i++) {
		if (heap->size == heap->capacity) {
			resizeHeap(heap);
		}
		heap->data[heap->size] = values[i];
		heap->size++;
		heapifyUp(heap, heap->size - 1);
	}
}

/*
 * Returns the root of the heap without removing it.
 * Returns INT_MIN if the heap is NULL or empty.
 */
int peekTop(const Heap *heap) {
	if (heap == NULL || heap->size == 0) {
		return INT_MIN; // Heap is empty
	}
	return heap->data[0];
}

/*
 * Function to remove and return the root of the heap.
 * heap: pointer to the heap.
 * return: the root value, or -1 if the heap is empty.
 */
int extractRoot(Heap *heap) {
	if (heap == NULL) return -1; // Check for null pointer

	if (heap->size == 0) {
		return -1;
	}

	int root = heap->data[0];
	heap->data[0] = heap->data[heap->size - 1];
	heap->size--;
	heapifyDown(heap, 0);

	return root;
}

/*
 * Function to free the memory used by the heap.
 * heap: pointer to the heap.
 */
void freeHeap(Heap *heap) {
	if (heap == NULL) return; // Check for null pointer

	free(heap->data);
	free(heap);
}

/*
 * Function to invert the heap from MinHeap to MaxHeap or vice versa.
 * heap: pointer to the heap.
 */
void invertHeap(Heap *heap) {
	if (heap == NULL) return; // Check for null pointer

	heap->is_min = !heap->is_min;
	for (int i = (heap->size / 2) - 1; i >= 0; i--) {
		heapifyDown(heap, i);
	}
}

/*
 * Function to print the elements in the heap.
 * heap: pointer to the heap.
 */
void printHeap(const Heap *heap) {
	if (heap == NULL) return; // Check for null pointer

	printf("Heap (%s): ", heap->is_min ? "Min" : "Max");
	for (int i = 0; i < heap->size; i++) {
		printf("%d ", heap->data[i]);
	}
	printf("\n\n");
}

/*
 * Function to print the heap as a tree structure.
 * heap: pointer to the heap.
 */
void printHeapAsTree(const Heap *heap) {
	if (heap == NULL || heap->size == 0) return;

	printf("Heap as Tree (%s):\n", heap->is_min ? "Min" : "Max");

	int level = 0;
	int count = 0;
	int elementsInLevel = 1;

	for (int i = 0; i < heap->size; i++) {
		// Print indent at the start of a new level
		if (count == 0) {
			int indent = (1 << ((int)log2(heap->size))) - level;
			for (int s = 0; s < indent; s++) printf("  ");
		}

		printf("%d ", heap->data[i]);
		count++;

		// If finished printing a level
		if (count == elementsInLevel) {
			printf("\n");
			level++;
			count = 0;
			elementsInLevel <<= 1; // 2^level
		}
	}
	printf("\n\n");
}

/*
 * Main function of the program.
 * argc: number of arguments passed on program call.
 * argv: array with the arguments passed on program call.
 * return: program execution status (0: no errors, otherwise: error code).
 */
int main(int argc, char *argv[]) {
	Heap *heap = createHeap(4); // Start as MinHeap

	insert(heap, 10);
	insert(heap, 5);
	insert(heap, 20);
	insert(heap, 1);
	insert(heap, 8);

	printHeap(heap); // MinHeap order
	// printHeapAsTree(heap); // Print as tree

	printf("Extracted root: %d\n", extractRoot(heap)); // Expected 1
	printHeap(heap);
	printHeapAsTree(heap); // Print as tree

	printf("Inverting from MinHeap to MaxHeap...\n");
	invertHeap(heap); // Convert to MaxHeap
	printHeap(heap);
	printHeapAsTree(heap); // Print as tree

	insert(heap, 25);
	printHeap(heap); // Should be MaxHeap now
	// printHeapAsTree(heap); // Print as tree

	printf("Extracted root: %d\n", extractRoot(heap)); // Expected 25
	printHeap(heap);
	// printHeapAsTree(heap); // Print as tree

	freeHeap(heap);

	// Test with a vector of elements
	int values[] = {15, 30, 25, 5, 10};
	Heap *heap2 = createHeap(4);
	insertVector(heap2, values, 5);
	printHeap(heap2); // Should be MinHeap
	printHeapAsTree(heap2); // Print as tree
	freeHeap(heap2);

	return 0;
}
