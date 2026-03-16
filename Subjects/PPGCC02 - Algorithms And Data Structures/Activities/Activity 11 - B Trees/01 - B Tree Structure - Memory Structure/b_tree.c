/*
 * Description: Implementation of B-Tree operations including search, insert, delete, traverse.
 * Author: Breno Farias da Silva.
 * Date: 24/06/2025.
 */

#include <stdio.h> // printf
#include <stdlib.h> // malloc, free
#include "b_tree.h"

/*
 * Creates a new B-Tree node.
 * leaf: true if node is leaf, false otherwise.
 * return: pointer to the new node.
 */
BTreeNode *btree_create_node(bool leaf) {
   BTreeNode *node = (BTreeNode *)malloc(sizeof(BTreeNode));
   if (!node) {
      printf("Memory allocation failed\n");
      exit(EXIT_FAILURE);
   }
   node->leaf = leaf;
   node->n = 0;
   for (int i = 0; i < 2 * MIN_DEGREE; i++) {
      node->children[i] = NULL;
   }
   return node;
}

/*
 * Creates an empty B-Tree.
 * return: pointer to the new B-Tree.
 */
BTree *btree_create() {
   BTree *tree = (BTree *)malloc(sizeof(BTree));
   if (!tree) {
      printf("Memory allocation failed\n");
      exit(EXIT_FAILURE);
   }
   tree->root = btree_create_node(true);
   return tree;
}

/*
 * Traverses the B-Tree in ascending order and prints keys.
 * root: pointer to the root node.
 */
void btree_traverse(BTreeNode *root) {
   if (root != NULL) {
      int i;
      for (i = 0; i < root->n; i++) {
         if (!root->leaf)
            btree_traverse(root->children[i]);
         printf("%d ", root->keys[i]);
      }
      if (!root->leaf)
         btree_traverse(root->children[i]);
   }
}

/*
 * Searches the key in the subtree rooted with root.
 * root: pointer to root node.
 * key: key to search.
 * return: pointer to node containing key, or NULL if not found.
 */
BTreeNode *btree_search(BTreeNode *root, int key) {
   int i = 0;
   while (i < root->n && key > root->keys[i]) {
      i++;
   }

   if (i < root->n && root->keys[i] == key) {
      return root;
   }

   if (root->leaf) {
      return NULL;
   }

   return btree_search(root->children[i], key);
}

/*
 * Splits the child y of node x at index i.
 * x: parent node.
 * i: index of child y in x->children.
 * y: child node to split.
 */
void btree_split_child(BTreeNode *x, int i, BTreeNode *y) {
   BTreeNode *z = btree_create_node(y->leaf);
   z->n = MIN_DEGREE - 1;

   // Copy last (t-1) keys of y to z
   for (int j = 0; j < MIN_DEGREE - 1; j++) {
      z->keys[j] = y->keys[j + MIN_DEGREE];
   }

   // Copy last t children of y to z
   if (!y->leaf) {
      for (int j = 0; j < MIN_DEGREE; j++) {
         z->children[j] = y->children[j + MIN_DEGREE];
      }
   }

   y->n = MIN_DEGREE - 1;

   // Shift children of x to make room for new child z
   for (int j = x->n; j >= i + 1; j--) {
      x->children[j + 1] = x->children[j];
   }
   x->children[i + 1] = z;

   // Shift keys of x to make room for y's middle key
   for (int j = x->n - 1; j >= i; j--) {
      x->keys[j + 1] = x->keys[j];
   }
   x->keys[i] = y->keys[MIN_DEGREE - 1];
   x->n++;
}

/*
 * Inserts key into non-full node x.
 * x: pointer to node.
 * key: key to insert.
 */
void btree_insert_nonfull(BTreeNode *x, int key) {
   int i = x->n - 1;

   if (x->leaf) {
      // Insert key into leaf node
      while (i >= 0 && key < x->keys[i]) {
         x->keys[i + 1] = x->keys[i];
         i--;
      }
      x->keys[i + 1] = key;
      x->n++;
   } else {
      // Move down to correct child
      while (i >= 0 && key < x->keys[i]) {
         i--;
      }
      i++;
      if (x->children[i]->n == 2 * MIN_DEGREE - 1) {
         btree_split_child(x, i, x->children[i]);
         if (key > x->keys[i]) {
            i++;
         }
      }
      btree_insert_nonfull(x->children[i], key);
   }
}

