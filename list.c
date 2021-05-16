#include <stdio.h>

#include "macros.h"
#include "list.h"

void insert(List * head, char * value) {
    Node * node = head->head;
    
    while(node->next != NULL)
        node = node->next;
    
    node->next = SMALLOC(Node);
    node->next->value = value;
}