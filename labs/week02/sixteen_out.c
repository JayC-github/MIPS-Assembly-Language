//
// Sample solution for COMP1521 lab exercises
//
// Convert a 16-bit signed integer to a string of binary digits

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#define N_BITS 16

char *sixteen_out(int16_t value);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        long l = strtol(argv[arg], NULL, 0);
        assert(l >= INT16_MIN && l <= INT16_MAX);
        int16_t value = l;

        char *bits = sixteen_out(value);
        printf("%s\n", bits);

        free(bits);
    }

    return 0;
}

// given a signed 16 bit integer
// return a null-terminated string of 16 binary digits ('1' and '0')
// storage for string is allocated using malloc
char *sixteen_out(int16_t value) {
    char *new = malloc(sizeof(char *) * 17);
    int16_t mask = 1;
    
    int i;
    for (i = 0; i < N_BITS; i++) {
        if ((mask << (15 - i) & value) == 0) {
            new[i] = '0';
        } else {
            new[i] = '1';
        }
    }      
    
    new[16] = '\0';
    return new;    
}

/*
    char *sixteen = malloc(17 * sizeof(char *));
    //int16_t mask;
    for (int i = 0; i < N_BITS; i++) {
        //mask = 1 << (15 - i);
        if ((1 << (15 - i) & value) == 0) {
            sixteen[i] = '0';
        } else {
            sixteen[i] = '1';
        }
    }
    sixteen[16] = '\0';
    return sixteen;
*/
