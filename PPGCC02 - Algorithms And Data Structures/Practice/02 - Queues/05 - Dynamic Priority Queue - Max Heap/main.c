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

#define ElementType int // Define a macro for the element type in the Heap.

/*
 * Structure representing the Max Heap Priority Queue.
 * data: Array to hold heap elements.
 * size: Current number of elements in the heap.
 * quantity: Allocated capacity of the heap.
 * is_max: true for MaxHeap, false for MinHeap.
 */
typedef struct {
	ElementType *data; // Array to hold heap elements.
	int size; // Current allocated size of the heap.
	int quantity; // Current number of elements in the heap.
	bool is_max; // true: MaxHeap, false: MinHeap.
} Heap;

// Function declarations
Heap* create_heap(const int size);
void swap(ElementType *a, ElementType *b);
void resize_heap(Heap *heap);
void heapify_up_iteractive(Heap *heap, int index);
void heapify_down_recursive(Heap *heap, const int index);
void insert(Heap *heap, const ElementType value);
void insert_vector(Heap *heap, const ElementType *values, const int count);
ElementType peek_top(const Heap *heap);
ElementType extract_root(Heap *heap);
int free_heap(Heap *heap);
void invert_heap(Heap *heap);
void print_heap(const Heap *heap);
void print_heap_as_tree(const Heap *heap);

/*
 * Creates a new heap with a given capacity and type.
 * size: initial size of the heap.
 * is_max: flag indicating if the heap is a MaxHeap (true) or MinHeap (false).
 * return: pointer to the newly created heap or NULL if memory allocation fails.
 */
Heap* create_heap(const int size) {
	Heap *heap = (Heap *) malloc(sizeof(Heap));
	if (!heap) return NULL;

	heap->data = (ElementType *) malloc(sizeof(ElementType) * size);
	if (!heap->data) {
		free(heap);
		return NULL;
	}

	heap->size = size;
	heap->quantity = 0;
	heap->is_max = true;
	return heap;
}

/*
 * Swaps the values of two integers.
 * a: pointer to the first integer.
 * b: pointer to the second integer.
 */
void swap(ElementType *a, ElementType *b) {
	if (!a || !b) return;

	ElementType temp = *a;
	*a = *b;
	*b = temp;
}

/*
 * Doubles the capacity of the heap when it becomes full.
 * heap: pointer to the heap to resize.
 */
void resize_heap(Heap *heap) {
	if (!heap) return;

	heap->size *= 2;
	heap->data = (ElementType *) realloc(heap->data, sizeof(ElementType) * heap->size);
}

/*
 * Maintains the max heap property from bottom to top after insertion in a iterative way.
 * heap: pointer to the heap.
 * index: index of the element to heapify up.
 */
void heapify_up_iteractive(Heap *heap, int index) {
	if (!heap || index < 0 || index >= heap->size) return;

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
 * Maintains the max heap property from bottom to top after insertion in a recursive way.
 * heap: pointer to the heap.
 * index: index of the element to heapify up.
 */
void heapify_up_recursive(Heap *heap, int index) {
	if (!heap || index < 0 || index >= heap->size) return;

	int parent = (index - 1) / 2;
	if (index > 0 && heap->data[parent] < heap->data[index]) {
		swap(&heap->data[parent], &heap->data[index]);
		heapify_up_recursive(heap, parent);
	}
}

/*
 * Maintains the max heap property from top to bottom in a recursive way.
 * heap: pointer to the heap.
 * index: index of the element to heapify down.
 */
void heapify_down_iteractive(Heap *heap, int index) {
	if (!heap || index < 0 || index >= heap->size) return;

	while (true) {
		int selected = index;
		int left = 2 * index + 1;
		int right = 2 * index + 2;

		if (left < heap->size &&
			((heap->is_max && heap->data[left] > heap->data[selected]) ||
			(!heap->is_max && heap->data[left] < heap->data[selected]))) {
			selected = left;
		}

		if (right < heap->size &&
			((heap->is_max && heap->data[right] > heap->data[selected]) ||
			(!heap->is_max && heap->data[right] < heap->data[selected]))) {
			selected = right;
		}

		if (selected == index) break;

		swap(&heap->data[index], &heap->data[selected]);
		index = selected;
	}
}

/*
 * Maintains the max heap property from top to bottom after extraction.
 * heap: pointer to the heap.
 * index: index of the element to heapify down.
 */
void heapify_down_recursive(Heap *heap, const int index) {
	if (!heap || index < 0 || index >= heap->size) return;

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
		heapify_down_recursive(heap, selected);
	}
}

