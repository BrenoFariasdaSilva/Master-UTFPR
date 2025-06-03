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

/*
 * Structure representing a Static Queue.
 * vector: fixed-size array to hold elements.
 * front: index of the front element.
 * rear: index where the next element will be inserted.
 * size: maximum size (capacity) of the queue.
 * quantity: current number of elements in the queue.
 */
typedef struct {
	ElementType vector[MAX_SIZE]; // Fixed-size array
	int front; // Index of the front element
	int rear; // Index where the next element will be inserted
	int size; // Maximum size (capacity)
	int quantity; // Current number of elements
} StaticQueue;

// Function declarations
StaticQueue create_queue();
int initialize_queue(StaticQueue *queue);
int enqueue(StaticQueue *queue, const ElementType add_element);
int dequeue(StaticQueue *queue, ElementType *removed_element);
int is_empty(const StaticQueue *queue);
int is_full(const StaticQueue *queue);
int peek(const StaticQueue *queue, ElementType *front_element);
int clear(StaticQueue *queue);
int search(const StaticQueue *queue, const ElementType element);
int clone(const StaticQueue *queue, StaticQueue *clone);
int invert(StaticQueue *queue);
int is_equal(const StaticQueue *queue1, const StaticQueue *queue2);
int insert_vector(StaticQueue *queue, const ElementType *vector, const int size);
int is_valid(const StaticQueue *queue);
int print_queue_attributes(const StaticQueue *queue);
int print_queue(const StaticQueue *queue);
int destroy_queue(StaticQueue *queue);

/*
 * Function to create and initialize the queue.
 * return: The created static queue instance.
*/
StaticQueue create_queue() {
	StaticQueue queue;
	
	if (initialize_queue(&queue) == -1) {
		printf("Error initializing the queue.\n");
	}

	return queue;
}

/* Function to initialize the queue.
 * queue: pointer to the StaticQueue instance.
 * return: status of the operation (1: success, -1: error).
*/
int initialize_queue(StaticQueue *queue) {
	if (!queue) {
		return -1;
	}

	queue->front = 0;
	queue->rear = 0;
	queue->size = MAX_SIZE;
	queue->quantity = 0;

	for (int i = 0; i < MAX_SIZE; i++) {
		queue->vector[i] = 0; // Initialize all elements to 0
	}

	return 1;
}

