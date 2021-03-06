#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#include "add.h"

// return the MIPS opcode for add $d, $s, $t
uint32_t add(uint32_t d, uint32_t s, uint32_t t) {

    
    return  (((s & 0x1F) << 21) + ((t & 0x1F) << 16) + 
    ((d & 0x1F) << 11) + (1 << 5));

}
