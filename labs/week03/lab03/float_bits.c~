cd// Extract the 3 parts of a float using bit operations only

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "floats.h"

// separate out the 3 components of a float
float_components_t float_bits(uint32_t f) {
    float_components_t new;
    int mask_sign = 1;
    int mask_exp = 0xff;
    int mask_frac = 0x7fffff;
    
    new.sign = (f >> 31) & mask_sign;
    new.exponent = (f >> 23) & mask_exp;
    new.frac = f & mask_frac;
    return new;
    /*
    int mask_sign = 1;
    int mask_expo = 0xff;
    int mask_frac = 0x7fffff;
    
    float_components_t fff;
    fff.sign = (f >> 31) & mask_sign;
    fff.exponent = (f >> 23) & mask_expo;
    fff.fraction = f & mask_frac;
    
    return fff;
*/
}


// given the 3 components of a float
// return 1 if it is NaN, 0 otherwise
int is_nan(float_components_t f) {
    
    return (f.exponent == 0xff && f.fraction != 0) ;
}


// given the 3 components of a float
// return 1 if it is inf, 0 otherwise
int is_positive_infinity(float_components_t f) {
    return (f.sign == 0 && f.fraction == 0 && f.exponent == 0xff);
}


// given the 3 components of a float
// return 1 if it is -inf, 0 otherwise
int is_negative_infinity(float_components_t f) {
    return (f.sign == 1 && f.fraction == 0 && f.exponent == 0xff);
}


// given the 3 components of a float
// return 1 if it is 0 or -0, 0 otherwise
int is_zero(float_components_t f) {

    return (f.exponent == 0 && f.fraction == 0);
}
