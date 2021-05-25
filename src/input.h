/*
    file: input.h
    author: Tomas Marques ist199338
    description: header file for all the input handling functions
*/

#include "list.h"

/* represents a command - a linked list of sequential tokens, the last
    of which can be an arbitrarily long, unformatted string */
typedef struct {
    List * tokens;
} Command;

Command * readCommand(int argc);
List * pathToList(char * path);
char * readLine();
char * nextToken(Command * command);
void destroyCommand(Command * command);