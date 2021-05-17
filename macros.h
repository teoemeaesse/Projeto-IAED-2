#include <stdlib.h>

#define MALLOC(S, T) malloc(S * sizeof(T))
#define SMALLOC(T) MALLOC(1, T)
#define REALLOC(P, S, T) realloc(P, S * sizeof(T))

#define EMPTY_STR "";
#define WHITESPACE ' '
#define WHITESPACE_STR " "
#define NEW_LINE '\n'
#define TAB '\t'
#define NULL_CHARACTER '\0'

#define MAX_INPUT 65535
#define ZERO 0
#define ONE 1

#define HELP_CMD "help"
#define QUIT_CMD "quit"
#define SET_CMD "set"
#define PRINT_CMD "print"
#define FIND_CMD "find"
#define LIST_CMD "list"
#define SEARCH_CMD "search"
#define DELETE_CMD "delete"