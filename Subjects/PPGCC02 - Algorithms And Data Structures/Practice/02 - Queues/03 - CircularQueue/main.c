/*
 * Description: This program shows an implementation of a Circular Queue using Dynamic Memory Allocation.
 * Author: Breno Farias da Silva.
 * Date: 22/05/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf, scanf
#include <stdlib.h> // malloc, free
#include <stdbool.h> // 'bool', 'true', and 'false' keywords

#define ElementType int // Define a macro for the element type in the Circular Queue.

/*
 * Structure to represent a Circular Queue.
 * data: pointer to the dynamically allocated array for queue elements.
 * front: index of the front element in the queue.
 * rear: index of the last element in the queue.
 * size: maximum number of elements the queue can hold (capacity).
 * quantity: current number of elements in the queue.
 */
typedef struct {
	ElementType *data; // Pointer to dynamically allocated array for queue elements
	int front; // Index of the front element
	int rear; // Index of the last element
	int size; // Maximum number of elements the queue can hold (capacity)
	int quantity; // Current number of elements in the queue
} CircularQueue;

// Function declarations
CircularQueue* create_circular_queue(const int size);
int initialize_circular_queue(CircularQueue *queue, const int size);
int enqueue(CircularQueue *queue, const ElementType add_element);
int dequeue(CircularQueue *queue, ElementType *removed_element);
int peek_front(const CircularQueue *queue, ElementType *front_element);
int clone_circular_queue(const CircularQueue *source, CircularQueue *destination);
int invert_circular_queue(CircularQueue *queue);
int search_element(const CircularQueue *queue, const ElementType value);
int are_circular_queues_equal(const CircularQueue *q1, const CircularQueue *q2);
int insert_vector(CircularQueue *queue, const ElementType *array, const int size);
bool is_valid(const CircularQueue *queue);
bool is_empty(const CircularQueue *queue);
int print_circular_queue(const CircularQueue *queue);
int print_circular_queue_attributes(const CircularQueue *queue);
int free_circular_queue(CircularQueue **queue);

/*
 * Function to create a new CircularQueue.
 * size: size of the internal array.
 * return: pointer to the newly allocated CircularQueue, or NULL on failure.
 */
CircularQueue* create_circular_queue(const int size) {
	CircularQueue *queue = (CircularQueue *) malloc(sizeof(CircularQueue));
	if (!queue) return NULL;

	if (initialize_circular_queue(queue, size) == -1) {
		free(queue);
		return NULL;
	}

	return queue;
}

/*
 * Function to initialize a CircularQueue instance.
 * queue: pointer to the CircularQueue to initialize.
 * size: size of the internal array.
 * return: status (1: success, -1: error).
 */
int initialize_circular_queue(CircularQueue *queue, const int size) {
	if (!queue || size <= 0) return -1;

	queue->data = (ElementType*) malloc(sizeof(ElementType) * size);
	if (!queue->data) return -1;

	queue->front = 0;
	queue->rear = -1;
	queue->size = size;
	queue->quantity = 0;

	return 1;
}

/*
 * Function to add an element to the rear of the CircularQueue.
 * queue: pointer to the CircularQueue.
 * add_element: element to add.
 * return: status (1: success, -1: queue full or error).
 */
int enqueue(CircularQueue *queue, const ElementType add_element) {
	if (!queue || queue->quantity == queue->size) return -1;

	queue->rear = (queue->rear + 1) % queue->size;
	queue->data[queue->rear] = add_element;
	queue->quantity++;

	return 1;
}

/*
 * Function to remove an element from the front of the CircularQueue.
 * queue: pointer to the CircularQueue.
 * removed_element: pointer to store the removed value.
 * return: status (1: success, -1: queue empty or error).
 */
int dequeue(CircularQueue *queue, ElementType *removed_element) {
	if (!queue || queue->size == 0 || !removed_element) return -1;

	*removed_element = queue->data[queue->front];

	queue->front = (queue->front + 1) % queue->size;
	queue->quantity--;

	return 1;
}

/*
 * Function to get the element at the front of the CircularQueue without removing it.
 * queue: pointer to the CircularQueue.
 * front_element: pointer to store the front element.
 * return: status (1: success, -1: queue empty or error).
 */
int peek_front(const CircularQueue *queue, ElementType *front_element) {
	if (!queue || queue->size == 0 || !front_element) return -1;

	*front_element = queue->data[queue->front];
	return 1;
}

