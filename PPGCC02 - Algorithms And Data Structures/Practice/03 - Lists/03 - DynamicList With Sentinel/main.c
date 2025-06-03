/*
 * Description: This program shows an implementation of a Dynamic Doubly Linked List with Sentinel.
 * Author: Breno Farias da Silva.
 * Date: 27/05/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf
#include <stdlib.h> // malloc, free
#include <stdbool.h> // bool

typedef int ElementType; // Define the type of elements in the list

/*
 * Node structure for doubly linked list
 * Each node contains data, a pointer to the previous node, and a pointer to the next node.
 */
typedef struct Node {
   ElementType data; // Data stored in the node
   struct Node *prev; // Pointer to the previous node
   struct Node *next; // Pointer to the next node
} Node;

/*
 * Dynamic list structure with sentinel node
 * The sentinel node simplifies insertion and deletion operations.
 */
typedef struct {
   Node *sentinel; // Sentinel node (does not hold valid data)
   int size; // Number of elements in the list
} DynamicList;

// Function declarations
DynamicList* create_list();
void initialize_list(DynamicList *list);
bool insert_at_end(DynamicList *list, const ElementType value);
bool insert_at_beginning(DynamicList *list, const ElementType value);
bool insert_at(DynamicList *list, const int position, const ElementType value);
bool insert_array(DynamicList *list, const ElementType *array, const int length);
int replace_all(DynamicList *list, const ElementType oldValue, const ElementType newValue);
bool replace_first_occurrence(DynamicList *list, const ElementType oldValue, const ElementType newValue);
int find_value_position(const DynamicList *list, const ElementType value);
int get_list_size(const DynamicList *list);
int find_first(const DynamicList *list, const ElementType value);
int find_last(const DynamicList *list, const ElementType value);
bool remove_at(DynamicList *list, const int position);
void destroy_list(DynamicList *list);
ElementType get_at(const DynamicList *list, const int position);
bool is_empty(const DynamicList *list);
bool is_full(const DynamicList *list);
bool invert_list(DynamicList *list);
bool interleave_lists(const DynamicList *list1, const DynamicList *list2, DynamicList *result);
bool is_sorted(const DynamicList *list);
void print_list(const DynamicList *list);

// --- Function implementations ---

/*
 * Creates a new DynamicList and initializes it.
 * Returns a pointer to the newly created list, or NULL if memory allocation fails.
 */
DynamicList* create_list() {
   DynamicList *list = (DynamicList *) malloc(sizeof(DynamicList));
   if (!list) {
      printf("Memory allocation failed while creating the list.\n");
      return NULL;
   }

   initialize_list(list);
   return list;
}

/*
 * Initializes the list by creating the sentinel node.
 * The sentinel's next and prev point to itself indicating an empty list.
 * list: pointer to the DynamicList to initialize.
 * return: void
 */
void initialize_list(DynamicList *list) {
   list->sentinel = (Node *) malloc(sizeof(Node));

   if (!list->sentinel) {
      printf("Memory allocation failed during list initialization.\n");
      exit(EXIT_FAILURE);
   }

   list->sentinel->next = list->sentinel;
   list->sentinel->prev = list->sentinel;
   list->size = 0;
}

/*
 * Inserts a new node with 'value' at the end of the list.
 * list: pointer to the DynamicList.
 * value: the value to be inserted.
 * Returns true if insertion is successful, false if memory allocation fails.
 */
bool insert_at_end(DynamicList *list, const ElementType value) {
   if (!list) return false;
   
   Node *newNode = (Node *) malloc(sizeof(Node));
   if (!newNode) return false;

   newNode->data = value;

   // Insert before sentinel (end)
   newNode->prev = list->sentinel->prev;
   newNode->next = list->sentinel;

   list->sentinel->prev->next = newNode;
   list->sentinel->prev = newNode;

   list->size++;
   return true;
}

/*
 * Inserts a new node with 'value' at the beginning of the list.
 * list: pointer to the DynamicList.
 * value: the value to be inserted.
 * Returns true if insertion is successful.
 */
