/*
* Description: Implementation of AVL tree functions.
* Author: Breno Farias da Silva.
* Date: 14/06/2025.
*/

#include "avl.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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

/*
* Finds the minimum element in the AVL tree.
* If the tree is empty, returns NULL.
*/
Node* avl_find_min(Node* root) {
	if (root == NULL) return NULL;
	Node* current = root;
	while (current->left != NULL)
		current = current->left;
	return current;
}

/*
* Finds the maximum element in the AVL tree.
* If the tree is empty, returns NULL.
*/
Node* avl_find_max(Node* root) {
	if (root == NULL) return NULL;
	Node* current = root;
	while (current->right != NULL)
		current = current->right;
	return current;
}

/*
* Checks if the AVL tree is balanced.
* A tree is balanced if the height difference between left and right subtrees is at most 1.
*/
bool avl_is_balanced(Node* root) {
	if (root == NULL) return true;

	int balance = height(root->left) - height(root->right);
	if (balance < -1 || balance > 1)
		return false;

	return avl_is_balanced(root->left) && avl_is_balanced(root->right);
}

/*
* Finds the successor of a given element in the AVL tree.
* The successor is the smallest element greater than the given element.
* Returns NULL if no successor exists.
*/
Node* avl_successor(Node* root, ElementType data) {
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
* Finds the predecessor of a given element in the AVL tree.
* The predecessor is the largest element smaller than the given element.
* Returns NULL if no predecessor exists.
*/
Node* avl_predecessor(Node* root, ElementType data) {
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
* Returns the k-th smallest element in the AVL tree (1-based index).
* If k is invalid (<=0 or > size), returns NULL.
*/
Node* avl_select(Node* root, int k) {
	if (root == NULL || k <= 0) return NULL;
	int left_size = avl_size(root->left);

	if (k == left_size + 1)
		return root;
	else if (k <= left_size)
		return avl_select(root->left, k);
	else
		return avl_select(root->right, k - left_size - 1);
}

/*
* Returns the rank of an element in the AVL tree.
* The rank is the number of elements less than the given element.
* If the element does not exist, returns the rank it would have if it were inserted.
*/
int avl_rank(Node* root, ElementType data) {
	if (root == NULL) return 0;
	if (data < root->data)
		return avl_rank(root->left, data);
	else if (data > root->data)
		return 1 + avl_size(root->left) + avl_rank(root->right, data);
	else
		return avl_size(root->left);
}

/*
* Converts the AVL tree to a sorted array.
* The array must be pre-allocated with enough space.
*/
void avl_to_array(Node* root, ElementType array[]) {
	static int index = 0;
	if (root == NULL) return;
	avl_to_array(root->left, array);
	array[index++] = root->data;
	avl_to_array(root->right, array);
	if (root->height == 0) index = 0; // Reset after full traversal
}

/*
* Constructs an AVL tree from a sorted array.
* The array must be sorted in ascending order.
*/
Node* avl_from_sorted_array(ElementType array[], int start, int end) {
	if (start > end) return NULL;

	int mid = (start + end) / 2;
	Node* node = create_node(array[mid]);

	node->left = avl_from_sorted_array(array, start, mid - 1);
	node->right = avl_from_sorted_array(array, mid + 1, end);

	node->height = 1 + max(height(node->left), height(node->right));

	return node;
}

/*
* Prints the AVL tree in a hierarchical format.
* The tree is printed with right children on top and left children below.
*/
void avl_print_tree(Node* root, int space) {
	if (root == NULL) return;

	space += 5;
	avl_print_tree(root->right, space);

	printf("\n");
	for (int i = 5; i < space; i++)
		printf(" ");
	printf("%d\n", root->data);

	avl_print_tree(root->left, space);
}

/*
* Counts the number of leaf nodes in the AVL tree.
* A leaf node is a node with no children.
*/
int avl_leaf_count(Node* root) {
	if (root == NULL) return 0;
	if (root->left == NULL && root->right == NULL) return 1;
	return avl_leaf_count(root->left) + avl_leaf_count(root->right);
}

/*
* Returns the depth of a specific element in the AVL tree.
* The depth is the number of edges from the root to the node containing the element.
*/
int avl_depth(Node* root, ElementType data) {
	int depth = 0;
	while (root != NULL) {
		if (data == root->data) return depth;
		else if (data < root->data) root = root->left;
		else root = root->right;
		depth++;
	}
	return -1; // Not found
}

/*
* Clears the AVL tree by freeing all nodes and setting root to NULL.
* root: pointer to the root node pointer.
* return: NULL after clearing the tree.
*/
Node* avl_clear(Node** root) {
	if (root == NULL || *root == NULL) return NULL;

	avl_destroy(root);
	return NULL;
}

/*
* Creates a deep copy (clone) of the AVL tree.
* root: pointer to the root node of the tree to copy.
* return: pointer to the root node of the new cloned tree.
*/
Node* avl_clone(Node* root) {
	if (root == NULL) return NULL;

	Node* new_node = create_node(root->data);
	new_node->left = avl_clone(root->left);
	new_node->right = avl_clone(root->right);
	new_node->height = root->height;

	return new_node;
}

/*
* Helper function to validate BST properties within min and max bounds.
*/
static bool is_bst_util(Node* node, ElementType min, ElementType max) {
	if (node == NULL) return true;
	if (node->data <= min || node->data >= max) return false;
	return is_bst_util(node->left, min, node->data) && is_bst_util(node->right, node->data, max);
}

/*
* Validates if the AVL tree satisfies the BST properties and balance conditions.
* root: pointer to the root node of the tree.
* return: true if valid AVL tree, false otherwise.
*/
bool avl_is_valid(Node* root) {
	if (root == NULL) return true;

	// Check BST property
	if (!is_bst_util(root, INT_MIN, INT_MAX))
		return false;

	// Check AVL balance
	if (!avl_is_balanced(root))
		return false;

	return true;
}

/*
* Removes the minimum element node from the AVL tree.
* root: pointer to the root node of the tree.
* return: pointer to the root node of the updated tree.
*/
Node* avl_remove_min(Node* root) {
	if (root == NULL) return NULL;
	if (root->left == NULL) {
		Node* right_subtree = root->right;
		free(root);
		return right_subtree;
	}
	root->left = avl_remove_min(root->left);

	// Update height
	root->height = 1 + max(height(root->left), height(root->right));

	// Balance node
	int balance = get_balance(root);

	if (balance > 1 && get_balance(root->left) >= 0)
		return rotate_right(root);

	if (balance > 1 && get_balance(root->left) < 0) {
		root->left = rotate_left(root->left);
		return rotate_right(root);
	}

	if (balance < -1 && get_balance(root->right) <= 0)
		return rotate_left(root);

	if (balance < -1 && get_balance(root->right) > 0) {
		root->right = rotate_right(root->right);
		return rotate_left(root);
	}

	return root;
}

/*
* Removes the maximum element node from the AVL tree.
* root: pointer to the root node of the tree.
* return: pointer to the root node of the updated tree.
*/
Node* avl_remove_max(Node* root) {
	if (root == NULL) return NULL;
	if (root->right == NULL) {
		Node* left_subtree = root->left;
		free(root);
		return left_subtree;
	}
	root->right = avl_remove_max(root->right);

	// Update height
	root->height = 1 + max(height(root->left), height(root->right));

	// Balance node
	int balance = get_balance(root);

	if (balance > 1 && get_balance(root->left) >= 0)
		return rotate_right(root);

	if (balance > 1 && get_balance(root->left) < 0) {
		root->left = rotate_left(root->left);
		return rotate_right(root);
	}

	if (balance < -1 && get_balance(root->right) <= 0)
		return rotate_left(root);

	if (balance < -1 && get_balance(root->right) > 0) {
		root->right = rotate_right(root->right);
		return rotate_left(root);
	}

	return root;
}

/*
* Counts the number of internal (non-leaf) nodes in the AVL tree.
* root: pointer to the root node of the tree.
* return: count of internal nodes.
*/
int avl_internal_node_count(Node* root) {
	if (root == NULL) return 0;
	if (root->left == NULL && root->right == NULL) return 0;
	return 1 + avl_internal_node_count(root->left) + avl_internal_node_count(root->right);
}

/*
* Returns the height balance factor of a node.
* root: pointer to the node.
* return: balance factor (height of left subtree - height of right subtree).
*/
int avl_height_balance_factor(Node* root) {
	if (root == NULL) return 0;
	return height(root->left) - height(root->right);
}

/*
* Checks if an element exists in the AVL tree using an iterative approach.
* root: pointer to the root node of the tree.
* data: element to search for.
* return: true if element exists, false otherwise.
*/
bool avl_contains_iterative(Node* root, ElementType data) {
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
* Finds the path from root to the element data.
* root: pointer to the root node.
* data: target element to find.
* path: pre-allocated array to store path elements.
* max_length: max capacity of the path array.
* return: length of path if found, 0 if not found or path exceeds max_length.
*/
int avl_find_path(Node* root, ElementType data, ElementType path[], int max_length) {
	int length = 0;
	Node* current = root;

	while (current != NULL) {
		if (length >= max_length) return 0;
		path[length++] = current->data;

		if (data == current->data)
			return length;

		if (data < current->data)
			current = current->left;
		else
			current = current->right;
	}

	return 0; // Not found
}

/*
* Performs a left rotation on the subtree rooted at *root.
* root: pointer to the root node pointer of the subtree.
*/
void avl_rotate_left(Node** root) {
	if (root == NULL || *root == NULL) return;

	Node* new_root = rotate_left(*root);
	*root = new_root;
}

/*
* Performs a right rotation on the subtree rooted at *root.
* root: pointer to the root node pointer of the subtree.
*/
void avl_rotate_right(Node** root) {
	if (root == NULL || *root == NULL) return;

	Node* new_root = rotate_right(*root);
	*root = new_root;
}

// Helper: Merge two sorted arrays into one sorted array
static void merge_sorted_arrays(ElementType arr1[], int size1, ElementType arr2[], int size2, ElementType dest[]) {
	int i = 0, j = 0, k = 0;
	while (i < size1 && j < size2) {
		if (arr1[i] < arr2[j])
			dest[k++] = arr1[i++];
		else
			dest[k++] = arr2[j++];
	}
	while (i < size1) dest[k++] = arr1[i++];
	while (j < size2) dest[k++] = arr2[j++];
}

/*
* Merges two AVL trees and returns the root of the merged AVL tree.
* Approach:
* 1. Convert both trees to sorted arrays.
* 2. Merge arrays.
* 3. Build AVL from merged sorted array.
*/
Node* avl_merge(Node* tree1, Node* tree2) {
	if (!tree1) return tree2;
	if (!tree2) return tree1;

	int size1 = avl_size(tree1);
	int size2 = avl_size(tree2);
	ElementType* arr1 = malloc(size1 * sizeof(ElementType));
	ElementType* arr2 = malloc(size2 * sizeof(ElementType));
	ElementType* merged = malloc((size1 + size2) * sizeof(ElementType));

	if (!arr1 || !arr2 || !merged) {
		free(arr1);
		free(arr2);
		free(merged);
		return NULL; // Allocation failure
	}

	avl_to_array(tree1, arr1);
	avl_to_array(tree2, arr2);
	merge_sorted_arrays(arr1, size1, arr2, size2, merged);

	Node* merged_tree = avl_from_sorted_array(merged, 0, size1 + size2 - 1);

	free(arr1);
	free(arr2);
	free(merged);

	return merged_tree;
}

/*
* Splits AVL tree into two trees: those less than key and those >= key.
* Returns via pointers leftTree and rightTree.
*/
void avl_split(Node* root, ElementType key, Node** leftTree, Node** rightTree) {
	if (!root) {
		*leftTree = NULL;
		*rightTree = NULL;
		return;
	}

	if (root->data < key) {
		// Current root goes to left tree
		Node* left_subtree = NULL;
		Node* right_subtree = NULL;
		avl_split(root->right, key, &left_subtree, &right_subtree);

		root->right = left_subtree;
		// Rebalance root if needed here (optional depending on your AVL code)
		*leftTree = root;
		*rightTree = right_subtree;
	} else {
		// Current root goes to right tree
		Node* left_subtree = NULL;
		Node* right_subtree = NULL;
		avl_split(root->left, key, &left_subtree, &right_subtree);

		root->left = right_subtree;
		// Rebalance root if needed here (optional depending on your AVL code)
		*leftTree = left_subtree;
		*rightTree = root;
	}
}