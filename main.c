#include <stdio.h>
#include <stdlib.h>
#include "singly_linked_list.h"

int run_test_cases() {

    LinkedList * myLinkedList = list_create();

    size_t actualSize = list_size(myLinkedList);
    if (actualSize != 0) {
        printf("FAILED test case due to size failure on empty list\n");
        return 1;
    }

    // Need to allocate memory on the heap and return a pointer to the memory address
    // for that block of memory then need to take a pointer to an int and store the memory block address.
    // Then have to dereference the pointer to access the block of memory and assign a value
    int * intA = malloc(sizeof(int));
    * intA = 20;
    int result = list_add(myLinkedList, intA);
    if (result != 0) {
        printf("FAILED test case due to failure to add 1\n");
        return 1;
    }

    actualSize = list_size(myLinkedList);
    if (actualSize != 1) {
        printf("FAILED test case due to size failure 2\n");
        return 1;
    }

    int * intB = malloc(sizeof(int));
    * intB = 10;
    result = list_add(myLinkedList, intB);
    if (result != 0) {
        printf("FAILED test case due to failure to add 2\n");
        return 1;
    }

    int * intC = malloc(sizeof(int));
    * intC = 37;
    result = list_add(myLinkedList, intC);
    if (result != 0) {
        printf("FAILED test case due to failure to add 3\n");
        return 1;
    }

    int * intD = malloc(sizeof(int));
    * intD = 12;
    result = list_add(myLinkedList, intD);
    if (result != 0) {
        printf("FAILED test case due to failure to add 3\n");
        return 1;
    }

    int * intE = malloc(sizeof(int));
    * intE = 21;
    result = list_add(myLinkedList, intE);
    if (result != 0) {
        printf("FAILED test case due to failure to add 3\n");
        return 1;
    }

    actualSize = list_size(myLinkedList);
    if (actualSize != 5) {
        printf("FAILED test case due to size failure 2\n");
        return 1;
    }

    int * container;

    result = list_get_at(myLinkedList, 300, (void **)&container);
    if (result != -1) {
        printf("FAILED test case due to failure to handle invalid index\n");
        return 1;
    }

    // test the insert
    int * intF = malloc(sizeof(int));
    *intF = 42;
    result = list_insert_at(myLinkedList, 2, intF);
    if (result != 0) {
        printf("FAILED test case due to failure to insert at valid index\n");
        free(intF);
        return 1;
    }

    result = list_get_at(myLinkedList, 2, (void **)&container);
    if (result != 0 || * container != 42) {
        printf("FAILED test case due to incorrect value after insert\n");
        return 1;
    }

    list_destroy(myLinkedList, free);
    return 0;
}

int main() {
    printf("welcome to the linked list test program!\n");
    int result = run_test_cases();
    if (result == 0){
        printf("Great success!\n");
    } else {
        printf("FAILED!!");
    }
    return 0;
}