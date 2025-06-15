/*
 * Description: Simple test for AVL tree implementation.
 * Author: Breno Farias da Silva.
 * Date: 14/06/2025.
 */

// Compile: gcc main.c avl.c -o main
// Run: ./main

#include <stdio.h>
#include "avl.h"

/*
 * Main function of the program.
 * argc: number of arguments passed on program call.
 * argv: array with the arguments passed on program call.
 * return: program execution status (0: no errors, otherwise: error code).
 */
int main(int argc, char *argv[]) {
	Node* root = avl_create();

	// Insert elements
	root = avl_insert(root, 20);
	root = avl_insert(root, 10);
	root = avl_insert(root, 30);
	root = avl_insert(root, 5);
	root = avl_insert(root, 15);
	root = avl_insert(root, 25);
	root = avl_insert(root, 35);

	printf("AVL Tree height: %d\n", avl_height(root));
	printf("AVL Tree size: %d\n", avl_size(root));

	printf("\nPreorder traversal:\n");
	avl_preorder(root);
	printf("\nInorder traversal:\n");
	avl_inorder(root);
	printf("\nPostorder traversal:\n");
	avl_postorder(root);
	printf("\n");

	// Remove some nodes
	root = avl_remove(root, 10);
	root = avl_remove(root, 30);

	printf("\nAfter removing 10 and 30:\n");
	printf("AVL Tree height: %d\n", avl_height(root));
	printf("AVL Tree size: %d\n", avl_size(root));

	printf("\nInorder traversal:\n");
	avl_inorder(root);
	printf("\n");

	// Test avl_find_min and avl_find_max
	Node* min = avl_find_min(root);
	Node* max = avl_find_max(root);
	printf("\nMinimum element: %d\n", min ? min->data : -1);
	printf("Maximum element: %d\n", max ? max->data : -1);

	// Test avl_is_balanced
	printf("\nIs tree balanced? %s\n", avl_is_balanced(root) ? "Yes" : "No");

	// Test avl_successor and avl_predecessor
	ElementType key = 25;
	Node* succ = avl_successor(root, key);
	Node* pred = avl_predecessor(root, key);
	printf("\nSuccessor of %d: %d\n", key, succ ? succ->data : -1);
	printf("Predecessor of %d: %d\n", key, pred ? pred->data : -1);

	// Test avl_select (k-th smallest element)
	int k = 2;
	Node* kth = avl_select(root, k);
	printf("\n%d-th smallest element: %d\n", k, kth ? kth->data : -1);

	// Test avl_rank
	ElementType rank_key = 25;
	int rank = avl_rank(root, rank_key);
	printf("Rank of %d: %d\n", rank_key, rank);

	// Test avl_to_array
	int size = avl_size(root);
	ElementType array[size];
	avl_to_array(root, array);
	printf("\nTree as sorted array: ");
	for (int i = 0; i < size; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");

	// Test avl_from_sorted_array
	Node* new_tree = avl_from_sorted_array(array, 0, size - 1);
	printf("\nTree built from sorted array (inorder traversal):\n");
	avl_inorder(new_tree);
	printf("\n");

	// Test avl_print_tree
	printf("\nTree structure:\n");
	avl_print_tree(root, 0);

	// Test avl_leaf_count
	int leaf_count = avl_leaf_count(root);
	printf("\nNumber of leaf nodes: %d\n", leaf_count);

	// Test avl_depth
	ElementType depth_key = 25;
	int depth = avl_depth(root, depth_key);
	printf("Depth of %d: %d\n", depth_key, depth);

	// Destroy trees
	avl_destroy(&root);
	avl_destroy(&new_tree);

	if (root == NULL && new_tree == NULL) {
		printf("\nTrees successfully destroyed.\n");
	}

	return 0;
}
