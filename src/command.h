#include "list.h"

typedef struct {
    List * tokens;
} Command;

Command * readCommand();
char * nextToken(Command * command);
void destroyCommand(Command * command);