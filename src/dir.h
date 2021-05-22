#include "stack.h"

struct dir_manager;

typedef struct node_avl {
    struct node_avl * left, * right;
    char * key;
    struct dir_manager * value;
} NodeAVL;

typedef struct {
    NodeAVL * root;
} TreeAVL;

typedef struct dir_manager{
    TreeAVL * subdirs;
    Stack * history;
    char * value;
} DirManager;

TreeAVL * createTreeAVL();
void destroyTreeAVL(TreeAVL * tree);
void insertTreeAVL(TreeAVL * tree, char * key, char * value);
void removeTreeAVL(TreeAVL * tree, char * key);
NodeAVL * maxNodeAVL(NodeAVL * node);
NodeAVL * minNodeAVL(NodeAVL * node);
int containsKeyAVL(TreeAVL * tree, char * str);
void printTree(NodeAVL * root);

DirManager * createDirManager();
void destroyDirManager(DirManager * dirManager);
void addPath(DirManager * dirManager, char * path, char * value);