/*
    file: macros.h
    author: Tomas Marques ist199338
    description: header file for all helper macros and constants
*/

#include <stdlib.h>
#include <string.h>

#define MALLOC(S, T) malloc(S * sizeof(T))
#define MALLOC_STR(S) malloc((strlen(S) + 1) * sizeof(char))
#define SMALLOC(T) MALLOC(1, T)
#define REALLOC(P, S, T) realloc(P, S * sizeof(T))

#define IS_EQUAL_STR(S1, S2) strcmp(S1, S2) == 0
#define PRINT_ERROR(E) printf("%s\n", E)
#define PRINT_VALUE(V) printf("%s\n", V)
#define PRINT_COMPONENT(C) printf("/%s", C)

#define EMPTY_STR ""
#define WHITESPACE ' '
#define WHITESPACE_STR " "
#define NEW_LINE '\n'
#define TAB '\t'
#define NULL_CHARACTER '\0'
#define PATH_SEPARATOR_STR "/"

#define MAX_INPUT 65535
#define ZERO 0
#define ONE 1
#define TWO 2

#define NOT_FOUND_ERR "not found"
#define NO_DATA_ERR "no data"

#define HELP_CMD "help"
#define QUIT_CMD "quit"
#define SET_CMD "set"
#define PRINT_CMD "print"
#define FIND_CMD "find"
#define LIST_CMD "list"
#define SEARCH_CMD "search"
#define DELETE_CMD "delete"

#define PRINT_HELP_CMD_TXT printf("%s\n", "help: Imprime os comandos disponíveis.\nquit: Termina o programa.\nset: Adiciona ou modifica o valor a armazenar.\nprint: Imprime todos os caminhos e valores.\nfind: Imprime o valor armazenado.\nlist: Lista todos os componentes imediatos de um sub-caminho.\nsearch: Procura o caminho dado um valor.\ndelete: Apaga um caminho e todos os subcaminhos.")