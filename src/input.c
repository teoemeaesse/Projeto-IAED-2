/*
    file: input.c
    author: Tomas Marques ist199338
    description: implementation of all the input handling functions
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "macros.h"
#include "input.h"

/*
    createCommand: () -> Command *
        allocates memory for and initializes a command
*/
Command * createCommand() {
    Command * command;

    command = SMALLOC(Command);
    command->tokens = createList();
    
    return command;
}

/*
    readLine: () -> char *
        reads in a line from stdin
*/
char * readLine() {
    int len = ZERO;
    char c;
    char * line = NULL;

    /* read characters until user presses enter or we reach EOF */
    while((c = getchar()) != NEW_LINE && c != EOF) {
        line = REALLOC(line, len + ONE, char);
        line[len++] = c;
    }

    /* user did not input any characters */
    if(len == ZERO) {
        free(line);
        return NULL;
    }

    /* add null-terminator to the end of the string */
    line = REALLOC(line, len + ONE, char);
    line[len] = NULL_CHARACTER;

    /* return user input */
    return line;
}

/*
    readCommand: int -> Command *
        reads a user command with a given amount of parameters
        last argument is an arbitrarily long, unformatted string
*/
Command * readCommand(int argc) {
    Command * command;
    char * token = NULL;

    /* initialize command */
    command = createCommand();

    /* separate arguments with whitespaces */
    while(--argc > ZERO) {
        token = strtok(NULL, WHITESPACE_STR);
        if(token == NULL)
            return NULL;

        /* add argument to command */
        insert(command->tokens, token);
    }

    /* read the rest of the input */
    token = strtok(NULL, EMPTY_STR);
    
    /* insert the last argument if it is not null */
    if(token != NULL)
        insert(command->tokens, token);
    
    return command;
}

/*
    pathToList: char * -> List *
        parses a raw path string and separates its components into a linked list
*/
List * pathToList(char * path) {
    List * components;
    char * token;
    
    /* guard for null parameter */
    if(path == NULL)
        return NULL;

    /* initialize path */
    components = createList();

    /* separate components into token */
    token = strtok(path, PATH_SEPARATOR_STR);
    while(token != NULL) {
        /* add component to path */
        insert(components, token);
        token = strtok(NULL, PATH_SEPARATOR_STR);
    }

    /* free unnecessary memory */
    free(token);

    /* return processed list */
    return components;
}

/*
    nextToken: Command * -> char *
        returns first token in command and removes it
*/
char * nextToken(Command * command) {
    char * token, * tmp;

    /* guard for null parameters */
    if(command == NULL || command->tokens->head == NULL)
        return NULL;

    /* get first component */
    tmp = getFirst(command->tokens);

    /* copy first component to a token */
    token = MALLOC_STR(tmp);
    strcpy(token, tmp);

    /* remove the first component from the command */
    removeFirst(command->tokens);

    /* return a copy of the first component */
    return token;
}

/*
    destroyCommand: Command * -> ()
        frees up all memory associated with a command
*/
void destroyCommand(Command * command) {
    /* guard for null parameter */
    if(command == NULL)
        return;

    destroyList(command->tokens);
    free(command);
}