
<div align="center">
  <h1>Persistent B-Tree Implementation in C with Binary File Indexing</h1>

This project implements a **persistent B-Tree** data structure in **C**, which stores nodes directly on disk in a binary file. The B-Tree supports **insertion**, **deletion**, **search**, and **traversal** operations while maintaining balanced tree properties. By storing nodes with file offsets instead of pointers, the structure enables efficient indexing and retrieval of large datasets that do not fit entirely in memory.

The binary file (`btree_index.dat`) acts as an index, maintaining the B-Tree on disk. The program creates this file on the first run and reads it on subsequent runs to restore the B-Tree structure, ensuring persistence across executions.

This project was developed for the **PPGCC02 - Algorithms And Data Structures** course in the master's program at **UTFPR**, taught by **Prof. Dr. Rodrigo Campiolo**.

</div>

## Table of Contents

- [Table of Contents](#table-of-contents)
- [About B-Trees](#about-b-trees)
  - [Key Characteristics](#key-characteristics)
- [Requirements](#requirements)
- [Setup](#setup)
- [Usage](#usage)
- [Project Files](#project-files)
  - [`main.c`](#mainc)
    - [Demonstrated Workflow](#demonstrated-workflow)
    - [Benefits of the Approach](#benefits-of-the-approach)
  - [`b_tree.h` – Header File Overview](#b_treeh--header-file-overview)
    - [Data Structures](#data-structures)
    - [Packing Directive](#packing-directive)
    - [Public API](#public-api)
    - [Internal Utilities](#internal-utilities)
  - [`b_tree.c`](#b_treec)
    - [Defined Constants](#defined-constants)
    - [Key Structures](#key-structures)
    - [Core Functional Areas](#core-functional-areas)
      - [1. Disk Persistence Helpers](#1-disk-persistence-helpers)
      - [2. Tree Lifecycle Management](#2-tree-lifecycle-management)
      - [3. Traversal](#3-traversal)
      - [4. Searching](#4-searching)
      - [5. Insertion](#5-insertion)
      - [6. Deletion](#6-deletion)
      - [7. Queue Operations (for Level Order Printing)](#7-queue-operations-for-level-order-printing)
      - [8. Tree Equality Comparison](#8-tree-equality-comparison)
  - [`btree_index.dat`](#btree_indexdat)

---

## About B-Trees

**B-Trees** are balanced tree structures optimized for large block reads/writes. They enable fast search, insertion, and deletion in **O(log n)** time.

### Key Characteristics

- Each node contains multiple keys and child pointers.
- The **minimum degree (t)** determines the minimum and maximum number of keys in a node.
- Internal nodes may store references to child nodes using **file offsets**, enabling persistent, disk-based storage.

This implementation prioritizes **persistence**, using a binary file as the underlying storage mechanism.

---

## Requirements

- GCC compiler (or compatible C compiler)
- Unix-like environment (Linux, macOS) or Windows with suitable shell
- Make utility (optional, for using the Makefile)

---

## Setup

1. Clone or download this project repository.
2. No additional dataset is required since the program inserts sample keys during execution.

---

## Usage

To compile, run, and clean the project, use the provided Makefile:

```bash
make
```

This will:
- Compile the source files (`main.c` and `b_tree.c`)
- Run the executable, demonstrating insertion, traversal, search, persistence, and modification of the B-Tree
- Clean up object files and executable after running

To manually compile and run without the Makefile:

```bash
gcc main.c b_tree.c -o main
./main
```

---

## Project Files

### `main.c`

The `main.c` file serves as the entry point for testing and demonstrating the **persistent B-Tree** functionality. It showcases the full cycle of operations that validate the correctness and durability of the tree structure stored on disk.

#### Demonstrated Workflow

1. **Creation and Initial Insertion**
   - A new B-Tree is created and linked to the binary index file (`btree_index.dat`).
   - The program inserts a predefined set of integer keys (`{10, 20, 5, 6, 12, 30, 7, 17}`) into the tree.
   - After each insertion, the tree is displayed using **level-order traversal**, showing how it reorganizes to remain balanced.
   
2. **Search Demonstration**
   - The program searches for several keys (e.g., 6, 15, 25, 30).
   - It prints whether each key was found or not, validating the `btree_search` functionality.

3. **Persistence Validation**
   - The B-Tree is closed using `btree_close`, simulating application termination.
   - It is then reopened from the same binary file with `btree_open`.
   - The reopened tree is traversed again using both in-order and level-order methods to confirm that the data persisted correctly across sessions.

4. **Structural Comparison**
   - The original and reopened trees are compared using `btree_are_equal` to verify that persistence preserved not only data but structure.

5. **Post-Reopen Modifications**
   - The program inserts a new key (`25`) and deletes an existing key (`10`) from the reopened tree.
   - These changes are followed by another round of traversals to demonstrate that the tree can continue operating seamlessly after being restored from disk.

6. **Finalization**
   - The modified tree is closed again to finalize the state on disk.
   - The test ends with a success message.

#### Benefits of the Approach

- This structure makes the B-Tree **persistent** by default: any insertion, deletion, or structural change is immediately reflected on disk.
- The tree can be reopened in future executions and continue from its exact previous state, including balanced structure and contents.
- The use of file offsets and fixed-size nodes enables fast seeking and low overhead during traversal and modification.

The `main.c` file is a practical and complete demonstration of how a **persistent B-Tree** can function seamlessly across program lifecycles, suitable for real-world applications like indexing in databases, filesystems, and key-value stores.

---

### `b_tree.h` – Header File Overview

Defines the core data structures and function prototypes used to implement the persistent B-Tree.

#### Data Structures

```c
typedef struct BTreeNode {
    int n;
    int keys[2 * MIN_DEGREE - 1];
    int64_t children[2 * MIN_DEGREE];
    uint8_t leaf;
    int64_t self_pos;
} BTreeNode;

typedef struct BTree {
    FILE *fp;
    int64_t root_pos;
} BTree;
```

#### Packing Directive

```c
#pragma pack(push, 1)
// ...structs...
#pragma pack(pop)
```

This eliminates padding bytes, preserving a predictable and compact layout when reading/writing nodes.

#### Public API

```c
BTree *btree_open(const char *filename);
void btree_close(BTree *tree);
void btree_insert(BTree *tree, int key);
void btree_delete(BTree *tree, int key);
int btree_search(BTree *tree, int key);
void btree_traverse(BTree *tree);
void btree_print_level_order(BTree *tree);
int btree_are_equal(BTree *tree1, BTree *tree2);
```

#### Internal Utilities

```c
BTreeNode *btree_create_node(uint8_t leaf, FILE *fp);
void btree_write_node(BTree *tree, BTreeNode *node);
BTreeNode *btree_read_node(BTree *tree, int64_t pos);
```

---

### `b_tree.c`

This source file implements the core functionality of the **persistent B-Tree** structure, including logic for insertion, deletion, traversal, disk I/O, and structure balancing.

#### Defined Constants

```c
#define BTREE_MAGIC 0xBEEFCAFE
```

* Used to validate the integrity of the B-Tree binary file during loading.

---

#### Key Structures

```c
typedef struct QueueNode {
   int64_t pos;
   struct QueueNode *next;
} QueueNode;
```

* Temporary structure used to support **level-order traversal** with a queue.

---

#### Core Functional Areas

##### 1. Disk Persistence Helpers

* `btree_alloc_node` – Allocates and writes a new node at the end of the file.
* `btree_write_node` – Serializes a node to its disk position.
* `btree_read_node` – Reads a node from a specific file offset.

##### 2. Tree Lifecycle Management

* `btree_open` – Opens an existing B-Tree from disk or creates a new one.
* `btree_close` – Flushes and closes the binary file, freeing memory.

##### 3. Traversal

* `btree_traverse` – Wrapper for recursive traversal.
* `btree_traverse_recursive` – Recursively performs in-order traversal.
* `btree_print_level_order` – Prints the tree level by level.

##### 4. Searching

* `btree_search` – Initiates search from the root.
* `btree_search_recursive` – Recursively searches for a key.

##### 5. Insertion

* `btree_insert` – Inserts a key into the B-Tree.
* `btree_split_child` – Splits a full child during insert.
* `btree_insert_nonfull` – Handles insertions into non-full nodes.

##### 6. Deletion

* `btree_delete` – Deletes a key from the B-Tree.
* `btree_delete_recursive` – Handles deletion recursively.
* `btree_get_predecessor`, `btree_get_successor` – Helpers to find adjacent keys.
* `btree_fill_child` – Ensures a child has the required number of keys.
* `btree_borrow_from_prev`, `btree_borrow_from_next` – Rebalance by borrowing.
* `btree_merge` – Merges child nodes when borrowing is not possible.

##### 7. Queue Operations (for Level Order Printing)

```c
void enqueue(int64_t pos);
int64_t dequeue();
```

* Internal linked queue for breadth-first traversal.

##### 8. Tree Equality Comparison

* `btree_are_equal` – Compares two B-Trees for structural and key equivalence.
* `btree_nodes_are_equal` – Recursively compares node contents.

---

This modular and disk-centric implementation allows the B-Tree to operate efficiently on large datasets while maintaining consistency and recoverability across sessions.

---

### `btree_index.dat`

The file used to store the B-Tree (`btree_index.dat`) is a binary file designed for fixed-size node storage. It enables random access to any part of the tree using file offsets instead of pointers.

- **Root Metadata**: At the beginning of the file, a small header section stores metadata such as the root node’s offset and a magic number (`0xBEEFCAFE`) used to verify file integrity.

- **Tree Nodes**: Each `BTreeNode` is stored as a compact binary block:
  ```c
  typedef struct BTreeNode {
      int n;                              // Number of keys
      int keys[2 * MIN_DEGREE - 1];       // Key array
      int64_t children[2 * MIN_DEGREE];   // Offsets to child nodes
      uint8_t leaf;                       // Is this a leaf node?
      int64_t self_pos;                   // Offset of this node
  } BTreeNode;
  ```
  - All nodes are serialized using `fwrite` and deserialized with `fread`.
  - The `#pragma pack(push, 1)` directive ensures no padding is added, maintaining consistent node sizes across different systems.
  - Child links are not memory pointers but `int64_t` file offsets that allow the tree to be fully navigated after reopening.

---
