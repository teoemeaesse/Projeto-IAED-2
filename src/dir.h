#include "list.h"

struct directory;

typedef struct node_avl {
    struct node_avl * left, * right;
    char * key;
    struct directory * value;
} NodeAVL;

typedef struct {
    NodeAVL * root;
} TreeAVL;

typedef struct directory {
    TreeAVL * subdirs;
    List * history;
    char * value;
} Directory;

typedef struct {
    Directory * root;
} FileSystem;

TreeAVL * createTreeAVL();
void destroyTreeAVL(TreeAVL * tree);
void insertTreeAVL(TreeAVL * tree, char * key, char * value);
void removeTreeAVL(TreeAVL * tree, char * key);
NodeAVL * maxNodeAVL(NodeAVL * node);
NodeAVL * minNodeAVL(NodeAVL * node);
int containsKeyAVL(TreeAVL * tree, char * key);
NodeAVL * searchAVL(TreeAVL * tree, char * key);
void printTreeAVL(NodeAVL * root);

Directory * createDirectory();
FileSystem * createFileSystem();
void destroyDirectory(Directory * dir);
void destroyFileSystem(FileSystem * fs);
void destroyPath(FileSystem * fs, List * components);
int isEmpty(Directory * dir);
void addDirectory(FileSystem * fs, char * path, char * value);
void printDirectory(Directory * dir, List * path);
Directory * findSubDirectory(Directory * dir, List * path);
List * searchDirectory(Directory * tree, char * value);