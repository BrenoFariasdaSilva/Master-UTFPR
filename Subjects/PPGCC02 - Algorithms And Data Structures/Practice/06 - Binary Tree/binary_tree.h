/*
* Description: Binary Search Tree (BST) interface header.
* Author: Breno Farias da Silva.
* Date: 15/06/2025.
*/

#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_

#include <stdbool.h>

typedef int ElementType;

typedef struct Node {
	ElementType data;
	struct Node* left;
	struct Node* right;
} Node;

/*
* Creates an empty BST (NULL root).
* return: NULL pointer representing an empty tree.
*/
Node* bst_create(void);

/*
* Inserts a new element into the BST.
* root: pointer to the root node of the tree.
* data: element to insert.
* return: pointer to the root node of the updated tree.
*/
Node* bst_insert(Node* root, ElementType data);

/*
* Removes an element from the BST.
* root: pointer to the root node of the tree.
* data: element to remove.
* return: pointer to the root node of the updated tree.
*/
Node* bst_remove(Node* root, ElementType data);

/*
* Checks if an element exists in the BST.
* root: pointer to the root node of the tree.
* data: element to search for.
* return: true if element exists, false otherwise.
*/
bool bst_contains(Node* root, ElementType data);

/*
* Prints the tree nodes in preorder traversal.
* root: pointer to the root node.
*/
void bst_preorder(Node* root);

/*
* Prints the tree nodes in inorder traversal.
* root: pointer to the root node.
*/
void bst_inorder(Node* root);

/*
* Prints the tree nodes in postorder traversal.
* root: pointer to the root node.
*/
void bst_postorder(Node* root);

/*
* Returns the height of the tree.
* root: pointer to the root node.
* return: height of the tree, -1 if tree is empty.
*/
int bst_height(Node* root);

/*
* Returns the total number of nodes in the tree.
* root: pointer to the root node.
* return: number of nodes in the tree.
*/
int bst_size(Node* root);

/*
* Destroys the tree, freeing all allocated memory.
* root: pointer to the root node pointer.
*/
void bst_destroy(Node** root);

/*
* Returns the node with the minimum value in the BST.
* root: pointer to the root node of the tree.
* return: pointer to the node with the smallest value, or NULL if tree is empty.
*/
Node* bst_find_min(Node* root);

/*
* Returns the node with the maximum value in the BST.
* root: pointer to the root node of the tree.
* return: pointer to the node with the largest value, or NULL if tree is empty.
*/
Node* bst_find_max(Node* root);

/*
* Returns the successor of a given element in the BST.
* The successor is the node with the smallest value greater than the given data.
* root: pointer to the root node of the tree.
* data: element to find the successor for.
* return: pointer to the successor node, or NULL if none exists.
*/
Node* bst_successor(Node* root, ElementType data);

/*
* Returns the predecessor of a given element in the BST.
* The predecessor is the node with the largest value smaller than the given data.
* root: pointer to the root node of the tree.
* data: element to find the predecessor for.
* return: pointer to the predecessor node, or NULL if none exists.
*/
Node* bst_predecessor(Node* root, ElementType data);

/*
* Checks if an element exists in the BST using an iterative approach.
* root: pointer to the root node of the tree.
* data: element to search for.
* return: true if element exists, false otherwise.
*/
bool bst_contains_iterative(Node* root, ElementType data);

/*
* Returns the depth (level) of an element in the BST.
* root: pointer to the root node of the tree.
* data: element to find the depth for.
* return: depth of the element (0-based), or -1 if not found.
*/
int bst_depth(Node* root, ElementType data);

/*
* Validates if a binary tree satisfies the BST properties.
* root: pointer to the root node of the tree.
* return: true if valid BST, false otherwise.
*/
bool bst_is_valid(Node* root);

/*
* Prints the BST in a structured hierarchical format.
* root: pointer to the root node of the tree.
* space: indentation space (typically start with 0).
*/
void bst_print_tree(Node* root, int space);

/*
* Returns the k-th smallest element in the BST (1-based index).
* root: pointer to the root node of the tree.
* k: the order of the smallest element to find.
* return: pointer to the k-th smallest node, or NULL if invalid k.
*/
Node* bst_select(Node* root, int k);

/*
* Returns the rank of an element in the BST.
* The rank is the number of elements smaller than the given data.
* root: pointer to the root node of the tree.
* data: element to find the rank for.
* return: rank of the element (0-based).
*/
int bst_rank(Node* root, ElementType data);

/*
* Converts the BST to a sorted array.
* root: pointer to the root node of the tree.
* array: pre-allocated array to store elements.
*/
void bst_to_array(Node* root, ElementType array[]);

/*
* Constructs a balanced BST from a sorted array.
* array: sorted array of elements.
* start: starting index.
* end: ending index.
* return: pointer to the root node of the constructed BST.
*/
Node* bst_from_sorted_array(ElementType array[], int start, int end);

/*
* Counts the number of leaf nodes in the BST.
* root: pointer to the root node of the tree.
* return: count of leaf nodes.
*/
int bst_leaf_count(Node* root);

/*
* Counts the number of internal (non-leaf) nodes in the BST.
* root: pointer to the root node of the tree.
* return: count of internal nodes.
*/
int bst_internal_node_count(Node* root);

/*
* Clears the BST by freeing all nodes and setting root to NULL.
* root: pointer to the root node pointer.
*/
void bst_clear(Node** root);

/*
* Creates a deep copy (clone) of the BST.
* root: pointer to the root node of the tree to copy.
* return: pointer to the root node of the new cloned tree.
*/
Node* bst_clone(Node* root);

/*
* Checks if the BST is height-balanced.
* root: pointer to the root node.
* return: true if balanced, false otherwise.
*/
bool bst_is_balanced(Node* root);

/*
* Finds the path from root to the element data.
* root: pointer to the root node.
* data: target element to find.
* path: pre-allocated array to store path elements.
* max_length: max capacity of the path array.
* return: length of path if found, 0 if not found or path exceeds max_length.
*/
int bst_find_path(Node* root, ElementType data, ElementType path[], int max_length);

#endif
