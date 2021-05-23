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
    printFileSystem(fs);
}