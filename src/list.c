/*
    file: list.c
    author: Tomas Marques ist199338
    description: implementation of all the linked list manipulation functions
*/

#include <string.h>
#include <stdio.h>

#include "macros.h"
#include "list.h"

/*
    createList: () -> List *
        allocates memory for and initializes an empty list
*/
List * createList() {
    List * list = SMALLOC(List);

    list->head = NULL;
    list->length = ZERO;

    return list;
}

/*
    sizeList: List * -> int
        simple getter method, returns the length of a given list
*/
int sizeList(List * list) {
    /* guard for null parameter */
    if(list == NULL)
        return ZERO;
    
    return list->length;
}

/*
    newNodeList: char * -> NodeList *
        allocates memory for and initializes a node with a copy of a given value
*/
NodeList * newNodeList(char * str) {
    NodeList * node;

    /* guard for null parameter */
    if(str == NULL)
        return NULL;

    node = SMALLOC(NodeList);
    node->str = MALLOC_STR(str);
    strcpy(node->str, str);
    node->next = NULL;

    return node;
}

/*
    destroyNodeList: NodeList * -> ()
        frees all memory associated with a given node
*/
void destroyNodeList(NodeList * node) {
    free(node->str);
    free(node);
}

/*
    insert: List *, char * -> ()
        inserts a string at the end of a linked list
*/
void insert(List * list, char * str) {
    NodeList * node;

    /* guard for null parameters */
    if(list == NULL || str == NULL)
        return;
    
    /* update list length */
    list->length++;

    /* empty list case */
    if(list->head == NULL) {
        list->head = newNodeList(str);
        return;
    }
    
    /* list is not empty - iterate until we reach the last node */
    node = list->head;
    while(node->next != NULL)
        node = node->next;
    
    /* add node at the end of the list */
    node->next = newNodeList(str);
}

/*
    destroyList: List * -> ()
        frees up all memory associated with a given list
*/
void destroyList(List * list) {
    NodeList * node;

    /* guard for null parameter */
    if(list == NULL)
        return;

    /* empty list case */
    if(list->head == NULL) {
        free(list);
        return;
    }

    /* iterate over all the nodes, destroying them */
    while(list->head->next != NULL) {
        node = list->head;
        list->head = list->head->next;
        
        destroyNodeList(node);
    }

    destroyNodeList(list->head);

    free(list);
}

/*
    getNth0: List *, int -> char *
        return the nth value of the linked list, starting at 0
*/
char * getNth0(List * list, int index) {
    NodeList * node;
    int count = ZERO;

    /* guard for null parameter / invalid index */
    if(list == NULL || list->head == NULL || index >= list->length || index < ZERO)
        return NULL;
    
    /* count out iterations until count == index */
    node = list->head;
    while(count++ < index)
        node = node->next;
    
    /* return the index-th string */
    return node->str;
}

/*
    getFirst: List * -> char *
        returns the first value of a given list
*/
char * getFirst(List * list) {
    return getNth0(list, ZERO);
}

/*
    removeValue: List *, char * -> ()
        removes a given value from a linked list
*/
void removeValue(List * list, char * value) {
    NodeList * node, * previous;

    /* guard for null parameters */
    if(list == NULL || list->head == NULL || value == NULL)
        return;

    /* first element case */
    node = list->head;
    if(IS_EQUAL_STR(value, list->head->str)) {
        list->head = list->head->next;
        destroyNodeList(node);
        list->length--;
        return;
    }
    
    /* first element does not contain the value - iterate until it is found */
    while(node != NULL) {
        if(IS_EQUAL_STR(value, node->str)) {
            previous->next = node->next;
            destroyNodeList(node);
            list->length--;
            return;
        }

        /* next node */
        previous = node;
        node = node->next;
    }
}

/*
    removeNth0: List *, int -> ()
        removes the nth element from a list
*/
void removeNth0(List * list, int index) {
    NodeList * node, * previous;
    int count = ZERO;

    /* guard for null parameter / invalid index */
    if(list == NULL || list->head == NULL || index >= list->length || index < ZERO)
        return;
    
    /* update list length */
    list->length--;

    /* first element case */
    node = list->head;
    if(index == ZERO) {
        list->head = list->head->next;
        destroyNodeList(node);
        return;
    }

    /* iterate over list until count == index */
    while(count++ < index) {
        previous = node;
        node = node->next;
    }

    /* remove index-th element from list */
    previous->next = node->next;
    destroyNodeList(node);
}

/*
    removeFirst: List * -> ()
        removes first element from a given list
*/
void removeFirst(List * list) {
    removeNth0(list, ZERO);
}