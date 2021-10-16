#include "bit_rotate.h"

// return the value bits rotated left n_rotations
uint16_t bit_rotate(int n_rotations, uint16_t bits) {
    // rotate left since n >= 0
    if (n_rotations >= 0) {
        n_rotations = n_rotations % 16;
        return (bits << n_rotations) | (bits >> (16 - n_rotations));  
    // rotate right since n < 0
    } else {
        int new = -n_rotations;
        new = new % 16;
        return (bits >> new) | (bits << (16 - new)); 
    }
    
}

