// COMP1521 19T3 ... lab 1
// cat4: Copy input to output

#include <stdlib.h>
#include<stdio.h>

static void copy(FILE *, FILE *);

int main(int argc, char *argv[]) {
    if (argc == 1) {
        copy(stdin, stdout);
    } else {
        FILE *fp;
        for (int i = 1; argv[i] != NULL; i++) {
            if ((fp = fopen(argv[i], "r")) == NULL) {
                printf("Can't read name-of-file");
            } else {
                copy(fp, stdout);
                fclose(fp);
            }
        }
    }
    return EXIT_SUCCESS;
}


// Copy contents of input to output, char-by-char
// Assumes both files open in appropriate mode
static void copy (FILE *input, FILE *output) {
    char s[BUFSIZ];
    while (fgets(s,BUFSIZ,input) != NULL) {
        fputs(s, output);
    }

}
