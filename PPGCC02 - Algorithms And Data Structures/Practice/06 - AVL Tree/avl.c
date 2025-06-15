/*
* Description: Implementation of AVL tree functions.
* Author: Breno Farias da Silva.
* Date: 14/06/2025.
*/

#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

/* 
* Helper function: returns max between two integers.
*/
static int max(int a, int b) {
	return (a > b) ? a : b;
}

/*
* Helper function: returns the height of a node.
* Returns -1 if node is NULL to be consistent with empty tree height.
*/
static int height(Node* node) {
	if (node == NULL) return -1;
	return node->height;
}

/*
* Creates an empty AVL tree (NULL root).
* return: NULL pointer representing an empty tree.
*/
Node* avl_create(void) {
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
	node->height = 0; // leaf node height is 0
	return node;
}

/*
* Right rotation to maintain AVL balance.
*/
static Node* rotate_right(Node* y) {
	Node* x = y->left;
	Node* T2 = x->right;

	// Perform rotation
	x->right = y;
	y->left = T2;

	// Update heights
	y->height = max(height(y->left), height(y->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;

	return x;
}

/*
* Left rotation to maintain AVL balance.
*/
static Node* rotate_left(Node* x) {
	Node* y = x->right;
	Node* T2 = y->left;

	// Perform rotation
	y->left = x;
	x->right = T2;

	// Update heights
	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;

	return y;
}

/*
* Gets the balance factor of a node.
*/
static int get_balance(Node* node) {
	if (node == NULL) return 0;
	return height(node->left) - height(node->right);
}

/*
* Inserts data into AVL tree and balances it.
*/
Node* avl_insert(Node* root, ElementType data) {
	if (root == NULL)
		return create_node(data);

	if (data < root->data)
		root->left = avl_insert(root->left, data);
	else if (data > root->data)
		root->right = avl_insert(root->right, data);
	else
		return root; // duplicate data not allowed

	// Update height
	root->height = 1 + max(height(root->left), height(root->right));

	// Check balance
	int balance = get_balance(root);

	// Left Left Case
	if (balance > 1 && data < root->left->data)
		return rotate_right(root);

	// Right Right Case
	if (balance < -1 && data > root->right->data)
		return rotate_left(root);

	// Left Right Case
	if (balance > 1 && data > root->left->data) {
		root->left = rotate_left(root->left);
		return rotate_right(root);
	}

	// Right Left Case
	if (balance < -1 && data < root->right->data) {
		root->right = rotate_right(root->right);
		return rotate_left(root);
	}

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
* Removes a node from the AVL tree and balances it.
*/
Node* avl_remove(Node* root, ElementType data) {
	if (root == NULL)
		return root;

	if (data < root->data)
		root->left = avl_remove(root->left, data);
	else if (data > root->data)
		root->right = avl_remove(root->right, data);
	else {
		// Node to delete found
		if ((root->left == NULL) || (root->right == NULL)) {
			Node* temp = root->left ? root->left : root->right;

			if (temp == NULL) {
				// No child case
				temp = root;
				root = NULL;
			} else {
				// One child case
				*root = *temp; // Copy contents
			}
			free(temp);
		} else {
			// Node with two children
			Node* temp = find_min(root->right);
			root->data = temp->data;
			root->right = avl_remove(root->right, temp->data);
		}
	}

	if (root == NULL)
		return root;

	// Update height
	root->height = 1 + max(height(root->left), height(root->right));

	// Check balance
	int balance = get_balance(root);

	// Left Left Case
	if (balance > 1 && get_balance(root->left) >= 0)
		return rotate_right(root);

	// Left Right Case
	if (balance > 1 && get_balance(root->left) < 0) {
		root->left = rotate_left(root->left);
		return rotate_right(root);
	}

	// Right Right Case
	if (balance < -1 && get_balance(root->right) <= 0)
		return rotate_left(root);

	// Right Left Case
	if (balance < -1 && get_balance(root->right) > 0) {
		root->right = rotate_right(root->right);
		return rotate_left(root);
	}

	return root;
}

/*
* Searches for data in the AVL tree.
*/
bool avl_contains(Node* root, ElementType data) {
	if (root == NULL) return false;
	if (data == root->data) return true;
	if (data < root->data)
		return avl_contains(root->left, data);
	else
		return avl_contains(root->right, data);
}

/*
* Preorder traversal: Root, Left, Right
*/
void avl_preorder(Node* root) {
	if (root == NULL) return;
	printf("%d ", root->data);
	avl_preorder(root->left);
	avl_preorder(root->right);
}

/*
* Inorder traversal: Left, Root, Right
*/
void avl_inorder(Node* root) {
	if (root == NULL) return;
	avl_inorder(root->left);
	printf("%d ", root->data);
	avl_inorder(root->right);
}

/*
* Postorder traversal: Left, Right, Root
*/
void avl_postorder(Node* root) {
	if (root == NULL) return;
	avl_postorder(root->left);
	avl_postorder(root->right);
	printf("%d ", root->data);
}

/*
* Returns height of the tree.
*/
int avl_height(Node* root) {
	if (root == NULL) return -1;
	return root->height;
}

/*
* Returns total number of nodes in the tree.
*/
int avl_size(Node* root) {
	if (root == NULL) return 0;
	return 1 + avl_size(root->left) + avl_size(root->right);
}

/*
* Frees all nodes of the tree and sets root pointer to NULL.
*/
void avl_destroy(Node** root) {
	if (root == NULL || *root == NULL) return;

	avl_destroy(&((*root)->left));
	avl_destroy(&((*root)->right));
	free(*root);
	*root = NULL;
}
