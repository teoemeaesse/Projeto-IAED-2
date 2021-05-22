#include <string.h>
#include <stdio.h>

#include "macros.h"
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
    
    node->value = createDirManager();
    node->value->value = MALLOC_STR(value);
    strcpy(node->value->value, value);

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

    if(tree == NULL || key == NULL || value == NULL)
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
                    destroyDirManager(node->value);
                destroyNodeAVL(node);

                return NULL;

            case ONE:
                tmp = getSingleChildAVL(node);
                
                /* free node and link parent with child */
                if(destructive == ONE)
                    destroyDirManager(node->value);
                destroyNodeAVL(node);

                return tmp;

            case TWO:
                tmp = maxNodeAVL(node->left);

                /* move rightmost node in left branch to current node */
                destroyDirManager(node->value);
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

int containsAuxAVL(NodeAVL * node, char * key) {
    if(node == NULL || key == NULL)
        return ZERO;

    if(compareKeysAVL(key, node->key) == EQUAL)
        return ONE;
    
    switch(compareKeysAVL(key, node->key)) {
        case LOWER:
            if(containsAuxAVL(node->left, key) == ONE)
                return ONE;
            break;
        case HIGHER:
            if(containsAuxAVL(node->right, key) == ONE)
                return ONE;
            break;
    }
    
    return ZERO;
}

int containsKeyAVL(TreeAVL * tree, char * key) {
    if(tree == NULL || key == NULL)
        return ZERO;

    return containsAuxAVL(tree->root, key);
}

void printTree(NodeAVL * root) {
    if(root == NULL)
        return;
    
    printTree(root->left);
    printf("[h: %d; val: %s]\n", balanceFactorAVL(root), root->value->value);
    printTree(root->right);
}

/* DIRECTORY FUNCTIONS */

DirManager * createDirManager() {
    DirManager * dirManager = SMALLOC(DirManager);

    dirManager->subdirs = NULL;
    dirManager->history = NULL;
    dirManager->value = NULL;

    return dirManager;
}

void destroyDirManager(DirManager * dirManager) {
    if(dirManager == NULL)
        return;
    
    if(dirManager->subdirs != NULL)
        destroyTreeAVL(dirManager->subdirs);
    
    if(dirManager->history != NULL)
        destroyStack(dirManager->history);
    
    free(dirManager->value);
    free(dirManager);
}

/*int isSubDirectory(TreeAVL * dir, char * sub) {
    
}

void addPath(DirManager * dirManager, char * path, char * value) {

}*/
