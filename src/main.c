#include <stdio.h>
#include <string.h>

#include "macros.h"
#include "commands.h"

int parseInput();

int main() {
    FileSystem * fs = createFileSystem();

    while(parseInput(fs) != ZERO);

    destroyFileSystem(fs);

    return ZERO;
}


int parseInput(FileSystem * fs) {
    Command * command = NULL;
    char * raw = NULL, * token = NULL;
    
    raw = readLine();
    if(raw == NULL)
        return ONE;
    token = strtok(raw, WHITESPACE_STR);
    if(token == NULL) {
        free(raw);
        return ONE;
    }

    if(strcmp(token, HELP_CMD) == ZERO)
        help();

    else if(strcmp(token, QUIT_CMD) == ZERO) {
        return quit(raw);
    }

    else if(strcmp(token, SET_CMD) == ZERO) {
        command = readCommand(3);
        set(fs, command);

        printf("key: %s | value: %s", fs->root->subdirs->root->key, fs->root->subdirs->root->value->value);
    }
    else if(strcmp(token, PRINT_CMD)) {
        
    }
    else if(strcmp(token, FIND_CMD)) {
        
    }
    else if(strcmp(token, LIST_CMD)) {
        
    }
    else if(strcmp(token, SEARCH_CMD)) {
        
    }
    else if(strcmp(token, DELETE_CMD)) {
        
    }

    if(command != NULL)
        destroyCommand(command);
    free(raw);

    return ONE;
}