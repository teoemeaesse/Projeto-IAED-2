typedef struct node_list {
    struct node_list * next;
    char * str;
} NodeList;

typedef struct {
    NodeList * head;
    int length;
} List;

List * createList();
void insert(List * list, char * str);
void destroyList(List * list);
char * getNth0(List * list, int index);
char * getFirst(List * list);
void removeNth0(List * list, int index);
void removeFirst(List * list);