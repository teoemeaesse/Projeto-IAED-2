#include <string.h>
#include <stdio.h>

#include "macros.h"
#include "avltree.h"

int maxAVL(int n1, int n2) {
    return n1 > n2 ? n1 : n2;
}

ValueAVL * createValueStrAVL(char * str) {
    ValueAVL * value = SMALLOC(ValueAVL);   

    value->type = STR;
    value->value = SMALLOC(ValueAVLUnion);

    value->value->str = MALLOC_STR(str);
    strcpy(value->value->str, str);

    return value;
}

ValueAVL * createValueIntAVL(int integer) {
    ValueAVL * value = SMALLOC(ValueAVL);   

    value->type = INT;
    value->value = SMALLOC(ValueAVLUnion);

    value->value->integer = integer;

    return value;
}

ValueAVL * copyValueAVL(ValueAVL * value) {
    if(value == NULL)
        return NULL;

    if(value->type == INT)
        return createValueIntAVL(value->value->integer);
    
    if(value->type == STR)
        return createValueStrAVL(value->value->str);
    
    return NULL;
}

void destroyValueAVL(ValueAVL * value) {
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
    destroyValueAVL(node->value);
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
        removeTreeAVL(tree, tree->root->value);
}

typedef enum Cmp {HIGHER, LOWER, EQUAL, ERROR} Cmp;
int compareValueAVL(ValueAVL * value1, ValueAVL * value2) {
    if(value1->type == INT) {
        if(value1->value->integer > value2->value->integer)
            return HIGHER;
        else if(value1->value->integer == value2->value->integer)
            return EQUAL;
        else
            return LOWER;
    }
    if(value1->type == STR) {
        if(strcmp(value1->value->str, value2->value->str) > ZERO)
            return HIGHER;
        else if(strcmp(value1->value->str, value2->value->str) == ZERO)
            return EQUAL;
        else
            return LOWER;
    }

    return ERROR;
}

NodeAVL * rotateLeftAVL(NodeAVL * pivot) {
    NodeAVL * new = pivot->right;
    pivot->right = new->left;
    new->left = pivot;

    return new;
}

NodeAVL * rotateRightAVL(NodeAVL * pivot) {
    NodeAVL * new = pivot->left;
    pivot->left = new->right;
    new->right = pivot;

    return new;
}

NodeAVL * balanceRootAVL(NodeAVL * root, ValueAVL * value) {
    int balance;

    if(root == NULL || value == NULL)
        return NULL;
    
    balance = balanceFactorAVL(root);

    if(balance > ONE) {
        if(compareValueAVL(value, root->left->value) == HIGHER)
            root->left = rotateLeftAVL(root->left);
        
        return rotateRightAVL(root);
    }
    else if(balance < -ONE) {
        if(compareValueAVL(value, root->right->value) == LOWER)
            root->right = rotateRightAVL(root->right);
        
        return rotateLeftAVL(root);
    }

    return root;
}

NodeAVL * insertTreeAuxAVL(NodeAVL * root, NodeAVL * node) {
    if(root == NULL)
        return node;

    switch (compareValueAVL(node->value, root->value)) {
        case EQUAL:
        case LOWER:
            root->left = insertTreeAuxAVL(root->left, node);
            break;
        case HIGHER:
            root->right = insertTreeAuxAVL(root->right, node);
            break;
    }

    return balanceRootAVL(root, node->value);
}

void insertTreeAVL(TreeAVL * tree, ValueAVL * original) {
    ValueAVL * value;
    NodeAVL * node;

    if(tree == NULL || original == NULL)
        return;
    
    value = copyValueAVL(original);
    node = createNodeAVL(value);

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

NodeAVL * removeTreeAuxAVL(NodeAVL * node, ValueAVL * value) {
    NodeAVL * tmp;
    int childCount;

    if(node == NULL)
        return NULL;

    childCount = getChildCountAVL(node);

    if(compareValueAVL(node->value, value) == EQUAL) {
        switch(childCount) {
            case ZERO:
                /* free node and return */
                destroyNodeAVL(node);

                return NULL;

            case ONE:
                tmp = getSingleChildAVL(node);
                
                /* free node and return child */
                destroyNodeAVL(node);

                return tmp;

            case TWO:
                tmp = maxNodeAVL(node->left);

                /* copy rightmost value in left branch to current node */
                destroyValueAVL(node->value);
                node->value = copyValueAVL(tmp->value);

                /* recursively remove rightmost node and return updated node */
                node->left = removeTreeAuxAVL(node->left, tmp->value);

                return node;
        }
    }

    node = balanceRootAVL(node, value);

    /* if node is not what were looking for, recursively check its branches */
    node->left = removeTreeAuxAVL(node->left, value);
    node->right = removeTreeAuxAVL(node->right, value);

    return node;
}

void removeTreeAVL(TreeAVL * tree, ValueAVL * value) {
    if(tree == NULL || tree->root == NULL || value == NULL)
        return;

    tree->root = removeTreeAuxAVL(tree->root, value);
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

void printTree(NodeAVL * root) {
    if(root == NULL)
        return;
    
    printTree(root->left);
    printf("[h: %d; val: %d]\n", balanceFactorAVL(root), root->value->value->integer);
    printTree(root->right);
}