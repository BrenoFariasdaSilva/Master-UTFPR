/*
 * Description: This program implements a hash table with three collision resolution methods:
 * linear probing, quadratic probing, and double hashing. It initializes a hash table,
 * inserts a set of integer keys, and counts collisions for each method. Finally, it prints
 * the contents of the hash table and identifies the method with the fewest and most collisions.
 * Author: Breno Farias da Silva.
 * Date: 07/06/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf
#include <stdlib.h> // malloc, free

#define TABLE_SIZE 13 // Prime number for better hash distribution

/*
 * Enumeration representing collision resolution methods.
 */
typedef enum { LINEAR, QUADRATIC, DOUBLE_HASH } Method;

/*
 * Stores the name of each probing method.
 */
const char* method_names[] = {
	"Linear Probing",
	"Quadratic Probing",
	"Double Hashing"
};

/*
 * Hash table structure including data array and collision counter.
 */
typedef struct {
	int table[TABLE_SIZE];
	int collisions;
} HashTable;

/*
 * Primary hash function.
 * Computes the initial index for a given key.
 * @param key The integer key to hash.
 * @return Index in the hash table (0 to TABLE_SIZE - 1).
 */
int primary_hash(int key) {
	return key % TABLE_SIZE;
}

/*
 * Secondary hash function used in double hashing.
 * Computes step size for probing sequence.
 * @param key The integer key.
 * @return Step size for double hashing (1 to TABLE_SIZE - 1).
 */
int secondary_hash(int key) {
	return 7 - (key % 7); // 7 is a prime smaller than TABLE_SIZE
}

/*
 * Computes the index using linear probing.
 * @param key The key to insert or search.
 * @param i The attempt number (0-based).
 * @return The computed index in the hash table.
 */
int linear_probing(int key, int i) {
	return (primary_hash(key) + i) % TABLE_SIZE;
}

/*
 * Computes the index using quadratic probing.
 * @param key The key to insert or search.
 * @param i The attempt number (0-based).
 * @return The computed index in the hash table.
 */
int quadratic_probing(int key, int i) {
	int c1 = 1;
	int c2 = 3;
	return (primary_hash(key) + c1 * i + c2 * i * i) % TABLE_SIZE;
}

/*
 * Computes the index using double hashing.
 * @param key The key to insert or search.
 * @param i The attempt number (0-based).
 * @return The computed index in the hash table.
 */
int double_hashing(int key, int i) {
	return (primary_hash(key) + i * secondary_hash(key)) % TABLE_SIZE;
}

/*
 * Initializes a hash table by setting all slots to -1 (empty).
 * Resets the collision counter to zero.
 * @param table Pointer to the hash table to initialize.
 */
void initialize_table(HashTable* table) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		table->table[i] = -1;
	}
	table->collisions = 0;
}

/*
 * Inserts a key into the hash table using the specified probing method.
 * Counts collisions only when probing a slot that is occupied (not empty or deleted).
 * @param table Pointer to the hash table.
 * @param key The key to insert.
 * @param method The collision resolution method to use.
 * @return 1 if insertion succeeded, 0 if failed (table full or no free slot found).
 */
int insert_key(HashTable* table, int key, Method method) {
	int index;
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (method == LINEAR)
			index = linear_probing(key, i);
		else if (method == QUADRATIC)
			index = quadratic_probing(key, i);
		else // DOUBLE_HASH
			index = double_hashing(key, i);

		if (table->table[index] == -1 || table->table[index] == -2) {
			table->table[index] = key;
			return 1;
		} else {
			// Collision occurs when slot is occupied by another key
			table->collisions++;
		}
	}
	return 0; // Table is full or no free slot found after probing
}

/*
 * Searches for a key in the hash table using the specified probing method.
 * Stops searching if an empty slot is found, indicating key absence.
 * @param table Pointer to the hash table.
 * @param key The key to search.
 * @param method The collision resolution method to use.
 * @return Index of the key if found, -1 otherwise.
 */
int search_key(HashTable* table, int key, Method method) {
	int index;
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (method == LINEAR)
			index = linear_probing(key, i);
		else if (method == QUADRATIC)
			index = quadratic_probing(key, i);
		else // DOUBLE_HASH
			index = double_hashing(key, i);

		if (table->table[index] == -1)
			return -1; // Stop search on empty slot: key not present
		if (table->table[index] == key)
			return index; // Key found
	}
	return -1; // Key not found after full probing
}

/*
 * Deletes a key from the hash table using the specified probing method.
 * Marks deleted slots with -2 to distinguish from empty (-1) slots.
 * @param table Pointer to the hash table.
 * @param key The key to delete.
 * @param method The collision resolution method to use.
 * @return 1 if deletion succeeded, 0 if key not found.
 */
