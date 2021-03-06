// If you use C library functions add includes here.

#include "emu.h"
#include "ram.h"
#include "registers.h"
#include <stdlib.h>


/////////////////////////////////////////////////////////////////////////
// change all the d,s,t,I,b,o part in bit pattern into 0

// add $d, $s, $t 	add 	d = s + t 	
#define ADD 0b00000000000000000000000000100000 
// sub $d, $s, $t 	subtract 	d = s - t 	
#define SUB 0b00000000000000000000000000100010 
// mul $d, $s, $t 	multiply to low 	d = s * t 	
#define MUL 0b01110000000000000000000000000010 
// and $d, $s, $t 	and 	d = s & t 	
#define AND 0b00000000000000000000000000100100 
// or $d, $s, $t 	or 	d = s l t 
#define OR 0b00000000000000000000000000100101 
// xor $d, $s, $t 	xor 	d = s ^ t 	
#define XOR 0b00000000000000000000000000100110 
// sllv $d, $t, $s 	shift left 	d = t << s 	
#define SLLV 0b00000000000000000000000000000100 
// srlv $d, $t, $s 	shift right 	d = t >> s 	
#define SRLV 0b00000000000000000000000000000110 
// slt $d, $s, $t 	set on less than 	d = (s < t) 	
#define SLT 0b00000000000000000000000000101010 

//////////////////////////////////////////////////////////

// addi $t, $s, I 	add immediate 	t = s + I 	
#define ADDI 0b00100000000000000000000000000000 
// andi $t, $s, I 	and with immediate 	t = s & I 	
#define ANDI 0b00110000000000000000000000000000 
// ori $t, $s, I 	or with immediate 	t = s l I 	
#define ORI 0b00110100000000000000000000000000 
// xori $t, $s, I 	xor with immediate 	t = s ^ I 	
#define XORI 0b00111000000000000000000000000000 
// slti $t, $s, I 	set on less than immediate 	t = (s < I) 	
#define SLTI 0b00101000000000000000000000000000 

///////////////////////////////////////////////////////////

// sll $d, $t, I 	shift left immediate 	d = t << I 	
#define SLL 0b00000000000000000000000000000000 
// srl $d, $t, I 	shift right immediate 	d = t >> I 	
#define SRL 0b00000000000000000000000000000010 
// lui $t, I 	load upper immediate 	t = I << 16 	
#define LUI 0b00111100000000000000000000000000 


///////////////////////////////////////////////////////////

// lb $t, O($b) 	load byte 	t = *(int8*)(b + O) 	
#define LB 0b10000000000000000000000000000000 
// lh $t, O($b) 	load half word 	t = *(int16*)(b + O) 	
#define LH 0b10000100000000000000000000000000 
// lw $t, O($b) 	load word 	t = *(int32*)(b + O) 	
#define LW 0b10001100000000000000000000000000 
// sb $t, O($b) 	store byte 	*(uint8*)(b + O) = (t & 0xff) 	
#define SB 0b10100000000000000000000000000000 
// sh $t, O($b) 	store half 	*(uint16*)(b + O) = (t & 0xffff) 	
#define SH 0b10100100000000000000000000000000 
// sw $t, O($b) 	store word 	*(uint32*)(b + O) = t 	
#define SW 0b10101100000000000000000000000000 

///////////////////////////////////////////////////////////////

// beq $s, $t, I 	branch on equal if (s == t)  	
#define BEQ 0b00010000000000000000000000000000 
// bne $s, $t, I 	branch on not equal if (s != t)
#define BNE 0b00010100000000000000000000000000 
// blez $s, I 	branch less than or equal than zero  	
#define BLEZ 0b00011000000000000000000000000000 
// bgtz $s, I 	branch greater than zero
#define BGTZ 0b00011100000000000000000000000000 
// bltz $s, I 	branch on less than zero
#define BLTZ 0b00000100000000000000000000000000 
// bgez $s, I 	branch on greater than or equal to zero 	
#define BGEZ 0b00000100000000010000000000000000 

////////////////////////////////////////////////////////////////

