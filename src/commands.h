/*
    file: commands.h
    author: Tomas Marques ist199338
    description: header file for all the commands the user can input
*/

#include "macros.h"
#include "input.h"
#include "dir.h"

void help();
int quit(char * raw);
void set(FileSystem * fs, Command * command);
void print(FileSystem * fs);
void find(FileSystem * fs, Command * command);
void list(FileSystem * fs, Command * command);
void search(FileSystem * fs, Command * command);
void delete(FileSystem * fs, Command * command);