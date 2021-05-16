#include <stdlib.h>

#define MALLOC(S, T) (T*) malloc(S * sizeof(T))
#define SMALLOC(T) MALLOC(1, T)

#define WHITESPACE ' '
#define NEW_LINE '\n'
#define TAB '\t'