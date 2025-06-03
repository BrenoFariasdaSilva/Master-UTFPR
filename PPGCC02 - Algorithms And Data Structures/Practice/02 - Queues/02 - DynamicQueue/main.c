/*
 * Description: This program shows an implementation of a Queue using Dynamic Memory Allocation.
 * Author: Breno Farias da Silva.
 * Date: 18/05/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf, scanf
#include <stdlib.h> // malloc, free
#include <stdbool.h> // 'bool', 'true', and 'false' keywords

#define ElementType int // Define a macro for the element type in the Queue.

typedef struct node {
	ElementType data;
	struct node *next;
} Node;

typedef struct {
	Node *front; // Pointer to the front node of the queue.
	Node *rear; // Pointer to the rear node of the queue.
	int size; // Size of the queue.
} DynamicQueue;

// Function declarations
DynamicQueue* create_queue();
int initialize_queue(DynamicQueue *queue);
int enqueue(DynamicQueue *queue, const ElementType add_element);
int dequeue(DynamicQueue *queue, ElementType *removed_element);
int peek_front(const DynamicQueue *queue, ElementType *front_element);
int clone_queue(const DynamicQueue *source, DynamicQueue *destination);
int invert_queue(DynamicQueue *queue);
int search_element(const DynamicQueue *queue, const ElementType value);
int are_queues_equal(const DynamicQueue *q1, const DynamicQueue *q2);
int insert_vector(DynamicQueue *queue, const ElementType *array, const int size);
bool is_valid(const DynamicQueue *queue);
bool is_empty(const DynamicQueue *queue);
int print_queue(const DynamicQueue *queue);
int print_queue_attributes(const DynamicQueue *queue);
void free_queue(DynamicQueue **queue);

/*
 * Function to create a new DynamicQueue instance using dynamic memory.
 * return: pointer to a newly allocated DynamicQueue (NULL on failure).
 */
DynamicQueue* create_queue() {
	DynamicQueue *queue = (DynamicQueue *) malloc(sizeof(DynamicQueue));

	if (!queue) {
		return NULL;
	}

	initialize_queue(queue);

	if (!is_valid(queue)) {
		free(queue);
		return NULL;
	}

	return queue;
}

/*
 * Function to initialize a DynamicQueue instance.
 * queue: pointer to the DynamicQueue to initialize.
 * return: status of the operation (1: success, -1: error).
 */
