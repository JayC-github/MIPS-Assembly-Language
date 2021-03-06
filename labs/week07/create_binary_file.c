#include <stdio.h>
#include <stdlib.h>

/*
int main(int argc, char *argv[]) {
    FILE *fp = fopen(argv[1], "w");
    
    if (fp == NULL) {
        perror(argv[1]);
        return 1;
    }
    
    int i = 2;

    while (i < argc) {
        fputc(atoi(argv[i]), fp);
        i++;
    }
    
    fclose(fp);

    return 0;
}
*/

int main(int argc, char *argv[]) {
    FILE *fp = fopen(argv[1], "w");
    if (fp == NULL) {
        perror(argv[1]);
        return 1;
    }

    int count = 2;
    while (count < argc) {
        fputc(atoi(argv[count]), fp);
        count++;
    }


    fclose(fp);
    return 0;
}
