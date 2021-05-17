#include <stdlib.h>

#define MALLOC(S, T) (T*) malloc(S * sizeof(T))
#define SMALLOC(T) MALLOC(1, T)
#define REALLOC(P, S, T) (T*) realloc(P, S * sizeof(T))

#define WHITESPACE ' '
#define NEW_LINE '\n'
#define TAB '\t'
#define NULL_CHARACTER '\0'

#define MAX_INPUT 65535