// If you use C library functions add includes here.

#include "emu.h"
#include "ram.h"
#include "registers.h"

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
/*
 * print a MIPS instruction (no newline)
 * run reference implementation if unsure what to print
 */
void print_instruction(uint32_t instruction) {
    int s = (instruction >> 21) & 0x1f;
    int t = (instruction >> 16) & 0x1f;
    int d = (instruction >> 11) & 0x1f;
    int i = instruction & 0xffff;
    int i2 = (instruction >> 6) & 0x1f;
    
    // for negative integer, change from i to i3
    // out of range -32768 .. 32767
    int i3 = (i > 32767) ? (i - 65536) : (i);
    
    int b = (instruction >> 21) & 0x1f;
    int o = instruction & 0xffff;
    int X = instruction & 0x03ffffff;
     
    
    // special mul 
    if ((instruction & MUL) == MUL) { 
        printf("mul ");
        printf("$%d, $%d, $%d", d, s, t);
        return;
    } 
    
    // special syscall
    // 12 = 0b00000000000000000000000000001100
    if (instruction == 12) {
        printf("syscall ");
        return;     
    } 
    
    // special jr
    // 8 = 0b000000000000000001000
    if ((instruction & JR) == JR 
    && (instruction & 0x1fffff) == 8) {
        printf("jr ");
        printf("$%d", s);
        return; 
    } 
    
    
    // special 000000000000tttttdddddIIIII + function
    if (((instruction >> 21) & 0x7ff) == 0
    && ((instruction & 0x3f) != 0b100000)) {    
        if ((instruction & SRL) == SRL
        && ((instruction & 0x3f) == 0b000010)) { 
            printf("srl ");    
        } else if ((instruction & SLL) == SLL
        && ((instruction & 0x3f) == 0b000000)) { 
            printf("sll ");
        }            
        printf("$%d, $%d, %d", d, t, i2);
        return;  
    }
    

    // group 1  
    // 000000ssssstttttddddd + function
    if (((instruction >> 26) & 0x3f) == 0) { 
        if ((instruction & XOR) == XOR 
        && ((instruction & 0x3f) == 0b100110)) { 
            printf("xor ");
        } else if ((instruction & OR) == OR 
        && ((instruction & 0x3f) == 0b100101)) { 
            printf("or ");
        } else if ((instruction & AND) == AND 
        && ((instruction & 0x3f) == 0b100100)) { 
            printf("and ");
        } else if ((instruction & ADD) == ADD 
        && ((instruction & 0x3f) == 0b100000)) { 
            printf("add ");
        } else if ((instruction & SUB) == SUB
        && ((instruction & 0x3f) == 0b100010)) { 
            printf("sub ");
        } else if ((instruction & SRLV) == SRLV
        && ((instruction & 0x3f) == 0b000110)) { 
            printf("srlv ");
            printf("$%d, $%d, $%d", d, t, s);
            return;
        } else if ((instruction & SLLV) == SLLV
        && ((instruction & 0x3f) == 0b000100)) { 
            printf("sllv ");
            printf("$%d, $%d, $%d", d, t, s);
            return;
        } else if ((instruction & SLT) == SLT
        && ((instruction & 0x3f) == 0b101010)) { 
            printf("slt ");
        }   
        printf("$%d, $%d, $%d", d, s, t);
        return;
    }
    
    
    // group 2    source + target number + constant
    // function + ssssstttttIIIIIIIIIIIII...    
    if ((instruction & XORI) == XORI 
    && ((instruction >> 26) & 0x3f) == 0b001110) { 
        printf("xori ");
        printf("$%d, $%d, %d", t, s, i3);
        return;
    } else if ((instruction & ANDI) == ANDI 
    && ((instruction >> 26) & 0x3f) == 0b001100) { 
        printf("andi ");
        printf("$%d, $%d, %d", t, s, i3);
        return;
    } else if ((instruction & SLTI) == SLTI
    && ((instruction >> 26) & 0x3f) == 0b001010) { 
        printf("slti ");
        printf("$%d, $%d, %d", t, s, i3);
        return;
    } else if ((instruction & ADDI) == ADDI
    && ((instruction >> 26) & 0x3f) == 0b001000) { 
        printf("addi ");
        printf("$%d, $%d, %d", t, s, i3);
        return;
    } else if ((instruction & ORI) == ORI
    && ((instruction >> 26) & 0x3f) == 0b001101) { 
        printf("ori ");
        printf("$%d, $%d, %d", t, s, i3);
        return;
    } 
    
    
    
    
    // group 3
    // funct + bbbbbtttttOOOOOOOOOOOOOOOO
    if ((instruction & SW) == SW
    && ((instruction >> 26) & 0x3f) == 0b101011) {
        printf("sw ");
        printf("$%d, %d($%d)", t, o, b);
        return;
    } else if ((instruction & SH) == SH
    && ((instruction >> 26) & 0x3f) == 0b101001) {
        printf("sh ");
        printf("$%d, %d($%d)", t, o, b);
        return;
    } else if ((instruction & SB) == SB
    && ((instruction >> 26) & 0x3f) == 0b101000) {
        printf("sb ");
        printf("$%d, %d($%d)", t, o, b);
        return;
    } else if ((instruction & LW) == LW
    && ((instruction >> 26) & 0x3f) == 0b100011) {
        printf("lw ");
        printf("$%d, %d($%d)", t, o, b);
        return;
    } else if ((instruction & LH) == LH
    && ((instruction >> 26) & 0x3f) == 0b100001) {
        printf("lh ");
        printf("$%d, %d($%d)", t, o, b);
        return;
    } else if ((instruction & LB) == LB
    && ((instruction >> 26) & 0x3f) == 0b100000) {
        printf("lb ");
        printf("$%d, %d($%d)", t, o, b);
        return;
    } 
    
    
    // special lui
    if ((instruction & LUI) == LUI 
    && ((instruction >> 21) & 0x7ff) == 0b00111100000) {
        printf("lui ");
        printf("$%d, %d", t, i3);
        return;
    }
    
    
    // group 4
    // function + sssss + ttttt/00000 + IIIIIIIIIIIIIIIII..
    if ((instruction & BGTZ) == BGTZ 
    && ((instruction >> 26) & 0x3f) == 0b000111) {
        printf("bgtz ");
        printf("$%d, %d", s, i3);
        return; 
    } else if ((instruction & BNE) == BNE
    && ((instruction >> 26) & 0x3f) == 0b000101) {
        printf("bne ");
        printf("$%d, $%d, %d", s, t, i3);
        return; 
    } else if ((instruction & BLEZ) == BLEZ
    && ((instruction >> 26) & 0x3f) == 0b000110) {
        printf("blez ");
        printf("$%d, %d", s, i3);
        return; 
    } else if ((instruction & BEQ) == BEQ
    && ((instruction >> 26) & 0x3f) == 0b000100) {
        printf("beq ");
        printf("$%d, $%d, %d", s, t, i3);
        return; 
    } else if ((instruction & BGEZ) == BGEZ
    && ((instruction >> 26) & 0x3f) == 0b000001
    && ((instruction >> 16) & 1) == 1) {
        printf("bgez ");
        printf("$%d, %d", s, i3);
        return; 
    } else if ((instruction & BLTZ) == BLTZ
    && ((instruction >> 26) & 0x3f) == 0b000001
    && ((instruction >> 16) & 1) == 0) {
        printf("bltz ");
        printf("$%d, %d", s, i3);
        return; 
    }
    
    // JUMP group
    if ((instruction & JAL) == JAL 
    && ((instruction >> 26) & 0x3f) == 0b000011) {
        printf("jal ");
        printf("0x%x", X);
        return; 
    } else if ((instruction & J) == J
    && ((instruction >> 26) & 0x3f) == 0b000010) {
        printf("j ");
        printf("0x%x", X);
        return; 
    } 
    
}

// PUT YOUR FUNCTIONS HERE
