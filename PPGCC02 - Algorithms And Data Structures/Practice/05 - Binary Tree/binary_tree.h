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

#endif
