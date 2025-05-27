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
void initializeList(DynamicList *list);
bool insertAtEnd(DynamicList *list, const ElementType value);
bool insertAtBeginning(DynamicList *list, const ElementType value);
bool insertAt(DynamicList *list, const int position, const ElementType value);
bool insertArray(DynamicList *list, const ElementType *array, const int length);
int replaceAll(DynamicList *list, const ElementType oldValue, const ElementType newValue);
bool replaceFirstOccurrence(DynamicList *list, const ElementType oldValue, const ElementType newValue);
int findValuePosition(const DynamicList *list, const ElementType value);
int getListSize(const DynamicList *list);
int findFirst(const DynamicList *list, const ElementType value);
bool removeAt(DynamicList *list, const int position);
void destroyList(DynamicList *list);
ElementType getAt(const DynamicList *list, const int position);
bool isEmpty(const DynamicList *list);
bool isFull(const DynamicList *list);
void printList(const DynamicList *list);

// --- Function implementations ---

/*
 * Initializes the list by creating the sentinel node.
 * The sentinel's next and prev point to itself indicating an empty list.
 * list: pointer to the DynamicList to initialize.
 * return: void
 */
void initializeList(DynamicList *list) {
   list->sentinel = (Node *)malloc(sizeof(Node));

   if (list->sentinel == NULL) {
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
bool insertAtEnd(DynamicList *list, const ElementType value) {
   if (list == NULL) return false;
   
   Node *newNode = (Node *)malloc(sizeof(Node));
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
bool insertAtBeginning(DynamicList *list, const ElementType value) {
   if (list == NULL) return false;

   Node *newNode = (Node *)malloc(sizeof(Node));
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
bool insertAt(DynamicList *list, const int position, const ElementType value) {
   if (list == NULL || position < 0 || position > list->size) return false;

   Node *newNode = (Node *)malloc(sizeof(Node));
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
bool insertArray(DynamicList *list, const ElementType *array, const int length) {
   if (list == NULL || array == NULL || length < 0)
      return false;

   for (int i = 0; i < length; i++) {
      if (!insertAtEnd(list, array[i])) {
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
int replaceAll(DynamicList *list, const ElementType oldValue, const ElementType newValue) {
   if (list == NULL) return 0;

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
bool replaceFirstOccurrence(DynamicList *list, const ElementType oldValue, const ElementType newValue) {
   if (list == NULL) return false;

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
int findValuePosition(const DynamicList *list, const ElementType value) {
   if (list == NULL) return -1;

   int position = -1;
   int index = 0;
   Node *current = list->sentinel->next;
   while (current != list->sentinel) {
      if (current->data == value) {
         position = index; // update last found position
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
int getListSize(const DynamicList *list) {
   if (list == NULL) return 0;
   return list->size;
}

/*
 * Finds the first occurrence position (0-based) of 'value' in the list.
 * list: pointer to the DynamicList.
 * value: the value to find.
 * Returns the position or -1 if not found.
 */
int findFirst(const DynamicList *list, const ElementType value) {
   if (list == NULL) return -1;

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
 * Removes the node at 'position' (0-based) from the list.
 * list: pointer to the DynamicList.
 * position: index of the node to remove (0-based).
 * Returns true if removal is successful.
 */
bool removeAt(DynamicList *list, const int position) {
   if (list == NULL || position < 0 || position >= list->size) return false;

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
void destroyList(DynamicList *list) {
   if (list == NULL) return;

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
ElementType getAt(const DynamicList *list, const int position) {
   if (list == NULL || position < 0 || position >= list->size) {
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
bool isEmpty(const DynamicList *list) {
   if (list == NULL) return true;
   return (list->size == 0);
}

/*
 * Returns true if the list is full.
 * For dynamic allocation, this returns false (unless malloc fails).
 * list: pointer to the DynamicList.
 * return: true if full, false otherwise.
 */
bool isFull(const DynamicList *list) {
   // Always returns false for dynamic list (limited only by memory)
   // If you want to simulate a full condition, implement a maximum size and check against it in the insert functions.
   return false;
}

/*
 * Prints the elements of the list in order.
 * If the list is empty, prints a corresponding message.
 * list: pointer to the DynamicList.
 * return: void
 */
void printList(const DynamicList *list) {
   if (list == NULL) {
      printf("List is NULL.\n");
      return;
   }

   if (isEmpty(list)) {
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

   DynamicList list;
   initializeList(&list);

   // Insert elements at the end
   insertAtEnd(&list, 5);
   insertAtEnd(&list, 10);

   // Insert element at the beginning
   insertAtBeginning(&list, 1);

   // Insert at position 1 (0-based)
   insertAt(&list, 1, 7);

   // Print current list
   printList(&list); // Expected: 1 7 5 10

   // Insert array of elements at the end
   ElementType arr[] = {20, 25, 30};
   insertArray(&list, arr, 3);
   printList(&list); // Expected: 1 7 5 10 20 25 30

   // Replace all 10 with 15
   int replaced = replaceAll(&list, 10, 15);
   printf("Replaced %d occurrence(s) of 10 with 15\n", replaced);
   printList(&list); // Expected: 1 7 5 15 20 25 30

   // Replace first occurrence of 7 with 8
   bool replacedFirst = replaceFirstOccurrence(&list, 7, 8);
   printf("Replaced first occurrence of 7 with 8? %s\n", replacedFirst ? "Yes" : "No");
   printList(&list); // Expected: 1 8 5 15 20 25 30

   // Find last position of 20
   int lastPos = findValuePosition(&list, 20);
   printf("Last position of 20: %d\n", lastPos); // Expected: 4 (0-based)

   // Get list size
   int size = getListSize(&list);
   printf("List size: %d\n", size); // Expected: 7

   // Find first occurrence of 5
   int firstPos = findFirst(&list, 5);
   printf("First occurrence of 5: %d\n", firstPos); // Expected: 2

   // Check if list is empty or full
   printf("Is list empty? %s\n", isEmpty(&list) ? "Yes" : "No");
   printf("Is list full? %s\n", isFull(&list) ? "Yes" : "No");

   // Get element at position 3
   ElementType val = getAt(&list, 3);
   printf("Element at position 3: %d\n", val); // Expected: 15

   // Remove element at position 1
   bool removed = removeAt(&list, 1);
   printf("Removed element at position 1? %s\n", removed ? "Yes" : "No");
   printList(&list); // Expected: 1 5 15 20 25 30

   // Destroy the list
   destroyList(&list);
   printList(&list); // Expected: List is empty.

   return 0;
}
