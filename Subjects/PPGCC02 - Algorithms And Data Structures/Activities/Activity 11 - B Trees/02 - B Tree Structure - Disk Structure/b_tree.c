/*
 * Persistent B-Tree Implementation
 *
 * This module provides a disk-based B-Tree data structure, where nodes are stored
 * persistently in a file using file offsets to identify node locations. The B-Tree
 * supports fundamental operations such as insertion, deletion, search, traversal,
 * and comparison, all while maintaining its balanced tree properties on disk.
 *
 * Nodes are serialized and deserialized with file I/O, enabling management of large
 * datasets that do not fit entirely in memory. A file header stores a magic number
 * for format verification and the file offset of the root node.
 *
 * The implementation uses recursive internal helper functions for core operations,
 * ensuring proper maintenance of the B-Tree invariants throughout modifications.
 *
 * Author: Breno Farias da Silva.
 * Date: 29/06/2025.
 */

#include <stdio.h> // FILE struct, fopen, fread, fwrite, fseek, fclose
#include <stdlib.h> // malloc, free, exit, perror
#include "b_tree.h" // Definitions of BTree, BTreeNode, and public B-Tree functions

/*
 * Internal helper function declarations:
 * These functions implement recursive operations on B-Tree nodes and manage
 * node splitting, merging, borrowing keys, and traversal logic.
 */

void btree_traverse_recursive(BTree *tree, BTreeNode *node);
int btree_search_recursive(BTree *tree, BTreeNode *node, int key);
void btree_split_child(BTree *tree, BTreeNode *parent, int i, BTreeNode *full_child);
void btree_insert_nonfull(BTree *tree, BTreeNode *node, int key);
void btree_delete_recursive(BTree *tree, BTreeNode *node, int key);
int btree_get_predecessor(BTree *tree, BTreeNode *node);
int btree_get_successor(BTree *tree, BTreeNode *node);
void btree_fill_child(BTree *tree, BTreeNode *node, int idx);
void btree_borrow_from_prev(BTree *tree, BTreeNode *node, int idx);
void btree_borrow_from_next(BTree *tree, BTreeNode *node, int idx);
void btree_merge(BTree *tree, BTreeNode *node, int idx);
void btree_print_level_order(BTree *tree);

/*
 * Magic number used to verify the B-Tree file format integrity.
 * Stored in the file header to ensure the file matches the expected format.
 */
#define BTREE_MAGIC 0xBEEFCAFE

/*
 * Allocates a new B-Tree node, initializes it as leaf or internal node,
 * sets its file offset, and writes it to the file.
 * 
 * @param tree Pointer to the BTree structure.
 * @param is_leaf Boolean indicating whether the node is a leaf (1) or internal (0).
 * @return Pointer to the newly allocated and initialized BTreeNode.
 */
BTreeNode *btree_alloc_node(BTree *tree, uint8_t is_leaf) {
   BTreeNode *node = malloc(sizeof(BTreeNode));
   if (!node) {
      perror("Failed to allocate node");
      exit(EXIT_FAILURE);
   }

   node->leaf = is_leaf;
   node->n = 0;
   for (int i = 0; i < 2 * MIN_DEGREE; i++) {
      node->children[i] = -1; // Initialize children offsets to -1 (null)
   }

   // Position node at the end of file for persistent storage
   fseek(tree->fp, 0, SEEK_END);
   node->self_pos = (int64_t)ftell(tree->fp);

   btree_write_node(tree, node);
   return node;
}

/*
 * Writes a BTreeNode to its designated position in the file.
 * This function persists all node fields to disk.
 * 
 * @param fp File pointer to the B-Tree file.
 * @param node Pointer to the BTreeNode to be written.
 */
void btree_write_node(BTree *tree, BTreeNode *node) {
   fseek(tree->fp, node->self_pos, SEEK_SET);
   fwrite(&node->n, sizeof(int), 1, tree->fp);
   fwrite(node->keys, sizeof(int), 2 * MIN_DEGREE - 1, tree->fp);
   fwrite(node->children, sizeof(int64_t), 2 * MIN_DEGREE, tree->fp);
   fwrite(&node->leaf, sizeof(uint8_t), 1, tree->fp);
   fwrite(&node->self_pos, sizeof(int64_t), 1, tree->fp);
   fflush(tree->fp);
}

/*
 * Reads a BTreeNode from the file at the specified file offset.
 * 
 * @param fp File pointer to the B-Tree file.
 * @param pos File offset where the node is stored.
 * @return Pointer to a newly allocated BTreeNode with data loaded from file.
 */
