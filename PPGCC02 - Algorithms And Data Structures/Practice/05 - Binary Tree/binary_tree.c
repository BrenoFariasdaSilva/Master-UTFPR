/*
* Description: Implementation of Binary Search Tree (BST) functions.
* Author: Breno Farias da Silva.
* Date: 15/06/2025.
*/

#include "binary_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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

/*
* Returns the node with the minimum value in the BST.
*/
Node* bst_find_min(Node* root) {
	if (root == NULL) return NULL;
	Node* current = root;
	while (current->left != NULL)
		current = current->left;
	return current;
}

/*
* Returns the node with the maximum value in the BST.
*/
Node* bst_find_max(Node* root) {
	if (root == NULL) return NULL;
	Node* current = root;
	while (current->right != NULL)
		current = current->right;
	return current;
}

/*
* Returns the successor of a given element in the BST.
*/
Node* bst_successor(Node* root, ElementType data) {
	Node* succ = NULL;
	while (root != NULL) {
		if (data < root->data) {
			succ = root;
			root = root->left;
		} else {
			root = root->right;
		}
	}
	return succ;
}

/*
* Returns the predecessor of a given element in the BST.
*/
Node* bst_predecessor(Node* root, ElementType data) {
	Node* pred = NULL;
	while (root != NULL) {
		if (data > root->data) {
			pred = root;
			root = root->right;
		} else {
			root = root->left;
		}
	}
	return pred;
}

/*
* Checks if an element exists in the BST using iterative approach.
*/
bool bst_contains_iterative(Node* root, ElementType data) {
	while (root != NULL) {
		if (data == root->data)
			return true;
		else if (data < root->data)
			root = root->left;
		else
			root = root->right;
	}
	return false;
}

/*
* Returns the depth (level) of an element in the BST.
*/
int bst_depth(Node* root, ElementType data) {
	int depth = 0;
	while (root != NULL) {
		if (data == root->data)
			return depth;
		else if (data < root->data)
			root = root->left;
		else
			root = root->right;
		depth++;
	}
	return -1; // Not found
}

/*
* Helper function for bst_is_valid, checks BST validity within range.
*/
static bool is_valid_bst_util(Node* node, ElementType min, ElementType max) {
	if (node == NULL) return true;

	if (node->data <= min || node->data >= max)
		return false;

	return is_valid_bst_util(node->left, min, node->data) &&
		   is_valid_bst_util(node->right, node->data, max);
}

/*
* Validates if a binary tree is a BST.
*/
bool bst_is_valid(Node* root) {
	return is_valid_bst_util(root, INT_MIN, INT_MAX);
}

/*
* Prints the BST in hierarchical rotated form.
*/
void bst_print_tree(Node* root, int space) {
	if (root == NULL) return;

	space += 5;

	bst_print_tree(root->right, space);

	printf("\n");
	for (int i = 5; i < space; i++)
		printf(" ");
	printf("%d\n", root->data);

	bst_print_tree(root->left, space);
}

/*
* Helper function to calculate size of left subtree.
*/
static int bst_size_static(Node* root) {
	if (root == NULL) return 0;
	return 1 + bst_size_static(root->left) + bst_size_static(root->right);
}

/*
* Returns the k-th smallest element in the BST (1-based index).
*/
Node* bst_select(Node* root, int k) {
	if (root == NULL || k <= 0) return NULL;

	int left_size = bst_size_static(root->left);

	if (k == left_size + 1)
		return root;
	else if (k <= left_size)
		return bst_select(root->left, k);
	else
		return bst_select(root->right, k - left_size - 1);
}

/*
* Returns the rank of an element in the BST.
*/
int bst_rank(Node* root, ElementType data) {
	if (root == NULL) return 0;

	if (data < root->data)
		return bst_rank(root->left, data);
	else if (data > root->data)
		return 1 + bst_size_static(root->left) + bst_rank(root->right, data);
	else
		return bst_size_static(root->left);
}

/*
* Converts BST to sorted array.
* Uses static variable for index.
*/
void bst_to_array(Node* root, ElementType array[]) {
	static int index = 0;
	if (root == NULL) return;

	bst_to_array(root->left, array);
	array[index++] = root->data;
	bst_to_array(root->right, array);

	// Reset index after full traversal (when called initially)
	if (root->left == NULL && root->right == NULL)
		index = 0;
}

/*
* Constructs balanced BST from sorted array.
*/
Node* bst_from_sorted_array(ElementType array[], int start, int end) {
	if (start > end) return NULL;

	int mid = (start + end) / 2;
	Node* node = create_node(array[mid]);

	node->left = bst_from_sorted_array(array, start, mid - 1);
	node->right = bst_from_sorted_array(array, mid + 1, end);

	return node;
}

/*
* Counts leaf nodes in the BST.
*/
int bst_leaf_count(Node* root) {
	if (root == NULL) return 0;
	if (root->left == NULL && root->right == NULL) return 1;
	return bst_leaf_count(root->left) + bst_leaf_count(root->right);
}

/*
* Counts internal (non-leaf) nodes in the BST.
*/
int bst_internal_node_count(Node* root) {
	if (root == NULL || (root->left == NULL && root->right == NULL)) return 0;
	return 1 + bst_internal_node_count(root->left) + bst_internal_node_count(root->right);
}

/*
* Frees all nodes and sets root pointer to NULL.
*/
void bst_clear(Node** root) {
	if (root == NULL || *root == NULL) return;
	bst_clear(&((*root)->left));
	bst_clear(&((*root)->right));
	free(*root);
	*root = NULL;
}

/*
* Helper function to clone nodes recursively.
*/
static Node* clone_node(Node* root) {
	if (root == NULL) return NULL;

	Node* new_node = (Node*)malloc(sizeof(Node));
	if (!new_node) {
		fprintf(stderr, "Memory allocation failed in bst_clone\n");
		exit(EXIT_FAILURE);
	}

	new_node->data = root->data;
	new_node->left = clone_node(root->left);
	new_node->right = clone_node(root->right);

	return new_node;
}

/*
* Creates a deep copy (clone) of BST.
*/
Node* bst_clone(Node* root) {
	return clone_node(root);
}

/*
* Helper function that returns height and balanced status.
* Returns -1 if unbalanced, else returns height.
*/
static int check_balanced(Node* root) {
	if (root == NULL) return 0;

	int left_height = check_balanced(root->left);
	if (left_height == -1) return -1;

	int right_height = check_balanced(root->right);
	if (right_height == -1) return -1;

	if (abs(left_height - right_height) > 1) return -1;

	return (left_height > right_height ? left_height : right_height) + 1;
}

/*
* Checks if tree is balanced.
*/
bool bst_is_balanced(Node* root) {
	return check_balanced(root) != -1;
}

/*
* Finds the path to the data element, storing path in array.
* Returns the length of the path found, or 0 if not found or if array is too small.
*/
int bst_find_path(Node* root, ElementType data, ElementType path[], int max_length) {
	int length = 0;
	Node* current = root;

	while (current != NULL && length < max_length) {
		path[length++] = current->data;
		if (data == current->data) {
			return length;
		} else if (data < current->data) {
			current = current->left;
		} else {
			current = current->right;
		}
	}

	return 0; // If not found or exceeded max_length
}