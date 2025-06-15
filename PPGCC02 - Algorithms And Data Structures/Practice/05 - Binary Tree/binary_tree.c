/*
* Description: Implementation of Binary Search Tree (BST) functions.
* Author: Breno Farias da Silva.
* Date: 15/06/2025.
*/

#include "binary_tree.h"
#include <stdio.h>
#include <stdlib.h>

/*
* Creates an empty BST (NULL root).
* return: NULL pointer representing an empty tree.
*/
Node* bst_create(void) {
	return NULL;
}

/*
* Creates a new node with given data and NULL children.
*/
static Node* create_node(ElementType data) {
	Node* node = (Node*) malloc(sizeof(Node));
	if (!node) {
		fprintf(stderr, "Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	return node;
}

/*
* Inserts data into BST maintaining BST property.
*/
Node* bst_insert(Node* root, ElementType data) {
	if (root == NULL) {
		return create_node(data);
	}

	if (data < root->data)
		root->left = bst_insert(root->left, data);
	else if (data > root->data)
		root->right = bst_insert(root->right, data);
	// Ignore duplicate values, no insertion

	return root;
}

/*
* Helper function to find the node with minimum value in a tree.
*/
static Node* find_min(Node* node) {
	Node* current = node;
	while (current && current->left != NULL)
		current = current->left;
	return current;
}

/*
* Removes a node from the BST maintaining BST property.
*/
Node* bst_remove(Node* root, ElementType data) {
	if (root == NULL)
		return root;

	if (data < root->data)
		root->left = bst_remove(root->left, data);
	else if (data > root->data)
		root->right = bst_remove(root->right, data);
	else {
		// Node to delete found
		if (root->left == NULL) {
			Node* temp = root->right;
			free(root);
			return temp;
		} 
		else if (root->right == NULL) {
			Node* temp = root->left;
			free(root);
			return temp;
		} 
		else {
			// Node with two children: get inorder successor
			Node* temp = find_min(root->right);
			root->data = temp->data;
			root->right = bst_remove(root->right, temp->data);
		}
	}

	return root;
}

/*
* Searches for data in the BST.
*/
bool bst_contains(Node* root, ElementType data) {
	if (root == NULL) return false;

	if (data == root->data) return true;

	if (data < root->data)
		return bst_contains(root->left, data);
	else
		return bst_contains(root->right, data);
}

/*
* Preorder traversal: Root, Left, Right
*/
void bst_preorder(Node* root) {
	if (root == NULL) return;
	printf("%d ", root->data);
	bst_preorder(root->left);
	bst_preorder(root->right);
}

/*
* Inorder traversal: Left, Root, Right
*/
void bst_inorder(Node* root) {
	if (root == NULL) return;
	bst_inorder(root->left);
	printf("%d ", root->data);
	bst_inorder(root->right);
}

/*
* Postorder traversal: Left, Right, Root
*/
void bst_postorder(Node* root) {
	if (root == NULL) return;
	bst_postorder(root->left);
	bst_postorder(root->right);
	printf("%d ", root->data);
}

/*
* Returns height of the tree.
* Height of empty tree is -1.
*/
int bst_height(Node* root) {
	if (root == NULL) return -1;

	int left_height = bst_height(root->left);
	int right_height = bst_height(root->right);

	return (left_height > right_height ? left_height : right_height) + 1;
}

/*
* Returns total number of nodes in the tree.
*/
int bst_size(Node* root) {
	if (root == NULL) return 0;
	return 1 + bst_size(root->left) + bst_size(root->right);
}

/*
* Frees all nodes of the tree and sets root pointer to NULL.
*/
void bst_destroy(Node** root) {
	if (root == NULL || *root == NULL) return;

	bst_destroy(&((*root)->left));
	bst_destroy(&((*root)->right));
	free(*root);
	*root = NULL;
}
