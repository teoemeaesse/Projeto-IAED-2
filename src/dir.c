/*
    file: dir.c
    author: Tomas Marques ist199338
    description: implementation of all the directory / avl tree manipulation functions
*/

#include <string.h>
#include <stdio.h>

#include "macros.h"
#include "dir.h"
#include "input.h"

/*
    maxAVL: int, int -> int
        returns the highest of two numbers
*/
int maxAVL(int n1, int n2) {
    return n1 > n2 ? n1 : n2;
}

/*
    createNodeAVL: char *, char * -> NodeAVL *
        allocates memory for and initializes a node
        with copies of the provided key and value
*/
NodeAVL * createNodeAVL(char * key, char * value) {
    NodeAVL * node = SMALLOC(NodeAVL);

    /* initialize key */
    node->key = MALLOC_STR(key);
    strcpy(node->key, key);
    
    /* initialize directory */
    node->value = createDirectory();
    if(value != NULL) {
        node->value->value = MALLOC_STR(value);
        strcpy(node->value->value, value);
    }

    /* intialize branches with null */
    node->left = NULL;
    node->right = NULL;
    
    return node;
}

/*
    destroyNodeAVL: NodeAVL * -> ()
        frees up all memory associated with a single avl node
*/
void destroyNodeAVL(NodeAVL * node) {
    free(node->key);
    free(node);
}

/*
    heightAVL: NodeAVL * -> int
        returns the height of a node in an avl tree (0 for leaves)
*/
int heightAVL(NodeAVL * node) {
    if(node == NULL)
        return -ONE;
    
    return ONE + maxAVL(heightAVL(node->left), heightAVL(node->right));
}

/*
    balanceFactorAVL: NodeAVL * -> int
        calculates the balances factor of a given node:
            height(left) - height(right)
*/
int balanceFactorAVL(NodeAVL * node) {
    if(node == NULL)
        return ZERO;
    
    return heightAVL(node->left) - heightAVL(node->right);
}

/*
    createTreeAVL: () -> TreeAVL *
        allocates memory for and initializes an avl tree
*/
TreeAVL * createTreeAVL() {
    TreeAVL * tree = SMALLOC(TreeAVL);

    tree->root = NULL;

    return tree;
}

/*
    destroyTreeAVL: TreeAVL * -> ()
        frees up all memory inside the provided avl tree, including all directories and subdirectories
*/
void destroyTreeAVL(TreeAVL * tree) {
    /* guard for null parameter */
    if(tree == NULL)
        return;

    /* recursively delete every node in the tree */
    while(tree->root != NULL)
        removeTreeAVL(tree, tree->root->key);
    
    free(tree);
}

/* enum to simplify comparisons between keys */
enum Cmp {HIGHER, LOWER, EQUAL, ERROR};

/*
    compareKeysAVL: char *, char * -> int
        compares two keys:
            HIGHER if key1 > key2
            EQUAL if key1 == key2
            LOWER if key1 < key2
*/
int compareKeysAVL(char * key1, char * key2) {
    if(strcmp(key1, key2) > ZERO)
        return HIGHER;
    else if(IS_EQUAL_STR(key1, key2))
        return EQUAL;
    else
        return LOWER;

    return ERROR;
}

/*
    rotateLeftAVL: NodeAVL * -> NodeAVL *
        performs RotL(pivot) and returns the new rotated node
*/
NodeAVL * rotateLeftAVL(NodeAVL * pivot) {
    NodeAVL * new = pivot->right;

    if(new == NULL)
        return pivot;

    pivot->right = new->left;
    new->left = pivot;

    return new;
}

/*
    rotateLeftAVL: NodeAVL * -> NodeAVL *
        performs RotR(pivot) and returns the new rotated node
*/
NodeAVL * rotateRightAVL(NodeAVL * pivot) {
    NodeAVL * new = pivot->left;

    if(new == NULL)
        return pivot;

    pivot->left = new->right;
    new->right = pivot;

    return new;
}

