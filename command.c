#include <stdio.h>
#include <string.h>

#include "macros.h"
#include "command.h"

char * readLine() {
    int len = 1;
    char c;
    char * line = MALLOC(len, char);

    while((c = getchar()) != NEW_LINE) {
        line = REALLOC(line, len, char);
        line[len++ - 1] = c;
    }
    
    line[len - 1] = NULL_CHARACTER;

    return line;
}

Command * readCommand() {
    return NULL;
}