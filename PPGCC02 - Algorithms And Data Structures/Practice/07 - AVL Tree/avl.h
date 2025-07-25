/*
* Description: AVL tree interface header.
* Author: Breno Farias da Silva.
* Date: 14/06/2025.
*/

#ifndef _AVL_H_
#define _AVL_H_

#include <stdbool.h>

typedef int ElementType;

typedef struct Node {
	ElementType data;
	struct Node* left;
	struct Node* right;
	int height;
} Node;

/*
* Creates an empty AVL tree (NULL root).
* return: NULL pointer representing an empty tree.
*/
Node* avl_create(void);

/*
* Inserts a new element into the AVL tree.
* root: pointer to the root node of the tree.
* data: element to insert.
* return: pointer to the root node of the updated tree.
*/
Node* avl_insert(Node* root, ElementType data);

/*
* Removes an element from the AVL tree.
* root: pointer to the root node of the tree.
* data: element to remove.
* return: pointer to the root node of the updated tree.
*/
Node* avl_remove(Node* root, ElementType data);

/*
* Checks if an element exists in the AVL tree.
* root: pointer to the root node of the tree.
* data: element to search for.
* return: true if element exists, false otherwise.
*/
bool avl_contains(Node* root, ElementType data);

/*
* Prints the tree nodes in preorder traversal.
* root: pointer to the root node.
*/
void avl_preorder(Node* root);

/*
* Prints the tree nodes in inorder traversal.
* root: pointer to the root node.
*/
void avl_inorder(Node* root);

/*
* Prints the tree nodes in postorder traversal.
* root: pointer to the root node.
*/
void avl_postorder(Node* root);

/*
* Returns the height of the tree.
* root: pointer to the root node.
* return: height of the tree, -1 if tree is empty.
*/
int avl_height(Node* root);

/*
* Returns the total number of nodes in the tree.
* root: pointer to the root node.
* return: number of nodes in the tree.
*/
int avl_size(Node* root);

/*
* Destroys the tree, freeing all allocated memory.
* root: pointer to the root node pointer.
*/
void avl_destroy(Node** root);

/*
* Returns the minimum element in the AVL tree.
* If the tree is empty, returns NULL.
*/
Node* avl_find_min(Node* root);

/*
* Returns the maximum element in the AVL tree.
* If the tree is empty, returns NULL.
*/
Node* avl_find_max(Node* root);

/*
* Finds the successor of a given element in the AVL tree.
* Returns NULL if no successor exists.
*/
Node* avl_successor(Node* root, ElementType data);

/*
* Finds the predecessor of a given element in the AVL tree.
* Returns NULL if no predecessor exists.
*/
Node* avl_predecessor(Node* root, ElementType data);

/*
* Returns the k-th smallest element in the AVL tree (1-based index).
* If k is invalid (<=0 or > size), returns NULL.
*/
Node* avl_select(Node* root, int k);

/*
* Returns the rank of an element in the AVL tree.
* The rank is the number of elements less than the given element.
*/
int avl_rank(Node* root, ElementType data);

/*
* Checks if the AVL tree is balanced.
* Return: true if balanced, false otherwise.
*/
bool avl_is_balanced(Node* root);

/*
* Converts the AVL tree into a sorted array.
* array: pre-allocated array of at least avl_size(root) elements.
*/
void avl_to_array(Node* root, ElementType array[]);

/*
* Builds a balanced AVL tree from a sorted array.
* array: sorted array.
* start: start index (typically 0).
* end: end index (typically size - 1).
* Returns: pointer to the root node of the new AVL tree.
*/
Node* avl_from_sorted_array(ElementType array[], int start, int end);

/*
* Prints the AVL tree in a hierarchical format.
*/
void avl_print_tree(Node* root, int space);

/*
* Counts the number of leaf nodes in the AVL tree.
*/
int avl_leaf_count(Node* root);

/*
* Returns the depth of a given element in the AVL tree.
* The depth of the root is 0.
* Returns -1 if the element is not found.
*/
int avl_depth(Node* root, ElementType data);

/*
* Clears the AVL tree by freeing all nodes and setting root to NULL.
* root: pointer to the root node pointer.
* return: NULL after clearing the tree.
*/
Node* avl_clear(Node** root);

/*
* Creates a deep copy (clone) of the AVL tree.
* root: pointer to the root node of the tree to copy.
* return: pointer to the root node of the new cloned tree.
*/
Node* avl_clone(Node* root);

/*
* Validates if the AVL tree satisfies the BST properties and balance conditions.
* root: pointer to the root node of the tree.
* return: true if valid AVL tree, false otherwise.
*/
bool avl_is_valid(Node* root);

/*
* Removes the minimum element node from the AVL tree.
* root: pointer to the root node of the tree.
* return: pointer to the root node of the updated tree.
*/
Node* avl_remove_min(Node* root);

/*
* Removes the maximum element node from the AVL tree.
* root: pointer to the root node of the tree.
* return: pointer to the root node of the updated tree.
*/
Node* avl_remove_max(Node* root);

/*
* Counts the number of internal (non-leaf) nodes in the AVL tree.
* root: pointer to the root node of the tree.
* return: count of internal nodes.
*/
int avl_internal_node_count(Node* root);

/*
* Returns the height balance factor of a node.
* root: pointer to the node.
* return: balance factor (height of left subtree - height of right subtree).
*/
int avl_height_balance_factor(Node* root);

/*
* Checks if an element exists in the AVL tree using an iterative approach.
* root: pointer to the root node of the tree.
* data: element to search for.
* return: true if element exists, false otherwise.
*/
bool avl_contains_iterative(Node* root, ElementType data);

/*
* Finds the path from root to the element data.
* root: pointer to the root node.
* data: target element to find.
* path: pre-allocated array to store path elements.
* max_length: max capacity of the path array.
* return: length of path if found, 0 if not found or path exceeds max_length.
*/
int avl_find_path(Node* root, ElementType data, ElementType path[], int max_length);

/*
* Performs a left rotation on the subtree rooted at *root.
* root: pointer to the root node pointer of the subtree.
*/
void avl_rotate_left(Node** root);

/*
* Performs a right rotation on the subtree rooted at *root.
* root: pointer to the root node pointer of the subtree.
*/
void avl_rotate_right(Node** root);

/*
* Merges two AVL trees and returns the root of the merged AVL tree.
*/
Node* avl_merge(Node* tree1, Node* tree2);

/*
* Splits AVL tree into two trees: those less than key and those >= key.
*/
void avl_split(Node* root, ElementType key, Node** leftTree, Node** rightTree);

#endif
