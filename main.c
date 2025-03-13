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

    int result = list_add(myLinkedList, 20);
    if (result != 0) {
        printf("FAILED test case due to failure to add 1\n");
        return 1;
    }

    actualSize = list_size(myLinkedList);
    if (actualSize != 1) {
        printf("FAILED test case due to size failure 2\n");
        return 1;
    }

    // at this point the code just says FAILED!! and not the designated printf

    result = list_add(myLinkedList, 5);
    if (result != 0) {
        printf("FAILED test case due to failure to add 2\n");
        return 1;
    }

    result = list_add(myLinkedList, 37);
    if (result != 0) {
        printf("FAILED test case due to failure to add 3\n");
        return 1;
    }

    result = list_add(myLinkedList, 12);
    if (result != 0) {
        printf("FAILED test case due to failure to add 3\n");
        return 1;
    }

    result = list_add(myLinkedList, 21);
    if (result != 0) {
        printf("FAILED test case due to failure to add 3\n");
        return 1;
    }

    // code now passes???

    actualSize = list_size(myLinkedList);
    if (actualSize != 5) {
        printf("FAILED test case due to size failure 2\n");
        return 1;
    }

    // looks like actualSize is failing

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