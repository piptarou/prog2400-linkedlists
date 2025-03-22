#include "singly_linked_list.h"
#include <stdlib.h>

typedef struct Node {
    void * data;
    struct Node * next;
} Node;

struct LinkedList {
    size_t size;
    struct Node * head;
    struct Node * tail;
};

LinkedList * list_create(void) {
    LinkedList * output = malloc(sizeof(LinkedList));
    if (output == NULL) {
        return NULL;
    }
    output->size = 0;
    output->head = NULL;
    output->tail = NULL;
    return output;
}

int list_add(LinkedList * list, void * data) {
    if (list == NULL) return -1;

    Node * newNode = malloc(sizeof(Node));
    if(newNode == NULL) return -1;
    newNode->next = NULL;
    newNode->data = data;

    if (list->size == 0) {
        list->head = newNode;
    } else {
        list->tail->next = newNode;
    }

    list->tail = newNode;
    list->size += 1;
    return 0;
}

int list_insert_at(LinkedList * list, size_t index, void * data) {
    if (list == NULL) return -1;
    if (index > list->size) return -1;

    Node * newNode = malloc(sizeof(Node));
    if(newNode == NULL) return -1;
    newNode->data = data;

    if (index == 0) {
        newNode->next = list->head;
        list->head = newNode;
    } else {
        Node * cursor = list->head;
        for (size_t i = 0; i < index - 1; i++) {
            cursor = cursor->next;
        }

        newNode->next = cursor->next;
        cursor->next = newNode;
    }

    if (index == list->size) {
        list->tail = newNode;
    }

    list->size += 1;
    return 0;
}

int list_get_at(LinkedList * list, size_t index, void ** out_data)
{
    if (list == NULL) return -1;
    if (index >= list->size) return -1;
    if (out_data == NULL) return -1;

    Node * cursor = list->head;
    for (size_t i = 0; i < index; i++) {
        cursor = cursor->next;
    }

    * out_data = cursor->data;
    return 0;
}

int list_remove_at(LinkedList * list, size_t index, void ** out_data)
{
    if (list == NULL) return -1;
    if (index >= list->size) return -1;
    if (out_data == NULL) return -1;

    Node * current = list->head;
    Node * previous = NULL;

    for (size_t i = 0; i < index; i++) {
        previous = current;
        current = current->next;
    }

    * out_data = current->data;

    if (previous == NULL) {
        list->head = current->next;
    } else {
        previous->next = current->next;
    }
    if (current->next == NULL) {
        list->tail = previous;
    }

    free(current);
    list->size--;
    return 0;
}

size_t list_size(const LinkedList * list)
{
    if (list == NULL) return 0;
    return list->size;
}

void list_destroy(LinkedList * list, void (* free_func)(void *))
{
    if (list == NULL) return;
    if (list->size == 0) {
        free(list);
        return;
    }
    Node * cursor = list->head;
    while (cursor->next != NULL) {
        Node * toDelete = cursor;
        cursor = cursor->next;

        if (free_func != NULL) {
            free_func(toDelete->data);
        }
        free(toDelete);
    }
    free(list);
    free(cursor);
}

// split linked list
static void list_split(Node * head, Node ** a, Node ** b, size_t size) {
    if (head == NULL || head->next == NULL) {
        * a = head;
        * b = NULL;
        return;
    }

    size_t middle = size / 2;
    Node * current = head;

    for (size_t i = 0; i < middle - 1; i++) {
        current = current->next;
    }

    * a = head;
    * b = current->next;
    current->next = NULL; // this is need to split the linked list into 2 fully separate lists
}

// Merge two sorted linked lists by rearranging pointers
// Uses a compare function pointer for generic data comparison
static Node *merge(Node *a, Node *b, int (*compare_func)(void *, void *)) {
    // Base cases - return the non-empty list when one list is exhausted
    if (a == NULL) return b;
    if (b == NULL) return a;

    Node *result = NULL;

    // Recursively build the merged list by selecting smaller element
    // compare_func returns ≤0 if a's data should come before b's data
    // This implementation maintains stability (equal elements preserve original order)
    if (compare_func(a->data, b->data) <= 0) {
        result = a;  // Take node from list a
        // Recursively process the rest of list a with all of list b
        result->next = merge(a->next, b, compare_func);
    } else {
        result = b;  // Take node from list b
        // Recursively process all of list a with the rest of list b
        result->next = merge(a, b->next, compare_func);
    }

    return result;
}

// Recursive merge sort function - implements divide and conquer strategy
static void merge_sort(Node **headRef, size_t size, int (*compare_func)(void *, void *)) {
    Node * head = *headRef;

    // Base case - nothing to sort (empty list or single node is already sorted)
    if (head == NULL || head->next == NULL) {
        return;
    }

    Node *a;  // Will point to first half of the list
    Node *b;  // Will point to second half of the list

    // Split the list into two sublists - O(n/2) operation
    list_split(head, &a, &b, size);

    // Calculate sizes for recursive calls - important for efficient splitting
    size_t a_size = size / 2;         // First half size
    size_t b_size = size - a_size;    // Second half size (handles odd-length lists correctly)

    // Recursively sort both sublists - T(n/2) work for each half
    merge_sort(&a, a_size, compare_func);
    merge_sort(&b, b_size, compare_func);

    // Merge the two sorted sublists - O(n) operation
    // This operation completes the merge sort for this level of recursion
    *headRef = merge(a, b, compare_func);
}

// Main sorting function - public interface for the merge sort implementation
int list_sort(LinkedList * list, int (* compare_func)(void *, void *)) {
    // Validate inputs - return error code (-1) for invalid parameters
    if (list == NULL) return -1;  // Cannot sort a NULL list
    if (compare_func == NULL) return -1;  // Need a valid comparison function
    if (list->size <= 1) return 0; // Already sorted - optimization for empty or single-element lists

    // Perform the merge sort - modifies list->head in place
    // Time complexity: O(n log n) where n is the number of elements
    merge_sort(&(list->head), list->size, compare_func);

    // Update tail pointer after sorting - essential for LinkedList integrity
    // Many operations depend on having a valid tail pointer
    Node *current = list->head;
    while (current != NULL && current->next != NULL) {
        current = current->next;
    }
    list->tail = current;  // Set tail to the last node in the sorted list

    return 0;
}