#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc > 1) {
        // get the enviroment string pointed to by name
        char *Env = getenv("HOME");
        // append the stiring pointed to the end of the string E
        strcat(Env, "/.diary");
        
        FILE *fp = fopen(Env, "a");
        for (int i = 1; i < argc; i++) {
            fputs(argv[i], fp);
            fputc(' ', fp);
        }
        fputc('\n', fp);
    } 
}