// j X 	jump 	PC = (PC & 0xF0000000) | (X << 2) 	
#define J 0b00001000000000000000000000000000 
// jal X 	jump and link 	$ra = PC + 4;
#define JAL 0b00001100000000000000000000000000 
// jr $s 	jump register 	PC = s 	
#define JR 0b00000000000000000000000000001000 
// syscall 	system call 	determined by $v0 	
#define SYSCALL 0b00000000000000000000000000001100 

///////////////////////////////////////////////////////////////


/**
 * execute a MIPS instruction
 *
 * This function should:
 *
 * get register values by calling `get_register(register_type register_number)`
 * change registers by calling `set_register(register_type register_number, uint32_t value)`
 *
 * get memory values by `calling get_byte(uint32_t address)`
 * changes memory by `set_byte(uint32_t address, uint8_t value)`
 *
 * updates program_counter to address of next instruction
 *
 * returns 1 if an exit syscall is executed, 0 otherwise
 */

int execute_instruction(uint32_t instruction, uint32_t *program_counter) {
/*  // example code to implement add $4, $14, $12
    uint32_t x = get_register(12);
    uint32_t y = get_register(15);
    uint32_t sum = x + y;
    set_register(7, sum);

    // Update program_counter to address of next instructions
    // Most instructions will simply do the following:
    (*program_counter) += 4;
    // Jump & Branch instructions will do something different

    // 0 should be returned, unless an exit syscall is executed
*/    
    uint32_t s = (instruction >> 21) & 0x1f;
    uint32_t t = (instruction >> 16) & 0x1f;
    uint32_t d = (instruction >> 11) & 0x1f;

    uint32_t i = instruction & 0xffff;
    int i2 = (instruction >> 6) & 0x1f;
    
    // for negative integer, change from i to i3
    // out of range -32768 .. 32767
    uint32_t i3 = (i > 32767) ? (i - 65536) : (i);

    
    uint32_t b = (instruction >> 21) & 0x1f;
    uint32_t o = instruction & 0xffff;
    uint32_t X = instruction & 0x03ffffff;
     
    
    // special mul 
    if ((instruction & MUL) == MUL) { 
        uint32_t x = get_register(s);
        uint32_t y = get_register(t);
        uint32_t new = x * y;
        set_register(d, new);
    } 
    
    // group 1  
    // 000000ssssstttttddddd + function
    if (((instruction >> 26) & 0x3f) == 0) { 
        if ((instruction & XOR) == XOR 
        && ((instruction & 0x3f) == 0b100110)) { 
            uint32_t x = get_register(s);
            uint32_t y = get_register(t);
            uint32_t new = x ^ y;
            set_register(d, new);
            
        } else if ((instruction & OR) == OR 
        && ((instruction & 0x3f) == 0b100101)) { 
            uint32_t x = get_register(s);
            uint32_t y = get_register(t);
            uint32_t new = x | y;
            set_register(d, new);
        
        } else if ((instruction & AND) == AND 
        && ((instruction & 0x3f) == 0b100100)) { 
            uint32_t x = get_register(s);
            uint32_t y = get_register(t);
            uint32_t new = x & y;
            set_register(d, new);
            
        } else if ((instruction & ADD) == ADD 
        && ((instruction & 0x3f) == 0b100000)) { 
            uint32_t x = get_register(s);
            uint32_t y = get_register(t);
            uint32_t new = x + y;
            set_register(d, new);
        
        } else if ((instruction & SUB) == SUB
        && ((instruction & 0x3f) == 0b100010)) { 
            uint32_t x = get_register(s);
            uint32_t y = get_register(t);
            uint32_t new = x - y;
            set_register(d, new);
        
        } else if ((instruction & SRLV) == SRLV
        && ((instruction & 0x3f) == 0b000110)) { 
            uint32_t x = get_register(s);
            uint32_t y = get_register(t);
            uint32_t new = y >> x;
            set_register(d, new);
        
        } else if ((instruction & SLLV) == SLLV
        && ((instruction & 0x3f) == 0b000100)) { 
            uint32_t x = get_register(s);
            uint32_t y = get_register(t);
            uint32_t new = y << x;
            set_register(d, new);
            
        } else if ((instruction & SLT) == SLT
        && ((instruction & 0x3f) == 0b101010)) { 
            uint32_t x = get_register(s);
            uint32_t y = get_register(t);
            uint32_t new = (x < y);
            set_register(d, new);
        }   
        
    } 
    
       
    // group 2    source + target number + constant
    // function + ssssstttttIIIIIIIIIIIII...      
    if ((instruction & XORI) == XORI 
    && ((instruction >> 26) & 0x3f) == 0b001110) { 
        uint32_t x = get_register(s);
        uint32_t new = x ^ i3;
        set_register(t, new);
    } else if ((instruction & ANDI) == ANDI 
    && ((instruction >> 26) & 0x3f) == 0b001100) { 
        uint32_t x = get_register(s);
        uint32_t new = x & i3;
        set_register(t, new);
    } else if ((instruction & SLTI) == SLTI
    && ((instruction >> 26) & 0x3f) == 0b001010) { 
        uint32_t x = get_register(s);
        uint32_t new = (x < i3);
        set_register(t, new);
    } else if ((instruction & ADDI) == ADDI
    && ((instruction >> 26) & 0x3f) == 0b001000) { 
        uint32_t x = get_register(s);
        uint32_t new = x + i3;
        set_register(t, new);
    } else if ((instruction & ORI) == ORI
    && ((instruction >> 26) & 0x3f) == 0b001101) { 
        uint32_t x = get_register(s);
        uint32_t new = x | i3;
        set_register(t, new);
    } 

     // special 000000000000tttttdddddIIIII + func
    if (((instruction >> 21) & 0x7ff) == 0
    && ((instruction & 0x3f) != 0b100000)) {    
        if ((instruction & SRL) == SRL
        && ((instruction & 0x3f) == 0b000010)) { 
            uint32_t x = get_register(t);
            uint32_t new = x >> i2;
            set_register(d, new);    
        } else if ((instruction & SLL) == SLL
        && ((instruction & 0x3f) == 0b000000)) { 
            uint32_t x = get_register(t);
            uint32_t new = x << i2;
            set_register(d, new);
        }            
    }
   
    // special lui
    if ((instruction & LUI) == LUI 
    && ((instruction >> 21) & 0x7ff) == 0b00111100000) {
        uint32_t new = i3 << 16;
        set_register(t, new);
    }
    
    // group 3
    // funct + bbbbbtttttOOOOOOOOOOOOOOOO
    if ((instruction & SW) == SW
    && ((instruction >> 26) & 0x3f) == 0b101011) {
        uint32_t x = get_register(b);
        uint32_t y = get_register(t);
        
        set_byte(x + o, y & 0xff);
        set_byte(x + o + 1, (y >> 8) & 0xff);
        set_byte(x + o + 2, (y >> 16) & 0xff);
        set_byte(x + o + 3, (y >> 24) & 0xff);
    
    } else if ((instruction & SH) == SH
    && ((instruction >> 26) & 0x3f) == 0b101001) {
        uint32_t x = get_register(b);
        uint32_t y = get_register(t);
        
        set_byte(x + o, y & 0xff);
        set_byte(x + o + 1, (y >> 8) & 0xff);
    
    } else if ((instruction & SB) == SB
    && ((instruction >> 26) & 0x3f) == 0b101000) {
        uint32_t value = get_register(t) & 0xff;
        register_type store = get_register(b) + o;
        set_byte(store, value);           
    
    } else if ((instruction & LW) == LW
    && ((instruction >> 26) & 0x3f) == 0b100011) {
        uint32_t x = get_register(b);
        uint32_t new1 = get_byte(x + o);
        uint32_t new2 = get_byte(x + o + 1);
        uint32_t new3 = get_byte(x + o + 2);
        uint32_t new4 = get_byte(x + o + 3);
        uint32_t new = new1 + (new2 << 8) + (new3 << 16) + (new4 << 24);
        set_register(t, new);
    } else if ((instruction & LH) == LH
    && ((instruction >> 26) & 0x3f) == 0b100001) {
        uint32_t x = get_register(b);
        uint32_t new1 = get_byte(x + o);
        uint32_t new2 = get_byte(x + o + 1);
        // 128 = 0b10000000 = 0x000080
        if ((new2 & 128) == 128) {
            new2 = new2 | 0xFFFF00;
        }

        uint32_t new = new1 + (new2 << 8);
        set_register(t, new);
    } else if ((instruction & LB) == LB
    && ((instruction >> 26) & 0x3f) == 0b100000) {
        uint32_t x = get_register(b);
        uint32_t new = get_byte(x + o);
        // 128 = 0b10000000 = 0x000080
        if ((new & 128) == 128) {
            new = new | 0xFFFFFF00;
        }
        set_register(t, new);
    }








        // group 4
    // function + sssss + ttttt/00000 + IIIIIIIIIIIIIIIII..
    if ((instruction & BGTZ) == BGTZ 
    && ((instruction >> 26) & 0x3f) == 0b000111) {
        
        uint32_t x = get_register(s);
        if (x > 0) {
            (*program_counter) += i3<<2;
            return 0;
        } 
    } else if ((instruction & BNE) == BNE
    && ((instruction >> 26) & 0x3f) == 0b000101) {
        
        uint32_t x = get_register(s);
        uint32_t y = get_register(t);
        if (x != y) {
            (*program_counter) += i3<<2;  
            return 0;
        }        
    
    } else if ((instruction & BLEZ) == BLEZ
    && ((instruction >> 26) & 0x3f) == 0b000110) {
        
        uint32_t x = get_register(s);
        if (x <= 0) {
            (*program_counter) += i3<<2;
            return 0;  
        }    
    
    } else if ((instruction & BEQ) == BEQ
    && ((instruction >> 26) & 0x3f) == 0b000100) {
        
        uint32_t x = get_register(s);
        uint32_t y = get_register(t);
        if (x == y) {
            (*program_counter) += i3<<2;
            return 0;  
        }    
        
    } else if ((instruction & BGEZ) == BGEZ
    && ((instruction >> 26) & 0x3f) == 0b000001
    && ((instruction >> 16) & 1) == 1) {
        
        uint32_t x = get_register(s);
        if (x >= 0) {
            (*program_counter) += i3<<2;
            return 0;  
        }    
    
    } else if ((instruction & BLTZ) == BLTZ
    && ((instruction >> 26) & 0x3f) == 0b000001
    && ((instruction >> 16) & 1) == 0) {
        
        uint32_t x = get_register(s);
        if (x >= 0) {
            (*program_counter) += i3<<2;
            return 0;  
        }
    }
  
  
    
    // special syscall
    // 12 = 0b00000000000000000000000000001100
    if (instruction == 12) {
        // R2 [$v0]   R4[$a0] R5[$a1]
        int request = get_register(2);
        
        // print integer
        if (request == 1) {
            int integer = get_register(4);
            printf("%d", integer);
        // print string
        } else if (request == 4) {
            // get the address of the string to print
            int string = get_register(4);
            int count = 0;
            while (get_byte(string + count) != '\0') {
                printf("%c", get_byte(string + count));
                count++;
            }     

        // read integer
        } else if (request == 5) {
            int integer;
            scanf("%d", &integer);
            set_register(2, integer); 
        // read string
        } else if (request == 8) {
            int address = get_register(4);
            int max = get_register(5);
            int count = 0;
            char c;
            while (count < max) {
                scanf("%c", &c);
                set_register(address + count, c);
                count++;
            }
            
        //  set_register(address + max, '\0');     
        
        // exit
        } else if (request == 10) {
            exit(1);
        // print character
        } else if (request == 11) {
            char c = get_register(4);
            printf("%c", c);
        // read character
        } else if (request == 12) {
            char c;
            scanf("%c", &c);
            set_register(2, c); 
        }
        
             
    } 
    
    // special jr
    // 8 = 0b000000000000000001000
    if ((instruction & JR) == JR 
    && (instruction & 0x1fffff) == 8) {
        // uint32_t x = get_register(s);
        (*program_counter) = s;
        return 0;
    }
    
    
    // JUMP group
    if ((instruction & JAL) == JAL 
    && ((instruction >> 26) & 0x3f) == 0b000011) {
        set_register(31, (*program_counter) + 4);
        (*program_counter) = ((*program_counter) & 0xF0000000) | (X << 2);
        return 0;
    } else if ((instruction & J) == J
    && ((instruction >> 26) & 0x3f) == 0b000010) {
        (*program_counter) = ((*program_counter) & 0xF0000000) | (X << 2);
        return 0;
    }     


    (*program_counter) += 4;
    return 0;
}


// PUT EXTRA FUNCTIONS HERE

