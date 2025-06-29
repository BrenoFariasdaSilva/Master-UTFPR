/*
 * File: b_tree.h
 * Description: Header file for the persistent B-Tree implementation.
 *              Defines core data structures and declares the API functions
 *              for creating, manipulating, persisting, and querying a B-Tree
 *              that is stored on disk to ensure data persistence between executions.
 *
 *              The B-Tree supports insertion, deletion, search, traversal (in-order
 *              and level-order), and tree equality comparison. The implementation
 *              uses file offsets to reference child nodes, allowing the tree
 *              structure to be maintained persistently in a binary file.
 *
 * Author: Breno Farias da Silva
 * Date: 29/06/2025
 */

#ifndef B_TREE_H
#define B_TREE_H

#include <stdio.h> // For FILE operations (fopen, fread, fwrite, fclose, etc.)
#include <stdint.h> // For fixed-width integer types such as int64_t
#include <stdbool.h> // For boolean type support (bool, true, false)

/* Minimum degree of the B-Tree.
 * Defines the minimum number of children per internal node (except root).
 * Affects the maximum and minimum number of keys per node.
 */
#define MIN_DEGREE 3

/* Filename used as default for storing the persistent B-Tree data */
#define BTREE_FILENAME "btree_index.dat"

/* 
 * Disable structure padding to guarantee fixed node size for disk storage.
 * Ensures binary compatibility and predictable layout when reading/writing nodes.
 */
#pragma pack(push, 1)

/*
 * Structure representing a single node in the B-Tree.
 *
 * Layout details:
 * - n: Number of keys currently stored in this node.
 * - keys: Array containing keys stored in this node (max 2*MIN_DEGREE - 1 keys).
 * - children: Array of file offsets pointing to child nodes in the file.
 *             A value of -1 indicates no child (NULL pointer equivalent).
 * - leaf: Flag indicating whether this node is a leaf (1 = leaf, 0 = internal node).
 * - self_pos: The byte offset in the file where this node is stored.
 */
typedef struct BTreeNode {
   int n;
   int keys[2 * MIN_DEGREE - 1];
   int64_t children[2 * MIN_DEGREE];
   uint8_t leaf;
   int64_t self_pos;
} BTreeNode;

/*
 * Structure representing the entire persistent B-Tree.
 *
 * Contains metadata necessary to manage the tree file:
 * - fp: File pointer to the open binary file storing the B-Tree nodes.
 * - root_pos: File offset of the root node within the B-Tree file.
 */
typedef struct BTree {
   FILE *fp;
   int64_t root_pos;
} BTree;

#pragma pack(pop) // Restore default packing alignment

// === Public API ===

/*
 * Opens an existing B-Tree file or creates a new one if it doesn't exist.
 *
 * If the file exists, loads the B-Tree metadata and prepares for operations.
 * If not, creates a new file and initializes an empty B-Tree root node.
 *
 * @param filename Path to the file used for persistent B-Tree storage.
 * @return Pointer to an allocated BTree instance, or NULL on failure.
 */
BTree *btree_open(const char *filename);

/*
 * Closes the B-Tree, flushing any buffered data and releasing resources.
 *
 * After calling this, the BTree pointer should not be used.
 *
 * @param tree Pointer to the BTree to be closed.
 */
void btree_close(BTree *tree);

/*
 * Inserts a new key into the B-Tree, maintaining B-Tree properties.
 *
 * Handles splitting nodes as needed to keep the tree balanced.
 *
 * @param tree Pointer to the BTree.
 * @param key Integer key to be inserted.
 */
void btree_insert(BTree *tree, int key);

/*
 * Deletes a key from the B-Tree if it exists.
 *
 * Rebalances the tree and merges nodes if necessary to maintain B-Tree properties.
 *
 * @param tree Pointer to the BTree.
 * @param key Integer key to be removed.
 */
void btree_delete(BTree *tree, int key);

/*
 * Searches the B-Tree for a given key.
 *
 * @param tree Pointer to the BTree.
 * @param key Integer key to search for.
 * @return 1 if the key is found; 0 if not found.
 */
int btree_search(BTree *tree, int key);

/*
 * Performs an in-order traversal of the B-Tree,
 * printing all keys in ascending sorted order.
 *
 * @param tree Pointer to the BTree.
 */
void btree_traverse(BTree *tree);

/*
 * Performs a level-order (breadth-first) traversal of the B-Tree,
 * printing the keys by tree level to visualize the tree structure.
 *
 * @param tree Pointer to the BTree.
 */
void btree_print_level_order(BTree *tree);

/*
 * Compares two B-Trees for equality in both structure and stored keys.
 *
 * Useful to verify persistence correctness by comparing trees before
 * and after closing/reopening.
 *
 * @param tree1 Pointer to the first BTree.
 * @param tree2 Pointer to the second BTree.
 * @return 1 if the trees are equal; 0 otherwise.
 */
int btree_are_equal(BTree *tree1, BTree *tree2);

// === Internal Helper Functions ===

/*
 * Allocates and initializes a new BTreeNode instance.
 *
 * The node is assigned a file offset based on the current file position.
 *
 * @param leaf Flag indicating if the new node is a leaf (1) or internal (0).
 * @param fp File pointer for the B-Tree storage file.
 * @return Pointer to the newly allocated node; must be freed by caller.
 */
BTreeNode *btree_create_node(uint8_t leaf, FILE *fp);

/*
 * Writes a BTreeNode to disk at the node's self_pos offset.
 *
 * This updates the persistent storage with the node's current data.
 *
 * @param tree Pointer to the BTree containing the file pointer.
 * @param node Pointer to the node to be written.
 */
void btree_write_node(BTree *tree, BTreeNode *node);

/*
 * Reads a BTreeNode from disk given its byte offset in the file.
 *
 * Allocates memory for the node which must be freed by the caller.
 *
 * @param tree Pointer to the BTree containing the file pointer.
 * @param pos Byte offset of the node to read.
 * @return Pointer to the read node, or NULL on failure.
 */
BTreeNode *btree_read_node(BTree *tree, int64_t pos);

#endif /* B_TREE_H */
