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