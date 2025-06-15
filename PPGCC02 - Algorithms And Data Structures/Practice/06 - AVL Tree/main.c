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

	avl_destroy(&root);

	if (root == NULL) {
		printf("Tree successfully destroyed.\n");
	}

	return 0;
}
