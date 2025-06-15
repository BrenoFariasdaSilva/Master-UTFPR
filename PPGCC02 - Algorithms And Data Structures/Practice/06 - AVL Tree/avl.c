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