/*
 * Function to clone one CircularQueue into another.
 * source: pointer to the source queue.
 * destination: pointer to the destination queue (must be initialized).
 * return: status (1: success, -1: error).
 */
int clone_circular_queue(const CircularQueue *source, CircularQueue *destination) {
	if (!source || !destination) return -1;
	if (destination->size < source->size) return -1;

	destination->front = 0;
	destination->rear = source->size - 1;
	destination->size = source->size;

	for (int i = 0; i < source->size; i++) {
		int index = (source->front + i) % source->size;
		destination->data[i] = source->data[index];
	}

	return 1;
}

/*
 * Function to invert the elements in the CircularQueue.
 * queue: pointer to the CircularQueue.
 * return: status (1: success, -1: error).
 */
int invert_circular_queue(CircularQueue *queue) {
	if (!queue || queue->size <= 1) return -1;

	int left = 0;
	int right = queue->size - 1;

	while (left < right) {
		int leftIndex = (queue->front + left) % queue->size;
		int rightIndex = (queue->front + right) % queue->size;

		ElementType temp = queue->data[leftIndex];
		queue->data[leftIndex] = queue->data[rightIndex];
		queue->data[rightIndex] = temp;

		left++;
		right--;
	}

	return 1;
}

/*
 * Function to search for an element in the CircularQueue.
 * queue: pointer to the CircularQueue.
 * value: element to search.
 * return: index of element (0-based relative to front), or -1 if not found.
 */
int search_element(const CircularQueue *queue, const ElementType value) {
	if (!queue || queue->size == 0) return -1;

	for (int i = 0; i < queue->size; i++) {
		int index = (queue->front + i) % queue->size;
		if (queue->data[index] == value) {
			return i;
		}
	}
	return -1;
}

/*
 * Function to check if two CircularQueues are equal (same size and elements in order).
 * q1, q2: pointers to the CircularQueues.
 * return: 1 if equal, 0 if not equal, -1 on error.
 */
int are_circular_queues_equal(const CircularQueue *q1, const CircularQueue *q2) {
	if (!q1 || !q2) return -1;
	if (q1->size != q2->size) return 0;

	for (int i = 0; i < q1->size; i++) {
		int idx1 = (q1->front + i) % q1->size;
		int idx2 = (q2->front + i) % q2->size;

		if (q1->data[idx1] != q2->data[idx2]) {
			return 0;
		}
	}
	return 1;
}

/*
 * Function to insert an array of elements into the CircularQueue.
 * queue: pointer to the CircularQueue.
 * array: pointer to the array of elements.
 * size: number of elements to insert.
 * return: number of elements actually inserted, or -1 on error.
 */
int insert_vector(CircularQueue *queue, const ElementType *array, const int size) {
	if (!queue || !array || size <= 0) return -1;

	int inserted = 0;
	for (int i = 0; i < size; i++) {
		if (enqueue(queue, array[i]) == -1) {
			break; // Queue full
		}
		inserted++;
	}
	return inserted;
}

/*
 * Function to validate the CircularQueue structure.
 * queue: pointer to the CircularQueue.
 * return: true if valid, false otherwise.
 */
bool is_valid(const CircularQueue *queue) {
	if (!queue) return false;
	if (!queue->data) return false;
	if (queue->size <= 0) return false;
	if (queue->size < 0 || queue->quantity > queue->size) return false;
	if (queue->front < 0 || queue->front >= queue->size) return false;
	if (queue->rear < -1 || queue->rear >= queue->size) return false;
	return true;
}

/*
 * Function to check if the CircularQueue is empty.
 * queue: pointer to the CircularQueue.
 * return: true if empty, false otherwise.
 */
bool is_empty(const CircularQueue *queue) {
	return (!queue || queue->quantity == 0);
}

/*
 * Function to print the elements in the CircularQueue.
 * queue: pointer to the CircularQueue.
 * return: number of elements printed, or -1 on error.
 */
int print_circular_queue(const CircularQueue *queue) {
	if (!queue || queue->quantity == 0) {
		printf("Queue is empty.\n");
		return -1;
	}

	printf("CircularQueue elements: ");
	for (int i = 0; i < queue->size; i++) {
		int index = (queue->front + i) % queue->size;
		printf("%d ", queue->data[index]);
	}
	printf("\n");
	return queue->size;
}