/*
 * Inserts a new value into the max heap.
 * heap: pointer to the heap.
 * value: value to be inserted.
 */
void insert(Heap *heap, const int value) {
	if (!heap) return;

	if (heap->quantity == heap->size) {
		resize_heap(heap);
	}

	heap->data[heap->quantity] = value;
	heap->quantity++;
	heapify_up_iteractive(heap, heap->quantity - 1);
}

/*
 * Inserts multiple values into the max heap from an array.
 * heap: pointer to the heap.
 * values: array of values to be inserted.
 * count: number of values in the array.
 */
void insert_vector(Heap *heap, const int *values, const int count) {
	if (!heap || !values || count <= 0) return;

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
 * Returns INT_MAX if the heap is NULL or empty.
 */
ElementType peek_top(const Heap *heap) {
	if (!heap || heap->quantity == 0) {
		return INT_MAX; // Heap is empty
	}
	return heap->data[0];
}

/*
 * Removes and returns the root (maximum) value from the heap.
 * heap: pointer to the heap.
 * return: the root value, or -1 if the heap is empty or NULL.
 */
ElementType extract_root(Heap *heap) {
	if (!heap || heap->quantity == 0) {
		return -1;
	}

	ElementType root = heap->data[0];
	heap->data[0] = heap->data[heap->quantity - 1];
	heap->quantity--;
	heapify_down_recursive(heap, 0);

	return root;
}

/*
 * Frees the memory used by the heap.
 * heap: pointer to the heap.
 * return: 1 on success, -1 if heap is NULL.
 */
int free_heap(Heap *heap) {
	if (!heap) return -1;

	free(heap->data);
	free(heap);
	return 1;
}

/*
 * Inverts the heap from max to min or vice versa.
 * heap: pointer to the heap.
 */
void invert_heap(Heap *heap) {
	if (!heap) return;

	heap->is_max = !heap->is_max;

	for (int i = (heap->size / 2) - 1; i >= 0; i--) {
		heapify_down_recursive(heap, i);
	}
}

/*
 * Prints the elements in the heap in array form.
 * heap: pointer to the heap.
 */
void print_heap(const Heap *heap) {
	if (!heap) return;

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
void print_heap_as_tree(const Heap *heap) {
	if (!heap || heap->size == 0) return;

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
	Heap *heap = create_heap(4); // Create MaxHeap

	insert(heap, 10);
	insert(heap, 5);
	insert(heap, 20);
	insert(heap, 1);
	insert(heap, 8);

	print_heap(heap); // MaxHeap order
	print_heap_as_tree(heap); // Print as tree

	printf("Extracted root: %d\n", extract_root(heap)); // Expected 20
	print_heap(heap);
	print_heap_as_tree(heap);

	printf("Inverting from MaxHeap to MinHeap...\n");
	invert_heap(heap); // Convert to MinHeap
	print_heap(heap);
	print_heap_as_tree(heap); // Print as tree

	insert(heap, 25);
	print_heap(heap);
	print_heap_as_tree(heap);

	printf("Extracted root: %d\n", extract_root(heap)); // Expected 25
	print_heap(heap);

	free_heap(heap);

	// Test with a vector of elements
	int values[] = {15, 30, 25, 5, 10};
	Heap *heap2 = create_heap(4);
	insert_vector(heap2, values, 5);
	print_heap(heap2);
	print_heap_as_tree(heap2);
	free_heap(heap2);

	return 0;
}
