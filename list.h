typedef struct {
    char * value;
    struct Node * next;
} Node;

typedef struct {
    Node * head;
} List;

void insert(List * head, char * value);
//void destroy(List * head);
//List * removeHead(List * head);
//List * removeTail(List * head);