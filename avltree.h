typedef enum Type {STR, INT} Type;

typedef union {
    char * str;
    int integer;
} ValueAVLUnion;

typedef struct {
    ValueAVLUnion * value;
    Type type;
} ValueAVL;

typedef struct node_avl {
    struct node_avl * left, * right;
    ValueAVL * value;
} NodeAVL;

typedef struct {
    NodeAVL * root;
} TreeAVL;

ValueAVL * createValueStr(char * str);
ValueAVL * createValueInt(int integer);
TreeAVL * createTree();
void destroyTree(TreeAVL * tree);
void insertTree(TreeAVL * tree, ValueAVL * value);
void removeTree(TreeAVL * tree, ValueAVL * value);
NodeAVL * maxNode(NodeAVL * node);
NodeAVL * minNode(NodeAVL * node);