/*
 * Inserts a key into the B-Tree.
 * tree: pointer to B-Tree.
 * key: key to insert.
 */
void btree_insert(BTree *tree, int key) {
   BTreeNode *r = tree->root;

   if (r->n == 2 * MIN_DEGREE - 1) {
      BTreeNode *s = btree_create_node(false);
      tree->root = s;
      s->children[0] = r;
      btree_split_child(s, 0, r);
      btree_insert_nonfull(s, key);
   } else {
      btree_insert_nonfull(r, key);
   }
}

/*
 * Finds the key index in node x, or returns -1 if not found.
 * x: pointer to node.
 * key: key to find.
 * return: index of key or -1.
 */
int btree_find_key(BTreeNode *x, int key) {
   int idx = 0;
   while (idx < x->n && x->keys[idx] < key) {
      idx++;
   }
   return idx;
}

/*
 * Removes the key from the leaf node x at index idx.
 * x: pointer to leaf node.
 * idx: index of key in x->keys.
 */
void btree_remove_from_leaf(BTreeNode *x, int idx) {
   for (int i = idx + 1; i < x->n; i++) {
      x->keys[i - 1] = x->keys[i];
   }
   x->n--;
}

/*
 * Removes the key from the internal node x at index idx.
 * x: pointer to internal node.
 * idx: index of key in x->keys.
 */
void btree_remove_from_nonleaf(BTreeNode *x, int idx);

/*
 * Gets predecessor of key at index idx in node x.
 * x: pointer to node.
 * idx: index of key.
 * return: predecessor key.
 */
int btree_get_predecessor(BTreeNode *x, int idx) {
   BTreeNode *cur = x->children[idx];
   while (!cur->leaf) {
      cur = cur->children[cur->n];
   }
   return cur->keys[cur->n - 1];
}

/*
 * Gets successor of key at index idx in node x.
 * x: pointer to node.
 * idx: index of key.
 * return: successor key.
 */
int btree_get_successor(BTreeNode *x, int idx) {
   BTreeNode *cur = x->children[idx + 1];
   while (!cur->leaf) {
      cur = cur->children[0];
   }
   return cur->keys[0];
}

/*
 * Fills child node x->children[idx] which has less than t-1 keys.
 * x: pointer to node.
 * idx: child index.
 */
void btree_fill(BTreeNode *x, int idx);

/*
 * Borrows a key from x->children[idx-1] and inserts into x->children[idx].
 * x: pointer to node.
 * idx: child index.
 */
void btree_borrow_from_prev(BTreeNode *x, int idx);

/*
 * Borrows a key from x->children[idx+1] and inserts into x->children[idx].
 * x: pointer to node.
 * idx: child index.
 */
void btree_borrow_from_next(BTreeNode *x, int idx);

/*
 * Merges x->children[idx] with x->children[idx+1].
 * x: pointer to node.
 * idx: child index.
 */
void btree_merge(BTreeNode *x, int idx);

/*
 * Removes the key k from the subtree rooted at x.
 * x: pointer to node.
 * key: key to remove.
 */
void btree_remove(BTreeNode *x, int key) {
   int idx = btree_find_key(x, key);

   if (idx < x->n && x->keys[idx] == key) {
      if (x->leaf) {
         btree_remove_from_leaf(x, idx);
      } else {
         btree_remove_from_nonleaf(x, idx);
      }
   } else {
      if (x->leaf) {
         // Key not found in tree
         printf("Key %d does not exist in the tree.\n", key);
         return;
      }

      bool flag = ((idx == x->n) ? true : false);

      if (x->children[idx]->n < MIN_DEGREE) {
         btree_fill(x, idx);
      }

      if (flag && idx > x->n) {
         btree_remove(x->children[idx - 1], key);
      } else {
         btree_remove(x->children[idx], key);
      }
   }
}

