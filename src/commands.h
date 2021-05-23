#include "macros.h"
#include "input.h"
#include "stack.h"
#include "dir.h"

void help();
int quit(char * raw);
void set(FileSystem * fs, Command * command);
void print(FileSystem * fs);
void find(FileSystem * fs, Command * command);
void list(FileSystem * fs, Command * command);
void search(FileSystem * fs, Command * command);
void delete(FileSystem * fs, Command * command);