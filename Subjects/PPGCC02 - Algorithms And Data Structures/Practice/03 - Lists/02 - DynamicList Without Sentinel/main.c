/*
 * Description: This program shows an implementation of a Dynamic Doubly Linked List without a Sentinel node.
 * Author: Breno Farias da Silva.
 * Date: 27/05/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf
#include <stdlib.h> // malloc, free
#include <stdbool.h> // bool, true, false

#define ElementType int // Define the type of elements in the list

/*
 * Node structure for the doubly linked list.
 * Each node contains data, a pointer to the previous node, and a pointer to the next node.
*/
typedef struct Node {
	ElementType data; // Data stored in the node
	struct Node *prev; // Pointer to the previous node
	struct Node *next; // Pointer to the next node
} Node;

/*
 * Dynamic List structure.
 * This structure holds pointers to the head and tail nodes, and the size of the list.
*/
typedef struct {
	Node *head; // Pointer to the first node
	Node *tail; // Pointer to the last node
	int size; // Current number of elements in the list
} DynamicList;

// Function declarations
DynamicList* create_list();
void initialize_list(DynamicList *list);
bool insert_at_end(DynamicList *list, const ElementType value);
bool insert_at_beginning(DynamicList *list, const ElementType value);
bool insert_at(DynamicList *list, const int position, const ElementType value);
bool insert_array(DynamicList *list, const ElementType *array, const int length);
int replace_all(DynamicList *list, const ElementType oldValue, const ElementType newValue);
bool replace_first_occurrence(DynamicList *list, const ElementType oldValue, const ElementType newValue);
int find_first(const DynamicList *list, const ElementType value);
int find_last(const DynamicList *list, const ElementType value);
int get_list_size(const DynamicList *list);
bool is_full(const DynamicList *list);
bool remove_at(DynamicList *list, const int position);
ElementType get_at(const DynamicList *list, const int position);
bool is_empty(const DynamicList *list);
void destroy_list(DynamicList *list);
bool invert_list(DynamicList *list);
bool interleave_lists(const DynamicList *list1, const DynamicList *list2, DynamicList *result);
bool is_sorted(const DynamicList *list);
void print_list(const DynamicList *list);

// --- Function implementations ---

/*
 * Creates a new DynamicList and initializes it.
 * return: pointer to the newly created DynamicList (NULL on failure).
 */
DynamicList* create_list() {
	DynamicList *list = (DynamicList *) malloc(sizeof(DynamicList));
	if (!list) return NULL;

	initialize_list(list);
	return list;
}

/*
 * Initializes an empty list.
 * list: pointer to the DynamicList to initialize.
 * return: void
 */
void initialize_list(DynamicList *list) {
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
}

/*
 * Inserts a value at the end of the list.
 * list: pointer to the DynamicList.
 * value: the value to be inserted.
 * return: true if inserted, false if memory allocation fails.
 */
bool insert_at_end(DynamicList *list, const ElementType value) {
	Node *newNode = (Node *) malloc(sizeof(Node));
	if (!newNode) return false;

	newNode->data = value;
	newNode->next = NULL;
	newNode->prev = list->tail;

	if (is_empty(list)) {
		list->head = newNode;
	} else {
		list->tail->next = newNode;
	}

	list->tail = newNode;
	list->size++;
	return true;
}

/*
 * Inserts a value at the beginning of the list.
 * list: pointer to the DynamicList.
 * value: the value to be inserted.
 * return: true if inserted, false if memory allocation fails.
 */
bool insert_at_beginning(DynamicList *list, const ElementType value) {
	Node *newNode = (Node *) malloc(sizeof(Node));
	if (!newNode) return false;

	newNode->data = value;
	newNode->prev = NULL;
	newNode->next = list->head;

	if (is_empty(list)) {
		list->tail = newNode;
	} else {
		list->head->prev = newNode;
	}

	list->head = newNode;
	list->size++;
	return true;
}

/*
 * Inserts a value at a specific position in the list.
 * list: pointer to the DynamicList.
 * position: index where the value should be inserted (0-based).
 * value: the value to insert.
 * return: true if inserted, false if position is invalid or memory allocation fails.
 */
bool insert_at(DynamicList *list, const int position, const ElementType value) {
	if (position < 0 || position > list->size) return false;
	if (position == 0) return insert_at_beginning(list, value);
	if (position == list->size) return insert_at_end(list, value);

	Node *newNode = (Node *) malloc(sizeof(Node));
	if (!newNode) return false;

	Node *current = list->head;
	for (int i = 0; i < position; i++) {
		current = current->next;
	}

	newNode->data = value;
	newNode->next = current;
	newNode->prev = current->prev;
	current->prev->next = newNode;
	current->prev = newNode;
	list->size++;
	return true;
}

