#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

int bcd(int bcd_value);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        long l = strtol(argv[arg], NULL, 0);
        assert(l >= 0 && l <= 0x0909);
        int bcd_value = l;

        printf("%d\n", bcd(bcd_value));
        printf("%x\n", bcd_value >> 8);
    }

    return 0;
}

// given a  BCD encoded value between 0 .. 99
// return corresponding integer
int bcd(int bcd_value) {
    int mask = 0XF;
    return (bcd_value >> 8 & mask) * 10 + (bcd_value & mask);
}








/* 
    int mask = 0xF; // 0000000000001111 == 2^3+2^2+2+1=15;
                    // 0000000100000010
    return (bcd_value >> 8 & mask)*10 + (bcd_value & mask);
*/
