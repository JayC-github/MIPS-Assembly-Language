#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

/* 
Write a C program, leave_only_ascii.c, which takes one argument, a filename.

leave_only_ascii.c should remove all non-ASCII bytes from the file.

After it is run the file should contain only a ASCII bytes.

It should print nothing on stdout. It should only change the file.

Assume a byte is non-ASCII if it contains a value between 128..255 inclusive. 
*/
int main(int argc, char *argv[]) {
    FILE *fp = fopen(argv[1], "r");
    FILE *newfp = fopen("tmp.txt", "w+");
    
    if (newfp == NULL) {
        fprintf(stderr,"%s", argv[0]);
        exit(1);
    }
    
    int c;
    while ((c = fgetc(fp)) != EOF) {
        if (!isascii(c)) continue;
        else fputc(c, newfp);
    }
    
    
    remove(argv[1]);
    rename("tmp.txt", argv[1]);
    return 0;
}
