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

ValueAVL * createValueStrAVL(char * str);
ValueAVL * createValueIntAVL(int integer);
void destroyValueAVL(ValueAVL * value);
int balanceFactorAVL(NodeAVL * node);
TreeAVL * createTreeAVL();
void destroyTreeAVL(TreeAVL * tree);
void insertTreeAVL(TreeAVL * tree, ValueAVL * value);
void removeTreeAVL(TreeAVL * tree, ValueAVL * value);
NodeAVL * maxNodeAVL(NodeAVL * node);
NodeAVL * minNodeAVL(NodeAVL * node);
void printTreeAVL(NodeAVL * root);