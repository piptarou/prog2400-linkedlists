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
}