#include <stdio.h>

#include "commands.h"

void help() {
    printf("%s", HELP_CMD_TXT);
}

int quit(char * raw) {
    free(raw);
    
    return ZERO;
}

void set(FileSystem * fs, Command * command) {
    char * path, * value;

    if(command == NULL || command->tokens == NULL || command->tokens->head == NULL)
        return;
    
    path = nextToken(command);
    if(path == NULL)
        return;
    value = nextToken(command);
    if(value == NULL) {
        free(path);
        return;
    }

    addDirectory(fs, path, value);

    free(path);
    free(value);
}

void print(FileSystem * fs) {
    List * path;

    if(fs == NULL || fs->root == NULL)
        return;
    
    path = createList();

    printDirectory(fs->root, path);

    destroyList(path);
}

void find(FileSystem * fs, Command * command) {
    Directory * dir;
    List * components;
    char * path;

    if(fs == NULL || command == NULL || sizeList(command->tokens) == ZERO)
        return;
    
    path = nextToken(command);

    if(path == NULL)
        return;
    
    components = pathToList(path);

    dir = findSubDirectory(fs->root, components);

    if(dir != NULL) {
        if(dir->value == NULL)
            printf("%s\n", NO_DATA_ERR);
        else
            printf("%s\n", dir->value);
    }

    destroyList(components);
    
    free(path);
}

void list(FileSystem * fs, Command * command) {
    Directory * dir;
    List * components;
    char * path;
    
    if(fs == NULL || command == NULL)
        return;
    
    path = nextToken(command);

    if(path == NULL) {
        printTreeAVL(fs->root->subdirs->root);

        free(path);
        return;
    }

    components = pathToList(path);

    dir = findSubDirectory(fs->root, components);

    if(dir == NULL) {
        free(path);
        destroyList(components);
        return;
    }

    printTreeAVL(dir->subdirs->root);

    free(path);
    destroyList(components);
}