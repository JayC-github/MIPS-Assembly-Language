#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<stdlib.h>


long file_size(char *pathname) {
    struct stat s;
    
    // stat() return 0 if success, -1 if fail
    if (stat(pathname, &s) != 0) {
        perror(pathname);
        exit(1);
    }
    
    printf("%s: %ld bytes\n", pathname, (long)s.st_size);
    return (long)s.st_size;
}



int main(int argc,char *argv[]) {
    long total = 0;
    for (int i = 1; i < argc; i++) {
        total = total + file_size(argv[i]);
    }
    
    printf("Total: %ld bytes\n", (long)total);
    return 0;
}