/*
    balanceRootAVL: NodeAVL *, char * -> NodeAVL *
        balances out an unbalanced node, performing a rotL or rotR
        depending on the sign of the balance factor
*/
NodeAVL * balanceRootAVL(NodeAVL * root, char * nkey) {
    int balance;

    /* guard for null parameters */
    if(root == NULL || nkey == NULL)
        return NULL;
    
    balance = balanceFactorAVL(root);

    /* left-heavy case */
    if(balance > ONE) {
        if(compareKeysAVL(nkey, root->left->key) == HIGHER)
            root->left = rotateLeftAVL(root->left);
        
        return rotateRightAVL(root);
    }
    /* right-heavy case */
    else if(balance < -ONE) {
        if(compareKeysAVL(nkey, root->right->key) == LOWER)
            root->right = rotateRightAVL(root->right);
        
        return rotateLeftAVL(root);
    }

    /* return balanced node */
    return root;
}

/*
    insertTreeAuxAVL: NodeAVL *, NodeAVL * -> NodeAVL *
        recursive auxiliary function to insertTreeAVL
        inserts a node in a branch of a given root
*/
NodeAVL * insertTreeAuxAVL(NodeAVL * root, NodeAVL * node) {
    /* stop condition */
    if(root == NULL)
        return node;

    /* compare keys for binary insertion */
    switch (compareKeysAVL(node->key, root->key)) {
        /* new node key is lower - insert in left branch */
        case LOWER:
            root->left = insertTreeAuxAVL(root->left, node);
            break;

        /* new node key is higher - insert in right branch */
        case HIGHER:
            root->right = insertTreeAuxAVL(root->right, node);
            break;
    }

    /* balance out the updated root before returning it */
    return balanceRootAVL(root, node->key);
}

/*
    insertTreeAVL: NodeAVL *, char * key, char * value -> NodeAVL *
        creates a node in a branch of a given root
*/
void insertTreeAVL(TreeAVL * tree, char * key, char * value) {
    NodeAVL * node;

    /* guard for null parameters */
    if(tree == NULL || key == NULL)
        return;
    
    /* key is already in the provided tree - no duplicates */
    if(containsKeyAVL(tree, key))
        return;
    
    /* initialize the new node with a key and value */
    node = createNodeAVL(key, value);

    /* insert node in the tree and update root */
    tree->root = insertTreeAuxAVL(tree->root, node);
}

/* 
    getChildCountAVL: NodeAVL * -> int
        returns the number of non-null branches that stem from a given node
*/
int getChildCountAVL(NodeAVL * node) {
    if(node->left != NULL && node->right != NULL)
        return TWO;
    
    if(node->left != NULL || node->right != NULL)
        return ONE;
    
    return ZERO;
}

/*
    getSingleChildAVL: NodeAVL * -> NodeAVL *
        returns the only non-null branch of a given node, null otherwise
*/
NodeAVL * getSingleChildAVL(NodeAVL * node) {
    /* guard for null parameter */
    if(node == NULL)
        return NULL;
    
    /* left branch case */
    if(node->left != NULL && node->right == NULL)
        return node->left;
    
    /* right branch case */
    if(node->right != NULL && node->left == NULL)
        return node->right;
    
    /* both or none null */
    return NULL;
}

