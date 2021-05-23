#ifndef _LISTH_
#define _LISTH_

typedef struct node_list {
    struct node_list * next;
    char * str;
} NodeList;

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
NodeList * searchList(List * list, char * value);
void removeValue(List * list, char * value);
void removeNth0(List * list, int index);
void removeFirst(List * list);

#endif