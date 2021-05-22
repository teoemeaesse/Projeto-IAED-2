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
    int count = TWO;

    command = createCommand();

    while((token != NULL && count++ < argc) || count == TWO) {
        token = strtok(NULL, WHITESPACE_STR);
        insert(command->tokens, token);
    }

    token = strtok(NULL, EMPTY_STR);
    if(token != NULL)
        insert(command->tokens, token);
    
    printf("--%s-%s-%s-%s--", getNth0(command->tokens, 0), getNth0(command->tokens, 1), getNth0(command->tokens, 2), getNth0(command->tokens, 3));

    return command;
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