bool insert_at_beginning(DynamicList *list, const ElementType value) {
   if (!list) return false;

   Node *newNode = (Node *) malloc(sizeof(Node));
   if (!newNode) return false;

   newNode->data = value;

   // Insert right after sentinel (beginning)
   newNode->next = list->sentinel->next;
   newNode->prev = list->sentinel;

   list->sentinel->next->prev = newNode;
   list->sentinel->next = newNode;

   list->size++;
   return true;
}

/*
 * Inserts a new node with 'value' at the specified 'position' (0-based).
 * list: pointer to the DynamicList.
 * position: index where the value should be inserted (0-based).
 * value: the value to insert.
 * Returns true if insertion is successful.
 * If position > size, insertion fails.
 */
bool insert_at(DynamicList *list, const int position, const ElementType value) {
   if (!list || position < 0 || position > list->size) return false;

   Node *newNode = (Node *) malloc(sizeof(Node));
   if (!newNode) return false;

   newNode->data = value;

   // Traverse to position-th node (or sentinel if at end)
   Node *current = list->sentinel->next;
   for (int i = 0; i < position; i++) {
      current = current->next;
   }

   // Insert before current
   newNode->prev = current->prev;
   newNode->next = current;

   current->prev->next = newNode;
   current->prev = newNode;

   list->size++;
   return true;
}

/*
 * Inserts multiple elements from 'array' of length 'length' at the end of the list.
 * list: pointer to the DynamicList.
 * array: pointer to the array of elements to insert.
 * length: number of elements in the array.
 * Returns true if all insertions succeed, false otherwise.
 */
bool insert_array(DynamicList *list, const ElementType *array, const int length) {
   if (!list || !array || length < 0)
      return false;

   for (int i = 0; i < length; i++) {
      if (!insert_at_end(list, array[i])) {
         return false;
      }
   }

   return true;
}

/*
 * Replaces all occurrences of 'oldValue' with 'newValue' in the list.
 * list: pointer to the DynamicList.
 * oldValue: the value to be replaced.
 * newValue: the value to replace with.
 * Returns the count of replacements done.
 */
int replace_all(DynamicList *list, const ElementType oldValue, const ElementType newValue) {
   if (!list) return 0;

   int count = 0;
   Node *current = list->sentinel->next;

   while (current != list->sentinel) {
      if (current->data == oldValue) {
         current->data = newValue;
         count++;
      }
      current = current->next;
   }

   return count;
}

/*
 * Replaces the first occurrence of 'oldValue' with 'newValue' in the list.
 * list: pointer to the DynamicList.
 * oldValue: the value to be replaced.
 * newValue: the value to replace with.
 * Returns true if a replacement was made.
 */
bool replace_first_occurrence(DynamicList *list, const ElementType oldValue, const ElementType newValue) {
   if (!list) return false;

   Node *current = list->sentinel->next;
   while (current != list->sentinel) {
      if (current->data == oldValue) {
         current->data = newValue;
         return true;
      }
      current = current->next;
   }

   return false;
}

/*
 * Finds the position (0-based) of the last occurrence of 'value' in the list.
 * list: pointer to the DynamicList.
 * value: the value to find.
 * Returns the position or -1 if not found.
 */
int find_value_position(const DynamicList *list, const ElementType value) {
   if (!list) return -1;

   int position = -1;
   int index = 0;
   Node *current = list->sentinel->next;
   while (current != list->sentinel) {
      if (current->data == value) {
         position = index; // Update last found position
      }
      current = current->next;
      index++;
   }

   return position;
}

/*
 * Returns the current size of the list.
 * list: pointer to the DynamicList.
 * return: number of elements in the list.
 */
int get_list_size(const DynamicList *list) {
   if (!list) return 0;
   return list->size;
}

/*
 * Finds the first occurrence position (0-based) of 'value' in the list.
 * list: pointer to the DynamicList.
 * value: the value to find.
 * Returns the position or -1 if not found.
 */