/*
 * Removes the key from the internal node x at index idx.
 * x: pointer to internal node.
 * idx: index of key in x->keys.
 */
void btree_remove_from_nonleaf(BTreeNode *x, int idx) {
   int key = x->keys[idx];

   if (x->children[idx]->n >= MIN_DEGREE) {
      int pred = btree_get_predecessor(x, idx);
      x->keys[idx] = pred;
      btree_remove(x->children[idx], pred);
   } else if (x->children[idx + 1]->n >= MIN_DEGREE) {
      int succ = btree_get_successor(x, idx);
      x->keys[idx] = succ;
      btree_remove(x->children[idx + 1], succ);
   } else {
      btree_merge(x, idx);
      btree_remove(x->children[idx], key);
   }
}

/*
 * Fills child node x->children[idx] which has less than t-1 keys.
 * x: pointer to node.
 * idx: child index.
 */
void btree_fill(BTreeNode *x, int idx) {
   if (idx != 0 && x->children[idx - 1]->n >= MIN_DEGREE) {
      btree_borrow_from_prev(x, idx);
   } else if (idx != x->n && x->children[idx + 1]->n >= MIN_DEGREE) {
      btree_borrow_from_next(x, idx);
   } else {
      if (idx != x->n) {
         btree_merge(x, idx);
      } else {
         btree_merge(x, idx - 1);
      }
   }
}

/*
 * Borrows a key from x->children[idx-1] and inserts into x->children[idx].
 * x: pointer to node.
 * idx: child index.
 */
void btree_borrow_from_prev(BTreeNode *x, int idx) {
   BTreeNode *child = x->children[idx];
   BTreeNode *sibling = x->children[idx - 1];

   for (int i = child->n - 1; i >= 0; i--) {
      child->keys[i + 1] = child->keys[i];
   }

   if (!child->leaf) {
      for (int i = child->n; i >= 0; i--) {
         child->children[i + 1] = child->children[i];
      }
   }

   child->keys[0] = x->keys[idx - 1];

   if (!x->leaf) {
      child->children[0] = sibling->children[sibling->n];
   }

   x->keys[idx - 1] = sibling->keys[sibling->n - 1];

   child->n += 1;
   sibling->n -= 1;
}

/*
 * Borrows a key from x->children[idx+1] and inserts into x->children[idx].
 * x: pointer to node.
 * idx: child index.
 */
void btree_borrow_from_next(BTreeNode *x, int idx) {
   BTreeNode *child = x->children[idx];
   BTreeNode *sibling = x->children[idx + 1];

   child->keys[(child->n)] = x->keys[idx];

   if (!(child->leaf)) {
      child->children[(child->n) + 1] = sibling->children[0];
   }

   x->keys[idx] = sibling->keys[0];

   for (int i = 1; i < sibling->n; i++) {
      sibling->keys[i - 1] = sibling->keys[i];
   }

   if (!sibling->leaf) {
      for (int i = 1; i <= sibling->n; i++) {
         sibling->children[i - 1] = sibling->children[i];
      }
   }

   child->n += 1;
   sibling->n -= 1;
}

/*
 * Merges x->children[idx] with x->children[idx+1].
 * x: pointer to node.
 * idx: child index.
 */
void btree_merge(BTreeNode *x, int idx) {
   BTreeNode *child = x->children[idx];
   BTreeNode *sibling = x->children[idx + 1];

   child->keys[MIN_DEGREE - 1] = x->keys[idx];

   for (int i = 0; i < sibling->n; i++) {
      child->keys[i + MIN_DEGREE] = sibling->keys[i];
   }

   if (!child->leaf) {
      for (int i = 0; i <= sibling->n; i++) {
         child->children[i + MIN_DEGREE] = sibling->children[i];
      }
   }

   for (int i = idx + 1; i < x->n; i++) {
      x->keys[i - 1] = x->keys[i];
   }

   for (int i = idx + 2; i <= x->n; i++) {
      x->children[i - 1] = x->children[i];
   }

   child->n += sibling->n + 1;
   x->n--;

   free(sibling);
}

