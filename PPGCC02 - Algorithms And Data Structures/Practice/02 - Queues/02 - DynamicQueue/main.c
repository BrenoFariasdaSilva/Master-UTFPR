/*
 * Description: This program shows an implementation of a Queue using Dynamic Memory Allocation.
 * Author: Breno Farias da Silva.
 * Date: 18/05/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h>  // printf, scanf
#include <stdlib.h> // malloc, free

#define ElementType int // Define a macro for the element type in the Queue.

typedef struct node {
	ElementType data;
	struct node *next;
} Node;

typedef struct {
	Node *front; // Pointer to the front node of the queue.
	Node *rear;  // Pointer to the rear node of the queue.
	int size;    // Size of the queue.
} DynamicQueue;

// Function declarations
DynamicQueue* create_queue();
int initialize_queue(DynamicQueue* queue);
int enqueue(DynamicQueue *queue, const ElementType add_element);
int dequeue(DynamicQueue *queue, ElementType* removed_element);
int peek_front(const DynamicQueue *queue, ElementType* front_element);
int is_empty(const DynamicQueue *queue);
int print_queue(const DynamicQueue* queue);
int print_queue_attributes(const DynamicQueue* queue);
void free_queue(DynamicQueue* queue);

/*
 * Function to create a new DynamicQueue instance using dynamic memory.
 * return: pointer to a newly allocated DynamicQueue (NULL on failure).
 */
DynamicQueue* create_queue() {
	DynamicQueue* queue = (DynamicQueue*) malloc(sizeof(DynamicQueue));

	if (!queue) {
		return NULL;
	}

	initialize_queue(queue);

	return queue;
}

/*
 * Function to initialize a DynamicQueue instance.
 * queue: pointer to the DynamicQueue to initialize.
 * return: status of the operation (1: success, -1: error).
 */
int initialize_queue(DynamicQueue* queue) {
	if (!queue) {
		return -1;
	}

	queue->front = NULL;
	queue->rear = NULL;
	queue->size = 0;

	return 1;
}

/*
 * Function to enqueue (add) a new element to the rear of the queue.
 * queue: pointer to the DynamicQueue instance.
 * add_element: element to be enqueued.
 * return: status of the operation (1: success, -1: error).
 */
int enqueue(DynamicQueue *queue, const ElementType add_element) {
	if (!queue) {
		return -1;
	}

	Node* new_node = (Node*) malloc(sizeof(Node));
	if (!new_node) {
		return -1;
	}

	new_node->data = add_element;
	new_node->next = NULL;

	if (!queue->rear) {
		// Queue is empty
		queue->front = new_node;
		queue->rear = new_node;
	} else {
		queue->rear->next = new_node;
		queue->rear = new_node;
	}

	queue->size++;

	return 1;
}

/*
 * Function to dequeue (remove) the front element from the queue.
 * queue: pointer to the DynamicQueue instance.
 * removed_element: pointer to store the dequeued element.
 * return: status of the operation (1: success, -1: error).
 */
int dequeue(DynamicQueue *queue, ElementType* removed_element) {
	if (!queue || !removed_element) {
		return -1;
	}

	if (!queue->front) {
		return -1; // Queue underflow
	}

	Node* temp = queue->front;
	*removed_element = temp->data;

	queue->front = temp->next;

	if (!queue->front) {
		queue->rear = NULL;
	}

	queue->size--;

	free(temp);

	return 1;
}

/*
 * Function to peek the front element of the queue without removing it.
 * queue: pointer to the DynamicQueue instance.
 * front_element: pointer to store the front element.
 * return: status of the operation (1: success, -1: error).
 */
int peek_front(const DynamicQueue *queue, ElementType* front_element) {
	if (!queue || !front_element || !queue->front) {
		return -1;
	}

	*front_element = queue->front->data;

	return 1;
}

/*
 * Function to check if the queue is empty.
 * queue: pointer to the DynamicQueue instance.
 * return: 1 if empty, 0 if not empty, -1 if invalid input.
 */
int is_empty(const DynamicQueue *queue) {
	if (!queue) {
		return -1;
	}

	return (queue->size == 0);
}

/*
 * Function to print all elements in the queue.
 * queue: pointer to the DynamicQueue instance.
 * return: status of the operation (1: success, -1: error).
 */
int print_queue(const DynamicQueue* queue) {
	if (!queue) {
		return -1;
	}

	printf("Dynamic Queue: ");
	Node *node = queue->front;
	while (node) {
		printf("%d ", node->data);
		node = node->next;
	}
	printf("\n");

	return 1;
}

/*
 * Function to print queue attributes.
 * queue: pointer to the DynamicQueue instance.
 * return: status of the operation (1: success, -1: error).
 */
int print_queue_attributes(const DynamicQueue* queue) {
	if (!queue) {
		return -1;
	}

	print_queue(queue);

	if (queue->front) {
		printf("Front: %d\n", queue->front->data);
	} else {
		printf("Front: NULL (Empty Queue)\n");
	}

	if (queue->rear) {
		printf("Rear: %d\n", queue->rear->data);
	} else {
		printf("Rear: NULL (Empty Queue)\n");
	}

	printf("Queue Size: %d\n\n", queue->size);

	return 1;
}

/*
 * Function to free all memory associated with the queue.
 * queue: pointer to the DynamicQueue instance.
 * return: void.
 */
void free_queue(DynamicQueue* queue) {
	if (!queue) {
		return;
	}

	Node* current = queue->front;
	while (current) {
		Node* temp = current;
		current = current->next;
		free(temp);
	}

	free(queue);
}

/*
 * Main function of the program.
 * argc: number of arguments passed when calling the program.
 * argv: array containing the arguments passed to the program.
 * return: program exit status (0: no errors, otherwise, error code).
 */
int main(int argc, char *argv[]) {
	printf("Welcome to the Dynamic Implementation of a Queue Data Structure!\n\n");

	DynamicQueue *queue = create_queue();

	print_queue_attributes(queue);

	enqueue(queue, 10);
	enqueue(queue, 20);
	enqueue(queue, 30);
	print_queue_attributes(queue);

	ElementType removed_element;
	dequeue(queue, &removed_element);
	print_queue_attributes(queue);

	ElementType front_element;
	if (peek_front(queue, &front_element) == 1) {
		printf("Peeked front element: %d\n\n", front_element);
	}

	if (is_empty(queue)) {
		printf("The queue is empty.\n");
	} else {
		printf("The queue is not empty.\n");
	}

	free_queue(queue);

	return 0;
}
