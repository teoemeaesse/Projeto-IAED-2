#include <string.h>
#include <stdio.h>

#include "macros.h"
#include "list.h"

List * createList() {
    List * list = SMALLOC(List);

    list->head = NULL;
    list->length = ZERO;

    return list;
}

NodeList * newNodeList(char * str) {
    NodeList * node;

    if(str == NULL)
        return NULL;

    node = SMALLOC(NodeList);
    node->str = MALLOC(strlen(str) + ONE, char);
    strcpy(node->str, str);
    node->next = NULL;

    return node;
}

void destroyNodeList(NodeList * node) {
    free(node->str);
    free(node);
}

void insert(List * list, char * str) {
    NodeList * node;

    if(list == NULL || str == NULL)
        return;
    
    list->length++;

    if(list->head == NULL) {
        list->head = newNodeList(str);
        return;
    }
    
    node = list->head;
    while(node->next != NULL)
        node = node->next;
    
    node->next = newNodeList(str);
}

void destroyList(List * list) {
    NodeList * node;

    if(list == NULL)
        return;
    if(list->head == NULL) {
        free(list);
        return;
    }

    while(list->head->next != NULL) {
        node = list->head;
        list->head = list->head->next;
        
        destroyNodeList(node);
    }

    destroyNodeList(list->head);

    free(list);
}

char * getNth0(List * list, int index) {
    NodeList * node;
    int count = ZERO;

    if(list == NULL || list->head == NULL || index >= list->length || index < ZERO)
        return NULL;
    
    node = list->head;
    while(count++ < index)
        node = node->next;
    
    return node->str;
}

char * getFirst(List * list) {
    return getNth0(list, ZERO);
}

void removeNth0(List * list, int index) {
    NodeList * node, * previous;
    int count = ZERO;

    if(list == NULL || list->head == NULL || index >= list->length || index < ZERO)
        return;
    
    list->length--;

    if(list->head->next == NULL) {
        destroyNodeList(list->head);
        list->head = NULL;
        return;
    }

    node = list->head;
    if(index == ZERO) {
        list->head = list->head->next;
        destroyNodeList(node);
        return;
    }
    while(count++ < index) {
        previous = node;
        node = node->next;
    }

    previous->next = node->next;
    destroyNodeList(node);
}

void removeFirst(List * list) {
    removeNth0(list, ZERO);
}