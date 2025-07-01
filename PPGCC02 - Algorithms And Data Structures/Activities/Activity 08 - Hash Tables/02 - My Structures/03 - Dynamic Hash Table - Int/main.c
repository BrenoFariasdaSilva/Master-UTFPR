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
* Hash table structure including data, size and collision counter.
*/
typedef struct {
	int* table;
	int size;
	int collisions;
} HashTable;

/*
* Primary hash function.
* @param table Pointer to the hash table.
* @param key The integer key to hash.
* @return Index in the hash table.
*/
int primary_hash(HashTable* table, int key) {
	return key % table->size;
}

/*
* Secondary hash function used in double hashing.
* @param key The integer key.
* @return Step size for double hashing.
*/
int secondary_hash(int key) {
	return 7 - (key % 7); // 7 is prime smaller than table->size
}

/*
* Computes the index using linear probing.
* @param table Pointer to the hash table.
* @param key The key to insert.
* @param i The attempt number.
* @return The computed index.
*/
int linear_probing(HashTable* table, int key, int i) {
	return (primary_hash(table, key) + i) % table->size;
}

/*
* Computes the index using quadratic probing.
* @param table Pointer to the hash table.
* @param key The key to insert.
* @param i The attempt number.
* @return The computed index.
*/
int quadratic_probing(HashTable* table, int key, int i) {
	int c1 = 1;
	int c2 = 3;
	return (primary_hash(table, key) + c1 * i + c2 * i * i) % table->size;
}

/*
* Computes the index using double hashing.
* @param table Pointer to the hash table.
* @param key The key to insert.
* @param i The attempt number.
* @return The computed index.
*/
int double_hashing(HashTable* table, int key, int i) {
	return (primary_hash(table, key) + i * secondary_hash(key)) % table->size;
}

/*
* Initializes a hash table by setting all positions to -1 (empty).
* @param table Pointer to the hash table to initialize.
* @param size Size of the hash table.
*/
void initialize_table(HashTable* table, int size) {
	table->size = size;
	table->collisions = 0;
	table->table = (int*)malloc(size * sizeof(int));
	for (int i = 0; i < size; i++)
		table->table[i] = -1;
}

/*
* Inserts a key into the hash table using the specified probing method.
* @param table Pointer to the hash table.
* @param key The key to insert.
* @param method The collision resolution method to use.
* @return 1 if insertion succeeded, 0 if failed.
*/
int insert_key(HashTable* table, int key, Method method) {
	int index;
	for (int i = 0; i < table->size; i++) {
		if (method == LINEAR)
			index = linear_probing(table, key, i);
		else if (method == QUADRATIC)
			index = quadratic_probing(table, key, i);
		else
			index = double_hashing(table, key, i);

		if (table->table[index] == -1 || table->table[index] == -2) {
			table->table[index] = key;
			return 1;
		} else {
			table->collisions++;
		}
	}
	return 0;
}

/*
* Searches for a key in the hash table using the specified probing method.
* @param table Pointer to the hash table.
* @param key The key to search.
* @param method The collision resolution method to use.
* @return Index of the key if found, -1 otherwise.
*/
int search_key(HashTable* table, int key, Method method) {
	int index;
	for (int i = 0; i < table->size; i++) {
		if (method == LINEAR)
			index = linear_probing(table, key, i);
		else if (method == QUADRATIC)
			index = quadratic_probing(table, key, i);
		else
			index = double_hashing(table, key, i);

		if (table->table[index] == -1)
			return -1;
		if (table->table[index] == key)
			return index;
	}
	return -1;
}

/*
* Deletes a key from the hash table using the specified probing method.
* Marks the slot as deleted with -2.
* @param table Pointer to the hash table.
* @param key The key to delete.
* @param method The collision resolution method to use.
* @return 1 if deletion succeeded, 0 if key not found.
*/
int delete_key(HashTable* table, int key, Method method) {
	int index;
	for (int i = 0; i < table->size; i++) {
		if (method == LINEAR)
			index = linear_probing(table, key, i);
		else if (method == QUADRATIC)
			index = quadratic_probing(table, key, i);
		else
			index = double_hashing(table, key, i);

		if (table->table[index] == -1)
			return 0;
		if (table->table[index] == key) {
			table->table[index] = -2;
			return 1;
		}
	}
	return 0;
}

