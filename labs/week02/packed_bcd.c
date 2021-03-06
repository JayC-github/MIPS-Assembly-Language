#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#define N_BCD_DIGITS 8

uint32_t packed_bcd(uint32_t packed_bcd);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        long l = strtol(argv[arg], NULL, 0);
        assert(l >= 0 && l <= UINT32_MAX);
        uint32_t packed_bcd_value = l;

        printf("%lu\n", (unsigned long)packed_bcd(packed_bcd_value));
    }

    return 0;
}

// given a packed BCD encoded value between 0 .. 99999999
// return the corresponding integer
uint32_t packed_bcd(uint32_t packed_bcd_value) {
    int mask = 0xF;
    int a = 1;
    int integer = 0;
    int i;
    for (i = 0; i < N_BCD_DIGITS; i++) {
        integer += (packed_bcd_value >> (4 * i) & mask) * a;
        a = a * 10;
    }
    
    return integer;
}












/*
    int num = 0;
    int mask = 15;
    int a = 1;
    for (int i = 0; i <= 7; i++) {
        num += (packed_bcd_value >> (i * 4) & mask) * a;
        a = a * 10;
    }   
    
    return num;
*/
