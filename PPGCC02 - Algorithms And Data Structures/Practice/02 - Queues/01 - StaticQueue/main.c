/*
 * Description: This program shows an implementation of a Queue using Static Memory Allocation.
 * Author: Breno Farias da Silva.
 * Date: 18/05/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf, scanf

#define ElementType int // Define a macro for the element type in the Queue.
#define MAX_SIZE 100 // Define the Max Size of the Queue.

typedef struct {
	ElementType vector[MAX_SIZE]; // Fixed-size array
	int front; // Index of the front element
	int rear; // Index where the next element will be inserted
	int size; // Maximum size (capacity)
	int quantity; // Current number of elements
} StaticQueue;

// Function declarations
StaticQueue create_queue();
int enqueue(StaticQueue* queue, const ElementType add_element);
int dequeue(StaticQueue* queue, ElementType* removed_element);
int is_empty(const StaticQueue* queue);
int is_full(const StaticQueue* queue);
int peek(const StaticQueue* queue, ElementType* front_element);
int clear(StaticQueue* queue);
int print_queue_attributes(const StaticQueue* queue);
int print_queue(const StaticQueue* queue);

/*
 * Function to create and initialize the queue.
 * return: The created static queue instance.
*/
StaticQueue create_queue() {
	StaticQueue queue;
	queue.front = 0;
	queue.rear = 0;
	queue.size = MAX_SIZE;
	queue.quantity = 0;
	return queue;
}

/*
 * Function to enqueue an element into the queue.
 * queue: pointer to the StaticQueue instance.
 * add_element: the element to add to the queue.
 * return: status of the operation (1: success, -1: error).
*/
int enqueue(StaticQueue* queue, const ElementType add_element) {
	if (!queue) {
		return -1;
	}

	if (queue->quantity >= queue->size) {
		printf("Queue is full. Can't enqueue another element!\n");
		return -1;
	}

	queue->vector[queue->rear] = add_element;
	queue->rear = (queue->rear + 1) % queue->size;
	queue->quantity++;

	return 1;
}

/*
 * Function to dequeue the front element from the queue.
 * queue: pointer to the StaticQueue instance.
 * removed_element: pointer to store the dequeued element.
 * return: status of the operation (1: success, -1: error).
*/
int dequeue(StaticQueue* queue, ElementType* removed_element) {
	if (!queue || !removed_element) {
		return -1;
	}

	if (queue->quantity <= 0) {
		printf("Empty Queue. Unable to dequeue any element!\n");
		return -1;
	}

	*removed_element = queue->vector[queue->front];
	queue->front = (queue->front + 1) % queue->size;
	queue->quantity--;

	return 1;
}

/*
 * Function to check if the queue is empty.
 * queue: pointer to the StaticQueue instance.
 * return: 1 if empty, 0 if not empty, -1 if error (null pointer).
*/
int is_empty(const StaticQueue* queue) {
	if (!queue) {
		return -1;
	}

	return (queue->quantity == 0) ? 1 : 0;
}

/*
 * Function to check if the queue is full.
 * queue: pointer to the StaticQueue instance.
 * return: 1 if full, 0 if not full, -1 if error (null pointer).
*/
int is_full(const StaticQueue* queue) {
	if (!queue) {
		return -1;
	}

	return (queue->quantity == queue->size) ? 1 : 0;
}

/*
 * Function to peek at the front element without dequeuing.
 * queue: pointer to the StaticQueue instance.
 * front_element: pointer to store the front element.
 * return: status of the operation (1: success, -1: error).
*/
int peek(const StaticQueue* queue, ElementType* front_element) {
	if (!queue || !front_element) {
		return -1;
	}

	if (queue->quantity == 0) {
		printf("Empty Queue. Nothing to peek!\n");
		return -1;
	}

	*front_element = queue->vector[queue->front];

	return 1;
}

/*
 * Function to clear the queue.
 * queue: pointer to the StaticQueue instance.
 * return: status of the operation (1: success, -1: error).
*/
int clear(StaticQueue* queue) {
	if (!queue) {
		return -1;
	}

	queue->front = 0;
	queue->rear = 0;
	queue->quantity = 0;

	return 1;
}

/*
 * Function to print queue attributes.
 * queue: pointer to the StaticQueue instance.
 * return: status of the operation (1: success, -1: error).
*/
int print_queue_attributes(const StaticQueue* queue) {
	if (!queue) {
		return -1;
	}

	print_queue(queue);
	printf("Queue Max Size: %d\n", queue->size);
	printf("Queue Current Size: %d\n\n", queue->quantity);

	return 1;
}

/*
 * Function to print all elements in the queue.
 * queue: pointer to the StaticQueue instance.
 * return: status of the operation (1: success, -1: error).
*/
int print_queue(const StaticQueue* queue) {
	if (!queue) {
		return -1;
	}

	printf("Static Queue: ");
	for (int i = 0, idx = queue->front; i < queue->quantity; i++) {
		printf("%d ", queue->vector[idx]);
		idx = (idx + 1) % queue->size;
	}
	printf("\n");

	return 1;
}

/*
 * Main function of the program.
 * argc: number of arguments passed when calling the program.
 * argv: array containing the arguments passed to the program.
 * return: program exit status (0: no errors, otherwise, error code).
*/
int main(int argc, char *argv[]) {
	printf("Welcome to the Static Implementation of a Queue Data Structure!\n\n");

	StaticQueue queue = create_queue();

	enqueue(&queue, 10);
	enqueue(&queue, 20);
	enqueue(&queue, 30);

	print_queue_attributes(&queue);

	ElementType removed;
	if (dequeue(&queue, &removed)) {
		printf("Dequeued: %d\n", removed);
	}

	print_queue_attributes(&queue);

	printf("Is Queue Empty? %s\n\n", is_empty(&queue) == 1 ? "Yes" : "No");

	ElementType front;
	if (peek(&queue, &front) == 1) {
		printf("Front element (peek): %d\n\n", front);
	} else {
		printf("Failed to peek front element.\n\n");
	}

	printf("Clearing the queue...\n");
	if (clear(&queue) == 1) {
		printf("Queue cleared successfully.\n\n");
	}

	print_queue_attributes(&queue);

	printf("Is Queue Full? %s\n", is_full(&queue) == 1 ? "Yes" : "No");

	return 0;
}
