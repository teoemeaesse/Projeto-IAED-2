#include <stdio.h>
#include <string.h>

#include "macros.h"
#include "command.h"
#include "stack.h"


int parseInput();

int main() {
    Stack * history = createStack();

    while(parseInput(history) != ZERO);

    return ZERO;
}

void help() {
    printf("%s", HELP_CMD_TXT);
}

int quit(Command * command, char * token) {
    destroyCommand(command);
    free(token);
    
    return ZERO;
}

void set(Command * command, Stack * history) {
    
}


int parseInput(Stack * history) {
    Command * command;
    char * token;

    command = readCommand();
    token = nextToken(command);
    
    if(strcmp(token, HELP_CMD) == ZERO)
        help();

    else if(strcmp(token, QUIT_CMD) == ZERO)
        return quit(command, token);

    else if(strcmp(token, SET_CMD))
        set(command, history);
        
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

    destroyCommand(command);
    free(token);

    return ONE;
}