int delete_key(HashTable* table, int key, Method method) {
	int index;
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (method == LINEAR)
			index = linear_probing(key, i);
		else if (method == QUADRATIC)
			index = quadratic_probing(key, i);
		else // DOUBLE_HASH
			index = double_hashing(key, i);

		if (table->table[index] == -1)
			return 0; // Key not found (empty slot reached)
		if (table->table[index] == key) {
			table->table[index] = -2; // Mark slot as deleted
			return 1;
		}
	}
	return 0; // Key not found after full probing
}

/*
 * Checks whether the hash table is full (i.e., no empty or deleted slots).
 * @param table Pointer to the hash table.
 * @return 1 if the table is full, 0 otherwise.
 */
int is_full(HashTable* table) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (table->table[i] == -1 || table->table[i] == -2)
			return 0; // Found at least one free slot
	}
	return 1; // No free slots found
}

/*
 * Checks whether the hash table is empty (i.e., all slots are empty).
 * @param table Pointer to the hash table.
 * @return 1 if the table is empty, 0 otherwise.
 */
int is_empty(HashTable* table) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (table->table[i] != -1)
			return 0; // Found at least one occupied or deleted slot
	}
	return 1; // All slots are empty
}

/*
 * Clears the hash table by resetting all slots to -1 (empty)
 * and resetting the collision counter.
 * @param table Pointer to the hash table to clear.
 */
void clear_table(HashTable* table) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		table->table[i] = -1;
	}
	table->collisions = 0;
}

/*
 * Prints the contents of a hash table.
 * Prints '-' for empty slots, '*' for deleted slots, or the stored key.
 * @param table Pointer to the hash table to print.
 */
void print_table(HashTable* table) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (table->table[i] == -1)
			printf("[%2d] -\n", i);
		else if (table->table[i] == -2)
			printf("[%2d] *\n", i); // * indicates deleted slot
		else
			printf("[%2d] %d\n", i, table->table[i]);
	}
}

/*
 * Main function of the program.
 * Tests the hash table with all collision resolution methods.
 * Inserts keys, searches, deletes, prints tables, and compares collisions.
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return Program exit status (0 = success).
 */
int main(int argc, char *argv[]) {
	int keys[] = {18, 41, 22, 44, 59, 32, 31, 73, 26, 56};
	int num_keys = sizeof(keys) / sizeof(int);

	HashTable tables[3];

	for (int m = 0; m < 3; m++) {
		initialize_table(&tables[m]);

		// Check if the table is initially empty
		if (is_empty(&tables[m]))
			printf("Table is initially empty.\n");
		else
			printf("Table is not initially empty.\n");

		int inserted_count = 0;
		for (int i = 0; i < num_keys; i++) {
			if (insert_key(&tables[m], keys[i], (Method)m))
				inserted_count++;
		}
		printf("Keys successfully inserted: %d out of %d\n", inserted_count, num_keys);

		printf("\n=== %s ===\n", method_names[m]);
		print_table(&tables[m]);
		printf("Collisions: %d\n", tables[m].collisions);

		// Check if the table is full
		if (is_full(&tables[m]))
			printf("The table is full.\n");
		else
			printf("The table is not full.\n");

		// Test search_key function with sample keys
		printf("Search tests:\n");
		int test_keys[] = {22, 100};
		for (int t = 0; t < 2; t++) {
			int key = test_keys[t];
			int found_index = search_key(&tables[m], key, (Method)m);
			if (found_index != -1)
				printf("Key %d found at index %d.\n", key, found_index);
			else
				printf("Key %d not found.\n", key);
		}

		// Test delete_key function
		int del_key = 44;
		int deleted = delete_key(&tables[m], del_key, (Method)m);
		if (deleted)
			printf("Key %d deleted successfully.\n", del_key);
		else
			printf("Key %d not found for deletion.\n", del_key);

		// Print table after deletion
		printf("Table after deletion:\n");
		print_table(&tables[m]);

		// Clear table after testing
		clear_table(&tables[m]);
		if (is_empty(&tables[m]))
			printf("Table successfully cleared.\n");
		else
			printf("Table not cleared properly.\n");
	}

	// Determine the method with most and fewest collisions
	int min = tables[0].collisions, max = tables[0].collisions;
	int best_method = 0, worst_method = 0;

	for (int i = 1; i < 3; i++) {
		if (tables[i].collisions < min) {
			min = tables[i].collisions;
			best_method = i;
		}
		if (tables[i].collisions > max) {
			max = tables[i].collisions;
			worst_method = i;
		}
	}

	printf("\n>>> Best method (fewest collisions): %s (%d collisions)\n", method_names[best_method], min);
	printf(">>> Worst method (most collisions): %s (%d collisions)\n", method_names[worst_method], max);

	return 0;
}
