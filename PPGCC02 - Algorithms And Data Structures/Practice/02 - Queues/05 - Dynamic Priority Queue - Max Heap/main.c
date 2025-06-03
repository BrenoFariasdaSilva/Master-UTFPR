/*
 * Description: Dynamic Priority Queue - Max Heap.
 * Author: Breno Farias da Silva.
 * Date: 22/05/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf, scanf
#include <stdlib.h> // malloc, realloc, free
#include <stdbool.h> // bool type
#include <limits.h> // INT_MAX
#include <math.h> // log function

/*
 * Structure representing the Max Heap Priority Queue.
 * It stores the capacity, current size, array of elements,
 * and a flag indicating if it is a min heap (true) or max heap (false).
 * For this implementation, is_max is always false.
 */
typedef struct {
	int *data; // Array to hold heap elements.
	int size; // Current number of elements in the heap.
	int capacity; // Allocated capacity of the heap.
	bool is_max; // true: MaxHeap, false: MinHeap
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
int freeHeap(Heap *heap);
void invertHeap(Heap *heap);
void printHeap(const Heap *heap);
void printHeapAsTree(const Heap *heap);

/*
 * Creates a new heap with a given capacity and type.
 * capacity: initial capacity of the heap.
 * is_max: flag indicating MinHeap (true) or MaxHeap (false).
 *         This function will create a MaxHeap regardless.
 * return: pointer to the newly created heap or NULL if memory allocation fails.
 */
Heap* createHeap(const int capacity) {
	Heap *heap = (Heap *) malloc(sizeof(Heap));
	if (heap == NULL) return NULL;

	heap->data = (int *) malloc(sizeof(int) * capacity);
	if (heap->data == NULL) {
		free(heap);
		return NULL;
	}

	heap->size = 0;
	heap->capacity = capacity;
	heap->is_max = true; // force MaxHeap
	return heap;
}

/*
 * Swaps the values of two integers.
 * a: pointer to the first integer.
 * b: pointer to the second integer.
 */
void swap(int *a, int *b) {
	if (a == NULL || b == NULL) return;

	int temp = *a;
	*a = *b;
	*b = temp;
}

/*
 * Doubles the capacity of the heap when it becomes full.
 * heap: pointer to the heap to resize.
 */
void resizeHeap(Heap *heap) {
	if (heap == NULL) return;

	heap->capacity *= 2;
	heap->data = (int *) realloc(heap->data, sizeof(int) * heap->capacity);
}

/*
 * Maintains the max heap property from bottom to top after insertion.
 * heap: pointer to the heap.
 * index: index of the element to heapify up.
 */
void heapifyUp(Heap *heap, int index) {
	if (heap == NULL || index < 0 || index >= heap->size) return;

	while (index > 0) {
		int parent = (index - 1) / 2;
		if (heap->data[parent] >= heap->data[index]) {
			break;
		}
		swap(&heap->data[parent], &heap->data[index]);
		index = parent;
	}
}

/*
 * Maintains the max heap property from top to bottom after extraction.
 * heap: pointer to the heap.
 * index: index of the element to heapify down.
 */
void heapifyDown(Heap *heap, const int index) {
	if (heap == NULL || index < 0 || index >= heap->size) return;

	int selected = index;
	int left = 2 * index + 1;
	int right = 2 * index + 2;

	if (left < heap->size) {
		if ((heap->is_max && heap->data[left] > heap->data[selected]) ||
			(!heap->is_max && heap->data[left] < heap->data[selected])) {
			selected = left;
		}
	}

	if (right < heap->size) {
		if ((heap->is_max && heap->data[right] > heap->data[selected]) ||
			(!heap->is_max && heap->data[right] < heap->data[selected])) {
			selected = right;
		}
	}

	if (selected != index) {
		swap(&heap->data[index], &heap->data[selected]);
		heapifyDown(heap, selected);
	}
}

/*
 * Inserts a new value into the max heap.
 * heap: pointer to the heap.
 * value: value to be inserted.
 */
void insert(Heap *heap, const int value) {
	if (heap == NULL) return;

	if (heap->size == heap->capacity) {
		resizeHeap(heap);
	}
	
	heap->data[heap->size] = value;
	heap->size++;
	heapifyUp(heap, heap->size - 1);
}

/*
 * Inserts multiple values into the max heap from an array.
 * heap: pointer to the heap.
 * values: array of values to be inserted.
 * count: number of values in the array.
 */
void insertVector(Heap *heap, const int *values, const int count) {
	if (heap == NULL || values == NULL || count <= 0) return;

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
 * Returns INT_MAX if the heap is NULL or empty.
 */
int peekTop(const Heap *heap) {
	if (heap == NULL || heap->size == 0) {
		return INT_MAX; // Heap is empty
	}
	return heap->data[0];
}

/*
 * Removes and returns the root (maximum) value from the heap.
 * heap: pointer to the heap.
 * return: the root value, or -1 if the heap is empty or NULL.
 */
int extractRoot(Heap *heap) {
	if (heap == NULL || heap->size == 0) {
		return -1;
	}

	int root = heap->data[0];
	heap->data[0] = heap->data[heap->size - 1];
	heap->size--;
	heapifyDown(heap, 0);

	return root;
}

/*
 * Frees the memory used by the heap.
 * heap: pointer to the heap.
 * return: 1 on success, -1 if heap is NULL.
 */
int freeHeap(Heap *heap) {
	if (heap == NULL) return -1;

	free(heap->data);
	free(heap);
	return 1;
}

/*
 * Inverts the heap from max to min or vice versa.
 * heap: pointer to the heap.
 */
void invertHeap(Heap *heap) {
	if (heap == NULL) return;

	heap->is_max = !heap->is_max;

	for (int i = (heap->size / 2) - 1; i >= 0; i--) {
		heapifyDown(heap, i);
	}
}

/*
 * Prints the elements in the heap in array form.
 * heap: pointer to the heap.
 */
void printHeap(const Heap *heap) {
	if (heap == NULL) return;

	printf("Heap as Tree (%s):\n", heap->is_max ? "Max" : "Min");

	for (int i = 0; i < heap->size; i++) {
		printf("%d ", heap->data[i]);
	}
	printf("\n\n");
}

/*
 * Prints the heap as a tree structure for visualization.
 * heap: pointer to the heap.
 */
void printHeapAsTree(const Heap *heap) {
	if (heap == NULL || heap->size == 0) return;

	printf("Heap as Tree (%s):\n", heap->is_max ? "Max" : "Min");

	int level = 0;
	int count = 0;
	int elementsInLevel = 1;

	for (int i = 0; i < heap->size; i++) {
		if (count == 0) {
			int indent = (1 << ((int)log2(heap->size))) - level;
			for (int s = 0; s < indent; s++) printf("  ");
		}

		printf("%d ", heap->data[i]);
		count++;

		if (count == elementsInLevel) {
			printf("\n");
			level++;
			count = 0;
			elementsInLevel <<= 1;
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
	Heap *heap = createHeap(4); // Create MaxHeap

	insert(heap, 10);
	insert(heap, 5);
	insert(heap, 20);
	insert(heap, 1);
	insert(heap, 8);

	printHeap(heap); // MaxHeap order
	printHeapAsTree(heap); // Print as tree

	printf("Extracted root: %d\n", extractRoot(heap)); // Expected 20
	printHeap(heap);
	printHeapAsTree(heap);

	printf("Inverting from MaxHeap to MinHeap...\n");
	invertHeap(heap); // Convert to MinHeap
	printHeap(heap);
	printHeapAsTree(heap); // Print as tree

	insert(heap, 25);
	printHeap(heap);
	printHeapAsTree(heap);

	printf("Extracted root: %d\n", extractRoot(heap)); // Expected 25
	printHeap(heap);

	freeHeap(heap);

	// Test with a vector of elements
	int values[] = {15, 30, 25, 5, 10};
	Heap *heap2 = createHeap(4);
	insertVector(heap2, values, 5);
	printHeap(heap2);
	printHeapAsTree(heap2);
	freeHeap(heap2);

	return 0;
}
