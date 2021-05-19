#include <string.h>

#include "macros.h"
#include "avltree.h"

ValueAVL * createValueStr(char * str) {
    ValueAVL * value = SMALLOC(ValueAVL);   

    value->type = STR;
    value->value = SMALLOC(ValueAVLUnion);

    value->value->str = MALLOC_STR(str);
    strcpy(value->value->str, str);

    return value;
}

ValueAVL * createValueInt(int integer) {
    ValueAVL * value = SMALLOC(ValueAVL);   

    value->type = INT;
    value->value = SMALLOC(ValueAVLUnion);

    value->value->integer = integer;

    return value;
}

void destroyValue(ValueAVL * value) {
    if(value == NULL || value->value == NULL)
        return;
    
    if(value->type == STR)
        free(value->value->str);

    free(value->value);
    free(value);
}

NodeAVL * createNodeAVL(ValueAVL * value) {
    NodeAVL * node = SMALLOC(NodeAVL);

    node->value = value;
    node->left = NULL;
    node->right = NULL;
    
    return node;
}

void destroyNodeAVL(NodeAVL * node) {
    destroyValue(node->value);
    free(node);
}

TreeAVL * createTree() {
    TreeAVL * tree = SMALLOC(TreeAVL);

    tree->root = NULL;

    return tree;
}

void destroyTree(TreeAVL * tree);

typedef enum Cmp {HIGHER, LOWER, ERROR} Cmp;
int compareNodeAVL(NodeAVL * node1, NodeAVL * node2) {
    if(node1->value->type == INT)
        return(node1->value->value->integer > node2->value->value->integer ? HIGHER : LOWER);
    
    if(node1->value->type == STR) {
        if(strcmp(node1->value->value->str, node2->value->value->str) > ZERO)
            return HIGHER;
        return LOWER;
    }

    return ERROR;
}

void insertTreeAux(NodeAVL * root, NodeAVL * node) {
    switch (compareNodeAVL(node, root)) {
        case HIGHER:
            if(root->right == NULL)
                root->right = node;
            else
                insertTreeAux(root->right, node);
            break;
        case LOWER:
            if(root->left == NULL)
                root->left = node;
            else
                insertTreeAux(root->left, node);
            break;
    }
}

void insertTree(TreeAVL * tree, ValueAVL * value) {
    NodeAVL * node;

    if(tree == NULL || value == NULL)
        return;
    
    node = createNodeAVL(value);

    if(tree->root == NULL) {
        tree->root = node;
        return;
    }

    insertTreeAux(tree->root, node);
}