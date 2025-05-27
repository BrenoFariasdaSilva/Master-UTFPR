/*
 * Description: This program shows an implementation of a List using Static Memory Allocation.
 * Author: Breno Farias da Silva.
 * Date: 27/05/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf, scanf
#include <stdbool.h> // bool, true, false

#define ElementType int // Define a macro for the element type in the List.
#define MAX_SIZE 100	// Define the Max Size of the List.

/*
 * Static List structure.
 * This structure holds the data, size, and quantity of elements in the list.
 */
typedef struct {
	ElementType data[MAX_SIZE]; // Array to hold the list elements.
	int size; // Stored size of the list (maximum capacity).
	int quantity; // Current number of elements in the list.
} StaticList;

// Function declarations
void initializeList(StaticList *list, const int size);
bool insertAtEnd(StaticList *list, const ElementType value);
bool insertAtBeginning(StaticList *list, const ElementType value);
bool insertAt(StaticList *list, const int position, const ElementType value);
bool insertArray(StaticList *list, const ElementType *array, const int length);
int replaceAll(StaticList *list, const ElementType oldValue, const ElementType newValue);
bool replaceFirstOccurrence(StaticList *list, const ElementType oldValue, const ElementType newValue);
int findFirst(const StaticList *list, const ElementType value);
int getSize(const StaticList *list);
int getCapacity(const StaticList *list);
bool removeAt(StaticList *list, const int position);
void destroyList(StaticList *list);
ElementType getAt(const StaticList *list, const int position);
bool isEmpty(const StaticList *list);
bool isFull(const StaticList *list);
bool invertList(StaticList *list);
void printList(const StaticList *list);

// --- Function implementations ---

/*
 * Initializes the list with a given size.
 * list: pointer to the list to initialize.
 * size: desired logical size (must be <= MAX_SIZE).
 * return: void.
 */
void initializeList(StaticList *list, const int size) {
	if (list == NULL || size < 1 || size > MAX_SIZE)
		return;

	list->size = size;
	list->quantity = 0;
}

/*
 * Inserts a value at the end of the list.
 * list: pointer to the list.
 * value: the value to be inserted.
 * return: true if inserted, false if the list is full.
 */
bool insertAtEnd(StaticList *list, const ElementType value) {
	if (list == NULL || isFull(list))
		return false;

	list->data[list->quantity++] = value;
	return true;
}

/*
 * Inserts a value at the beginning of the list.
 * list: pointer to the list.
 * value: the value to be inserted.
 * return: true if inserted, false if the list is full.
 */
bool insertAtBeginning(StaticList *list, const ElementType value) {
	if (list == NULL || isFull(list))
		return false;

	for (int i = list->quantity; i > 0; i--) {
		list->data[i] = list->data[i - 1];
	}

	list->data[0] = value;
	list->quantity++;
	return true;
}

/*
 * Inserts a value at a specific position in the list.
 * list: pointer to the list.
 * position: index where the value should be inserted (0-based).
 * value: the value to insert.
 * return: true if inserted, false if position is invalid or list is full.
 */
bool insertAt(StaticList *list, const int position, const ElementType value) {
	if (list == NULL || isFull(list) || position < 0 || position > list->quantity)
		return false;

	for (int i = list->quantity; i > position; i--) {
		list->data[i] = list->data[i - 1];
	}

	list->data[position] = value;
	list->quantity++;
	return true;
}

/*
 * Inserts an array of elements into the list, if space allows.
 * list: pointer to the list.
 * array: pointer to the array of values to insert.
 * length: number of elements in the array.
 * return: true if all elements inserted, false if not enough space.
 */
bool insertArray(StaticList *list, const ElementType *array, const int length) {
	if (list == NULL || array == NULL || isFull(list))
		return false;

	if (list->quantity + length > list->size)
		return false;

	for (int i = 0; i < length; i++) {
		list->data[list->quantity++] = array[i];
	}

	return true;
}

/*
 * Replaces all occurrences of a specific value with another.
 * list: pointer to the list.
 * oldValue: value to be replaced.
 * newValue: value to replace with.
 * return: number of replacements made.
 */
int replaceAll(StaticList *list, const ElementType oldValue, const ElementType newValue) {
	if (list == NULL || isEmpty(list))
		return 0;

	int count = 0;
	for (int i = 0; i < list->quantity; i++) {
		if (list->data[i] == oldValue) {
			list->data[i] = newValue;
			count++;
		}
	}

	return count;
}

/*
 * Replaces the first occurrence of a value with another.
 * list: pointer to the list.
 * oldValue: value to be replaced.
 * newValue: value to replace with.
 * return: true if replaced, false if not found or list is empty.
 */
bool replaceFirstOccurrence(StaticList *list, const ElementType oldValue, const ElementType newValue) {
	if (list == NULL || isEmpty(list))
		return false;

	for (int i = 0; i < list->quantity; i++) {
		if (list->data[i] == oldValue) {
			list->data[i] = newValue;
			return true;
		}
	}
	return false;
}

/*
 * Finds the first occurrence of a value in the list.
 * list: pointer to the list.
 * value: the value to find.
 * return: index of the first occurrence, or -1 if not found.
 */
int findFirst(const StaticList *list, const ElementType value) {
	if (list == NULL || isEmpty(list))
		return -1;

	for (int i = 0; i < list->quantity; i++) {
		if (list->data[i] == value) {
			return i;
		}
	}

	return -1;
}

