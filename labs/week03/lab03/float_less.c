// Compare 2 floats using bit operations only

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "floats.h"

// float_less is given the bits of 2 floats bits1, bits2 as a uint32_t
// and returns 1 if bits1 < bits2, 0 otherwise
// 0 is return if bits1 or bits2 is Nan
// only bit operations and integer comparisons are used
uint32_t float_less(uint32_t bits1, uint32_t bits2) { //1 -    0 +
    uint32_t sign1 = (bits1 >> 31) & 1;
    uint32_t expo1 = (bits1 >> 23) & 0xff;
    uint32_t frac1 = bits1 & 0x7fffff;
    
    uint32_t sign2 = (bits2 >> 31) & 1;
    uint32_t expo2 = (bits2 >> 23) & 0xff;
    uint32_t frac2 = bits2 & 0x7fffff;
    
    
    // one of them is Nan
    if ((expo1 == 0xff && frac1 != 0) || (expo2 == 0xff && frac2 != 0)) {
        return 0;
    }      
    
    // bits1 negative, bits positive
    if (sign1 > sign2) { 
        return 1;
    // both are negative
    } else if (sign1 == 1 && sign2 == 1) {
        //   -6      -5
        if (expo1 > expo2) {
            return 1;
        //   -6.5555  -6.4444         
        } else if (expo1 == expo2 && frac1 > frac2) {
            return 1;
        }
    // both are positive
    } else if (sign1 == 0 && sign2 == 0) {
        if (expo1 < expo2) {
            return 1;
        } else if (expo1 == expo2 && frac2 > frac1) {
            return 1;
        }
    }
    // bits1 is postivie infinity and bits2 is not
    if (sign2 == 0 && expo2 == 0xff && frac2 == 0 && (expo1 != 0xff)) {
        return 1;
    }
    
    return 0;  
}
