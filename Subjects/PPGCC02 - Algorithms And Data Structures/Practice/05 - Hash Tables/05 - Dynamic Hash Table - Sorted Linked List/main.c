/*
 * Description: This program implements a hash table using separate chaining
 * with linked lists, where each node contains a sorted array of integers.
 * Binary search is used within each array to locate keys efficiently.
 * Author: Breno Farias da Silva.
 * Date: 07/06/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf
#include <stdlib.h> // malloc, free, realloc

#define TABLE_SIZE 13 // Prime number for better distribution
#define BLOCK_CAPACITY 4 // Initial array size per node

/*
 * Node of the linked list, each holding a sorted array of integers.
 */
typedef struct Node {
	int* keys; // Sorted array of keys
	int count; // Number of keys in the array
	int capacity; // Capacity of the array
	struct Node* next; // Pointer to the next node
} Node;

/*
* Hash table structure using chaining.
*/
typedef struct {
	Node** table; // Array of linked list heads
	int size; // Number of buckets
} HashTable;

/*
* Creates a new node with initialized array.
* @return Pointer to the created node.
*/
Node* create_node() {
	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->keys = (int*)malloc(BLOCK_CAPACITY * sizeof(int));
	new_node->count = 0;
	new_node->capacity = BLOCK_CAPACITY;
	new_node->next = NULL;
	return new_node;
}

/*
* Initializes the hash table.
* @param table Pointer to the hash table.
* @param size Number of buckets.
*/
void initialize_table(HashTable* table, int size) {
	table->size = size;
	table->table = (Node**)malloc(size * sizeof(Node*));
	for (int i = 0; i < size; i++) {
		table->table[i] = NULL;
	}
}

/*
* Hash function.
* @param table Pointer to the hash table.
* @param key Integer key.
* @return Index in the hash table.
*/
int hash(HashTable* table, int key) {
	return key % table->size;
}

/*
* Performs binary search in a sorted array.
* @param arr Pointer to the array.
* @param size Size of the array.
* @param key Key to search for.
* @return Index if found, -1 otherwise.
*/
int binary_search(int* arr, int size, int key) {
	int left = 0, right = size - 1;
	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (arr[mid] == key)
			return mid;
		else if (arr[mid] < key)
			left = mid + 1;
		else
			right = mid - 1;
	}
	return -1;
}

/*
* Inserts a key into a sorted array within a node.
* @param node Pointer to the node.
* @param key Key to insert.
*/
void insert_into_node(Node* node, int key) {
	if (node->count == node->capacity) {
		node->capacity *= 2;
		node->keys = (int*)realloc(node->keys, node->capacity * sizeof(int));
	}
	int i = node->count - 1;
	while (i >= 0 && node->keys[i] > key) {
		node->keys[i + 1] = node->keys[i];
		i--;
	}
	node->keys[i + 1] = key;
	node->count++;
}

/*
* Inserts a key into the hash table.
* @param table Pointer to the hash table.
* @param key Key to insert.
*/
void insert_key(HashTable* table, int key) {
	int index = hash(table, key);
	Node* current = table->table[index];
	while (current != NULL) {
		if (binary_search(current->keys, current->count, key) != -1)
			return; // Key already exists
		current = current->next;
	}
	// Insert in the first node or create a new one if necessary
	current = table->table[index];
	if (current == NULL) {
		table->table[index] = create_node();
		insert_into_node(table->table[index], key);
	} else {
		insert_into_node(current, key); // Insert into first node
	}
}

/*
* Searches for a key in the hash table.
* @param table Pointer to the hash table.
* @param key Key to search.
* @return 1 if found, 0 otherwise.
*/
int search_key(HashTable* table, int key) {
	int index = hash(table, key);
	Node* current = table->table[index];
	while (current != NULL) {
		if (binary_search(current->keys, current->count, key) != -1)
			return 1;
		current = current->next;
	}
	return 0;
}

/*
* Deletes a key from the hash table.
* @param table Pointer to the hash table.
* @param key Key to delete.
* @return 1 if deleted, 0 if not found.
*/
int delete_key(HashTable* table, int key) {
	int index = hash(table, key);
	Node* current = table->table[index];
	while (current != NULL) {
		int pos = binary_search(current->keys, current->count, key);
		if (pos != -1) {
			for (int i = pos; i < current->count - 1; i++)
				current->keys[i] = current->keys[i + 1];
			current->count--;
			return 1;
		}
		current = current->next;
	}
	return 0;
}

/*
* Prints the hash table.
* @param table Pointer to the hash table.
*/
void print_table(HashTable* table) {
	for (int i = 0; i < table->size; i++) {
		printf("[%2d]", i);
		Node* current = table->table[i];
		while (current != NULL) {
			printf(" | ");
			for (int j = 0; j < current->count; j++)
				printf("%d ", current->keys[j]);
			current = current->next;
		}
		printf("\n");
	}
}

/*
 * Clear the hash table by freeing all nodes and their arrays.
 * @param table Pointer to the hash table.
 */
void clear_table(HashTable* table) {
	for (int i = 0; i < table->size; i++) {
		Node* current = table->table[i];
		while (current != NULL) {
			Node* temp = current;
			current = current->next;
			free(temp->keys);
			free(temp);
		}
		table->table[i] = NULL;
	}
}

/*
* Frees all memory used by the hash table.
* @param table Pointer to the hash table.
*/
void free_table(HashTable* table) {
	for (int i = 0; i < table->size; i++) {
		Node* current = table->table[i];
		while (current != NULL) {
			Node* temp = current;
			current = current->next;
			free(temp->keys);
			free(temp);
		}
	}
	free(table->table);
}

/*
* Main function.
*/
int main() {
	int keys[] = {18, 41, 22, 44, 59, 32, 31, 73, 26, 56};
	int num_keys = sizeof(keys) / sizeof(int);

	HashTable table;
	initialize_table(&table, TABLE_SIZE);

	for (int i = 0; i < num_keys; i++) {
		insert_key(&table, keys[i]);
	}

	printf("\n=== Hash Table Contents ===\n");
	print_table(&table);

	int test_keys[] = {22, 100};
	printf("\nSearch tests:\n");
	for (int i = 0; i < 2; i++) {
		printf("Key %d %s\n", test_keys[i], search_key(&table, test_keys[i]) ? "found" : "not found");
	}

	int del_key = 44;
	printf("\nDeleting key %d...\n", del_key);
	if (delete_key(&table, del_key))
		printf("Key %d deleted successfully.\n", del_key);
	else
		printf("Key %d not found for deletion.\n", del_key);

	printf("\nTable after deletion:\n");
	print_table(&table);

	clear_table(&table);
	printf("\nTable after clearing:\n");
	print_table(&table);

	free_table(&table);
	return 0;
}
