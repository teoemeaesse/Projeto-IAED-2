#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "macros.h"
#include "input.h"

Command * createCommand() {
    Command * command;

    command = SMALLOC(Command);
    command->tokens = createList();
    
    return command;
}

char * readLine() {
    int len = ZERO;
    char c;
    char * line = NULL;

    while((c = getchar()) != NEW_LINE) {
        line = REALLOC(line, len + ONE, char);
        line[len++] = c;
    }

    if(len == ZERO) {
        free(line);
        return NULL;
    }

    line = REALLOC(line, len + ONE, char);
    line[len] = NULL_CHARACTER;

    return line;
}

Command * readCommand(int argc) {
    Command * command;
    char * token;
    int count = ONE;

    command = createCommand();
    while(token != NULL && ++count < argc) {
        insert(command->tokens, token);
        token = strtok(NULL, WHITESPACE_STR);
    }

    token = strtok(NULL, EMPTY_STR);
    insert(command->tokens, token);

    free(token);

    return command;
}

char * nextToken(Command * command) {
    char * token, * tmp;

    if(command == NULL || command->tokens->head == NULL) {
        token = SMALLOC(char);
        * token = NULL_CHARACTER;
        return token; 
    }

    tmp = getFirst(command->tokens);
    token = MALLOC_STR(tmp);
    strcpy(token, tmp);
    removeFirst(command->tokens);

    return token;
}

void destroyCommand(Command * command) {
    if(command == NULL)
        return;

    destroyList(command->tokens);

    free(command);
}