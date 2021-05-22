#include <stdio.h>

#include "commands.h"

/*void help() {
    printf("%s", HELP_CMD_TXT);
}

int quit(char * raw, char * token) {
    free(raw);
    free(token);
    
    return ZERO;
}

void set(DirManager * dirManager, Command * command) {
    char * path, * value;

    if(command == NULL || command->tokens == NULL || command->tokens->head == NULL)
        return;
    
    path = nextToken(command);
    value = nextToken(command);

    addPath(dirManager, path, value);
}
*/