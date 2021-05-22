#include <stdio.h>
#include <string.h>

#include "macros.h"
#include "commands.h"

int parseInput();

int main() {
    DirManager * root = createDirManager();
    TreeAVL * tree = createTreeAVL();
    
    

    root->subdirs = tree;

    insertTreeAVL(tree, "a", "1");
    insertTreeAVL(tree, "b", "2");
    insertTreeAVL(tree, "c", "3");
    insertTreeAVL(tree, "3", "3");
    insertTreeAVL(tree, "as", "3");
    insertTreeAVL(tree, "b", "3");
    insertTreeAVL(tree, "z", "3");
    insertTreeAVL(tree, "ss", "3");
    insertTreeAVL(tree, "2", "3");
    insertTreeAVL(tree, "6", "3");
    insertTreeAVL(tree, "7", "3");
    insertTreeAVL(tree, "8", "3");
    insertTreeAVL(tree, "9", "3");
    insertTreeAVL(tree, "99", "3");
    insertTreeAVL(tree, "asd", "3");
    insertTreeAVL(tree, "bac", "3");
    insertTreeAVL(tree, "asdc", "3");
    insertTreeAVL(tree, "cac", "3");
    insertTreeAVL(tree, "0", "3");
    insertTreeAVL(tree, "+", "3");
    insertTreeAVL(tree, "_", "3");
    insertTreeAVL(tree, "[", "3");
    insertTreeAVL(tree, "]", "3");
    insertTreeAVL(tree, "\\", "3");
    insertTreeAVL(tree, "|", "3");
    insertTreeAVL(tree, "^", "3");
    insertTreeAVL(tree, "&", "3");
    insertTreeAVL(tree, "*", "3");
    insertTreeAVL(tree, ")", "3");
    insertTreeAVL(tree, "(", "3");
    insertTreeAVL(tree, "@", "3");

    printTree(tree->root);

    destroyDirManager(root);

    return ZERO;
    
    /*DirManager * dirManager = createDirManager();

    while(parseInput(dirManager) != ZERO);

    destroyDirManager(dirManager);

    return ZERO;*/
}


/*int parseInput(DirManager * dirManager) {
    Command * command;
    char * raw, * token;
    
    raw = readLine();
    if(raw == NULL)
        return NULL;
    token = strtok(raw, WHITESPACE_STR);
    
    if(strcmp(token, HELP_CMD) == ZERO)
        help();

    else if(strcmp(token, QUIT_CMD) == ZERO)
        return quit(raw, token);

    else if(strcmp(token, SET_CMD)) {
        command = readCommand(3);
        set(dirManager, command);
    }
    else if(strcmp(token, PRINT_CMD)) {
        
    }
    else if(strcmp(token, FIND_CMD)) {
        
    }
    else if(strcmp(token, LIST_CMD)) {
        
    }
    else if(strcmp(token, SEARCH_CMD)) {
        
    }
    else if(strcmp(token, DELETE_CMD)) {
        
    }

    destroyCommand(command);
    free(raw);
    free(token);

    return ONE;
}*/