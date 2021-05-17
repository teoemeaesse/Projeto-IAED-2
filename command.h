#include "stack.h"

typedef struct {
    Node * tokens;
} Command;

Command * readCommand();
char * nextToken(Command * command);
void destroyCommand(Command * command);