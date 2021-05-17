typedef struct node {
    struct node * next;
    char * str;
} Node;

Node * push(Node * head, char * str);
Node * pop(Node * head);
Node * popFirst(Node * head);