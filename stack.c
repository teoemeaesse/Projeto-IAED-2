#include <string.h>
#include <stdio.h>

#include "macros.h"
#include "stack.h"

Node * newNode(char * str) {
    Node * node = SMALLOC(Node);

    node->str = MALLOC(strlen(str) + ONE, char);
    strcpy(node->str, str);
    node->next = NULL;

    return node;
}

void destroyNode(Node * node) {
    free(node->str);
    free(node);
}

Node * push(Node * head, char * str) {
    Node * node = head;

    if(head == NULL)
        return newNode(str);
    
    while(node->next != NULL)
        node = node->next;
    node->next = newNode(str);

    return(head);
}

Node * pop(Node * head) {
    Node * node = head;

    if(head == NULL || head->next == NULL)
        return NULL;

    while(node->next->next != NULL)
        node = node->next;
    
    destroyNode(node->next);
    node->next = NULL;

    return head;
}

Node * popFirst(Node * head) {
    Node * new_head;

    if(head == NULL)
        return NULL;
    if(head->next == NULL) {
        destroyNode(head);
        return NULL;
    }

    new_head = head->next;
    
    destroyNode(head);

    return new_head;
}