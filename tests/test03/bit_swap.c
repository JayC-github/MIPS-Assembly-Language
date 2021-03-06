// swap pairs of bits of a 64-bit value, using bitwise operators

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>


// return value with pairs of bits swapped
uint64_t bit_swap(uint64_t value) {
    long mask1 = 0b1010101010101010101010101010101010101010101010101010101010101010; 
    long mask2 = 0b0101010101010101010101010101010101010101010101010101010101010101;
    return ((value & mask1) >> 1) | ((value & mask2) << 1);
}