int find_first(const DynamicList *list, const ElementType value) {
   if (!list) return -1;

   int index = 0;
   Node *current = list->sentinel->next;
   while (current != list->sentinel) {
      if (current->data == value) {
         return index;
      }
      current = current->next;
      index++;
   }

   return -1;
}

/*
 * Finds the last occurrence position (0-based) of 'value' in the list.
 * list: pointer to the DynamicList.
 * value: the value to find.
 * Returns the position or -1 if not found.
 */
int find_last(const DynamicList *list, const ElementType value) {
   if (!list) return -1;

   int position = -1;
   int index = 0;
   Node *current = list->sentinel->next;
   while (current != list->sentinel) {
      if (current->data == value) {
         position = index; // Update last found position
      }
      current = current->next;
      index++;
   }

   return position;
}

/*
 * Removes the node at 'position' (0-based) from the list.
 * list: pointer to the DynamicList.
 * position: index of the node to remove (0-based).
 * Returns true if removal is successful.
 */
bool remove_at(DynamicList *list, const int position) {
   if (!list || position < 0 || position >= list->size) return false;

   Node *current = list->sentinel->next;
   for (int i = 0; i < position; i++) {
      current = current->next;
   }

   current->prev->next = current->next;
   current->next->prev = current->prev;

   free(current);
   list->size--;
   return true;
}

/*
 * Frees all nodes and resets the list to empty state.
 * list: pointer to the DynamicList to destroy.
 * return: void
 */
void destroy_list(DynamicList *list) {
   if (!list) return;

   Node *current = list->sentinel->next;
   while (current != list->sentinel) {
      Node *toDelete = current;
      current = current->next;
      free(toDelete);
   }
   
   list->sentinel->next = list->sentinel;
   list->sentinel->prev = list->sentinel;
   list->size = 0;
}

/*
 * Returns the value at 'position' (0-based).
 * If position is invalid, returns 0 and prints an error message.
 * list: pointer to the DynamicList.
 * position: index to retrieve (0-based).
 * return: the value at the given position, or 0 if invalid.
 */
ElementType get_at(const DynamicList *list, const int position) {
   if (!list || position < 0 || position >= list->size) {
      printf("getAt: Invalid position %d\n", position);
      return 0;
   }

   Node *current = list->sentinel->next;
   for (int i = 0; i < position; i++) {
      current = current->next;
   }

   return current->data;
}

/*
 * Returns true if the list is empty.
 * list: pointer to the DynamicList.
 * return: true if empty, false otherwise.
 */
bool is_empty(const DynamicList *list) {
   if (!list) return true;
   return (list->size == 0);
}

/*
 * Returns true if the list is full.
 * For dynamic allocation, this returns false (unless malloc fails).
 * list: pointer to the DynamicList.
 * return: true if full, false otherwise.
 */
bool is_full(const DynamicList *list) {
   // Always returns false for dynamic list (limited only by memory)
   // If you want to simulate a full condition, implement a maximum size and check against it in the insert functions.
   return false;
}

/*
 * Inverts the order of elements in the list.
 * list: pointer to the DynamicList.
 * return: true if inverted, false if the list is empty or NULL.
 */
bool invert_list(DynamicList *list) {
   if (!list || is_empty(list)) return false;

   Node *current = list->sentinel->next;
   Node *temp = NULL;

   // Swap next and prev pointers for each node
   while (current != list->sentinel) {
      temp = current->prev;
      current->prev = current->next;
      current->next = temp;
      current = current->prev; // Move to the next node in the original order
   }

   // Adjust sentinel pointers
   temp = list->sentinel->next;
   list->sentinel->next = list->sentinel->prev;
   list->sentinel->prev = temp;

   return true;
}

/*
 * Interleaves two lists into a result list.
 * list1: pointer to the first DynamicList.
 * list2: pointer to the second DynamicList.
 * result: pointer to the result DynamicList.
 * return: true if interleaved successfully, false if any list is NULL or result is full.
 */
