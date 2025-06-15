/*
 * Description: Simple test for Binary Tree implementation.
 * Author: Breno Farias da Silva.
 * Date: 15/06/2025.
 */

// Compile: gcc main.c binary_tree.c -o main
// Run: ./main

#include <stdio.h>
#include "binary_tree.h"

/*
 * Main function of the program.
 * argc: number of arguments passed on program call.
 * argv: array with the arguments passed on program call.
 * return: program execution status (0: no errors, otherwise: error code).
 */
int main(int argc, char *argv[]) {
	Node* root = bst_create();

	// Insert elements
	root = bst_insert(root, 20);
	root = bst_insert(root, 10);
	root = bst_insert(root, 30);
	root = bst_insert(root, 5);
	root = bst_insert(root, 15);
	root = bst_insert(root, 25);
	root = bst_insert(root, 35);

	printf("Binary Tree height: %d\n", bst_height(root));
	printf("Binary Tree size: %d\n", bst_size(root));

	printf("\nPreorder traversal:\n");
	bst_preorder(root);
	printf("\nInorder traversal:\n");
	bst_inorder(root);
	printf("\nPostorder traversal:\n");
	bst_postorder(root);
	printf("\n");

	// Remove some nodes
	root = bst_remove(root, 10);
	root = bst_remove(root, 30);

	printf("\nAfter removing 10 and 30:\n");
	printf("Binary Tree height: %d\n", bst_height(root));
	printf("Binary Tree size: %d\n", bst_size(root));

	printf("\nInorder traversal:\n");
	bst_inorder(root);
	printf("\n");

	bst_destroy(&root);

	if (root == NULL) {
		printf("Tree successfully destroyed.\n");
	}

	return 0;
}
