#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr,"Argument not right");
    }
    
    
    FILE *fp = fopen(argv[1], "w");
    if (fp == NULL) {
        perror(argv[1]);
        return 1;
    }

    int start = atoi(argv[2]);
    int end = atoi(argv[3]);

    if(start > end) {
        fprintf(stderr, "Fail. start greater.");
    }

    while (start <= end) {
        fprintf(fp, "%d\n", start);
        start++;
    }


    fclose(fp);
    return 0;
}



























/*
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *fp = fopen(argv[1], "w");
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <source file> <destination file>\n", argv[0]);
    }    
    
    
    if (fp == NULL) {
        perror(argv[1]);
        return 1;
    }
    
    int counter = atoi(argv[2]);
    int end = atoi(argv[3]);
    
    if (counter > end) {
        fprintf(stderr,"invalid.\n");
        abort();
    }
    
    while (counter <= end) {
        fprintf(fp, "%d\n", counter);
        counter++;
    }
    
    fclose(fp);

    return 0;
}
*/