/*
 * Function to enqueue an element into the queue.
 * queue: pointer to the StaticQueue instance.
 * add_element: the element to add to the queue.
 * return: status of the operation (1: success, -1: error).
*/
int enqueue(StaticQueue *queue, const ElementType add_element) {
	if (!is_valid(queue)) {
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
int dequeue(StaticQueue *queue, ElementType *removed_element) {
	if (!is_valid(queue) || !removed_element) {
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
int is_empty(const StaticQueue *queue) {
	if (!is_valid(queue)) {
		return -1;
	}

	return (queue->quantity == 0) ? 1 : 0;
}

/*
 * Function to check if the queue is full.
 * queue: pointer to the StaticQueue instance.
 * return: 1 if full, 0 if not full, -1 if error (null pointer).
*/
int is_full(const StaticQueue *queue) {
	if (!is_valid(queue)) {
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
int peek(const StaticQueue *queue, ElementType *front_element) {
	if (!is_valid(queue) || !front_element) {
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
int clear(StaticQueue *queue) {
	if (!is_valid(queue)) {
		return -1;
	}

	queue->front = 0;
	queue->rear = 0;
	queue->quantity = 0;

	return 1;
}

/*
 * Function to search for an element in the queue.
 * queue: pointer to the StaticQueue instance.
 * element: the element to search for.
 * return: index relative to the front (0-based), -1 if not found or error.
*/
int search(const StaticQueue *queue, const ElementType element) {
	if (!is_valid(queue) || queue->quantity == 0) {
		return -1;
	}

	int idx = queue->front;
	for (int i = 0; i < queue->quantity; i++) {
		if (queue->vector[idx] == element) {
			return i;
		}
		idx = (idx + 1) % queue->size;
	}

	return -1;
}

/*
 * Function to clone a queue into another.
 * queue: pointer to the original StaticQueue instance.
 * clone: pointer to the StaticQueue instance that will receive the copy.
 * return: status of the operation (1: success, -1: error).
*/
int clone(const StaticQueue *queue, StaticQueue *clone) {
	if (!is_valid(queue) || !clone) {
		return -1;
	}

	clone->size = queue->size;
	clone->front = queue->front;
	clone->rear = queue->rear;
	clone->quantity = queue->quantity;

	for (int i = 0; i < queue->size; i++) {
		clone->vector[i] = queue->vector[i];
	}

	return 1;
}

/*
 * Function to invert the queue.
 * queue: pointer to the StaticQueue instance.
 * return: status of the operation (1: success, -1: error).
*/
int invert(StaticQueue *queue) {
	if (!is_valid(queue) || queue->quantity <= 1) {
		return -1;
	}

	for (int i = 0; i < queue->quantity / 2; i++) {
		int from_idx = (queue->front + i) % queue->size;
		int to_idx = (queue->front + queue->quantity - 1 - i) % queue->size;
		ElementType temp = queue->vector[from_idx];
		queue->vector[from_idx] = queue->vector[to_idx];
		queue->vector[to_idx] = temp;
	}

	return 1;
}

/*
 * Function to compare two queues for equality.
 * queue1: pointer to the first StaticQueue instance.
 * queue2: pointer to the second StaticQueue instance.
 * return: 1 if equal, 0 if different, -1 if error.
*/
int is_equal(const StaticQueue *queue1, const StaticQueue *queue2) {
	if (!is_valid(queue1) || !is_valid(queue2)) {
		return -1;
	}

	if (queue1->quantity != queue2->quantity || queue1->size != queue2->size) {
		return 0;
	}

	for (int i = 0; i < queue1->quantity; i++) {
		int idx1 = (queue1->front + i) % queue1->size;
		int idx2 = (queue2->front + i) % queue2->size;

		if (queue1->vector[idx1] != queue2->vector[idx2]) {
			return 0;
		}
	}

	return 1;
}

/*
 * Function to insert multiple elements from a vector into the queue.
 * queue: pointer to the StaticQueue instance.
 * vector: array of elements to insert.
 * size: number of elements in the vector.
 * return: number of elements successfully inserted, -1 if error.
*/
int insert_vector(StaticQueue *queue, const ElementType *vector, const int size) {
	if (!is_valid(queue) || !vector || size < 0) {
		return -1;
	}

	int inserted = 0;
	for (int i = 0; i < size; i++) {
		if (enqueue(queue, vector[i]) == 1) {
			inserted++;
		} else {
			break;
		}
	}

	return inserted;
}

/*
 * Function to validate the internal state of the queue.
 * queue: pointer to the StaticQueue instance.
 * return: 1 if valid, 0 if inconsistent, -1 if null pointer.
*/
int is_valid(const StaticQueue *queue) {
	if (!queue) {
		return -1;
	}

	if (queue->size != MAX_SIZE) return 0;
	if (queue->quantity < 0 || queue->quantity > queue->size) return 0;
	if (queue->front < 0 || queue->front >= queue->size) return 0;
	if (queue->rear < 0 || queue->rear >= queue->size) return 0;

	return 1;
}

/*
 * Function to print queue attributes.
 * queue: pointer to the StaticQueue instance.
 * return: status of the operation (1: success, -1: error).
*/
int print_queue_attributes(const StaticQueue *queue) {
	if (!is_valid(queue)) {
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
int print_queue(const StaticQueue *queue) {
	if (!is_valid(queue)) {
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
 * Function to destroy the queue and free resources.
 * queue: pointer to the StaticQueue instance.
 * return: status of the operation (1: success, -1: error).
*/
int destroy_queue(StaticQueue *queue) {
	if (!is_valid(queue)) {
		return -1;
	}

	queue->front = 0;
	queue->rear = 0;
	queue->quantity = 0;

	return 1;
}

/*
 * Main function of the program.
 * argc: number of arguments passed when calling the program.
 * argv: array containing the arguments passed to the program.
 * return: program exit status (0: success, otherwise, error code).
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

	// Test clone
	StaticQueue cloned_queue = create_queue();
	if (clone(&queue, &cloned_queue) == 1) {
		printf("Queue cloned successfully:\n");
		print_queue_attributes(&cloned_queue);
	} else {
		printf("Failed to clone queue.\n");
	}

	// Test invert
	if (invert(&queue) == 1) {
		printf("Queue after inversion:\n");
		print_queue(&queue);
	} else {
		printf("Failed to invert queue.\n");
	}

	// Test search
	int position = search(&queue, 20);
	if (position >= 0) {
		printf("Element 20 found at relative position: %d\n", position);
	} else {
		printf("Element 20 not found in queue.\n");
	}

	// Test is_equal
	printf("Are queues equal? %s\n\n", is_equal(&queue, &cloned_queue) == 1 ? "Yes" : "No");

	// Test insert_vector
	ElementType arr[] = {40, 50, 60};
	if (insert_vector(&queue, arr, 3) == 1) {
		printf("Elements inserted from array:\n");
		print_queue(&queue);
	} else {
		printf("Failed to insert elements from array.\n");
	}

	// Test is_valid
	printf("Is queue valid? %s\n", is_valid(&queue) == 1 ? "Yes" : "No");

	printf("Clearing the queue...\n");
	if (clear(&queue) == 1) {
		printf("Queue cleared successfully.\n\n");
	} else {
		printf("Failed to clear queue.\n\n");
	}

	print_queue_attributes(&queue);

	printf("Is Queue Full? %s\n", is_full(&queue) == 1 ? "Yes" : "No");

	printf("Destroying the queue...\n");
	if (destroy_queue(&queue) == 1) {
		printf("Queue destroyed successfully.\n");
	} else {
		printf("Failed to destroy queue.\n");
	}

	return 0;
}