int initialize_queue(DynamicQueue *queue) {
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
	if (!is_valid(queue)) {
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
int dequeue(DynamicQueue *queue, ElementType *removed_element) {
	if (!is_valid(queue) || !removed_element) {
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
int peek_front(const DynamicQueue *queue, ElementType *front_element) {
	if (!is_valid(queue) || !front_element || !queue->front) {
		return -1;
	}

	*front_element = queue->front->data;

	return 1;
}

/*
 * Function to clone the contents of one queue into another.
 * source: pointer to the source DynamicQueue instance.
 * destination: pointer to the destination DynamicQueue instance.
 * return: status of the operation (1: success, -1: error).
 */
int clone_queue(const DynamicQueue *source, DynamicQueue *destination) {
	if (!source || !destination) {
		return -1;
	}

	initialize_queue(destination);

	Node* current = source->front;
	while (current) {
		if (enqueue(destination, current->data) == -1) {
			free_queue(&destination);
			return -1;
		}
		current = current->next;
	}

	return 1;
}

/*
 * Function to invert the queue.
 * queue: pointer to the DynamicQueue instance.
 * return: status of the operation (1: success, -1: error).
 */
int invert_queue(DynamicQueue *queue) {
	if (!is_valid(queue)) {
		return -1;
	}

	Node* prev = NULL;
	Node* current = queue->front;
	Node* next = NULL;

	queue->rear = queue->front;

	while (current) {
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}

	queue->front = prev;

	return 1;
}

/*
 * Function to search for an element in the queue.
 * queue: pointer to the DynamicQueue instance.
 * value: element value to be searched.
 * return: 1 if found, 0 if not found, -1 on error.
 */
int search_element(const DynamicQueue *queue, const ElementType value) {
	if (!is_valid(queue)) {
		return -1;
	}

	Node* current = queue->front;
	while (current) {
		if (current->data == value) {
			return 1;
		}
		current = current->next;
	}

	return 0;
}

/*
 * Function to compare if two queues are equal (same size and same element order).
 * q1: pointer to the first DynamicQueue instance.
 * q2: pointer to the second DynamicQueue instance.
 * return: 1 if equal, 0 if different, -1 on error.
 */
int are_queues_equal(const DynamicQueue *q1, const DynamicQueue *q2) {
	if (!q1 || !q2) {
		return -1;
	}

	if (q1->size != q2->size) {
		return 0;
	}

	Node* n1 = q1->front;
	Node* n2 = q2->front;

	while (n1 && n2) {
		if (n1->data != n2->data) {
			return 0;
		}
		n1 = n1->next;
		n2 = n2->next;
	}

	return 1;
}

/*
 * Function to insert multiple elements from an array into the queue.
 * queue: pointer to the DynamicQueue instance.
 * array: pointer to the array of elements.
 * size: number of elements in the array.
 * return: status of the operation (1: success, -1: error).
 */
int insert_vector(DynamicQueue *queue, const ElementType *array, const int size) {
	if (!is_valid(queue) || !array || size <= 0) {
		return -1;
	}

	for (int i = 0; i < size; i++) {
		if (enqueue(queue, array[i]) == -1) {
			return -1;
		}
	}

	return 1;
}

/*
 * Function to validate the queue structure.
 * Checks for consistency like size matching actual nodes.
 * queue: pointer to DynamicQueue instance.
 * return: true if valid, false otherwise.
 */
bool is_valid(const DynamicQueue *queue) {
	if (!queue) return false;

	int count = 0;
	Node* current = queue->front;
	Node* last = NULL;

	while (current) {
		count++;
		last = current;
		current = current->next;
	}

	if (count != queue->size) {
		return false;
	}

	if ((queue->size == 0 && (queue->front != NULL || queue->rear != NULL)) ||
		(queue->size > 0 && queue->rear != last)) {
		return false;
	}

	return true;
}

/*
 * Function to check if the queue is empty.
 * queue: pointer to the DynamicQueue instance.
 * return: 1 if empty, 0 if not empty, -1 if invalid input.
 */
bool is_empty(const DynamicQueue *queue) {
	if (!is_valid(queue)) {
		return false;
	}

	return (queue->size == 0);
}

/*
 * Function to print all elements in the queue.
 * queue: pointer to the DynamicQueue instance.
 * return: status of the operation (1: success, -1: error).
 */
int print_queue(const DynamicQueue *queue) {
	if (!is_valid(queue)) {
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
int print_queue_attributes(const DynamicQueue *queue) {
	if (!is_valid(queue)) {
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
void free_queue(DynamicQueue ** queue) {
	if (!queue || !*queue) return;

	Node* current = (*queue)->front;
	while (current) {
		Node* temp = current;
		current = current->next;
		free(temp);
	}

	free(*queue);
	*queue = NULL;
}

/*
 * Main function of the program.
 * argc: number of arguments passed when calling the program.
 * argv: array containing the arguments passed to the program.
 * return: program exit status (0: no errors, otherwise, error code).
 */
int main(int argc, char *argv[]) {
	printf("Welcome to the Dynamic Implementation of a Queue Data Structure!\n\n");

	// Create a new queue
	DynamicQueue *queue = create_queue();
	if (!queue) {
		printf("Failed to create queue.\n");
		return 1;
	}

	// Print attributes of an empty queue
	printf("Initial queue attributes:\n");
	print_queue_attributes(queue);

	// Enqueue elements
	printf("Enqueuing elements 10, 20, 30...\n");
	enqueue(queue, 10);
	enqueue(queue, 20);
	enqueue(queue, 30);
	print_queue_attributes(queue);

	// Dequeue one element
	ElementType removed_element;
	printf("Dequeuing one element...\n");
	if (dequeue(queue, &removed_element) == 1) {
		printf("Dequeued element: %d\n", removed_element);
	} else {
		printf("Failed to dequeue element.\n");
	}
	print_queue_attributes(queue);

	// Peek front element
	ElementType front_element;
	printf("Peeking front element...\n");
	if (peek_front(queue, &front_element) == 1) {
		printf("Front element is: %d\n", front_element);
	} else {
		printf("Failed to peek front element.\n");
	}
	printf("\n");

	// Check if queue is empty
	printf("Checking if queue is empty...\n");
	if (is_empty(queue)) {
		printf("The queue is empty.\n");
	} else {
		printf("The queue is not empty.\n");
	}
	printf("\n");

	// Test is_valid
	printf("Checking if queue is valid...\n");
	if (is_valid(queue)) {
		printf("Queue is valid.\n");
	} else {
		printf("Queue is invalid.\n");
	}
	printf("\n");

	// Insert vector of elements
	ElementType array[] = {100, 200, 300};
	printf("Inserting vector {100, 200, 300} into queue...\n");
	if (insert_vector(queue, array, 3) == 1) {
		printf("Vector inserted successfully.\n");
	} else {
		printf("Failed to insert vector.\n");
	}
	print_queue_attributes(queue);

	// Search for element 200 in queue
	printf("Searching for element 200 in queue...\n");
	int found = search_element(queue, 200);
	if (found == 1) {
		printf("Element 200 found in queue.\n");
	} else if (found == 0) {
		printf("Element 200 not found in queue.\n");
	} else {
		printf("Error searching for element.\n");
	}
	printf("\n");

	// Clone queue into a new queue
	DynamicQueue *cloned_queue = create_queue();
	printf("Cloning current queue into a new queue...\n");
	if (clone_queue(queue, cloned_queue) == 1) {
		printf("Cloning successful. Cloned queue attributes:\n");
		print_queue_attributes(cloned_queue);
	} else {
		printf("Cloning failed.\n");
	}
	printf("\n");

	// Check if queues are equal
	printf("Checking if original queue and cloned queue are equal...\n");
	int equal = are_queues_equal(queue, cloned_queue);
	if (equal == 1) {
		printf("Queues are equal.\n");
	} else if (equal == 0) {
		printf("Queues are not equal.\n");
	} else {
		printf("Error comparing queues.\n");
	}
	printf("\n");

	// Invert the original queue
	printf("Inverting the original queue...\n");
	if (invert_queue(queue) == 1) {
		printf("Queue inverted successfully.\n");
	} else {
		printf("Failed to invert queue.\n");
	}
	print_queue_attributes(queue);

	// Print final queue states
	printf("Final original queue:\n");
	print_queue(queue);

	printf("Final cloned queue (should be empty):\n");
	print_queue(cloned_queue);

	// Free both queues
	printf("Freeing the original and cloned queues...\n");
	free_queue(&queue);
	free_queue(&cloned_queue);

	return 0;
}
