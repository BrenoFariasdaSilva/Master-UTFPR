/*
 * Description: This program implements a hash table with three collision resolution methods:
 * linear probing, quadratic probing, and double hashing. It initializes a hash table,
 * inserts a set of string keys, and counts collisions for each method. It also demonstrates
 * search, deletion, clearing, and reports the number of valid keys. Finally, it identifies
 * the best and worst probing methods based on collision counts.
 * Author: Breno Farias da Silva.
 * Date: 07/06/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf, strcmp
#include <stdlib.h> // malloc, free
#include <string.h> // strcmp, strcpy

#define TABLE_SIZE 13 // Prime number for better hash distribution

/*
 * Enumeration representing collision resolution strategies.
 */
typedef enum { LINEAR, QUADRATIC, DOUBLE_HASH } Method;

/*
 * Human-readable names for each probing method.
 */
const char* method_names[] = {
	"Linear Probing",
	"Quadratic Probing",
	"Double Hashing"
};

/*
* Hash table structure containing the table and collision count.
*/
typedef struct {
	char* table[TABLE_SIZE];
	int collisions;
} HashTable;

/*
* Hash function using the djb2 algorithm.
* @param str The input string.
* @return The computed hash as an unsigned long.
*/
unsigned long hash_string(const char *str) {
	unsigned long hash = 5381;
	int c;
	while ((c = *str++))
		hash = ((hash << 5) + hash) + c; // hash * 33 + c
	return hash;
}

/*
* Computes the primary hash index.
* @param key The string key.
* @return Index in the hash table.
*/
int primary_hash(const char* key) {
	return (int)(hash_string(key) % TABLE_SIZE);
}

/*
* Computes the secondary hash for double hashing.
* @param key The string key.
* @return Step size for double hashing.
*/
int secondary_hash(const char* key) {
	return 7 - (int)(hash_string(key) % 7);
}

/*
* Computes index using linear probing.
* @param key The string key.
* @param i The attempt number.
* @return The computed index.
*/
int linear_probing(const char* key, int i) {
	return (primary_hash(key) + i) % TABLE_SIZE;
}

/*
* Computes index using quadratic probing.
* @param key The string key.
* @param i The attempt number.
* @return The computed index.
*/
int quadratic_probing(const char* key, int i) {
	int c1 = 1;
	int c2 = 3;
	return (primary_hash(key) + c1 * i + c2 * i * i) % TABLE_SIZE;
}

/*
* Computes index using double hashing.
* @param key The string key.
* @param i The attempt number.
* @return The computed index.
*/
int double_hashing(const char* key, int i) {
	return (primary_hash(key) + i * secondary_hash(key)) % TABLE_SIZE;
}

/*
* Initializes the hash table.
* @param table Pointer to the hash table.
*/
void initialize_table(HashTable* table) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		table->table[i] = NULL;
	}
	table->collisions = 0;
}

/*
* Allocates and copies a key string.
* @param key The string key.
* @return Pointer to the copied key.
*/
char* copy_key(const char* key) {
	if (key == NULL) return NULL;
	char* copy = malloc(strlen(key) + 1);
	if (copy != NULL) strcpy(copy, key);
	return copy;
}

/*
* Frees the memory of a key.
* @param key Pointer to the string key.
*/
void free_key(char* key) {
	if (key != NULL) free(key);
}

/*
* Compares two keys.
* @param a First key.
* @param b Second key.
* @return 1 if equal, 0 otherwise.
*/
int compare_keys(const char* a, const char* b) {
	if (a == NULL || b == NULL) return 0;
	return strcmp(a, b) == 0;
}

/*
* Inserts a key into the hash table.
* @param table Pointer to the hash table.
* @param key The string key to insert.
* @param method Collision resolution method.
* @return 1 if successful, 0 otherwise.
*/
int insert_key(HashTable* table, const char* key, Method method) {
	int index;
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (method == LINEAR)
			index = linear_probing(key, i);
		else if (method == QUADRATIC)
			index = quadratic_probing(key, i);
		else
			index = double_hashing(key, i);

		if (table->table[index] == NULL || table->table[index] == (char*)(-1)) {
			table->table[index] = copy_key(key);
			return 1;
		} else {
			table->collisions++;
		}
	}
	return 0;
}

