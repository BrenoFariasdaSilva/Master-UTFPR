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
 * Hash table structure including data and collision counter.
 */
typedef struct {
	int table[TABLE_SIZE];
	int collisions;
} HashTable;

/*
 * Primary hash function.
 * @param key The integer key to hash.
 * @return Index in the hash table.
 */
int primary_hash(int key) {
	return key % TABLE_SIZE;
}

/*
 * Secondary hash function used in double hashing.
 * @param key The integer key.
 * @return Step size for double hashing.
 */
int secondary_hash(int key) {
	return 7 - (key % 7); // 7 is prime smaller than TABLE_SIZE
}

/*
 * Computes the index using linear probing.
 * @param key The key to insert.
 * @param i The attempt number.
 * @return The computed index.
 */
int linear_probing(int key, int i) {
	return (primary_hash(key) + i) % TABLE_SIZE;
}

/*
 * Computes the index using quadratic probing.
 * @param key The key to insert.
 * @param i The attempt number.
 * @return The computed index.
 */
int quadratic_probing(int key, int i) {
	int c1 = 1;
	int c2 = 3;
	return (primary_hash(key) + c1 * i + c2 * i * i) % TABLE_SIZE;
}

/*
 * Computes the index using double hashing.
 * @param key The key to insert.
 * @param i The attempt number.
 * @return The computed index.
 */
int double_hashing(int key, int i) {
	return (primary_hash(key) + i * secondary_hash(key)) % TABLE_SIZE;
}

/*
 * Initializes a hash table by setting all positions to -1 (empty).
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
 * @param table Pointer to the hash table.
 * @param key The key to insert.
 * @param method The collision resolution method to use.
 * @return 1 if insertion succeeded, 0 if failed.
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

		if (table->table[index] == -1) {
			table->table[index] = key;
			return 1;
		} else {
			table->collisions++;
		}
	}
	return 0; // Table is full or collision limit exceeded
}

/*
 * Prints the contents of a hash table.
 * @param table Pointer to the hash table to print.
 */
void print_table(HashTable* table) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (table->table[i] == -1)
			printf("[%2d] -\n", i);
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
		initialize_table(&tables[m]);

		for (int i = 0; i < num_keys; i++) {
			insert_key(&tables[m], keys[i], (Method)m);
		}

		printf("\n=== %s ===\n", method_names[m]);
		print_table(&tables[m]);
		printf("Collisions: %d\n", tables[m].collisions);
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

	printf("\n>>> Best method (fewest collisions): %s (%d collisions)\n",
		method_names[best_method], min);
	printf(">>> Worst method (most collisions): %s (%d collisions)\n",
		method_names[worst_method], max);

    return 0;
}