/*
* Checks whether the hash table is full (i.e., no empty or deleted slots).
* @param table Pointer to the hash table.
* @return 1 if the table is full, 0 otherwise.
*/
int is_full(HashTable* table) {
	for (int i = 0; i < table->size; i++) {
		if (table->table[i] == -1 || table->table[i] == -2)
			return 0;
	}
	return 1;
}

/*
* Checks whether the hash table is empty (i.e., all slots are -1).
* @param table Pointer to the hash table.
* @return 1 if the table is empty, 0 otherwise.
*/
int is_empty(HashTable* table) {
	for (int i = 0; i < table->size; i++) {
		if (table->table[i] != -1)
			return 0;
	}
	return 1;
}

/*
* Clears the hash table by resetting all positions to -1 and the collision counter to 0.
* @param table Pointer to the hash table to clear.
*/
void clear_table(HashTable* table) {
	for (int i = 0; i < table->size; i++) {
		table->table[i] = -1;
	}
	table->collisions = 0;
}

/*
* Dynamically resizes the hash table and rehashes all valid elements.
* @param old_table Pointer to the existing hash table.
* @param new_size Desired new size for the hash table.
* @param method Collision resolution method to use.
* @return Pointer to a new hash table with rehashed values.
*/
HashTable* resize_table_dynamic(HashTable* old_table, int new_size, Method method) {
	HashTable* new_table = (HashTable*)malloc(sizeof(HashTable));
	initialize_table(new_table, new_size);

	for (int i = 0; i < old_table->size; i++) {
		if (old_table->table[i] >= 0) {
			insert_key(new_table, old_table->table[i], method);
		}
	}

	return new_table;
}

/*
* Prints the contents of a hash table.
* @param table Pointer to the hash table to print.
*/
void print_table(HashTable* table) {
	for (int i = 0; i < table->size; i++) {
		if (table->table[i] == -1)
			printf("[%2d] -\n", i);
		else if (table->table[i] == -2)
			printf("[%2d] *\n", i);
		else
			printf("[%2d] %d\n", i, table->table[i]);
	}
}

/*
* Main function of the program.
* @param argc Number of command-line arguments.
* @param argv Array of command-line arguments.
* @return Program exit status (0 = success).
*/
int main(int argc, char *argv[]) {
	int keys[] = {18, 41, 22, 44, 59, 32, 31, 73, 26, 56};
	int num_keys = sizeof(keys) / sizeof(int);

	HashTable tables[3];

	for (int m = 0; m < 3; m++) {
		initialize_table(&tables[m], TABLE_SIZE);

		if (is_empty(&tables[m]))
			printf("Table is initially empty.\n");

		for (int i = 0; i < num_keys; i++)
			insert_key(&tables[m], keys[i], (Method)m);

		printf("\n=== %s ===\n", method_names[m]);
		print_table(&tables[m]);
		printf("Collisions: %d\n", tables[m].collisions);

		if (is_full(&tables[m]))
			printf("The table is full.\n");

		HashTable* resized = resize_table_dynamic(&tables[m], tables[m].size * 2 + 1, (Method)m);
		printf("Table after dynamic resize:\n");
		print_table(resized);

		free(tables[m].table);
		tables[m] = *resized;
		free(resized);

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

		int del_key = 44;
		if (delete_key(&tables[m], del_key, (Method)m))
			printf("Key %d deleted successfully.\n", del_key);

		printf("Table after deletion:\n");
		print_table(&tables[m]);
	}

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
	printf(">>> Worst method (most collisions): %s (%d collisions)\n\n", method_names[worst_method], max);

	for (int m = 0; m < 3; m++) {
		clear_table(&tables[m]);

		if (is_empty(&tables[m]))
			printf("Table %d is empty after clearing.\n", m);
		else
			printf("Error: Table %d is not empty after clearing.\n", m);

		free(tables[m].table);
	}

	return 0;
}
