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

    // test list_remove_at
    void* removed_data;
    result = list_remove_at(myLinkedList, 2, &removed_data);
    if (result != 0) {
        printf("FAILED test case due to failure to remove at valid index\n");
        return 1;
    }

    int* removed_int = (int*)removed_data;
    if (*removed_int != 42) {
        printf("FAILED test case due to incorrect value removed\n");
        return 1;
    }
    free(removed_data);

    actualSize = list_size(myLinkedList);
    if (actualSize != 5) {
        printf("FAILED test case due to incorrect size after removal\n");
        return 1;
    }

    list_destroy(myLinkedList, free);
    return 0;
}

// linked list merge sort

int compare_ints(void * a, void * b) {
    int * int_a = (int *)a;
    int * int_b = (int *)b;
    return *int_a - *int_b;
}

int test_list_sort() {
    LinkedList * list = list_create();
    int * values[5];
    int unsorted[] = {42, 17, 9, 36, 25};

    for (int i = 0; i < 5; i++) {
        values[i] = malloc(sizeof(int));
        if (values[i] == NULL) {
            printf("FAILED test case due to memory allocation failure\n");
            for (int j = 0; j < i; j++) {
                free(values[j]);
            }
            list_destroy(list, NULL);
            return 1;
        }

        * values[i] = unsorted[i];
        int result = list_add(list, values[i]);
        if (result != 0) {
            printf("FAILED test case due to failure to add element\n");
            for (int j = 0; j <= i; j++) {
                free(values[j]);
            }
            list_destroy(list, NULL);
            return 1;
        }
    }

    printf("Original list: ");
    void * data;
    for (size_t i = 0; i < 5; i++) {
        list_get_at(list, i, &data);
        printf("%d ", * (int *)data);
    }
    printf("\n");

    int result = list_sort(list, compare_ints);
    if (result != 0) {
        printf("FAILED test case due to sort failure\n");
        list_destroy(list, free);
        return 1;
    }

    printf("Sorted list: ");
    int expected[] = {9, 17, 25, 36, 42};

    for (size_t i = 0; i < 5; i++) {
        result = list_get_at(list, i, &data);
        if (result != 0) {
            printf("FAILED test case due to failure to get element\n");
            list_destroy(list, free);
            return 1;
        }

        int value = * (int *)data;
        printf("%d ", value);

        if (value != expected[i]) {
            printf("\nFAILED test case due to incorrect sorting\n", i);
            list_destroy(list, free);
            return 1;
        }
    }
    list_destroy(list, free);
    return 0;
}

int main() {
    printf("welcome to the linked list test program!\n");
    int result = run_test_cases();
    if (result == 0){
        printf("Great success!\n");
    } else
    {
        printf("FAILED!!\n");
    }

    result = test_list_sort();
    if (result == 0) {
        printf("Great success! All tests passed.\n");
    } else {
        printf("FAILED sort test!\n");
    }
    return 0;
}