/*
    removeTreeAuxAVL: NodeAVL *, char *, int -> NodeAVL *
        recursive auxiliary function to removeTreeAVL
        removes a node from a given roots branches
*/
NodeAVL * removeTreeAuxAVL(NodeAVL * node, char * key, int destructive) {
    NodeAVL * tmp;
    int childCount;

    /* stop condition */
    if(node == NULL)
        return NULL;

    /* number of non-null branches */
    childCount = getChildCountAVL(node);

    /* compare given key with the current node */
    if(compareKeysAVL(node->key, key) == EQUAL) {
        switch(childCount) {
            /* no children - destroy node and return null */
            case ZERO:
                /* free node and return - if case TWO was run before,
                    we want to move the directory, not destroy it */
                if(destructive == ONE)
                    destroyDirectory(node->value);
                destroyNodeAVL(node);

                return NULL;

            case ONE:
                tmp = getSingleChildAVL(node);
                
                /* free node and link parent with child - if case TWO was run before,
                    we want to move the directory, not destroy it */
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

    /* balance out updated node */
    node = balanceRootAVL(node, key);

    /* if node is not what were looking for, recursively check its branches */
    node->left = removeTreeAuxAVL(node->left, key, destructive);
    node->right = removeTreeAuxAVL(node->right, key, destructive);

    return node;
}

/*
    removeTreeAVL: TreeAVL *, char * -> ()
        removes a node corresponding to the given key in an avl tree
*/
void removeTreeAVL(TreeAVL * tree, char * key) {
    /* guard for null parameters */
    if(tree == NULL || tree->root == NULL || key == NULL)
        return;

    /* remove node from tree and update the root */
    tree->root = removeTreeAuxAVL(tree->root, key, ONE);
}

/*
    maxNodeAVL: NodeAVL * -> NodeAVL *
        returns the node with the highest key in the given nodes branches
*/
NodeAVL * maxNodeAVL(NodeAVL * node) {
    /* stop condition */
    if(node == NULL || node->right == NULL)
        return node;

    /* recursive call to right branch */
    return maxNodeAVL(node->right);
}

/*
    minNodeAVL: NodeAVL * -> NodeAVL *
        returns the node with the lowest key in the given nodes branches
*/
NodeAVL * minNodeAVL(NodeAVL * node) {
    /* stop condition */
    if(node == NULL || node->left == NULL)
        return node;

    /* recursive call to left branch */
    return minNodeAVL(node->left);
}

/*
    containsKeyAVL: TreeAVL *, char * -> int
        returns whether a node with the given key is contained in a tree
*/
int containsKeyAVL(TreeAVL * tree, char * key) {
    /* guard for null parameters */
    if(tree == NULL || key == NULL)
        return ZERO;

    /* search for node in tree */
    return searchAVL(tree, key) != NULL;
}

/*
    searchAuxAVL: NodeAVL *, char * -> NodeAVL *
        recursive auxiliary function to searchAVL
        searches for a node with the given key in a nodes branches
*/
NodeAVL * searchAuxAVL(NodeAVL * node, char * key) {
    /* stop condition */
    if(node == NULL || key == NULL)
        return NULL;

    /* node found - return it */
    if(compareKeysAVL(key, node->key) == EQUAL)
        return node;
    
    switch(compareKeysAVL(key, node->key)) {
        /* key is lower than current node - recursive call to left branch */
        case LOWER:
            return searchAuxAVL(node->left, key);

        /* key is higher than current node - recursive call to right branch */
        case HIGHER:
            return searchAuxAVL(node->right, key);
    }
    
    /* base case */
    return NULL;
}

/*
    searchAVL: TreeAVL *, char * -> NodeAVL *
        searches for and returns the node with given key in a tree - null if not found
*/
NodeAVL * searchAVL(TreeAVL * tree, char * key) {
    /* guard for null parameters */
    if(tree == NULL || key == NULL)
        return NULL;

    /* search for the key */
    return searchAuxAVL(tree->root, key);
}

/*
    printTreeAVL: NodeAVL * -> ()
        print the contents of a tree, given its root, in-order (sorted alphabetically)
*/
void printTreeAVL(NodeAVL * root) {
    /* guard for null parameter */
    if(root == NULL)
        return;
    
    /* recursive call to left branch */
    printTreeAVL(root->left);

    /* print key */
    PRINT_VALUE(root->key);

    /* recursive call to right branch */
    printTreeAVL(root->right);
}

/*
    searchDirectoryAux: Directory *, List *, char * -> int
        recursive auxiliary function to searchDirectory
        looks for a subdirectory of dir, by order of most recently created,
        given the subdirectorys value 
*/
int searchDirectoryAux(Directory * dir, List * components, char * value) {
    NodeAVL * target;
    char * key;
    int i;

    /* stop condition */
    if(dir == NULL)
        return ZERO;

    /* iterate over the directorys history */
    for(i = ZERO; (key = getNth0(dir->history, i)) != NULL; i++) {
        /* get a pointer to the subdirectory corresponding to the key */
        target = searchAVL(dir->subdirs, key);
    
        /* update path */
        insert(components, key);

        /* directory found */
        if(target->value->value != NULL && IS_EQUAL_STR(value, target->value->value)) 
            return ONE;
        
        /* directory was found in a subdirectory */
        if(searchDirectoryAux(target->value, components, value) == ONE)
            return ONE;

        /* directory was not found, revert path update */
        removeNth0(components, sizeList(components) - ONE);
    }

    /* no directory with given value */
    return ZERO;
}

/*
    searchDirectory: Directory *, char * -> List *
        search for a subdirectory, given its value, and return its path
*/
List * searchDirectory(Directory * dir, char * value) {
    List * components;

    /* guard for null parameters */
    if(dir == NULL || value == NULL)
        return NULL;
    
    /* initialize path */
    components = createList();

    /* search for directory, place its path in a linked list */
    searchDirectoryAux(dir, components, value);

    /* directory was not found - destroy path and return null */
    if(sizeList(components) == ZERO) {
        destroyList(components);
        return NULL;
    }

    /* directory was found - return its path */
    return components;
}

/*
    createDirectory: () -> Directory *
        allocates memory for and initializes a directory
*/
Directory * createDirectory() {
    Directory * dir = SMALLOC(Directory);

    dir->subdirs = createTreeAVL();
    dir->history = createList();
    dir->value = NULL;

    return dir;
}

/*
    createFileSystem: () -> FileSystem *
        allocates memory for and initializes a file system
*/
FileSystem * createFileSystem() {
    FileSystem * fs = SMALLOC(FileSystem);

    fs->root = createDirectory();

    return fs;
}

/*
    destroyDirectory: Directory * -> ()
        frees up all memory associated with a given directory,
        including all its subdirectories
*/
void destroyDirectory(Directory * dir) {
    /* guard for null parameters */
    if(dir == NULL)
        return;
    
    destroyTreeAVL(dir->subdirs);
    destroyList(dir->history);
    free(dir->value);

    free(dir);
}

/*
    destroyFileSystem: FileSystem * -> ()
        frees up all memory associated with a given file system
*/
void destroyFileSystem(FileSystem * fs) {
    destroyDirectory(fs->root);
    free(fs);
}

/*
    isSubDirectory: Directory *, char * -> int
        checks whether there is an immediate subdirectory 
        of a given directory with a given key
*/
int isSubDirectory(Directory * dir, char * key) {
    /* guard for null parameters */
    if(dir == NULL || dir->subdirs == NULL || key == NULL)
        return ZERO;

    /* search for key in the immediate subdirectories */
    return containsKeyAVL(dir->subdirs, key);
}

/*
    destroyPath: FileSystem *, List * -> ()
        destroys the directory at a given path and all its subdirectories
*/
void destroyPath(FileSystem * fs, List * components) {
    Directory * parent = fs->root;
    NodeAVL * tmp;

    /* no parameters - reset file system */
    if(components == NULL) {
        destroyDirectory(fs->root);
        fs->root = createDirectory();
        return;
    }

    /* search for the directory */
    while(sizeList(components) > ONE) {
        /* search for subdirectory */
        tmp = searchAVL(parent->subdirs, getFirst(components));

        /* component not contained in immediate subdirectories - path does not exist */
        if(tmp == NULL) {
            PRINT_ERROR(NOT_FOUND_ERR);
            return;
        }

        /* subdirectory found, iterate until the directory
            were looking for is contained in parents subdirectories */
        parent = tmp->value;

        /* update path */
        removeFirst(components);
    }
    
    /* path exists - delete directory at path and all its subdirectories */
    if(isSubDirectory(parent, getFirst(components))) {
        removeValue(parent->history, getFirst(components));
        removeTreeAVL(parent->subdirs, getFirst(components));
    }
    /* path does not exist - print out error */
    else
        PRINT_ERROR(NOT_FOUND_ERR);
}

/*
    isEmpty: Directory * -> int
        returns whether a given directory has no subdirectories
*/
int isEmpty(Directory * dir) {
    /* guard for null parameter */
    if(dir == NULL)
        return ZERO;
    
    /* if root is null, there are no subdirectories */
    return dir->subdirs->root == NULL;
}

/*
    addDirectoryAux: Directory *, List *, char * -> Directory *
        recursive auxiliary function to addDirectory
        adds directory at a given path, assigning it a given value
*/
Directory * addDirectoryAux(Directory * dir, List * components, char * value) {
    NodeAVL * target;
    char * first;
    
    /* stop condition */
    if(dir == NULL)
        return NULL;

    /* first component of the given path */
    first = MALLOC_STR(getFirst(components));
    strcpy(first, getFirst(components));

    /* path exists, no need to create it */
    if(isSubDirectory(dir, first)) {
        /* weve reached the directory where we want to add the new directory */
        if(sizeList(components) == ONE) {
            /* search for immediate subdirectory */
            target = searchAVL(dir->subdirs, first);

            /* path already existed with a value - overwrite it with the new value */
            if(target->value->value != NULL) 
                free(target->value->value);
            target->value->value = MALLOC_STR(value);
            strcpy(target->value->value, value);
        }
        /* recursively search for the directory where the new directory is to be added */
        else {
            /* update path */
            removeFirst(components);

            /* search for immediate subdirectory */
            target = searchAVL(dir->subdirs, first);

            /* recursive call to add the new directory to the subdirectory */
            target->value = addDirectoryAux(target->value, components, value);
        }
    }
    /* path does not exist, insert into subdirectories */
    else {
        /* update directory history with new directory */
        insert(dir->history, first);
        
        /* weve reached the directory where we want to add the new directory */
        if(sizeList(components) == ONE) {

            /* update subdirectories with the new directory */
            insertTreeAVL(dir->subdirs, first, value);
        }
        /* recursively search for the directory where the new directory is to be added */
        else {
            /* update path */
            removeFirst(components);
            
            /* add new null value directory to subdirectories */
            insertTreeAVL(dir->subdirs, first, NULL);
            
            /* search for subdirectory */
            target = searchAVL(dir->subdirs, first);
            target->value = addDirectoryAux(target->value, components, value);
        }
    }

    /* free unnecessary memory */
    free(first);
    
    return dir;
}

/*
    addDirectory: FileSystem *, char *, char * -> ()
        creates or modifies a directory at a given path with given value
*/
void addDirectory(FileSystem * fs, char * path, char * value) {
    List * components;

    /* guard for null parameters */
    if(fs == NULL || path == NULL || value == NULL)
        return;

    /* separate raw string input into a linked list */
    components = pathToList(path);

    /* path is valid - add directory */
    if(sizeList(components) != ZERO)
        fs->root = addDirectoryAux(fs->root, components, value);

    /* free up components */
    destroyList(components);
}

/*
    printDirectory: Directory *, List * -> ()
        recursively prints out all subdirectories of a given directory,
        depth-first, by order of most recently added
*/
void printDirectory(Directory * dir, List * path) {
    NodeAVL * target;
    int i, j, len;
    char * tmp;

    /* stop condition */
    if(dir == NULL)
        return;

    /* iterate over the directorys history */    
    for(i = ZERO; (tmp = getNth0(dir->history, i)) != NULL; i++) {
        /* update path and get its length */
        insert(path, tmp);
        len = sizeList(path);
        
        /* search for the subdirectory */
        target = searchAVL(dir->subdirs, tmp);

        /* mismatch between history and subdirectories - update history and continue */
        if(target == NULL) {
            removeNth0(dir->history, i);
            removeNth0(path, len - ONE);
            continue;
        }

        /* value of the directory is not null - print out its path and value */
        if(target->value->value != NULL) {
            for(j = ZERO; j < len; j++)
                PRINT_COMPONENT(getNth0(path, j));
            putchar(WHITESPACE);
            PRINT_VALUE(target->value->value);
        }

        /* recursive call to print its subdirectories */
        printDirectory(target->value, path);

        /* revert path update */
        removeNth0(path, len - ONE);
    }
}

/*
    findSubDirectory: Directory *, List *
        look for and return a directory at a given path
*/
Directory * findSubDirectory(Directory * dir, List * path) {
    NodeAVL * target;
    
    /* search for the directory */
    target = searchAVL(dir->subdirs, getFirst(path));

    /* directory does not exist - print error */
    if(target == NULL) {
        PRINT_ERROR(NOT_FOUND_ERR);
        return NULL;
    }

    /* directory found */
    if(sizeList(path) == ONE)
        return target->value;

    /* update path */
    removeFirst(path);

    /* recursive call to search the subdirectory */
    return findSubDirectory(target->value, path);
}