BTreeNode *btree_read_node(BTree *tree, int64_t pos) {
   BTreeNode *node = malloc(sizeof(BTreeNode));
   if (!node) {
      perror("Failed to allocate node");
      exit(EXIT_FAILURE);
   }

   fseek(tree->fp, pos, SEEK_SET);
   fread(&node->n, sizeof(int), 1, tree->fp);
   fread(node->keys, sizeof(int), 2 * MIN_DEGREE - 1, tree->fp);
   fread(node->children, sizeof(int64_t), 2 * MIN_DEGREE, tree->fp);
   fread(&node->leaf, sizeof(uint8_t), 1, tree->fp);
   fread(&node->self_pos, sizeof(int64_t), 1, tree->fp);
   return node;
}

/*
 * Opens a persistent B-Tree stored in the specified file.
 * If the file does not exist, creates a new B-Tree with an empty root node.
 * 
 * @param filename Path to the B-Tree file.
 * @return Pointer to the initialized BTree structure.
 */
BTree *btree_open(const char *filename) {
   BTree *tree = malloc(sizeof(BTree));
   if (!tree) {
      perror("Failed to allocate tree");
      exit(EXIT_FAILURE);
   }

   FILE *fp = fopen(filename, "r+b");
   if (!fp) {
      // File doesn't exist, create new B-Tree file
      fp = fopen(filename, "w+b");
      if (!fp) {
         perror("Failed to create file");
         exit(EXIT_FAILURE);
      }

      // Write magic number and placeholder root position
      unsigned int magic = BTREE_MAGIC;
      int64_t root_pos = sizeof(unsigned int) + sizeof(int64_t);
      fwrite(&magic, sizeof(unsigned int), 1, fp);
      fwrite(&root_pos, sizeof(int64_t), 1, fp);
      fflush(fp);

      tree->fp = fp;
      BTreeNode *root = btree_alloc_node(tree, 1); // root is leaf initially
      tree->root_pos = root->self_pos;

      // Update root position in file header
      fseek(fp, sizeof(unsigned int), SEEK_SET);
      fwrite(&tree->root_pos, sizeof(int64_t), 1, fp);
      fflush(fp);
      free(root);
   } else {
      // Existing file: verify magic number and read root position
      unsigned int magic;
      fread(&magic, sizeof(unsigned int), 1, fp);
      if (magic != BTREE_MAGIC) {
         fprintf(stderr, "Invalid B-Tree file format.\n");
         exit(EXIT_FAILURE);
      }
      fread(&tree->root_pos, sizeof(int64_t), 1, fp);
      tree->fp = fp;
   }

   return tree;
}

/*
 * Closes the B-Tree file and frees associated memory.
 * 
 * @param tree Pointer to the BTree structure.
 */
void btree_close(BTree *tree) {
   if (tree) {
      fclose(tree->fp);
      free(tree);
   }
}

/*
 * Traverses the B-Tree in-order and prints keys to stdout.
 * 
 * @param tree Pointer to the BTree structure.
 */
void btree_traverse(BTree *tree) {
   if (!tree) return;

   BTreeNode *root = btree_read_node(tree, tree->root_pos);
   btree_traverse_recursive(tree, root);
   printf("\n");
   free(root);
}

/*
 * Recursive helper function for in-order traversal.
 * 
 * @param tree Pointer to the BTree structure.
 * @param node Pointer to the current BTreeNode.
 */
void btree_traverse_recursive(BTree *tree, BTreeNode *node) {
   for (int i = 0; i < node->n; i++) {
      if (!node->leaf) {
         BTreeNode *child = btree_read_node(tree, node->children[i]);
         btree_traverse_recursive(tree, child);
         free(child);
      }
      printf("%d ", node->keys[i]);
   }
   if (!node->leaf) {
      BTreeNode *child = btree_read_node(tree, node->children[node->n]);
      btree_traverse_recursive(tree, child);
      free(child);
   }
}

/*
 * Searches for a key in the B-Tree.
 * 
 * @param tree Pointer to the BTree structure.
 * @param key Key to search for.
 * @return 1 if found, 0 if not found.
 */
int btree_search(BTree *tree, int key) {
   BTreeNode *root = btree_read_node(tree, tree->root_pos);
   int result = btree_search_recursive(tree, root, key);
   free(root);
   return result;
}

