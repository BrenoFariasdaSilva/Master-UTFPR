/*
 * Description: Main program to test B-Tree implementation.
 * Author: Breno Farias da Silva.
 * Date: 24/06/2025.
 */

// Compile: gcc main.c b_tree.c -o main
// Run: ./main

#include <stdio.h>
#include "b_tree.h"

/*
 * Main function of the program.
 * argc: number of arguments passed on program call.
 * argv: array with the arguments passed on program call.
 * return: program execution status (0: no errors, otherwise: error code).
 */
int main(int argc, char *argv[]) {
	printf("\nB-Tree Implementation\n\n");
   BTree *tree = btree_create();

   int keys[] = {10, 20, 5, 6, 12, 30, 7, 17};
   int n = sizeof(keys) / sizeof(keys[0]);

   for (int i = 0; i < n; i++) {
		printf("Inserting key %d into the B-Tree...\n", keys[i]);
      btree_insert(tree, keys[i]);
		// print the b tree by levels after each insertion
		btree_print_levels(tree->root);
		printf("\n");
   }

   printf("Traversal of the constructed B-Tree (in ascending order):\n");
   btree_traverse(tree->root);
   printf("\n\n");

   printf("Level by level print of the constructed B-Tree:\n");
   btree_print_levels(tree->root);
   printf("\n");

   int key_to_search = 6;
   BTreeNode *res = btree_search(tree->root, key_to_search);
   if (res != NULL) {
      printf("Search result: Key %d found in the B-Tree.\n\n", key_to_search);
   } else {
      printf("Search result: Key %d not found in the B-Tree.\n\n", key_to_search);
   }

   int key_to_delete = 6;
   printf("Deleting key %d from the B-Tree...\n\n", key_to_delete);
   btree_delete(tree, key_to_delete);

   printf("Traversal of the B-Tree after deletion:\n");
   btree_traverse(tree->root);
   printf("\n\n");

   printf("Level by level print of the B-Tree after deletion:\n");
   btree_print_levels(tree->root);

   return 0;
}
