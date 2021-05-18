#include <stdio.h>
#include <string.h>

#include "macros.h"
#include "command.h"

int parseInput();

int main() {
    while(parseInput() != ZERO);

    return ZERO;
}

void help() {
    
}

int parseInput() {
    Command * command;
    char * token;

    command = readCommand();
    token = nextToken(command);
    
    if(strcmp(token, HELP_CMD) == ZERO)
        help();
    if(strcmp(token, QUIT_CMD) == ZERO) {
        destroyCommand(command);
        free(token);
        return ZERO;
    }

    free(token);
    destroyCommand(command);

    return ONE;
}