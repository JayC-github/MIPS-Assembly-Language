#include "sign_flip.h"

// given the 32 bits of a float return it with its sign flipped
uint32_t sign_flip(uint32_t f) {
    uint32_t sign = (f >> 31) & 1;
    uint32_t expo = (f >> 23) & 0xff;
    uint32_t frac = f & 0x7fffff;
    
    if(sign == 0) {
        sign = 1;
    } else if (sign == 1) {
        sign = 0;
    }
    
    
    return (sign << 31) + (expo << 23) + frac; 

}
