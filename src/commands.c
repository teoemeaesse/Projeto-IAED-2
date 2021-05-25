/*
    file: commands.c
    author: Tomas Marques ist199338
    description: implementation of all the commands the user can input
*/

#include <stdio.h>

#include "commands.h"

/*
    help: () -> ()
        simply prints out the predefined help text
*/
void help() {
    PRINT_HELP_CMD_TXT;
}

/*
    quit: char * -> int
        frees memory used up for input and returns exit code ZERO to stop execution
*/
int quit(char * raw) {
    free(raw);
    
    return ZERO;
}

/*
    set: FileSystem *, Command * -> ()
        sets the value for a directory in the file system, given its path
*/
void set(FileSystem * fs, Command * command) {
    char * path, * value;

    /* guard for null parameters */
    if(command == NULL || command->tokens == NULL || command->tokens->head == NULL)
        return;
    
    /* check for invalid input */
    path = nextToken(command);
    if(path == NULL)
        return;
    value = nextToken(command);
    if(value == NULL) {
        free(path);
        return;
    }

    /* add/modify directory at path location */
    addDirectory(fs, path, value);

    /* free unnecessary memory */
    free(path);
    free(value);
}


/*
    print: FileSystem * -> ()
        prints out all directories depth-first, by order of most recently added, 
        present in the given file system which have non-null value
*/
void print(FileSystem * fs) {
    List * path;

    /* guard for null parameters */
    if(fs == NULL || fs->root == NULL)
        return;
    
    /* initialize list */
    path = createList();

    /* recursively print root and its subdirectories */
    printDirectory(fs->root, path);

    /* free unnecessary memory */
    destroyList(path);
}

/*
    find: FileSystem *, Command * -> ()
        search for and print the value of the directory at a given path
*/
void find(FileSystem * fs, Command * command) {
    Directory * dir;
    List * components;
    char * path;

    /* guard for null parameters */
    if(fs == NULL || command == NULL || sizeList(command->tokens) == ZERO)
        return;
    
    path = nextToken(command);

    /* check for invalid input */
    if(path == NULL)
        return;
    
    /* divide raw string input up into a linked list of components */
    components = pathToList(path);

    /* look for directory at path */
    dir = findSubDirectory(fs->root, components);

    /* handle errors */
    if(dir != NULL) {
        if(dir->value == NULL)
            PRINT_ERROR(NO_DATA_ERR);
        else
            PRINT_VALUE(dir->value);
    }

    /* free unnecessary memory */
    destroyList(components);    
    free(path);
}

/*
    list: FileSystem *, Command * -> ()
        lists all immediate subdirectories of a directory at a given path (root if path is empty)
*/
void list(FileSystem * fs, Command * command) {
    Directory * dir;
    List * components;
    char * path;
    
    /* guard for null parameters */
    if(fs == NULL || command == NULL)
        return;
    
    path = nextToken(command);

    /* no parameters case: list root subdirectories */
    if(path == NULL) {
        printTreeAVL(fs->root->subdirs->root);

        free(path);
        return;
    }

    /* divide raw string input up into a linked list of components */
    components = pathToList(path);

    /* look for directory at path */
    dir = findSubDirectory(fs->root, components);

    /* directory not found: free memory and return */
    if(dir == NULL) {
        free(path);
        destroyList(components);
        return;
    }

    /* print all immediate subdirectories of dir */
    printTreeAVL(dir->subdirs->root);

    /* free unnecessary memory */
    free(path);
    destroyList(components);
}

/*
    search: FileSystem * fs, Command * -> ()
        prints out first path found containing a given value, by creation order
*/
void search(FileSystem * fs, Command * command) {
    List * components;
    char * value;

    /* guard for null parameters */
    if(fs == NULL || command == NULL)
        return;
    
    value = nextToken(command);

    /* check for invalid input */
    if(value == NULL)
        return;
    
    /* search for directory with a given value */
    components = searchDirectory(fs->root, value);

    /* directory not found case */
    if(components == NULL) {
        PRINT_ERROR(NOT_FOUND_ERR);
        free(value);
        return;
    }

    /* print out all the components */
    while(sizeList(components) > ZERO) {
        PRINT_COMPONENT(getFirst(components));
        removeFirst(components);
    }
    putchar(NEW_LINE);

    /* free unnecessary memory */
    destroyList(components);
    free(value);
}

/*
    delete: FileSystem *, Command * -> ()
        delete directory at given path
*/
void delete(FileSystem * fs, Command * command) {
    List * components;
    char * path;

    /* guard for null parameters */
    if(fs == NULL || command == NULL)
        return;
    
    path = nextToken(command);

    /* divide raw string input up into a linked list of components */
    components = pathToList(path);

    /* destroy directory at given path, or print an error if not found */
    destroyPath(fs, components);

    /* free unnecessary memory */
    destroyList(components);
    free(path);
}