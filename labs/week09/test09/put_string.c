#include <stdio.h>

#include "put_string.h"

// print s to stdout with a new line appended using fputc (only)

void put_string(char *s) {

    for (int counter = 0; s[counter] != '\0'; counter++) {
        fputc(s[counter], stdout);
    }
    
    fputc('\n', stdout);
}
