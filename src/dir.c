#include <string.h>
#include <stdio.h>

#include "macros.h"
#include "list.h"
#include "dir.h"

int maxAVL(int n1, int n2) {
    return n1 > n2 ? n1 : n2;
}

/*
    createNodeAVL: char *, char * -> NodeAVL *
    
    Allocates memory for and initializes a node
    with copies of the provided key and value
*/
NodeAVL * createNodeAVL(char * key, char * value) {
    NodeAVL * node = SMALLOC(NodeAVL);

    node->key = MALLOC_STR(key);
    strcpy(node->key, key);
    
    node->value = createDirectory();
    if(value != NULL) {
        node->value->value = MALLOC_STR(value);
        strcpy(node->value->value, value);
    }

    node->left = NULL;
    node->right = NULL;
    
    return node;
}

void destroyNodeAVL(NodeAVL * node) {
    free(node->key);
    free(node);
}

int heightAVL(NodeAVL * node) {
    if(node == NULL)
        return -ONE;
    
    return ONE + maxAVL(heightAVL(node->left), heightAVL(node->right));
}

int balanceFactorAVL(NodeAVL * node) {
    if(node == NULL)
        return ZERO;
    
    return heightAVL(node->left) - heightAVL(node->right);
}

TreeAVL * createTreeAVL() {
    TreeAVL * tree = SMALLOC(TreeAVL);

    tree->root = NULL;

    return tree;
}

void destroyTreeAVL(TreeAVL * tree) {
    if(tree == NULL)
        return;

    while(tree->root != NULL)
        removeTreeAVL(tree, tree->root->key);
    
    free(tree);
}

enum Cmp {HIGHER, LOWER, EQUAL, ERROR};
int compareKeysAVL(char * key1, char * key2) {
    if(strcmp(key1, key2) > ZERO)
        return HIGHER;
    else if(strcmp(key1, key2) == ZERO)
        return EQUAL;
    else
        return LOWER;

    return ERROR;
}

NodeAVL * rotateLeftAVL(NodeAVL * pivot) {
    NodeAVL * new = pivot->right;

    if(new == NULL)
        return pivot;

    pivot->right = new->left;
    new->left = pivot;

    return new;
}

NodeAVL * rotateRightAVL(NodeAVL * pivot) {
    NodeAVL * new = pivot->left;

    if(new == NULL)
        return pivot;

    pivot->left = new->right;
    new->right = pivot;

    return new;
}

NodeAVL * balanceRootAVL(NodeAVL * root, char * nkey) {
    int balance;

    if(root == NULL || nkey == NULL)
        return NULL;
    
    balance = balanceFactorAVL(root);

    if(balance > ONE) {
        if(compareKeysAVL(nkey, root->left->key) == HIGHER)
            root->left = rotateLeftAVL(root->left);
        
        return rotateRightAVL(root);
    }
    else if(balance < -ONE) {
        if(compareKeysAVL(nkey, root->right->key) == LOWER)
            root->right = rotateRightAVL(root->right);
        
        return rotateLeftAVL(root);
    }

    return root;
}

NodeAVL * insertTreeAuxAVL(NodeAVL * root, NodeAVL * node) {
    if(root == NULL)
        return node;

    switch (compareKeysAVL(node->key, root->key)) {
        case EQUAL:
        case LOWER:
            root->left = insertTreeAuxAVL(root->left, node);
            break;
        case HIGHER:
            root->right = insertTreeAuxAVL(root->right, node);
            break;
    }

    return balanceRootAVL(root, node->key);
}

void insertTreeAVL(TreeAVL * tree, char * key, char * value) {
    NodeAVL * node;

    if(tree == NULL || key == NULL)
        return;
    
    if(containsKeyAVL(tree, key))
        return;
    
    node = createNodeAVL(key, value);

    if(tree->root == NULL) {
        tree->root = node;
        return;
    }

    tree->root = insertTreeAuxAVL(tree->root, node);
}

int getChildCountAVL(NodeAVL * node) {
    if(node->left != NULL && node->right != NULL)
        return TWO;
    
    if(node->left != NULL || node->right != NULL)
        return ONE;
    
    return ZERO;
}

NodeAVL * getSingleChildAVL(NodeAVL * node) {
    if(node == NULL)
        return NULL;
    
    if(node->left != NULL && node->right == NULL)
        return node->left;
    
    if(node->right != NULL && node->left == NULL)
        return node->right;
    
    return NULL;
}

NodeAVL * removeTreeAuxAVL(NodeAVL * node, char * key, int destructive) {
    NodeAVL * tmp;
    int childCount;

    if(node == NULL)
        return NULL;

    childCount = getChildCountAVL(node);

    if(compareKeysAVL(node->key, key) == EQUAL) {
        switch(childCount) {
            case ZERO:
                /* free node and return */
                if(destructive == ONE)
                    destroyDirectory(node->value);
                destroyNodeAVL(node);

                return NULL;

            case ONE:
                tmp = getSingleChildAVL(node);
                
                /* free node and link parent with child */
                if(destructive == ONE)
                    destroyDirectory(node->value);
                destroyNodeAVL(node);

                return tmp;

            case TWO:
                tmp = maxNodeAVL(node->left);

                /* move rightmost node in left branch to current node */
                destroyDirectory(node->value);
                node->value = tmp->value;

                /* recursively remove rightmost node and return updated node */
                node->left = removeTreeAuxAVL(node->left, tmp->key, ZERO);

                return node;
        }
    }

    node = balanceRootAVL(node, key);

    /* if node is not what were looking for, recursively check its branches */
    node->left = removeTreeAuxAVL(node->left, key, destructive);
    node->right = removeTreeAuxAVL(node->right, key, destructive);

    return node;
}