/*
 * Recursive helper function to search for a key starting from a node.
 * 
 * @param tree Pointer to the BTree structure.
 * @param node Pointer to the current BTreeNode.
 * @param key Key to search for.
 * @return 1 if found, 0 if not found.
 */
int btree_search_recursive(BTree *tree, BTreeNode *node, int key) {
   int i = 0;
   while (i < node->n && key > node->keys[i]) i++;

   if (i < node->n && key == node->keys[i]) {
      return 1;
   }

   if (node->leaf) return 0;

   BTreeNode *child = btree_read_node(tree, node->children[i]);
   int result = btree_search_recursive(tree, child, key);
   free(child);
   return result;
}

/*
 * Inserts a key into the B-Tree.
 * If the key already exists, insertion is skipped.
 * 
 * @param tree Pointer to the BTree structure.
 * @param key Key to insert.
 */
void btree_insert(BTree *tree, int key) {
   if (btree_search(tree, key)) {
      printf("Key %d already exists. Skipping insertion.\n\n", key);
      return;
   }

   BTreeNode *root = btree_read_node(tree, tree->root_pos);
   if (root->n == 2 * MIN_DEGREE - 1) {
      // Root is full, create new root and split
      BTreeNode *s = btree_alloc_node(tree, 0); // New root is internal
      s->children[0] = root->self_pos;
      tree->root_pos = s->self_pos;

      // Update root position in file header
      fseek(tree->fp, sizeof(unsigned int), SEEK_SET);
      fwrite(&tree->root_pos, sizeof(int64_t), 1, tree->fp);
      fflush(tree->fp);

      btree_split_child(tree, s, 0, root);
      btree_insert_nonfull(tree, s, key);
      btree_write_node(tree, s);
      free(s);
   } else {
      btree_insert_nonfull(tree, root, key);
   }
   btree_write_node(tree, root);
   free(root);
}

/*
 * Splits the full child node of a parent at index i.
 * 
 * @param tree Pointer to the BTree structure.
 * @param parent Pointer to the parent BTreeNode.
 * @param i Index of the child to split.
 * @param full_child Pointer to the full child node to split.
 */
void btree_split_child(BTree *tree, BTreeNode *parent, int i, BTreeNode *full_child) {
   BTreeNode *z = btree_alloc_node(tree, full_child->leaf);
   z->n = MIN_DEGREE - 1;

   // Copy higher keys from full_child to z
   for (int j = 0; j < MIN_DEGREE - 1; j++) {
      z->keys[j] = full_child->keys[j + MIN_DEGREE];
   }

   // Copy corresponding children if not leaf
   if (!full_child->leaf) {
      for (int j = 0; j < MIN_DEGREE; j++) {
         z->children[j] = full_child->children[j + MIN_DEGREE];
      }
   }

   full_child->n = MIN_DEGREE - 1;

   // Shift children of parent to make space for new child
   for (int j = parent->n; j >= i + 1; j--) {
      parent->children[j + 1] = parent->children[j];
   }
   parent->children[i + 1] = z->self_pos;

   // Shift keys of parent to make space for median key
   for (int j = parent->n - 1; j >= i; j--) {
      parent->keys[j + 1] = parent->keys[j];
   }

   // Move median key from full_child to parent
   parent->keys[i] = full_child->keys[MIN_DEGREE - 1];
   parent->n++;

   // Persist changes to disk
   btree_write_node(tree, full_child);
   btree_write_node(tree, z);
   btree_write_node(tree, parent);

   free(z);
}

/*
 * Inserts a key into a node that is guaranteed not to be full.
 * 
 * @param tree Pointer to the BTree structure.
 * @param node Pointer to the BTreeNode.
 * @param key Key to insert.
 */
void btree_insert_nonfull(BTree *tree, BTreeNode *node, int key) {
   int i = node->n - 1;

   if (node->leaf) {
      // Insert key into leaf node at proper position
      while (i >= 0 && key < node->keys[i]) {
         node->keys[i + 1] = node->keys[i];
         i--;
      }
      node->keys[i + 1] = key;
      node->n++;
      btree_write_node(tree, node);
   } else {
      // Traverse child node where key should be inserted
      while (i >= 0 && key < node->keys[i]) i--;
      i++;
      BTreeNode *child = btree_read_node(tree, node->children[i]);

      if (child->n == 2 * MIN_DEGREE - 1) {
         btree_split_child(tree, node, i, child);
         if (key > node->keys[i]) {
            i++;
            free(child);
            child = btree_read_node(tree, node->children[i]);
         }
      }
      btree_insert_nonfull(tree, child, key);
      free(child);
   }
}

