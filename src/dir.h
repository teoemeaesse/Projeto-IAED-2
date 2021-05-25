/*
    file: dir.h
    author: Tomas Marques ist199338
    description: header file for all the directory / avl tree manipulation functions
*/

#include "list.h"

/* forward declare directory for circular dependency */
struct directory;

/* 
    represents a node in an avl tree 
     - left and right branches;
     - key (directory name)
     - value (directory contents)
*/
typedef struct node_avl {
    struct node_avl * left, * right;
    char * key;
    struct directory * value;
} NodeAVL;

/* represents an avl tree, consisting of its root node */
typedef struct {
    NodeAVL * root;
} TreeAVL;

/* 
    represents a directory
     - TreeAVL containing all its subdirectories
     - Linked list of subdirectory names sorted by oldest to most recently added
     - value (associated string)
*/
typedef struct directory {
    TreeAVL * subdirs;
    List * history;
    char * value;
} Directory;

/* represents a filesystem, containing the root directory */
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