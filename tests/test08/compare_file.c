#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>


int main(int argc, char *argv[]) {
    FILE *fp1 = fopen(argv[1], "r");
    FILE *fp2 = fopen(argv[2], "r");
    
    if (fp1 == NULL || fp2 == NULL) {
        fprintf(stderr,"%s", argv[0]);
        exit(1);
    }
    
    int c1 = fgetc(fp1);
    int c2 = fgetc(fp2);
    int counter = 0;
    int check = 0;
    while (check == 0) {
        if (c1 != EOF && c2 != EOF && c1 != c2) {
            printf("Files differ at byte %d\n", counter);
            check = 1;
        } else if (c1 != EOF && c2 == EOF) {
            printf("EOF on %s\n", argv[2]);
            check = 1;
        } else if (c1 == EOF && c2 != EOF) {
            printf("EOF on %s\n", argv[1]);
            check = 1;
        } else if (c1 == EOF && c2 == EOF) {
            break;
        }
        c1 = fgetc(fp1);
        c2 = fgetc(fp2);
        counter++;
    }
    if (check == 0) printf("Files are identical\n");
     
    fclose(fp1);
    fclose(fp2);
    return 0;
}
