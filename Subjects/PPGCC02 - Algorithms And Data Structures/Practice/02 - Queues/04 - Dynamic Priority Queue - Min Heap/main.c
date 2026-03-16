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

#define ElementType int // Define a macro for the element type in the Heap.

/*
 * Structure representing the Min Heap Priority Queue.
 * data: Array to hold heap elements.
 * size: Current number of elements in the heap.
 * quantity: Allocated capacity of the heap.
 * is_min: true for MinHeap, false for MaxHeap.
 */
typedef struct {
	ElementType *data; // Array to hold heap elements.
	int size; // Current allocated size of the heap.
	int quantity; // Current number of elements in the heap.
	bool is_min; // true: MinHeap, false: MaxHeap
} Heap;

// Function declarations
Heap* create_heap(const int size);
void swap(ElementType *a, ElementType *b);
void resize_heap(Heap *heap);
void heapify_up_iteractive(Heap *heap, int index);
void heapify_up_recursive(Heap *heap, int index);
void heapify_down_iteractive(Heap *heap, int index);
void heapify_down_recursive(Heap *heap, const int index);
void insert(Heap *heap, const ElementType value);
void insert_vector(Heap *heap, const ElementType *values, const int count);
ElementType peek_top(const Heap *heap);
ElementType extract_root(Heap *heap);
int free_heap(Heap *heap);
void invert_heap(Heap *heap);
void print_heap(const Heap *heap);
void print_heap_as_tree(const Heap *heap);

// Functions Implementation

/*
 * Function to create a new heap with a given size and type.
 * size: initial size of the heap.
 * is_min: true to create a MinHeap, false for MaxHeap.
 * return: pointer to the newly created heap.
 */
Heap* create_heap(const int size) {
	Heap *heap = (Heap *) malloc(sizeof(Heap));
	if (!heap) return NULL; // Memory allocation failed

	heap->data = (int *) malloc(sizeof(int) * size);
	if (!heap->data) {
		free(heap);
		return NULL; // Memory allocation failed
	}

	heap->size = size;
	heap->quantity = 0; // Initially, the heap is empty
	heap->is_min = true;
	return heap;
}

/*
 * Function to swap two integer values.
 * a, b: pointers to the integers to be swapped.
 */
void swap(ElementType *a, ElementType *b) {
	if (!a || !b) return; // Check for null pointers

	ElementType temp = *a;
	*a = *b;
	*b = temp;
}

/*
 * Function to double the capacity of the heap.
 * heap: pointer to the heap to be resized.
 */
void resize_heap(Heap *heap) {
	if (!heap) return; // Check for null pointer

	heap->size *= 2; // Double the size
	heap->data = (ElementType *) realloc(heap->data, sizeof(ElementType) * heap->size);
}

/*
 * Function to maintain the heap property from bottom to top in a iteractive way.
 * heap: pointer to the heap.
 * index: index of the element to heapify up.
 */
void heapify_up_iteractive(Heap *heap, int index) {
	if (!heap || index < 0 || index >= heap->size) return; // Check for null pointer and valid index

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
 * Function to maintain the heap property from bottom to top in a recursive way.
 * heap: pointer to the heap.
 * index: index of the element to heapify up.
 */
void heapify_up_recursive(Heap *heap, int index) {
	if (!heap || index < 0 || index >= heap->size) return; // Check for null pointer and valid index
	
	int parent = (index - 1) / 2;
	if (index > 0 && ((heap->is_min && heap->data[parent] > heap->data[index]) ||
		(!heap->is_min && heap->data[parent] < heap->data[index]))) {
		swap(&heap->data[parent], &heap->data[index]);
		heapify_up_recursive(heap, parent);
	}
}

/*
 * Function to maintain the heap property from top to bottom in a iteractive way.
 * heap: pointer to the heap.
 * index: index of the element to heapify down.
 */
void heapify_down_iteractive(Heap *heap, int index) {
	if (!heap || index < 0 || index >= heap->size) return; // Check for null pointer and valid index
	
	while (true) {
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

		if (selected == index) break; // If no swap needed, exit loop

		swap(&heap->data[index], &heap->data[selected]);
		index = selected;
	}
}

/*
 * Function to maintain the heap property from top to bottom in a recursive way.
 * heap: pointer to the heap.
 * index: index of the element to heapify down.
 */
void heapify_down_recursive(Heap *heap, const int index) {
	if (!heap || index < 0 || index >= heap->size) return; // Check for null pointer and valid index

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
		heapify_down_recursive(heap, selected);
	}
}

/*
 * Function to insert a new value into the heap.
 * heap: pointer to the heap.
 * value: value to be inserted.
 */
