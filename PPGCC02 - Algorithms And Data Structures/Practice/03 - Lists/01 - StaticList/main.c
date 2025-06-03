/*
 * Description: This program shows an implementation of a List using Static Memory Allocation.
 * Author: Breno Farias da Silva.
 * Date: 27/05/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf, scanf
#include <stdlib.h> // malloc, free
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
StaticList* createList();
void initialize_list(StaticList *list, const int size);
bool insert_at_end(StaticList *list, const ElementType value);
bool insert_at_beginning(StaticList *list, const ElementType value);
bool insert_at(StaticList *list, const int position, const ElementType value);
bool insert_array(StaticList *list, const ElementType *array, const int length);
int replace_all(StaticList *list, const ElementType oldValue, const ElementType newValue);
bool replace_first_occurrence(StaticList *list, const ElementType oldValue, const ElementType newValue);
int find_first(const StaticList *list, const ElementType value);
int get_size(const StaticList *list);
int get_capacity(const StaticList *list);
bool remove_at(StaticList *list, const int position);
bool destroy_list(StaticList *list);
ElementType get_at(const StaticList *list, const int position);
bool is_empty(const StaticList *list);
bool is_full(const StaticList *list);
bool invert_list(StaticList *list);
bool interleave_lists(const StaticList *list1, const StaticList *list2, StaticList *result);
bool is_sorted(const StaticList *list);
void print_list(const StaticList *list);
bool destroy_list(StaticList *list);

// --- Function implementations ---

/*
 * Creates a new StaticList and initializes it.
 * return: pointer to the newly created StaticList.
 */
StaticList* create_list() {
	StaticList *list = (StaticList *) malloc(sizeof(StaticList));
	
	if (!list) return NULL; // Memory allocation failed.

	initialize_list(list, MAX_SIZE); // Initialize the list with maximum size.

	return list;
}

/*
 * Initializes the list with a given size.
 * list: pointer to the list to initialize.
 * size: desired logical size (must be <= MAX_SIZE).
 * return: void.
 */
void initialize_list(StaticList *list, const int size) {
	if (!list || size < 1 || size > MAX_SIZE)
		return;

	list->size = size;
	list->quantity = 0;

	for (int i = 0; i < size; i++) {
		list->data[i] = 0; // Clear the data array.
	}
}

/*
 * Inserts a value at the end of the list.
 * list: pointer to the list.
 * value: the value to be inserted.
 * return: true if inserted, false if the list is full.
 */
