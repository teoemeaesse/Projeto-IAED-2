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
    else if(strcmp(token, QUIT_CMD) == ZERO) 
        return quit(raw);
    else if(strcmp(token, SET_CMD) == ZERO) {
        command = readCommand(TWO);
        set(fs, command);
    }
    else if(strcmp(token, PRINT_CMD) == ZERO)
        print(fs);
    else if(strcmp(token, FIND_CMD) == ZERO) {
        command = readCommand(ONE);
        find(fs, command);
    }
    else if(strcmp(token, LIST_CMD) == ZERO) {
        command = readCommand(ONE);
        list(fs, command);
    }
    else if(strcmp(token, SEARCH_CMD) == ZERO) {
        command = readCommand(ONE);
        search(fs, command);
    }
    else if(strcmp(token, DELETE_CMD) == ZERO) {
        command = readCommand(ONE);
        delete(fs, command);
    }


    if(command != NULL)
        destroyCommand(command);
    free(raw);

    return ONE;
}