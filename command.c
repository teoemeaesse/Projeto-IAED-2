#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "macros.h"
#include "command.h"

Command * newCommand() {
    Command * command;

    command = SMALLOC(Command);
    command->tokens = createList();
    
    return command;
}

char * readLine() {
    int len = ZERO;
    char c;
    char * line = MALLOC(len, char);

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

Command * readCommand() {
    Command * command;
    char * raw, * token;

    raw = readLine();
    if(raw == NULL)
        return NULL;
    token = strtok(raw, WHITESPACE_STR);

    command = newCommand();
    while(token != NULL) {
        insert(command->tokens, token);
        token = strtok(NULL, WHITESPACE_STR);
    }

    free(raw);
    free(token);

    return command;
}

char * nextToken(Command * command) {
    char * token, * tmp;

    if(command == NULL) {
        token = SMALLOC(char);
        * token = NULL_CHARACTER;
        return token; 
    }

    tmp = getFirst(command->tokens);
    token = MALLOC(strlen(tmp) + ONE, char);
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