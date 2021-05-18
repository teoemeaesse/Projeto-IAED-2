#include <string.h>
#include <stdio.h>

#include "macros.h"
#include "stack.h"

Stack * createStack() {
    Stack * stack = SMALLOC(Stack);

    stack->head = NULL;

    return stack;
}

NodeStack * newNodeStack(char * str) {
    NodeStack * node = SMALLOC(NodeStack);

    node->str = MALLOC(strlen(str) + ONE, char);
    strcpy(node->str, str);
    node->next = NULL;

    return node;
}

void push(Stack * stack, char * str) {
    NodeStack * next = newNodeStack(str);

    if(stack->head == NULL) {
        stack->head = next;
        return;
    }

    next->next = stack->head;
    stack->head = next;
}

char * pop(Stack * stack) {
    NodeStack * old_head = stack->head;
    char * str;

    if(stack->head == NULL)
        return NULL;
    
    str = stack->head->str;
    stack->head = stack->head->next;

    free(old_head);

    return str;
}

void destroyStack(Stack * stack) {
    char * str;

    if(stack == NULL)
        return;

    while(stack->head != NULL) {
        str = pop(stack);
        free(str);
    }

    free(stack);
}