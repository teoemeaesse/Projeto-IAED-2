#include <stdio.h>

#include "macros.h"
#include "command.h"

int main() {
    char * line = readLine();
    printf("%s", line);
    free(line);
    return 0;
}