// Multiply a float by 2048 using bit operations only

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "floats.h"

// float_2048 is given the bits of a float f as a uint32_t
// it uses bit operations and + to calculate f * 2048
// and returns the bits of this value as a uint32_t
//
// if the result is too large to be represented as a float +inf or -inf is returned
//
// if f is +0, -0, +inf or -inf, or Nan it is returned unchanged
//
// float_2048 assumes f is not a denormal number
//
uint32_t float_2048(uint32_t f) {
    unit32_t sign = (f >> 31) & 1; 
    unit32_t exp = (f >> 23) & 0xff;
    unit32_t frac = f & 0x7fffff;

    if (exp == 0 && frac == 0) {
        return f;
    }

    if (exp = 0xff && frac != 0) {
        return f;
    }
    
    if (exp = 0xff && frac == 0) {
        return f;
    }

    exp = exp + 11;
    if (exp > 0xff) {
        return sign << 31 + 0xff << 23;
    } else {
        return sign << 31 + exp << 23 + frac;
    }
}

/*
    uint32_t sign = (f >> 31) & 1;
    uint32_t expo = (f >> 23) & 0xff;
    uint32_t frac = f & 0x7fffff;
    
    // +inf, -inf
    if (expo == 0xff && frac == 0) {
        return f;
    }
    // +0, -0
    if (expo == 0 && frac == 0) {
        return f;
    }
    // Nan
    if (expo == 0xff && frac != 0) {
        return f;
    }
    
    expo = expo + 11;
    if (expo > 0xff) { // infinity exponent == 11111111, fraction == 0
        return (sign << 31) + (0xff << 23); 
    } else { // normal situation
        return (sign << 31) + (expo << 23) + frac;
    }
       
*/
