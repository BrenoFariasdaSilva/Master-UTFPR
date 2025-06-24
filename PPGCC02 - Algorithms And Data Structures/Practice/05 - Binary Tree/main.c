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

	Node* minNode = bst_find_min(root);
	printf("\nMinimum value in BST: %d\n", minNode ? minNode->data : -1);

	Node* maxNode = bst_find_max(root);
	printf("Maximum value in BST: %d\n", maxNode ? maxNode->data : -1);

	ElementType testData = 15;
	Node* succNode = bst_successor(root, testData);
	printf("Successor of %d: %d\n", testData, succNode ? succNode->data : -1);

	Node* predNode = bst_predecessor(root, testData);
	printf("Predecessor of %d: %d\n", testData, predNode ? predNode->data : -1);

	bool foundIter = bst_contains_iterative(root, 25);
	printf("Contains 25 (iterative search): %s\n", foundIter ? "Yes" : "No");

	bool foundRec = bst_contains(root, 25);
	printf("Contains 25 (recursive search): %s\n", foundRec ? "Yes" : "No");

	int depth = bst_depth(root, 25);
	printf("Depth of 25: %d\n", depth);

	bool validBST = bst_is_valid(root);
	printf("Is valid BST: %s\n", validBST ? "Yes" : "No");

	printf("\nStructured print of BST:\n");
	bst_print_tree(root, 0);

	int k = 3;
	Node* kthNode = bst_select(root, k);
	printf("\n%d-th smallest element: %d\n", k, kthNode ? kthNode->data : -1);

	int rank = bst_rank(root, 25);
	printf("Rank of 25: %d\n", rank);

	ElementType array[bst_size(root)];
	bst_to_array(root, array);
	printf("BST to sorted array: ");
	for (int i = 0; i < bst_size(root); i++)
		printf("%d ", array[i]);
	printf("\n");

	// Build BST from sorted array
	Node* newRoot = bst_from_sorted_array(array, 0, bst_size(root) - 1);
	printf("\nBST built from sorted array (inorder traversal):\n");
	bst_inorder(newRoot);
	printf("\n");

	int leafCount = bst_leaf_count(root);
	int internalCount = bst_internal_node_count(root);
	printf("\nLeaf nodes count: %d\n", leafCount);
	printf("Internal nodes count: %d\n", internalCount);

	// Test bst_clone
	Node* clone = bst_clone(root);
	printf("\nCloned BST inorder traversal:\n");
	bst_inorder(clone);
	printf("\n");

	// Test bst_is_balanced
	printf("Is original BST balanced? %s\n", bst_is_balanced(root) ? "Yes" : "No");
	printf("Is cloned BST balanced? %s\n", bst_is_balanced(clone) ? "Yes" : "No");

	// Test bst_find_path
	ElementType path[20];
	ElementType target = 15;
	int path_len = bst_find_path(root, target, path, 20);
	if (path_len > 0) {
		printf("Path to %d: ", target);
		for (int i = 0; i < path_len; i++)
			printf("%d ", path[i]);
		printf("\n");
	} else {
		printf("Element %d not found in BST.\n", target);
	}

	// Test bst_clear on clone
	bst_clear(&clone);
	printf("Cloned BST cleared. Is clone NULL? %s\n", clone == NULL ? "Yes" : "No");

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
	bst_destroy(&newRoot);

	if (root == NULL && newRoot == NULL) {
		printf("Trees successfully destroyed.\n");
	}

	return 0;
}
