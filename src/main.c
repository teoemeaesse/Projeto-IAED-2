/*
    file: main.c
    author: Tomas Marques ist199338
    description: driver code for a file management system
*/

#include <stdio.h>
#include <string.h>

#include "macros.h"
#include "commands.h"

/* forward declaration */
int parseInput();

/*
    main: () -> int
        main driver function, initializes the file system and waits for an exit code
*/
int main() {
    /* initialize file system */
    FileSystem * fs = createFileSystem();

    /* wait for exit code */
    while(parseInput(fs) != ZERO);

    /* free all used memory */
    destroyFileSystem(fs);

    return ZERO;
}

/*
    parseInput: FileSystem * -> int
        handles all user input, returning 0 on program termination
*/
int parseInput(FileSystem * fs) {
    Command * command = NULL;
    char * raw = NULL, * token = NULL;
    
    /* read user input */
    raw = readLine();
    
    /* user did not input anything, wait for more input */
    if(raw == NULL)
        return ONE;
    
    /* read first word in input */
    token = strtok(raw, WHITESPACE_STR);

    /* user did not input anything aside from whitespaces, wait for more input */
    if(token == NULL) {
        free(raw);
        return ONE;
    }

    /* user inputs 'help' */
    if(IS_EQUAL_STR(token, HELP_CMD))
        help();
        
    /* user inputs 'quit' */
    else if(IS_EQUAL_STR(token, QUIT_CMD)) 
        return quit(raw);
        
    /* user inputs 'set' */
    else if(IS_EQUAL_STR(token, SET_CMD)) {
        command = readCommand(TWO);
        set(fs, command);
    }
    
    /* user inputs 'print' */
    else if(IS_EQUAL_STR(token, PRINT_CMD))
        print(fs);
        
    /* user inputs 'find' */
    else if(IS_EQUAL_STR(token, FIND_CMD)) {
        command = readCommand(ONE);
        find(fs, command);
    }
    
    /* user inputs 'list' */
    else if(IS_EQUAL_STR(token, LIST_CMD)) {
        command = readCommand(ONE);
        list(fs, command);
    }
    
    /* user inputs 'search' */
    else if(IS_EQUAL_STR(token, SEARCH_CMD)) {
        command = readCommand(ONE);
        search(fs, command);
    }
    
    /* user inputs 'delete' */
    else if(IS_EQUAL_STR(token, DELETE_CMD)) {
        command = readCommand(ONE);
        delete(fs, command);
    }

    /* free up memory associated with the command */
    if(command != NULL)
        destroyCommand(command);
    
    /* free raw input */
    free(raw);

    /* wait for more input */
    return ONE;
}