/*
 * Inserts multiple elements from an array at the end of the list.
 * list: pointer to the DynamicList.
 * array: pointer to the array of elements to insert.
 * length: number of elements in the array.
 * return: true if all elements are inserted successfully, false otherwise.
 */
bool insert_array(DynamicList *list, const ElementType *array, const int length) {
	for (int i = 0; i < length; i++) {
		if (!insert_at_end(list, array[i])) {
			return false; // Failed to insert due to memory allocation failure
		}
	}
	return true;
}

/*
 * Replaces all occurrences of oldValue with newValue.
 * list: pointer to the DynamicList.
 * oldValue: the value to be replaced.
 * newValue: the value to replace with.
 * return: the count of replaced elements.
 */
int replace_all(DynamicList *list, const ElementType oldValue, const ElementType newValue) {
	int count = 0;
	Node *current = list->head;

	while (current) {
		if (current->data == oldValue) {
			current->data = newValue;
			count++;
		}
		current = current->next;
	}
	return count;
}

/*
 * Replaces the first occurrence of oldValue with newValue.
 * list: pointer to the DynamicList.
 * oldValue: the value to be replaced.
 * newValue: the value to replace with.
 * return: true if a replacement was made, false otherwise.
 */
bool replace_first_occurrence(DynamicList *list, const ElementType oldValue, const ElementType newValue) {
	Node *current = list->head;
	while (current) {
		if (current->data == oldValue) {
			current->data = newValue;
			return true;
		}
		current = current->next;
	}
	return false;
}

/*
 * Finds the position of the first occurrence of value in the list.
 * list: pointer to the DynamicList.
 * value: the value to find.
 * return: index of the value if found (0-based), -1 if not found.
 */
int find_first(const DynamicList *list, const ElementType value) {
	Node *current = list->head;
	int index = 0;

	while (current) {
		if (current->data == value) {
			return index;
		}
		current = current->next;
		index++;
	}

	return -1;
}

/*
 * Finds the position of the last occurrence of value in the list.
 * list: pointer to the DynamicList.
 * value: the value to find.
 * return: index of the value if found (0-based), -1 if not found.
 */
int find_last(const DynamicList *list, const ElementType value) {
	if (!list) return -1;

	Node *current = list->head;
	int position = -1;
	int index = 0;
	while (current) {
		if (current->data == value) {
			position = index;
		}
		current = current->next;
		index++;
	}

	return position;
}

/*
 * Gets the current size (number of elements) of the list.
 * list: pointer to the DynamicList.
 * return: size of the list.
 */
int get_list_size(const DynamicList *list) {
	return list->size;
}

/*
 * Verify if the list is full.
 * Since this is a dynamic list, it is never full unless memory is exhausted.
 * return: always false.
 */
bool is_full(const DynamicList *list) {
   // Always returns false for dynamic list (limited only by memory)
   // If you want to simulate a full condition, implement a maximum size and check against it in the insert functions.
   return false;
}

/*
 * Removes a value at a specific position in the list.
 * list: pointer to the DynamicList.
 * position: index of the value to remove (0-based).
 * return: true if removed, false if position is invalid or list is empty.
 */
bool remove_at(DynamicList *list, const int position) {
	if (position < 0 || position >= list->size || is_empty(list)) return false;

	Node *current = list->head;
	for (int i = 0; i < position; i++) {
		current = current->next;
	}

	if (current->prev) {
		current->prev->next = current->next;
	} else {
		list->head = current->next;
	}

	if (current->next) {
		current->next->prev = current->prev;
	} else {
		list->tail = current->prev;
	}
	
	free(current);
	list->size--;
	return true;
}

/*
 * Gets the value at a specific position.
 * list: pointer to the DynamicList.
 * position: index to retrieve (0-based).
 * return: the value at the given position, or -1 if invalid.
 */
ElementType get_at(const DynamicList *list, const int position) {
	if (position < 0 || position >= list->size || is_empty(list)) return -1;

	Node *current = list->head;
	for (int i = 0; i < position; i++) {
		current = current->next;
	}

	return current->data;
}

/*
 * Verify if the list is empty.
 * list: pointer to the DynamicList.
 * return: true if empty, false otherwise.
 */
bool is_empty(const DynamicList *list) {
	return list->size == 0;
}

/*
 * Destroys the list and frees all allocated memory.
 * list: pointer to the DynamicList.
 * return: void
 */
void destroy_list(DynamicList *list) {
	Node *current = list->head;
	while (current) {
		Node *next = current->next;
		free(current);
		current = next;
	}
	list->head = list->tail = NULL;
	list->size = 0;
}

/*
 * Inverts the order of elements in the list.
 * list: pointer to the DynamicList.
 * return: true if inverted, false if the list is empty or NULL.
 */
