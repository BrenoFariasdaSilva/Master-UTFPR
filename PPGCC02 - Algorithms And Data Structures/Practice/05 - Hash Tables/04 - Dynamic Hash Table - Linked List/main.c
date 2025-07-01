/*
 * Description: This program implements a hash table with chaining using linked lists
 * to handle collisions. It inserts a set of integer keys, prints the contents
 * of the hash table, and allows for key search and deletion. It also identifies
 * the bucket with the longest chain (worst-case access).
 * Author: Breno Farias da Silva.
 * Date: 07/06/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf
#include <stdlib.h> // malloc, free

#define TABLE_SIZE 13 // Prime number for better distribution

/*
 * Node of the linked list used for chaining in the hash table.
 */
typedef struct Node {
	int key;
	struct Node* next;
} Node;

/*
* Hash table structure using chaining.
*/
typedef struct {
	Node** table; // Array of linked list heads
	int size; // Number of buckets
} HashTable;

/*
* Creates a new node with the given key.
* @param key Integer key to store in the node.
* @return Pointer to the created node.
*/
Node* create_node(int key) {
	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->key = key;
	new_node->next = NULL;
	return new_node;
}

/*
* Initializes a hash table with all buckets set to NULL.
* @param table Pointer to the hash table.
* @param size Number of buckets in the hash table.
*/
void initialize_table(HashTable* table, int size) {
	table->size = size;
	table->table = (Node**)malloc(size * sizeof(Node*));
	for (int i = 0; i < size; i++) {
		table->table[i] = NULL;
	}
}

/*
* Computes the hash index for a given key.
* @param table Pointer to the hash table.
* @param key The integer key.
* @return The index in the table.
*/
int hash(HashTable* table, int key) {
	return key % table->size;
}

/*
* Inserts a key into the hash table using chaining.
* @param table Pointer to the hash table.
* @param key The key to insert.
*/
void insert_key(HashTable* table, int key) {
	int index = hash(table, key);
	Node* new_node = create_node(key);
	new_node->next = table->table[index];
	table->table[index] = new_node;
}

/*
* Searches for a key in the hash table.
* @param table Pointer to the hash table.
* @param key The key to search.
* @return 1 if found, 0 otherwise.
*/
int search_key(HashTable* table, int key) {
	int index = hash(table, key);
	Node* current = table->table[index];
	while (current != NULL) {
		if (current->key == key)
			return 1;
		current = current->next;
	}
	return 0;
}

/*
* Deletes a key from the hash table.
* @param table Pointer to the hash table.
* @param key The key to delete.
* @return 1 if deleted, 0 if not found.
*/
int delete_key(HashTable* table, int key) {
	int index = hash(table, key);
	Node* current = table->table[index];
	Node* prev = NULL;
	while (current != NULL) {
		if (current->key == key) {
			if (prev == NULL)
				table->table[index] = current->next;
			else
				prev->next = current->next;
			free(current);
			return 1;
		}
		prev = current;
		current = current->next;
	}
	return 0;
}

/*
* Prints the contents of the hash table.
* @param table Pointer to the hash table.
*/
void print_table(HashTable* table) {
	for (int i = 0; i < table->size; i++) {
		printf("[%2d]", i);
		Node* current = table->table[i];
		while (current != NULL) {
			printf(" -> %d", current->key);
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
			free(temp);
		}
	}
	free(table->table);
}

/*
* Main function of the program.
* @param argc Number of command-line arguments.
* @param argv Array of command-line arguments.
* @return Exit code.
*/
int main(int argc, char* argv[]) {
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