/*
* Searches for a key in the hash table.
* @param table Pointer to the hash table.
* @param key The string key to search.
* @param method Collision resolution method.
* @return Index of the key if found, -1 otherwise.
*/
int search_key(HashTable* table, const char* key, Method method) {
	int index;
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (method == LINEAR)
			index = linear_probing(key, i);
		else if (method == QUADRATIC)
			index = quadratic_probing(key, i);
		else
			index = double_hashing(key, i);

		if (table->table[index] == NULL)
			return -1;
		if (compare_keys(table->table[index], key))
			return index;
	}
	return -1;
}

/*
* Deletes a key from the table.
* @param table Pointer to the hash table.
* @param key The string key to delete.
* @param method Collision resolution method.
* @return 1 if deleted, 0 if not found.
*/
int delete_key(HashTable* table, const char* key, Method method) {
	int index;
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (method == LINEAR)
			index = linear_probing(key, i);
		else if (method == QUADRATIC)
			index = quadratic_probing(key, i);
		else
			index = double_hashing(key, i);

		if (table->table[index] == NULL)
			return 0;
		if (compare_keys(table->table[index], key)) {
			free_key(table->table[index]);
			table->table[index] = (char*)(-1);
			return 1;
		}
	}
	return 0;
}

/*
* Checks if the table is full.
* @param table Pointer to the hash table.
* @return 1 if full, 0 otherwise.
*/
int is_full(HashTable* table) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (table->table[i] == NULL || table->table[i] == (char*)(-1))
			return 0;
	}
	return 1;
}

/*
* Checks if the table is empty.
* @param table Pointer to the hash table.
* @return 1 if empty, 0 otherwise.
*/
int is_empty(HashTable* table) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (table->table[i] != NULL && table->table[i] != (char*)(-1))
			return 0;
	}
	return 1;
}

/*
* Clears the hash table, freeing all keys.
* @param table Pointer to the hash table.
*/
void clear_table(HashTable* table) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (table->table[i] != NULL && table->table[i] != (char*)(-1))
			free_key(table->table[i]);
		table->table[i] = NULL;
	}
	table->collisions = 0;
}

/*
* Prints the current state of the hash table.
* @param table Pointer to the hash table.
*/
void print_table(HashTable* table) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (table->table[i] == NULL)
			printf("[%2d] -\n", i);
		else if (table->table[i] == (char*)(-1))
			printf("[%2d] *\n", i);
		else
			printf("[%2d] %s\n", i, table->table[i]);
	}
}

/*
* Counts total valid (non-deleted) keys in the table.
* @param table Pointer to the hash table.
* @return Number of valid keys.
*/
int total_keys(HashTable* table) {
	int count = 0;
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (table->table[i] != NULL && table->table[i] != (char*)(-1))
			count++;
	}
	return count;
}

int main() {
	char* keys[] = {"apple", "banana", "grape", "orange", "lemon", "melon", "berry", "kiwi", "mango", "pear"};
	int num_keys = sizeof(keys) / sizeof(char*);
	HashTable tables[3];

	for (int m = 0; m < 3; m++) {
		initialize_table(&tables[m]);

		for (int i = 0; i < num_keys; i++)
			insert_key(&tables[m], keys[i], (Method)m);

		printf("\n=== %s ===\n", method_names[m]);
		print_table(&tables[m]);
		printf("Collisions: %d\n", tables[m].collisions);
		printf("Valid keys in table: %d\n", total_keys(&tables[m]));

		char* test_keys[] = {"grape", "pineapple"};
		for (int t = 0; t < 2; t++) {
			int found_index = search_key(&tables[m], test_keys[t], (Method)m);
			if (found_index != -1)
					printf("Key %s found at index %d.\n", test_keys[t], found_index);
			else
					printf("Key %s not found.\n", test_keys[t]);
		}

		char* del_key = "orange";
		if (delete_key(&tables[m], del_key, (Method)m))
			printf("Key %s deleted successfully.\n", del_key);

		printf("Table after deletion:\n");
		print_table(&tables[m]);

		clear_table(&tables[m]);
		printf("Table cleared.\n");
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
	printf(">>> Worst method (most collisions): %s (%d collisions)\n", method_names[worst_method], max);

	return 0;
}