bool invert_list(DynamicList *list) {
   if (!list || is_empty(list)) return false;

   Node *current = list->head;
	Node *temp = NULL;

	// Swap next and prev pointers for each node
	while (current) {
		temp = current->prev;
		current->prev = current->next;
		current->next = temp;
		current = current->prev; // Move to the next node in the original order
	}

	// Adjust head and tail pointers
	temp = list->head;
	list->head = list->tail;
	list->tail = temp;

	return true;
}

/*
 * Interleaves two lists into a new list.
 * list1: pointer to the first DynamicList.
 * list2: pointer to the second DynamicList.
 * result: pointer to the DynamicList where the interleaved result will be stored (must be initialized).
 * return: bool
 */
bool interleave_lists(const DynamicList *list1, const DynamicList *list2, DynamicList *result) {
	if (!list1 || !list2 || !result) return false;

	if (is_empty(list1) && is_empty(list2)) {
		initialize_list(result);
		return true; // Both lists are empty, result is also empty
	}

	initialize_list(result);

	// Interleave elements from list1 and list2
	Node *current1 = list1->head;
	Node *current2 = list2->head;
	while (current1 || current2) {
		if (current1) {
			insert_at_end(result, current1->data);
			current1 = current1->next;
		}
		if (current2) {
			insert_at_end(result, current2->data);
			current2 = current2->next;
		}
	}

	return true;
}

/*
 * Verify if the list is sorted in ascending order.
 * list: pointer to the DynamicList.
 * return: true if sorted, false otherwise.
 */
bool is_sorted(const DynamicList *list) {
	if (!list || is_empty(list)) return true; // An empty list is considered sorted

	Node *current = list->head;
	while (current && current->next) {
		if (current->data > current->next->data) {
			return false; // Found an unsorted pair
		}
		current = current->next;
	}

	return true; // No unsorted pairs found
}

/*
 * Prints the contents of the list.
 * list: pointer to the DynamicList.
 * return: void
 */
void print_list(const DynamicList *list) {
	if (is_empty(list)) {
		printf("List is empty.\n");
		return;
	}

	printf("List (%d): ", list->size);
	Node *current = list->head;
	while (current) {
		printf("%d ", current->data);
		current = current->next;
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
	printf("Welcome to the Dynamic Doubly Linked List Implementation!\n\n");

	DynamicList *list = create_list();
	if (!list) {
		printf("Failed to create list.\n");
		return 1;
	}

	// Test insert_at_end
	insert_at_end(list, 5);
	insert_at_end(list, 10);

	// Test insert_at_beginning
	insert_at_beginning(list, 1);

	// Test insert_at (insert 7 at position 1)
	insert_at(list, 1, 7);

	// Print list (expected: 1 7 5 10)
	printf("List after inserts:\n");
	print_list(list);

	// Test insert_array
	ElementType array[] = {20, 25, 30};
	bool insertedArray = insert_array(list, array, 3);
	printf("Inserted array? %s\n", insertedArray ? "Yes" : "No");
	print_list(list); // Expected: 1 7 5 10 20 25 30

	// Test replace_all (replace all 10 with 15)
	int replacedCount = replace_all(list, 10, 15);
	printf("Replaced %d occurrences of 10 with 15\n", replacedCount);
	print_list(list); // Expected: 1 7 5 15 20 25 30

	// Test replace_first_occurrence (replace first 7 with 8)
	bool replacedFirst = replace_first_occurrence(list, 7, 8);
	printf("Replaced first occurrence of 7 with 8? %s\n", replacedFirst ? "Yes" : "No");
	print_list(list); // Expected: 1 8 5 15 20 25 30

	// Test find_first (position of 20)
	int pos = find_first(list, 20);
	printf("Position of 20: %d\n", pos); // Expected: 4 (0-based)

	// Test get_list_size
	int size = get_list_size(list);
	printf("List size: %d\n", size); // Expected: 7

	// Test find_first (first occurrence of 5)
	int firstPos = find_first(list, 5);
	printf("First occurrence of 5 at: %d\n", firstPos); // Expected: 2

	// Test find_last (last occurrence of 20)
	int lastPos = find_last(list, 20);
	printf("Last occurrence of 20 at: %d\n", lastPos); // Expected: 4

	// Test is_empty and is_full
	printf("Is list empty? %s\n", is_empty(list) ? "Yes" : "No"); // Expected: No
	printf("Is list full? %s\n", is_full(list) ? "Yes" : "No"); // Depends on capacity if any

	// Test get_at (element at position 3)
	ElementType valAt = get_at(list, 3);
	printf("Element at position 3: %d\n", valAt); // Expected: 15

	// Test remove_at (remove element at position 1)
	bool removed = remove_at(list, 1);
	printf("Removed element at position 1? %s\n", removed ? "Yes" : "No");
	print_list(list); // Expected: 1 5 15 20 25 30

	// Destroy list and print again
	destroy_list(list);
	printf("After destroying list:\n");
	print_list(list); // Should say list is empty

	return 0;
}
