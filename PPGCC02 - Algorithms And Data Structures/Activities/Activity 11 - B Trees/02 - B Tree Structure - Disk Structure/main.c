/*
 * File: main.c
 * Description: Entry point to test and demonstrate the persistent B-Tree implementation.
 *              This program performs the following:
 *              - Creation of a persistent B-Tree stored on disk.
 *              - Insertion of initial keys into the B-Tree.
 *              - Display of the B-Tree content using both in-order and level-order traversals.
 *              - Closure and reopening of the B-Tree from disk to validate persistence.
 *              - Comparison of the original and reopened trees to ensure data integrity.
 *              - Additional insertion and deletion operations after reopening.
 *              - Final display of the updated tree and proper resource cleanup.
 *
 * Author: Breno Farias da Silva
 * Date: 29/06/2025
 *
 * Compilation:
 *   gcc main.c b_tree.c -o main
 *
 * Usage:
 *   ./main
 */

#include <stdio.h> // For printf
#include "b_tree.h" // BTree structure and related functions

/**
 * Main entry point of the program.
 *
 * This function serves as a comprehensive test harness for the persistent B-Tree:
 * 1. Creates or opens a B-Tree file on disk.
 * 2. Inserts a predefined set of keys into the B-Tree, displaying the tree after each insertion.
 * 3. Performs in-order traversal to print sorted keys after initial insertions.
 * 4. Closes the B-Tree to simulate program termination.
 * 5. Reopens the B-Tree from disk and verifies that the data was correctly persisted.
 * 6. Compares the reopened tree with the original to confirm structural and key equality.
 * 7. Performs further insertion and deletion operations on the reopened tree.
 * 8. Displays the final state of the B-Tree.
 * 9. Properly closes and cleans up all allocated resources before exiting.
 *
 * @param argc Number of command-line arguments (unused).
 * @param argv Array of command-line argument strings (unused).
 * @return Exit status code: 0 on successful execution.
 */
int main(int argc, char *argv[]) {
   printf("\n=== Persistent B-Tree Test ===\n");

   // Display the size of each BTreeNode struct for informational purposes.
   printf("Node size: %lu bytes\n", sizeof(BTreeNode));

   // === STEP 1: OPEN OR CREATE THE B-TREE AND INSERT INITIAL KEYS ===
   BTree *tree = btree_open(BTREE_FILENAME);

   // Predefined keys to insert into the B-Tree.
   int keys[] = {10, 20, 5, 6, 12, 30, 7, 17};
   int n = sizeof(keys) / sizeof(keys[0]);

   for (int i = 0; i < n; i++) {
      printf("Inserting key %d into the B-Tree...\n", keys[i]);
      btree_insert(tree, keys[i]);

      // After each insertion, display the tree in level-order to observe structure changes.
      printf("Level-order traversal after insertion:\n");
      btree_print_level_order(tree);
      printf("\n");
   }

   // Display the B-Tree contents in sorted order (in-order traversal).
   printf("In-order traversal after initial insertions:\n");
   btree_traverse(tree);
   printf("\n");

   // Final snapshot of the B-Tree before closing.
   printf("Final level-order traversal before closing:\n");
   btree_print_level_order(tree);
   printf("\n");

   // Close the B-Tree to simulate program termination and flush data to disk.
   btree_close(tree);

   // === STEP 2: REOPEN THE B-TREE FROM DISK AND VALIDATE PERSISTENCE ===
   printf("\n=== Reopening the B-Tree from Disk ===\n");

   // Reopen the B-Tree, loading the persisted data from disk.
   BTree *new_tree = btree_open(BTREE_FILENAME);

   // Display the reopened tree to verify the data.
   printf("In-order traversal after reopening:\n");
   btree_traverse(new_tree);
   printf("\n");

   printf("Level-order traversal after reopening:\n");
   btree_print_level_order(new_tree);
   printf("\n");

   // === STEP 2.1: COMPARE ORIGINAL AND REOPENED TREES FOR EQUALITY ===
   tree = btree_open(BTREE_FILENAME); // Reopen original tree for comparison

   int equal = btree_are_equal(tree, new_tree);
   printf("Are the two B-Trees equal after reopening? %s\n", equal ? "Yes" : "No");

   btree_close(tree);

   // === STEP 3: PERFORM MODIFICATIONS ON THE REOPENED TREE ===
   int key_to_insert = 25;
   int key_to_delete = 10;

   printf("Inserting key %d into reopened B-Tree...\n", key_to_insert);
   btree_insert(new_tree, key_to_insert);

   printf("Deleting key %d from reopened B-Tree...\n", key_to_delete);
   btree_delete(new_tree, key_to_delete);

   // Display the B-Tree after modifications.
   printf("In-order traversal after modifications:\n");
   btree_traverse(new_tree);
   printf("\n");

   printf("Level-order traversal after modifications:\n");
   btree_print_level_order(new_tree);
   printf("\n");

   // === STEP 4: CLEANUP AND FINALIZATION ===
   btree_close(new_tree);

   printf("=== Test Completed ===\n");
   return 0;
}