bool insert_at_end(StaticList *list, const ElementType value) {
	if (!list || is_full(list))
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
bool insert_at_beginning(StaticList *list, const ElementType value) {
	if (!list || is_full(list))
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
bool insert_at(StaticList *list, const int position, const ElementType value) {
	if (!list || is_full(list) || position < 0 || position > list->quantity)
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
bool insert_array(StaticList *list, const ElementType *array, const int length) {
	if (!list || !array || is_full(list))
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
int replace_all(StaticList *list, const ElementType oldValue, const ElementType newValue) {
	if (!list || is_empty(list))
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
bool replace_first_occurrence(StaticList *list, const ElementType oldValue, const ElementType newValue) {
	if (!list || is_empty(list))
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
int find_first(const StaticList *list, const ElementType value) {
	if (!list || is_empty(list))
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
int get_size(const StaticList *list) {
	if (!list)
		return 0;
	
	return list->quantity;
}

/*
 * Returns the capacity of the list.
 * list: pointer to the list.
 * return: capacity of the list.
 */
int get_capacity(const StaticList *list) {
	if (!list)
		return 0;
	
	return list->size;
}

/*
 * Removes a value at a specific position in the list.
 * list: pointer to the list.
 * position: index of the value to remove (0-based).
 * return: true if removed, false if position is invalid.
 */
bool remove_at(StaticList *list, const int position) {
	if (!list || is_empty(list) || position < 0 || position >= list->quantity)
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
bool destroy_list(StaticList *list) {
	if (!list)
		return false;

	free(list);
	return true;
}

/*
 * Gets the value at a specific position.
 * list: pointer to the list.
 * position: index to retrieve.
 * return: the value at the given position, or -1 if invalid.
 */
ElementType get_at(const StaticList *list, const int position) {
	if (!list || position < 0 || position >= list->quantity)
		return -1;

	return list->data[position];
}

/*
 * Verify if the list is empty.
 * list: pointer to the list.
 * return: true if empty, false otherwise.
 */
bool is_empty(const StaticList *list) {
	return (!list || list->quantity == 0);
}

/*
 * Verify if the list is full.
 * list: pointer to the list.
 * return: true if full, false otherwise.
 */
bool is_full(const StaticList *list) {
	return (list != NULL && list->quantity >= list->size);
}

/*
 * Inverts the order of elements in the list.
 * list: pointer to the list.
 * return: true if inverted, false if the list is empty or NULL.
 */
bool invert_list(StaticList *list) {
	if (!list || is_empty(list))
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
 * Interleaves two lists into a result list.
 * list1: pointer to the first list.
 * list2: pointer to the second list.
 * result: pointer to the result list.
 * return: true if interleaved successfully, false if any list is NULL or result is full.
 */
bool interleave_lists(const StaticList *list1, const StaticList *list2, StaticList *result) {
	if (!list1 || !list2 || !result || is_full(result))
		return false;

	for (int i = 0; i < list1->quantity + list2->quantity; i++) {
		if (i % 2 == 0 && i / 2 < list1->quantity) {
			// Take from list1
			if (!insert_at_end(result, list1->data[i / 2])) {
				return false; // Failed to insert
			}
		} else if (i / 2 < list2->quantity) {
			// Take from list2
			if (!insert_at_end(result, list2->data[i / 2])) {
				return false; // Failed to insert
			}
		}
	}
	return true;
}

/*
 * Verify if the list is sorted in non-decreasing order.
 * list: pointer to the list.
 * return: true if sorted, false otherwise.
 */
bool is_sorted(const StaticList *list) {
	if (!list || is_empty(list))
		return true; // An empty list is considered sorted

	for (int i = 1; i < list->quantity; i++) {
		if (list->data[i] < list->data[i - 1]) {
			return false; // Found an unsorted pair
		}
	}
	return true; // All elements are in non-decreasing order
}

/*
 * Prints the contents of the list.
 * list: pointer to the list.
 */
void print_list(const StaticList *list) {
	if (!list || is_empty(list)) {
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

	StaticList *list = create_list();
	if (!list) {
		printf("Failed to create list.\n");
		return 1; // Memory allocation failed.
	}

	// Basic insertions
	insert_at_end(list, 5); // Insert 5 at the end
	insert_at_end(list, 10); // Insert 10 at the end
	insert_at_beginning(list, 1); // Insert 1 at the beginning
	insert_at(list, 1, 7); // Insert 7 at position 1
	print_list(list); // Expected output: 1 7 5 10

	// Remove an element
	remove_at(list, 2); // Remove the element at position 2 (value 5)
	print_list(list); // Expected output: 1 7 10

	// Retrieve an element by index
	printf("Element at index 1: %d\n", get_at(list, 1)); // Expected: 7

	// Insert an array of elements
	ElementType arrayToInsert[] = {100, 200};
	insert_array(list, arrayToInsert, 2);
	print_list(list); // Expected output: 1 7 10 100 200

	// Replace an element's value (first occurrence)
	replace_first_occurrence(list, 7, 77); // Replace value 7 with 77
	print_list(list); // Expected output: 1 77 10 100 200

	// Replace all occurrences of 10 with 42
	insert_at_end(list, 10); // Insert a duplicate to test replace_all
	int replaced = replace_all(list, 10, 42);
	printf("Number of values replaced with 42: %d\n", replaced);
	print_list(list); // Expected: 1 77 42 100 200 42

	// Use find_first directly
	int firstPos = find_first(list, 42);
	printf("First position of value 42: %d\n", firstPos); // Expected: 2

	// Get current size of the list
	printf("getSize: %d\n", get_size(list)); // Expected: 6

	// Get the capacity of the list
	printf("List capacity: %d\n", get_capacity(list)); // Expected: 10

	// Check if the list is full
	printf("Is list full? %s\n", is_full(list) ? "Yes" : "No");

	// Destroy the list
	destroy_list(list);
	print_list(list); // Expected output: "List is empty."

	// Check if the list is empty after destruction
	printf("Is list empty? %s\n", is_empty(list) ? "Yes" : "No");

	return 0;
}