/*
 * Deletes a key from the B-Tree.
 * 
 * @param tree Pointer to the BTree structure.
 * @param key Key to delete.
 */
void btree_delete(BTree *tree, int key) {
   BTreeNode *root = btree_read_node(tree, tree->root_pos);

   btree_delete_recursive(tree, root, key);

   // If root node has no keys and is not leaf, change root
   if (root->n == 0 && !root->leaf) {
      tree->root_pos = root->children[0];
      fseek(tree->fp, sizeof(unsigned int), SEEK_SET);
      fwrite(&tree->root_pos, sizeof(int64_t), 1, tree->fp);
      fflush(tree->fp);
      free(root);
   // Deletion of old root node from file not handled here
   } else {
      btree_write_node(tree, root);
      free(root);
   }
}

/*
 * Recursively deletes a key from a node.
 * 
 * @param tree Pointer to the BTree structure.
 * @param node Pointer to the current BTreeNode.
 * @param key Key to delete.
 */
void btree_delete_recursive(BTree *tree, BTreeNode *node, int key) {
   int idx = 0;
   while (idx < node->n && node->keys[idx] < key) idx++;

   if (idx < node->n && node->keys[idx] == key) {
      if (node->leaf) {
         // Case 1: key found in leaf node, remove key directly
         for (int i = idx + 1; i < node->n; i++) {
            node->keys[i - 1] = node->keys[i];
         }
         node->n--;
         btree_write_node(tree, node);
      } else {
         // Case 2: key found in internal node
         BTreeNode *pred = btree_read_node(tree, node->children[idx]);
         if (pred->n >= MIN_DEGREE) {
            int pred_key = btree_get_predecessor(tree, pred);
            node->keys[idx] = pred_key;
            btree_write_node(tree, node);
            btree_delete_recursive(tree, pred, pred_key);
            free(pred);
         } else {
            BTreeNode *succ = btree_read_node(tree, node->children[idx + 1]);
            if (succ->n >= MIN_DEGREE) {
               int succ_key = btree_get_successor(tree, succ);
               node->keys[idx] = succ_key;
               btree_write_node(tree, node);
               btree_delete_recursive(tree, succ, succ_key);
               free(succ);
            } else {
               btree_merge(tree, node, idx);
               BTreeNode *merged_child = btree_read_node(tree, node->children[idx]);
               btree_delete_recursive(tree, merged_child, key);
               free(merged_child);
            }
         }
      }
   } else {
      // Case 3: key not found in this node
      if (node->leaf) {
      // Key not found in tree
         return;
      }

      uint8_t flag = (idx == node->n);
      BTreeNode *child = btree_read_node(tree, node->children[idx]);

      if (child->n < MIN_DEGREE) {
         btree_fill_child(tree, node, idx);
         free(child);
         if (flag) { // idx == node->n
            child = btree_read_node(tree, node->children[idx - 1]);
         } else {
            child = btree_read_node(tree, node->children[idx]);
         }
      }

      btree_delete_recursive(tree, child, key);
      free(child);
   }
}

/*
 * Finds the predecessor key (maximum key) in the subtree rooted at node.
 * 
 * @param tree Pointer to the BTree structure.
 * @param node Pointer to the subtree root node.
 * @return The predecessor key.
 */
int btree_get_predecessor(BTree *tree, BTreeNode *node) {
   BTreeNode *current = node;
   while (!current->leaf) {
      BTreeNode *child = btree_read_node(tree, current->children[current->n]);
      if (current != node) free(current);
      current = child;
   }
   int pred_key = current->keys[current->n - 1];
   if (current != node) free(current);
   return pred_key;
}

/*
 * Finds the successor key (minimum key) in the subtree rooted at node.
 * 
 * @param tree Pointer to the BTree structure.
 * @param node Pointer to the subtree root node.
 * @return The successor key.
 */
int btree_get_successor(BTree *tree, BTreeNode *node) {
   BTreeNode *current = node;
   while (!current->leaf) {
      BTreeNode *child = btree_read_node(tree, current->children[0]);
      if (current != node) free(current);
      current = child;
   }
   int succ_key = current->keys[0];
   if (current != node) free(current);
   return succ_key;
}

/*
 * Ensures that the child node at index idx has at least MIN_DEGREE keys.
 * If not, tries to borrow from siblings or merges nodes.
 * 
 * @param tree Pointer to the BTree structure.
 * @param node Pointer to the parent node.
 * @param idx Index of the child to fill.
 */
