#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*
S_IFLNK    1100000000000000   symbolic link
S_IFREG    1010000000000000   regular file
S_IFBLK    0110000000000000   block device
S_IFDIR    0100000000000000   directory
S_IFCHR    0010000000000000   character device
S_IFIFO    0001000000000000   FIFO
S_IRUSR    0000000100000000   owner has read permission
S_IWUSR    0000000010000000   owner has write permission
S_IXUSR    0000000001000000   owner has execute permission
S_IRGRP    0000000000100000   group has read permission
S_IWGRP    0000000000010000   group has write permission
S_IXGRP    0000000000001000   group has execute permission
S_IROTH    0000000000000100   others have read permission
S_IWOTH    0000000000000010   others have write permission
S_IXOTH    0000000000000001   others have execute permission
*/


void file_mode(char *pathname) {
    
    struct stat s;
    // stat() return 0 if success, -1 if fail
    if (stat(pathname, &s) != 0) {
        perror(pathname);
        exit(1);
    }
    
    mode_t mode = s.st_mode;
    char permission[] = "?rwxrwxrwx";
    int n_per = strlen(permission);
    
    if(S_ISREG(mode)) {
        permission[0] = '-';
    } else if (S_ISDIR(mode)) {
        permission[0] = 'd';
    }
    
    for (int i = 1; i < 10; i++) {
        if (!(mode & (1 << (i - 1)))) {
            permission[n_per - i] = '-';
        }
    
    }
    
    printf("%s %s\n", permission, pathname);
    
/*  int16_t mode = s.st_mode;
    if ((mode >> 14) & 1) {
        printf("d");
    } else {
        printf("-");
    }
    
    if ((mode >> 8) & 1) {
        printf("r");
    } else {
        printf("-");
    }
    
    if ((mode >> 7) & 1) {
        printf("w");
    } else {
        printf("-");
    }
    
    if ((mode >> 6) & 1) {
        printf("x");
    } else {
        printf("-");
    }
    
    if ((mode >> 5) & 1) {
        printf("r");
    } else {
        printf("-");
    }
    
    if ((mode >> 4) & 1) {
        printf("w");
    } else {
        printf("-");
    }
    
    if ((mode >> 3) & 1) {
        printf("x");
    } else {
        printf("-");
    }
    
    if ((mode >> 2) & 1) {
        printf("r");
    } else {
        printf("-");
    }
    
    if ((mode >> 1) & 1) {
        printf("w");
    } else {
        printf("-");
    }
    
    if (mode & 1) {
        printf("x");
    } else {
        printf("-");
    }
    
    printf(" %s\n", pathname);
*/
}



int main(int argc,char *argv[]) {

    for (int i = 1; i < argc; i++) {
        file_mode(argv[i]);
    }
    

    return 0;
}






