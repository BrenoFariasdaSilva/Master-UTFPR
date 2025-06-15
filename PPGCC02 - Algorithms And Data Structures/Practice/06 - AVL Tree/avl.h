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

#endif
