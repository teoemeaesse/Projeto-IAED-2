#include <stdlib.h>

#define MALLOC(S, T) malloc(S * sizeof(T))
#define MALLOC_STR(S) malloc((strlen(S) + 1) * sizeof(char))
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

#define HELP_CMD_TXT "help: Imprime os comandos disponiveis.\nquit: Termina o programa.\nset: Adiciona ou modifica o valor a armazenar.\nprint: Imprime todos os caminhos e valores.\nfind: Imprime o valor armazenado.\nlist: Lista todos os componentes de um caminho.\nsearch: Procura o caminho dado um valor.\ndelete: Apaga um caminho e todos os subcaminhos.\n"