void insert(Heap *heap, const ElementType value) {
	if (!heap) return; // Check for null pointer

	if (heap->quantity == heap->size) {
		resize_heap(heap);
	}

	heap->data[heap->quantity] = value;
	heap->quantity++;
	heapify_up_iteractive(heap, heap->quantity - 1);
}

/*
 * Function to insert multiple values into the heap from an array.
 * heap: pointer to the heap.
 * values: array of values to be inserted.
 * count: number of values in the array.
 */
void insert_vector(Heap *heap, const ElementType *values, const int count) {
	if (!heap || !values || count <= 0) return; // Validate input

	for (int i = 0; i < count; i++) {
		if (heap->quantity == heap->size) {
			resize_heap(heap);
		}
		heap->data[heap->quantity] = values[i];
		heap->quantity++;
		heapify_up_iteractive(heap, heap->quantity - 1);
	}
}

/*
 * Returns the root of the heap without removing it.
 * Returns INT_MIN if the heap is NULL or empty.
 */
ElementType peek_top(const Heap *heap) {
	if (!heap || heap->quantity == 0) {
		return INT_MIN; // Heap is empty
	}
	return heap->data[0];
}

/*
 * Function to remove and return the root of the heap.
 * heap: pointer to the heap.
 * return: the root value, or -1 if the heap is empty.
 */
ElementType extract_root(Heap *heap) {
	if (!heap) return -1; // Check for null pointer

	if (heap->quantity == 0) {
		return -1;
	}

	ElementType root = heap->data[0];
	heap->data[0] = heap->data[heap->quantity - 1];
	heap->quantity--;
	heapify_down_recursive(heap, 0);

	return root;
}

/*
 * Function to free the memory used by the heap.
 * heap: pointer to the heap.
 * return: 1 on success, -1 if heap is NULL.
 */
int free_heap(Heap *heap) {
	if (!heap) return -1; // Check for null pointer

	free(heap->data);
	free(heap);
	return 1; // Return 0 to indicate success
}

/*
 * Function to invert the heap from MinHeap to MaxHeap or vice versa.
 * heap: pointer to the heap.
 */
void invert_heap(Heap *heap) {
	if (!heap) return; // Check for null pointer

	heap->is_min = !heap->is_min;
	for (int i = (heap->quantity / 2) - 1; i >= 0; i--) {
		heapify_down_recursive(heap, i);
	}
}

/*
 * Function to print the elements in the heap.
 * heap: pointer to the heap.
 */
void print_heap(const Heap *heap) {
	if (!heap) return; // Check for null pointer

	printf("Heap (%s): ", heap->is_min ? "Min" : "Max");
	for (int i = 0; i < heap->quantity; i++) {
		printf("%d ", heap->data[i]);
	}
	printf("\n\n");
}

/*
 * Function to print the heap as a tree structure.
 * heap: pointer to the heap.
 */
void print_heap_as_tree(const Heap *heap) {
	if (!heap || heap->quantity == 0) return;

	printf("Heap as Tree (%s):\n", heap->is_min ? "Min" : "Max");

	int level = 0;
	int count = 0;
	int elementsInLevel = 1;

	for (int i = 0; i < heap->quantity; i++) {
		// Print indent at the start of a new level
		if (count == 0) {
			int indent = (1 << ((int)log2(heap->quantity))) - level;
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
	Heap *heap = create_heap(4); // Start as MinHeap

	insert(heap, 10);
	insert(heap, 5);
	insert(heap, 20);
	insert(heap, 1);
	insert(heap, 8);

	print_heap(heap); // MinHeap order
	// print_heap_as_tree(heap); // Print as tree

	printf("Extracted root: %d\n", extract_root(heap)); // Expected 1
	print_heap(heap);
	print_heap_as_tree(heap); // Print as tree

	printf("Inverting from MinHeap to MaxHeap...\n");
	invert_heap(heap); // Convert to MaxHeap
	print_heap(heap);
	print_heap_as_tree(heap); // Print as tree

	insert(heap, 25);
	print_heap(heap); // Should be MaxHeap now
	// print_heap_as_tree(heap); // Print as tree

	printf("Extracted root: %d\n", extract_root(heap)); // Expected 25
	print_heap(heap);
	// print_heap_as_tree(heap); // Print as tree

	free_heap(heap);

	// Test with a vector of elements
	int values[] = {15, 30, 25, 5, 10};
	Heap *heap2 = create_heap(4);
	insert_vector(heap2, values, 5);
	print_heap(heap2); // Should be MinHeap
	print_heap_as_tree(heap2); // Print as tree
	free_heap(heap2);

	return 0;
}