/*
 * Function to print the attributes of the CircularQueue.
 * queue: pointer to the CircularQueue.
 * return: 1 on success, -1 on error.
 */
int print_circular_queue_attributes(const CircularQueue *queue) {
	if (!queue) return -1;

	printf("Queue size: %d\n", queue->size);
	printf("Queue quantity: %d\n", queue->quantity);
	printf("Queue front index: %d\n", queue->front);
	printf("Queue rear index: %d\n", queue->rear);

	return 1;
}

/*
 * Function to free the CircularQueue and its resources.
 * queue: double pointer to the CircularQueue.
 * return: 1 on success, -1 on error.
 */
int free_circular_queue(CircularQueue **queue) {
	if (!queue || !(*queue)) return -1;

	free((*queue)->data);
	(*queue)->data = NULL;

	free(*queue);
	*queue = NULL;
	return 1;
}

/*
 * Main function to demonstrate and test CircularQueue operations.
 * argc: argument count (not used).
 * argv: argument vector (not used).
 * return: exit status (0 on success, 1 on failure).
 */
int main(int argc, char *argv[]) {
	printf("Welcome to the Dynamic Circular Queue Demonstration!\n\n");

	int size = 5;

	// Create a new circular queue
	CircularQueue *queue = create_circular_queue(size);
	if (!queue) {
		printf("Failed to create queue.\n");
		return 1;
	}

	// Print initial attributes
	printf("Initial queue attributes:\n");
	print_circular_queue_attributes(queue);

	// Enqueue elements
	printf("\nEnqueueing elements: 10, 20, 30\n");
	enqueue(queue, 10);
	enqueue(queue, 20);
	enqueue(queue, 30);

	print_circular_queue(queue);
	print_circular_queue_attributes(queue);

	// Peek front element
	ElementType front_val;
	if (peek_front(queue, &front_val) == 1) {
		printf("Front element (peek): %d\n", front_val);
	} else {
		printf("Failed to peek front element.\n");
	}

	// Dequeue one element
	printf("\nDequeuing one element...\n");
	ElementType removed;
	if (dequeue(queue, &removed) == 1) {
		printf("Removed element: %d\n", removed);
	} else {
		printf("Failed to dequeue element.\n");
	}

	print_circular_queue(queue);

	// Insert multiple elements from vector
	ElementType vals[] = {40, 50, 60};
	printf("\nInserting vector {40, 50, 60} into queue...\n");
	int inserted = insert_vector(queue, vals, 3);
	printf("Inserted %d elements.\n", inserted);

	print_circular_queue(queue);
	print_circular_queue_attributes(queue);

	// Search for an element
	printf("\nSearching for element 50 in queue...\n");
	int pos = search_element(queue, 50);
	if (pos != -1) {
		printf("Element 50 found at position (relative to front): %d\n", pos);
	} else {
		printf("Element 50 not found in queue.\n");
	}

	// Test if queue is empty
	printf("\nIs the queue empty? %s\n", is_empty(queue) ? "Yes" : "No");

	// Validate the queue structure
	printf("Is the queue valid? %s\n", is_valid(queue) ? "Yes" : "No");

	// Invert the queue
	printf("\nInverting queue...\n");
	if (invert_circular_queue(queue) == 1) {
		printf("Queue after inversion:\n");
		print_circular_queue(queue);
	} else {
		printf("Failed to invert queue.\n");
	}

	// Clone the queue
	printf("\nCloning the queue...\n");
	CircularQueue *clone = create_circular_queue(size);
	if (!clone) {
		printf("Failed to create clone queue.\n");
		free_circular_queue(&queue);
		return 1;
	}
	if (clone_circular_queue(queue, clone) == 1) {
		printf("Cloned queue contents:\n");
		print_circular_queue(clone);
	} else {
		printf("Failed to clone queue.\n");
	}

	// Compare original and clone queues
	printf("\nComparing original and clone queues...\n");
	int eq = are_circular_queues_equal(queue, clone);
	if (eq == 1) {
		printf("Queues are equal.\n");
	} else if (eq == 0) {
		printf("Queues are not equal.\n");
	} else {
		printf("Error comparing queues.\n");
	}

	// Final cleanup
	free_circular_queue(&queue);
	free_circular_queue(&clone);

	return 0;
}
