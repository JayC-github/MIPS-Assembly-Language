#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char *argv[]) {
    char *home = getenv("HOME");
    strcat(home, "/.diary");
    
    struct stat s;
    if (stat(home, &s) != 0) {
        perror(home);
        exit(1);
    }
    
    mode_t new = s.st_mode;
    if ((S_IRUSR & new) == 0 || (S_IRGRP & new) == 0 || (S_IROTH & new) == 0) {
        printf("no");
    } else {
        printf("yes");
    }   
    
    
    return 0;
}
