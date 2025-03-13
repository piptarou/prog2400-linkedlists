#include "singly_linked_list.h"
#include <stdlib.h>

typedef struct Node {
    void* data;
    struct Node * next;
} Node;

struct LinkedList {
    size_t size;
    struct Node * head;
    struct Node * tail;
};

LinkedList* list_create(void) {
    LinkedList* output = malloc(sizeof(LinkedList));
    if (output == NULL) {
        return NULL;
    }
    output->size = 0;
    output->head = NULL;
    output->tail = NULL;
    return output;
}