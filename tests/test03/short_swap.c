// Swap bytes of a short

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

// given uint16_t value return the value with its bytes swapped
uint16_t short_swap(uint16_t value) {
    int mask = 0xff; // 0000000011111111
    return ((mask & value) << 8) + (value >> 8);
}