bool interleave_lists(const DynamicList *list1, const DynamicList *list2, DynamicList *result) {
   if (!list1 || !list2 || !result) return false;

   // Initialize result list
   initialize_list(result);

   Node *current1 = list1->sentinel->next;
   Node *current2 = list2->sentinel->next;

   // Interleave elements from both lists
   while (current1 != list1->sentinel || current2 != list2->sentinel) {
      if (current1 != list1->sentinel) {
         insert_at_end(result, current1->data);
         current1 = current1->next;
      }
      if (current2 != list2->sentinel) {
         insert_at_end(result, current2->data);
         current2 = current2->next;
      }
   }

   return true;
}

/*
 * Verify if the list is sorted in ascending order.
 * list: pointer to the DynamicList.
 * return: true if sorted, false otherwise.
 */
bool is_sorted(const DynamicList *list) {
   if (!list || is_empty(list)) return true; // An empty list is considered sorted

   Node *current = list->sentinel->next;
   while (current->next != list->sentinel) {
      if (current->data > current->next->data) {
         return false; // Found an out-of-order pair
      }
      current = current->next;
   }

   return true; // No out-of-order pairs found
}

/*
 * Prints the elements of the list in order.
 * If the list is empty, prints a corresponding message.
 * list: pointer to the DynamicList.
 * return: void
 */
void print_list(const DynamicList *list) {
   if (!list) {
      printf("List is NULL.\n");
      return;
   }

   if (is_empty(list)) {
      printf("List is empty.\n");
      return;
   }

   printf("List elements: ");
   Node *current = list->sentinel->next;
   while (current != list->sentinel) {
      printf("%d ", current->data);
      current = current->next;
   }
   printf("\n");
}

/*
 * Main function of the program.
 * argc: number of arguments passed on program call.
 * argv: array with the arguments passed on program call.
 * return: program execution status (0: no errors, otherwise: error code).
 */
int main(int argc, char *argv[]) {
   printf("Welcome to the Dynamic Doubly Linked List with Sentinel Implementation!\n\n");

   DynamicList *list = create_list(); // Create a new dynamic list

   if (!list) {
      printf("Failed to create the list.\n");
      return 1; // Exit with error
   }

   // Insert elements at the end
   insert_at_end(list, 5);
   insert_at_end(list, 10);

   // Insert element at the beginning
   insert_at_beginning(list, 1);

   // Insert at position 1 (0-based)
   insert_at(list, 1, 7);

   // Print current list
   print_list(list); // Expected: 1 7 5 10

   // Insert array of elements at the end
   ElementType arr[] = {20, 25, 30};
   insert_array(list, arr, 3);
   print_list(list); // Expected: 1 7 5 10 20 25 30

   // Replace all 10 with 15
   int replaced = replace_all(list, 10, 15);
   printf("Replaced %d occurrence(s) of 10 with 15\n", replaced);
   print_list(list); // Expected: 1 7 5 15 20 25 30

   // Replace first occurrence of 7 with 8
   bool replacedFirst = replace_first_occurrence(list, 7, 8);
   printf("Replaced first occurrence of 7 with 8? %s\n", replacedFirst ? "Yes" : "No");
   print_list(list); // Expected: 1 8 5 15 20 25 30

   // Find last position of 20
   int lastPos = find_last(list, 20);
   printf("Last position of 20: %d\n", lastPos); // Expected: 4 (0-based)

   // Get list size
   int size = get_list_size(list);
   printf("List size: %d\n", size); // Expected: 7

   // Find first occurrence of 5
   int firstPos = find_first(list, 5);
   printf("First occurrence of 5: %d\n", firstPos); // Expected: 2

   // Check if list is empty or full
   printf("Is list empty? %s\n", is_empty(list) ? "Yes" : "No");
   printf("Is list full? %s\n", is_full(list) ? "Yes" : "No");

   // Get element at position 3
   ElementType val = get_at(list, 3);
   printf("Element at position 3: %d\n", val); // Expected: 15

   // Remove element at position 1
   bool removed = remove_at(list, 1);
   printf("Removed element at position 1? %s\n", removed ? "Yes" : "No");
   print_list(list); // Expected: 1 5 15 20 25 30

   // Destroy the list
   destroy_list(list);
   print_list(list); // Expected: List is empty.

   return 0;
}
