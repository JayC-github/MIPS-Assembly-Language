#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>


int main(int argc, char *argv[]) {
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        fprintf(stderr,"%s", argv[0]);
        exit(1);
    }
    
    int c = fgetc(fp);
    int byte = 0;
    while (c != EOF) {
        if (!isascii(c)) {
            printf("%s: byte %d is non-ASCII\n", argv[1], byte);    
            fclose(fp);
            return 0;
        }
        
        byte++;
        c = fgetc(fp);
    }
    
    
    printf("%s is all ASCII\n", argv[1]);
    fclose(fp);
    return 0;
}