void btree_fill_child(BTree *tree, BTreeNode *node, int idx) {
   BTreeNode *child = btree_read_node(tree, node->children[idx]);

   if (idx != 0) {
      BTreeNode *left_sibling = btree_read_node(tree, node->children[idx - 1]);
      if (left_sibling->n >= MIN_DEGREE) {
         btree_borrow_from_prev(tree, node, idx);
         free(child);
         free(left_sibling);
         return;
      }
      free(left_sibling);
   }

   if (idx != node->n) {
      BTreeNode *right_sibling = btree_read_node(tree, node->children[idx + 1]);
      if (right_sibling->n >= MIN_DEGREE) {
         btree_borrow_from_next(tree, node, idx);
         free(child);
         free(right_sibling);
         return;
      }
      free(right_sibling);
   }

   if (idx != node->n) {
      btree_merge(tree, node, idx);
   } else {
      btree_merge(tree, node, idx - 1);
   }
   free(child);
}

/*
 * Borrows a key from the left sibling and moves it to the child at index idx.
 * 
 * @param tree Pointer to the BTree structure.
 * @param node Pointer to the parent node.
 * @param idx Index of the child which will borrow the key.
 */
void btree_borrow_from_prev(BTree *tree, BTreeNode *node, int idx) {
   BTreeNode *child = btree_read_node(tree, node->children[idx]);
   BTreeNode *sibling = btree_read_node(tree, node->children[idx - 1]);

   // Shift child keys and children right to make space
   for (int i = child->n - 1; i >= 0; i--)
      child->keys[i + 1] = child->keys[i];

   if (!child->leaf) {
      for (int i = child->n; i >= 0; i--)
         child->children[i + 1] = child->children[i];
   }

   // Move key from parent down to child
   child->keys[0] = node->keys[idx - 1];

   if (!child->leaf)
      child->children[0] = sibling->children[sibling->n];

   // Move key from sibling up to parent
   node->keys[idx - 1] = sibling->keys[sibling->n - 1];

   child->n += 1;
   sibling->n -= 1;

   btree_write_node(tree, child);
   btree_write_node(tree, sibling);
   btree_write_node(tree, node);

   free(child);
   free(sibling);
}

/*
 * Borrows a key from the right sibling and moves it to the child at index idx.
 * 
 * @param tree Pointer to the BTree structure.
 * @param node Pointer to the parent node.
 * @param idx Index of the child which will borrow the key.
 */
void btree_borrow_from_next(BTree *tree, BTreeNode *node, int idx) {
   BTreeNode *child = btree_read_node(tree, node->children[idx]);
   BTreeNode *sibling = btree_read_node(tree, node->children[idx + 1]);

   // Move key from parent down to child
   child->keys[child->n] = node->keys[idx];

   if (!child->leaf)
      child->children[child->n + 1] = sibling->children[0];

   // Move key from sibling up to parent
   node->keys[idx] = sibling->keys[0];

   // Shift sibling keys and children left
   for (int i = 1; i < sibling->n; i++)
      sibling->keys[i - 1] = sibling->keys[i];

   if (!sibling->leaf) {
      for (int i = 1; i <= sibling->n; i++)
         sibling->children[i - 1] = sibling->children[i];
   }

   child->n += 1;
   sibling->n -= 1;

   btree_write_node(tree, child);
   btree_write_node(tree, sibling);
   btree_write_node(tree, node);

   free(child);
   free(sibling);
}

/*
 * Merges the child at index idx with its right sibling.
 * Moves a key down from the parent into the merged node.
 * 
 * @param tree Pointer to the BTree structure.
 * @param node Pointer to the parent node.
 * @param idx Index of the child to merge.
 */
void btree_merge(BTree *tree, BTreeNode *node, int idx) {
   BTreeNode *child = btree_read_node(tree, node->children[idx]);
   BTreeNode *sibling = btree_read_node(tree, node->children[idx + 1]);

   // Pull key down from parent into child
   child->keys[MIN_DEGREE - 1] = node->keys[idx];

   // Copy keys from sibling into child
   for (int i = 0; i < sibling->n; i++)
      child->keys[i + MIN_DEGREE] = sibling->keys[i];

   // Copy children from sibling if not leaf
   if (!child->leaf) {
      for (int i = 0; i <= sibling->n; i++)
         child->children[i + MIN_DEGREE] = sibling->children[i];
   }

   child->n += sibling->n + 1;

   // Shift keys and children in parent to remove key and pointer to sibling
   for (int i = idx + 1; i < node->n; i++) {
      node->keys[i - 1] = node->keys[i];
   }
   for (int i = idx + 1; i <= node->n; i++) {
      node->children[i - 1] = node->children[i];
   }
   node->n--;

   btree_write_node(tree, child);
   btree_write_node(tree, node);

   free(child);
   free(sibling);
}

