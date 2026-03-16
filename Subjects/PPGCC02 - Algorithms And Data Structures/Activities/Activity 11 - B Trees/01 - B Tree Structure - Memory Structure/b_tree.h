/*
 * Description: Header file for B-Tree implementation with basic operations.
 * Author: Breno Farias da Silva.
 * Date: 24/06/2025.
 */

#ifndef B_TREE_H
#define B_TREE_H

#include <stdbool.h>

#define MIN_DEGREE 3 // Minimum degree (t) of B-Tree

/*
 * Structure for a B-Tree node.
 */
typedef struct BTreeNode {
   int n; // Current number of keys
   int keys[2 * MIN_DEGREE - 1]; // Keys array
   struct BTreeNode *children[2 * MIN_DEGREE]; // Child pointers
   bool leaf; // Is true when node is leaf. Otherwise false
} BTreeNode;

/*
 * Structure for the B-Tree.
 */
typedef struct BTree {
   BTreeNode *root; // Pointer to root node
} BTree;

/*
 * Creates an empty B-Tree.
 * return: pointer to the new B-Tree.
 */
BTree *btree_create();

/*
 * Creates a new B-Tree node.
 * leaf: true if node is leaf, false otherwise.
 * return: pointer to the new node.
 */
BTreeNode *btree_create_node(bool leaf);

/*
 * Traverses the B-Tree in ascending order and prints keys.
 * root: pointer to the root node.
 */
void btree_traverse(BTreeNode *root);

/*
 * Searches for a key in the B-Tree.
 * root: pointer to root node.
 * key: key to search.
 * return: pointer to node containing key, or NULL if not found.
 */
BTreeNode *btree_search(BTreeNode *root, int key);

/*
 * Inserts a key into the B-Tree.
 * tree: pointer to B-Tree.
 * key: key to insert.
 */
void btree_insert(BTree *tree, int key);

/*
 * Deletes a key from the B-Tree.
 * tree: pointer to B-Tree.
 * key: key to delete.
 */
void btree_delete(BTree *tree, int key);

/*
 * Prints the B-Tree level by level.
 * Each line shows the keys in all nodes at that level,
 * sibling nodes separated by " | ".
 * root: pointer to root node.
 */
void btree_print_levels(BTreeNode *root);

#endif /* B_TREE_H */
