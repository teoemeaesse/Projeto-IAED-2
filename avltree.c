#include <string.h>
#include <stdio.h>

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

int isEqualValueAVL(ValueAVL * value1, ValueAVL * value2) {
    if(value1->type == INT)
        return value1->value->integer == value2->value->integer;

    if(value1->type == STR)
        return strcmp(value1->value->str, value2->value->str) == ZERO ? ONE : ZERO;
    
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

int getChildCount(NodeAVL * node) {
    if(node->left != NULL && node->right != NULL)
        return TWO;
    
    if(node->left != NULL || node->right != NULL)
        return ONE;
    
    return ZERO;
}

NodeAVL * getSingleChild(NodeAVL * node) {
    if(node == NULL)
        return NULL;
    
    if(node->left != NULL && node->right == NULL)
        return node->left;
    
    if(node->right != NULL && node->left == NULL)
        return node->right;
    
    return NULL;
}

ValueAVL * copyValueAVL(ValueAVL * value) {
    if(value == NULL)
        return NULL;

    if(value->type == INT)
        return createValueInt(value->value->integer);
    
    if(value->type == STR)
        return createValueStr(value->value->str);
    
    return NULL;
}

/*void removeTreeAux(NodeAVL * node, ValueAVL * value) {
    NodeAVL * tmp;
    int children;

    if(node == NULL)
        return;

    if(node->left != NULL && node->left->value == value) {
        children = childCount(node->left);

        if(children == ZERO) {
            destroyNodeAVL(node->left);
            node->left = NULL;
        }        
        else if(children == ONE) {
            tmp = node->left;
            node->left = getSingleChild(node->left);
            destroyNodeAVL(tmp);
        }
        else if(children == TWO) {
            tmp = maxNode(node->left->left);
            destroyValue(node->left->value);
            node->left->value = copyValueAVL(tmp->value);
            removeTreeAux(node->left, tmp->value);
        }
    }
    else if(node->right != NULL && node->right->value == value) {
        children = childCount(node->right);

        if(children == ZERO) {
            destroyNodeAVL(node->right);
            node->right = NULL;
        }        
        else if(children == ONE) {
            tmp = node->right;
            node->right = getSingleChild(node->right);
            destroyNodeAVL(tmp);
        }
        else if(children == TWO) {
            tmp = maxNode(node->right->right);
            destroyValue(node->right->value);
            node->right->value = copyValueAVL(tmp->value);
            removeTreeAux(node->right, tmp->value);
        }
    }
    else {
        if(node->left != NULL)
            removeTreeAux(node->left, value);
        if(node->right != NULL)
            removeTreeAux(node->left, value);
    }
}*/

void removeTreeAux(NodeAVL * parent, NodeAVL * node, ValueAVL * value) {
    NodeAVL * tmp;
    int childCount = getChildCount(node);

    /* if node is not what were looking for, recursively check its branches */
    if(!isEqualValueAVL(node->value, value)) {
        switch(childCount) {
            case ZERO:
                return;
            case ONE:
                removeTreeAux(node, getSingleChild(node), value);
                return;
            case TWO:
                removeTreeAux(node, node->left, value);
                removeTreeAux(node, node->right, value);
                return;
        }
    }

    /* node found, now to remove it */
    switch(childCount) {
        case ZERO:
            /* update parent node */
            if(parent->left == node)
                parent->left = NULL;
            else if(parent->right == node)
                parent->right = NULL;
            
            /* free node and return */
            destroyNodeAVL(node);
            return;
        
        case ONE:
            tmp = getSingleChild(node);\

            /* update parent node */
            if(parent->left == node)
                parent->left = tmp;
            else if(parent->right == node)
                parent->right = tmp;
            
            /* free node and return */
            destroyNodeAVL(node);
            return;

        case TWO:
            tmp = maxNode(node->left);

            /* copy rightmost value in left branch to current node */
            destroyValue(node->value);
            node->value = copyValueAVL(tmp->value);

            /* recursively remove rightmost node and return */
            removeTreeAux(node, node->left, tmp->value);
            return;
    }
}

void removeTree(TreeAVL * tree, ValueAVL * value) {
    NodeAVL * tmp;
    int childCount;

    if(tree == NULL || tree->root == NULL || value == NULL)
        return;
    
    /* separate logic for root node, since tree must be updated as well */
    if(isEqualValueAVL(tree->root->value, value)) {
        childCount = getChildCount(tree->root);

        switch(childCount) {
            case ZERO:
                /* update tree and return */
                destroyNodeAVL(tree->root);
                tree->root = NULL;
                return;
            
            case ONE:
                /* update tree and return */
                tmp = getSingleChild(tree->root);
                destroyNodeAVL(tree->root);
                tree->root = tmp;
                return;
            
            case TWO:
                tmp = maxNode(tree->root->left);

                /* copy rightmost value in left branch to root */
                destroyValue(tree->root->value);
                tree->root->value = copyValueAVL(tmp->value);

                /* recursively remove rightmost node and return */
                removeTreeAux(tree->root, tree->root->left, tmp->value);
                return;
        }
    }

    removeTreeAux(NULL, tree->root, value);
}

NodeAVL * maxNode(NodeAVL * node) {
    if(node == NULL || node->right == NULL)
        return node;

    return maxNode(node->right);
}

NodeAVL * minNode(NodeAVL * node) {
    if(node == NULL || node->left == NULL)
        return node;

    return minNode(node->left);
}