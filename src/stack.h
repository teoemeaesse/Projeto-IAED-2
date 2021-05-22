#ifndef _STACKH_
#define _STACKH_

typedef struct node_stack {
    struct node_stack * next;
    char * str;
} NodeStack;

typedef struct {
    NodeStack * head;
} Stack; 

Stack * createStack();
void push(Stack * stack, char * str);
char * pop(Stack * stack);
void destroyStack(Stack * stack);

#endif