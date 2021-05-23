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
    char * token = NULL;

    command = createCommand();

    while(--argc > ZERO) {
        token = strtok(NULL, WHITESPACE_STR);
        if(token == NULL)
            return NULL;

        insert(command->tokens, token);
    }

    token = strtok(NULL, EMPTY_STR);
    if(token != NULL)
        insert(command->tokens, token);
    
    return command;
}

List * pathToList(char * path) {
    List * components;
    char * token;
    
    if(path == NULL)
        return NULL;

    components = createList();

    token = strtok(path, PATH_SEPARATOR_STR);
    while(token != NULL) {
        insert(components, token);
        token = strtok(NULL, PATH_SEPARATOR_STR);
    }

    free(token);

    return components;
}

char * nextToken(Command * command) {
    char * token, * tmp;

    if(command == NULL || command->tokens->head == NULL)
        return NULL;

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