void removeTreeAVL(TreeAVL * tree, char * key) {
    if(tree == NULL || tree->root == NULL || key == NULL)
        return;

    tree->root = removeTreeAuxAVL(tree->root, key, ONE);
}

NodeAVL * maxNodeAVL(NodeAVL * node) {
    if(node == NULL || node->right == NULL)
        return node;

    return maxNodeAVL(node->right);
}

NodeAVL * minNodeAVL(NodeAVL * node) {
    if(node == NULL || node->left == NULL)
        return node;

    return minNodeAVL(node->left);
}

int containsKeyAVL(TreeAVL * tree, char * key) {
    if(tree == NULL || key == NULL)
        return ZERO;

    return searchAVL(tree, key) != NULL;
}

NodeAVL * searchAuxAVL(NodeAVL * node, char * key) {
    if(node == NULL || key == NULL)
        return NULL;

    if(compareKeysAVL(key, node->key) == EQUAL)
        return node;
    
    switch(compareKeysAVL(key, node->key)) {
        case LOWER:
            return searchAuxAVL(node->left, key);
        case HIGHER:
            return searchAuxAVL(node->right, key);
    }
    
    return NULL;
}

NodeAVL * searchAVL(TreeAVL * tree, char * key) {
    if(tree == NULL || key == NULL)
        return NULL;

    return searchAuxAVL(tree->root, key);
}

void printTreeAVL(NodeAVL * root, List * path) {
    int i;

    if(root == NULL)
        return;
    
    insert(path, root->key);
    printTreeAVL(root->left, path);
    printTreeAVL(root->right, path);
    removeNth0(path, sizeList(path) - ONE);

    for(i = ZERO; i < sizeList(path); i++)
        printf("/%s", getNth0(path, i));
    printf(" %s\n", root->value->value);
}

/* DIRECTORY FUNCTIONS */

Directory * createDirectory() {
    Directory * dir = SMALLOC(Directory);

    dir->subdirs = createTreeAVL();
    dir->history = createList();
    dir->value = NULL;

    return dir;
}

FileSystem * createFileSystem() {
    FileSystem * fs = SMALLOC(FileSystem);

    fs->root = createDirectory();

    return fs;
}

void destroyDirectory(Directory * dir) {
    if(dir == NULL)
        return;
    
    destroyTreeAVL(dir->subdirs);
    destroyList(dir->history);
    
    free(dir->value);
    free(dir);
}

void destroyFileSystem(FileSystem * fs) {
    destroyDirectory(fs->root);
    free(fs);
}

int isSubDirectory(Directory * dir, char * sub) {
    if(dir == NULL || dir->subdirs == NULL || sub == NULL)
        return ZERO;

    return containsKeyAVL(dir->subdirs, sub);
}

int isEmpty(Directory * dir) {
    if(dir == NULL)
        return ZERO;
    
    return dir->subdirs->root == NULL;
}

Directory * addDirectoryAux(Directory * dir, List * components, char * value) {
    NodeAVL * target;
    char * first;
    
    if(dir == NULL)
        return NULL;

    first = MALLOC_STR(getFirst(components));
    strcpy(first, getFirst(components));

    if(isSubDirectory(dir, first)) {
        if(sizeList(components) == ONE) {
            target = searchAVL(dir->subdirs, first);

            if(target->value->value == NULL) 
                target->value->value = MALLOC_STR(value);

            strcpy(target->value->value, value);
        }
        else {
            removeFirst(components);

            target = searchAVL(dir->subdirs, first);

            target->value = addDirectoryAux(target->value, components, value);
        }
    }
    else {
        if(sizeList(components) == ONE) {
            insert(dir->history, first);

            insertTreeAVL(dir->subdirs, first, value);
        }
        else {
            removeFirst(components);

            insert(dir->history, first);
            
            insertTreeAVL(dir->subdirs, first, NULL);
            
            target = searchAVL(dir->subdirs, first);
            target->value = addDirectoryAux(target->value, components, value);
        }
    }

    free(first);
    
    return dir;
}

void addDirectory(FileSystem * fs, char * path, char * value) {
    List * components;
    char * token;

    if(fs == NULL || path == NULL || value == NULL)
        return;

    components = createList();
    
    token = strtok(path, PATH_SEPARATOR_STR);
    while(token != NULL) {
        insert(components, token);
        token = strtok(NULL, PATH_SEPARATOR_STR);
    }

    if(sizeList(components) != ZERO)
        fs->root = addDirectoryAux(fs->root, components, value);

    destroyList(components);
}

void printFileSystemAux(Directory * dir, List * path) {
    NodeAVL * target;
    int i, j, len;
    char * tmp;

    if(dir == NULL)
        return;

    for(i = ZERO; (tmp = getNth0(dir->history, i)) != NULL; i++) {
        insert(path, tmp);
        len = sizeList(path);
        
        target = searchAVL(dir->subdirs, tmp);
        printFileSystemAux(target->value, path);

        if(target->value->value != NULL) {
            for(j = ZERO; j < len; j++)
                printf("/%s", getNth0(path, j));
            printf(" %s", target->value->value);
            putchar('\n');
        }

        removeNth0(path, len - ONE);
    }
}

void printFileSystem(FileSystem * fs) {
    List * path;

    if(fs == NULL || fs->root == NULL)
        return;
    
    path = createList();

    printFileSystemAux(fs->root, path);

    destroyList(path);
}