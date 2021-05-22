#include "list.h"

typedef struct {
    List * tokens;
} Command;

Command * readCommand(int argc);
char * readLine();
char * nextToken(Command * command);
void destroyCommand(Command * command);