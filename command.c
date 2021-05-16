#include <stdio.h>
#include <string.h>

#include "macros.h"
#include "command.h"

Command * readCommand() {
    char * token;
    Command command;

    while((token = strtok(stdin, WHITESPACE))) {

    }

    free(token);
}