/*
 * Deletes key from the B-Tree.
 * tree: pointer to B-Tree.
 * key: key to delete.
 */
void btree_delete(BTree *tree, int key) {
   if (!tree->root) {
      printf("The tree is empty\n");
      return;
   }

   btree_remove(tree->root, key);

   if (tree->root->n == 0) {
      BTreeNode *tmp = tree->root;
      if (tree->root->leaf) {
         tree->root = NULL;
      } else {
         tree->root = tree->root->children[0];
      }
      free(tmp);
   }
}

/* Queue node struct for level order traversal */
typedef struct QueueNode {
   BTreeNode *node;
   struct QueueNode *next;
} QueueNode;

/* Enqueue function */
void enqueue(QueueNode **front, QueueNode **rear, BTreeNode *n) {
   QueueNode *temp = (QueueNode *)malloc(sizeof(QueueNode));
   temp->node = n;
   temp->next = NULL;
   if (*rear == NULL) {
      *front = *rear = temp;
   } else {
      (*rear)->next = temp;
      *rear = temp;
   }
}

/* Dequeue function */
BTreeNode *dequeue(QueueNode **front, QueueNode **rear) {
   if (*front == NULL) return NULL;
   QueueNode *temp = *front;
   BTreeNode *node = temp->node;
   *front = (*front)->next;
   if (*front == NULL) *rear = NULL;
   free(temp);
   return node;
}

/* Check if queue is empty */
int is_empty(QueueNode *front) {
   return front == NULL;
}

/*
 * Prints the B-Tree level by level.
 * Each line shows the keys in all nodes at that level,
 * sibling nodes separated by " | ".
 * root: pointer to root node.
 */
void btree_print_levels(BTreeNode *root) {
   if (root == NULL) {
      printf("Empty tree\n");
      return;
   }

   QueueNode *front = NULL;
   QueueNode *rear = NULL;

   enqueue(&front, &rear, root);
   int level = 0;

   while (!is_empty(front)) {
      // Count nodes at current level
      int level_node_count = 0;
      QueueNode *tmp = front;
      while (tmp != NULL) {
         level_node_count++;
         tmp = tmp->next;
      }

      printf("level %d: ", level);

      for (int i = 0; i < level_node_count; i++) {
         BTreeNode *curr = dequeue(&front, &rear);

         // Print keys of current node inside brackets with commas
         printf("[");
         for (int k = 0; k < curr->n; k++) {
            printf("%d", curr->keys[k]);
            if (k < curr->n - 1) {
               printf(", ");
            }
         }
         printf("]");

         // Print separator between sibling nodes except after last node
         if (i < level_node_count - 1) {
            printf(" | ");
         }

         // Enqueue children if not leaf
         if (!curr->leaf) {
            for (int c = 0; c <= curr->n; c++) {
               if (curr->children[c] != NULL) {
                  enqueue(&front, &rear, curr->children[c]);
               }
            }
         }
      }

      printf("\n");

      // Check if next level contains any non-leaf nodes
      int next_level_non_leaf_count = 0;
      tmp = front;
      while (tmp != NULL) {
         if (!tmp->node->leaf) {
            next_level_non_leaf_count++;
         }
         tmp = tmp->next;
      }

      if (next_level_non_leaf_count == 0) {
         // If next level has only leaf nodes or is empty, print them and break
         if (!is_empty(front)) {
            printf("level %d: ", level + 1);

            // Print all leaf nodes on next level
            int next_level_count = 0;
            tmp = front;
            while (tmp != NULL) {
               next_level_count++;
               tmp = tmp->next;
            }

            for (int i = 0; i < next_level_count; i++) {
               BTreeNode *curr = dequeue(&front, &rear);

               printf("[");
               for (int k = 0; k < curr->n; k++) {
                  printf("%d", curr->keys[k]);
                  if (k < curr->n - 1) {
                     printf(", ");
                  }
               }
               printf("]");

               if (i < next_level_count - 1) {
                  printf(" | ");
               }
            }
            printf("\n");
         }
         break;
      }

      level++;
   }
}