/*
 * Returns the current number of elements in the list.
 * list: pointer to the list.
 * return: quantity of elements.
 */
int getSize(const StaticList *list) {
	if (list == NULL)
		return 0;
	
	return list->quantity;
}

/*
 * Returns the capacity of the list.
 * list: pointer to the list.
 * return: capacity of the list.
 */
int getCapacity(const StaticList *list) {
	if (list == NULL)
		return 0;
	
	return list->size;
}

/*
 * Removes a value at a specific position in the list.
 * list: pointer to the list.
 * position: index of the value to remove (0-based).
 * return: true if removed, false if position is invalid.
 */
bool removeAt(StaticList *list, const int position) {
	if (list == NULL || isEmpty(list) || position < 0 || position >= list->quantity)
		return false;

	for (int i = position; i < list->quantity - 1; i++) {
		list->data[i] = list->data[i + 1];
	}

	list->quantity--;
	return true;
}

/*
 * Resets the list to its initial empty state.
 * list: pointer to the list.
 */
void destroyList(StaticList *list) {
	if (list != NULL) {
		list->quantity = 0;
	}

	for (int i = 0; i < MAX_SIZE; i++) {
		list->data[i] = 0; // Optional: clear the data array.
	}
}

/*
 * Gets the value at a specific position.
 * list: pointer to the list.
 * position: index to retrieve.
 * return: the value at the given position, or -1 if invalid.
 */
ElementType getAt(const StaticList *list, const int position) {
	if (list == NULL || position < 0 || position >= list->quantity)
		return -1;

	return list->data[position];
}

/*
 * Checks if the list is empty.
 * list: pointer to the list.
 * return: true if empty, false otherwise.
 */
bool isEmpty(const StaticList *list) {
	return (list == NULL || list->quantity == 0);
}

/*
 * Checks if the list is full.
 * list: pointer to the list.
 * return: true if full, false otherwise.
 */
bool isFull(const StaticList *list) {
	return (list != NULL && list->quantity >= list->size);
}

/*
 * Inverts the order of elements in the list.
 * list: pointer to the list.
 * return: true if inverted, false if the list is empty or NULL.
 */
bool invertList(StaticList *list) {
	if (list == NULL || isEmpty(list))
		return false;

	for (int i = 0; i < list->quantity / 2; i++) {
		// Swap elements at positions i and quantity - 1 - i
		ElementType temp = list->data[i];
		list->data[i] = list->data[list->quantity - 1 - i];
		list->data[list->quantity - 1 - i] = temp;
	}

	return true;
}

/*
 * Prints the contents of the list.
 * list: pointer to the list.
 */
void printList(const StaticList *list) {
	if (list == NULL || isEmpty(list)) {
		printf("List is empty.\n");
		return;
	}

	printf("List (%d/%d): ", list->quantity, list->size);
	for (int i = 0; i < list->quantity; i++) {
		printf("%d ", list->data[i]);
	}
	printf("\n");
}

/*
 * Main function of the program.
 * argc: number of arguments passed to the program.
 * argv: array with the arguments passed to the program.
 * return: execution status (0: no errors, otherwise: error code).
 */
int main(int argc, char *argv[]) {
	printf("Welcome to the Static Implementation of a List Data Structure!\n\n");

	StaticList list;
	initializeList(&list, 10); // Initialize the list with a maximum capacity of 10.

	// Basic insertions
	insertAtEnd(&list, 5); // Insert 5 at the end
	insertAtEnd(&list, 10); // Insert 10 at the end
	insertAtBeginning(&list, 1); // Insert 1 at the beginning
	insertAt(&list, 1, 7); // Insert 7 at position 1
	printList(&list); // Expected output: 1 7 5 10

	// Remove an element
	removeAt(&list, 2); // Remove the element at position 2 (value 5)
	printList(&list); // Expected output: 1 7 10

	// Retrieve an element by index
	printf("Element at index 1: %d\n", getAt(&list, 1)); // Expected: 7

	// Insert an array of elements
	ElementType arrayToInsert[] = {100, 200};
	insertArray(&list, arrayToInsert, 2);
	printList(&list); // Expected output: 1 7 10 100 200

	// Replace an element's value (first occurrence)
	replaceFirstOccurrence(&list, 7, 77); // Replace value 7 with 77
	printList(&list); // Expected output: 1 77 10 100 200

	// Replace all occurrences of 10 with 42
	insertAtEnd(&list, 10); // Insert a duplicate to test replaceAll
	int replaced = replaceAll(&list, 10, 42);
	printf("Number of values replaced with 42: %d\n", replaced);
	printList(&list); // Expected: 1 77 42 100 200 42

	// Use findFirst directly
	int firstPos = findFirst(&list, 42);
	printf("First position of value 42: %d\n", firstPos); // Expected: 2

	// Get current size of the list
	printf("getSize: %d\n", getSize(&list)); // Expected: 6

	// Get the capacity of the list
	printf("List capacity: %d\n", getCapacity(&list)); // Expected: 10

	// Check if the list is full
	printf("Is list full? %s\n", isFull(&list) ? "Yes" : "No");

	// Destroy the list
	destroyList(&list);
	printList(&list); // Expected output: "List is empty."

	// Check if the list is empty after destruction
	printf("Is list empty? %s\n", isEmpty(&list) ? "Yes" : "No");

	return 0;
}