/*
 * Queue node structure for level order traversal.
 */
typedef struct QueueNode {
   int64_t pos;
   struct QueueNode *next;
} QueueNode;

static QueueNode *front = NULL, *rear = NULL;

/*
 * Enqueues a node position into the queue.
 * 
 * @param pos File offset of the BTreeNode.
 */
void enqueue(int64_t pos) {
   QueueNode *new_node = malloc(sizeof(QueueNode));
   if (!new_node) {
      perror("Failed to allocate queue node");
      exit(EXIT_FAILURE);
   }
   new_node->pos = pos;
   new_node->next = NULL;
   if (rear == NULL) {
      front = rear = new_node;
   } else {
      rear->next = new_node;
      rear = new_node;
   }
}

/*
 * Dequeues a node position from the queue.
 * 
 * @return File offset of the dequeued BTreeNode, or -1 if queue is empty.
 */
int64_t dequeue() {
   if (front == NULL) return -1;
   QueueNode *temp = front;
   int64_t pos = temp->pos;
   front = front->next;
   if (front == NULL) rear = NULL;
   free(temp);
   return pos;
}

/*
 * Prints the B-Tree level by level.
 * Each level's nodes are printed on a new line.
 * 
 * @param tree Pointer to the BTree structure.
 */
void btree_print_level_order(BTree *tree) {
   if (!tree) return;

   // Initialize queue
   front = rear = NULL;

   enqueue(tree->root_pos);

   while (front != NULL) {
      int level_size = 0;
      QueueNode *temp = front;
      while (temp) {
         level_size++;
         temp = temp->next;
      }

      for (int i = 0; i < level_size; i++) {
         int64_t pos = dequeue();
         if (pos == -1) break;

         BTreeNode *node = btree_read_node(tree, pos);
         printf("[");
         for (int j = 0; j < node->n; j++) {
            printf("%d", node->keys[j]);
            if (j < node->n - 1) printf(" ");
         }
         printf("] ");

         if (!node->leaf) {
            for (int j = 0; j <= node->n; j++) {
               enqueue(node->children[j]);
            }
         }
         free(node);
      }
      printf("\n");
   }
}

/*
 * Recursive helper function to compare two nodes for equality.
 * 
 * @param tree1 Pointer to the first BTree.
 * @param node1 Pointer to a node in the first BTree.
 * @param tree2 Pointer to the second BTree.
 * @param node2 Pointer to a node in the second BTree.
 * @return 1 if nodes and their subtrees are equal, 0 otherwise.
 */
static int btree_nodes_are_equal(BTree *tree1, BTreeNode *node1, BTree *tree2, BTreeNode *node2) {
   if (node1->n != node2->n || node1->leaf != node2->leaf)
      return 0;

   for (int i = 0; i < node1->n; i++) {
      if (node1->keys[i] != node2->keys[i])
         return 0;
   }

   if (node1->leaf && node2->leaf) {
   // Both are leaves and keys match
      return 1;
   }

   // Compare children recursively
   for (int i = 0; i <= node1->n; i++) {
      BTreeNode *child1 = btree_read_node(tree1, node1->children[i]);
      BTreeNode *child2 = btree_read_node(tree2, node2->children[i]);

      int res = btree_nodes_are_equal(tree1, child1, tree2, child2);

      free(child1);
      free(child2);

      if (!res)
         return 0;
   }

   return 1;
}

/*
 * Checks whether two B-Trees are equal in structure and keys.
 * 
 * @param tree1 Pointer to the first BTree.
 * @param tree2 Pointer to the second BTree.
 * @return 1 if equal, 0 otherwise.
 */
int btree_are_equal(BTree *tree1, BTree *tree2) {
   if (!tree1 || !tree2)
      return 0;

   BTreeNode *root1 = btree_read_node(tree1, tree1->root_pos);
   BTreeNode *root2 = btree_read_node(tree2, tree2->root_pos);

   int result = btree_nodes_are_equal(tree1, root1, tree2, root2);

   free(root1);
   free(root2);

   return result;
}
