/*
    file: list.h
    author: Tomas Marques ist199338
    description: header file for all the linked list manipulation functions
*/

#ifndef _LISTH_
#define _LISTH_

/* represents a node in a linked list, containing a pointer to the next one and a string value */
typedef struct node_list {
    struct node_list * next;
    char * str;
} NodeList;

/* represents a list, containing its head and length */
typedef struct {
    NodeList * head;
    int length;
} List;

List * createList();
int sizeList(List * list);
void insert(List * list, char * str);
void destroyList(List * list);
char * getNth0(List * list, int index);
char * getFirst(List * list);
void removeValue(List * list, char * value);
void removeNth0(List * list, int index);
void removeFirst(List * list);

#endif