# MIPS-Assembly-Language


Mips style guide: https://wiki.jashankj.space/Scribblings/BetterAssembly/


SPIM Instruction Set
An overview of the instruction set in the SPIM MIPS emulator. Based on a document from the University of Stuttgart.

The SPIM emulator implements instructions from the MIPS32 instruction set, as well as pseudo-instructions (which look like MIPS instrcutions, but are not actually provided on the MIPS32 hardware).

Architecture
MIPS has 32 × 32-bit general purpose registers and 16 × 64-bit floating point registers, as well a two special registers Hi and Lo for manipulating 64-bit integer quantities. In addition, it has a memory which is partitioned as follows:


Registers
The 32 general purpose registers can be referenced as $0..$31, or by symbolic names, and are used as follows:

Reg	Name	Description
$0	zero	the value 0, not changeable
$1	$at	assembler temporary; reserved for assembler use
$2,$3	$v0,$v1	value from expression evaluation or function return
$4..$7	$a0..$a3	first four arguments to a function/subroutine, if needed
$8..$15	$t0..$t7	temporary; must be saved by caller to subroutine;
subroutine can overwrite
$16..$23	$s0..$s7	safe function variable;
must not be overwritten by called subroutine
$24..$25	$t8..$t9	temporary; must be saved by caller to subroutine;
subroutine can overwrite
$26..$27	$k0..$k1	for kernel use; may change unexpectedly
$28	$gp	global pointer (address of global area)
$29	$sp	stack pointer (top of stack)
$30	$fp	frame pointer (bottom of current stack frame)
$31	$ra	return address of most recent caller
The 16 floating point registers are referenced in pairs; each pair is 64-bits.

Reg	Description
$f0..$f2	value floating-point expression evaluation or function return
$f4..$f10	temporary; must be saved by caller to subroutine;
subroutine can overwrite
$f12..$f14	first two double-precision function arguments
$f16..$f18	temporary registers; used for expression evaluation
$f20..$f30	safe function variables; must be preserved across function calls
Instructions
Each instruction is written on a single line and has the general format

Label:   OpCode, Operand1, Operand2, Operand3
Some instructions have only one operand, others have two and many have three.

Operands
The following notation is used in describing operands in the description of instructions below.

Operand	Description
Rn	a register; Rs and Rt are sources, and Rd is a destination
Imm	a constant value; a literal constant in decimal or hexadecimal format
Label	a symbolic name which is associated with a memory address
Addr	a memory address, in one of the formats described below
Addressing Modes
Many instructions have one operand which is an address. Addresses can be written in a number of formats:

Format	Address
Label	the address associated with the label
(Rn)	the value stored in register Rn (indirect address)
Imm(Rn)	the sum of Imm and the value stored in register Rn
Label(Rn)	the sum of Label's address and the value stored in register Rn
Label ± Imm	the sum of Label's address and Imm
Label ± Imm(Rn)	the sum of Label's address, Imm and the value stored in register Rn
List of SPIM instructions
Real MIPS instructions are marked with a ✓. All other instructions are pseudoinstructions, special to the SPIM emulator. Operators in expressions have the same meaning as their C counterparts.

 	Instruction	Description
✓	add	Rd, Rs, Rt	Rd = Rs + Rt   (signed)
✓	addu	Rd, Rs, Rt	Rd = Rs + Rt   (unsigned)
✓	addi	Rd, Rs, Imm	Rd = Rs + Imm   (signed)
✓	sub	Rd, Rs, Rt	Rd = Rs - Rt   (signed)
✓	subu	Rd, Rs, Rt	Rd = Rs - Rt   (unsigned)
✓	div	Rs, Rt	Lo = Rs / Rt, Hi = Rs % Rt   (int division, signed)
✓	divu	Rs, Rt	Lo = Rs / Rt, Hi = Rs % Rt   (int division, unsigned)
div	Rd, Rs, Rt	Rd = Rs / Rt   (int division, signed)
divu	Rd, Rs, Rt	Rd = Rs / Rt   (int division, unsigned)
rem	Rd, Rs, Rt	Rd = Rs % Rt   (modulo, signed)
remu	Rd, Rs, Rt	Rd = Rs % Rt   (modulo, unsigned)
mul	Rd, Rs, Rt	Rd = Rs * Rt   (signed)
✓	mult	Rs, Rt	(Hi,Lo) = Rs * Rt   (Lo = bits 0..31, Hi = bits 32..63, signed)
✓	multu	Rs, Rt	(Hi,Lo) = Rs * Rt   (Lo = bits 0..31, Hi = bits 32..63, unsigned)
✓	and	Rd, Rs, Rt	Rd = Rs & Rt  
✓	and	Rd, Rs, Imm	Rd = Rs & Imm  
neg	Rd, Rs	Rd = ~ Rs  
✓	nor	Rd, Rs, Rt	Rd = !(Rs | Rt)  
not	Rd, Rs	Rd = !Rs  
✓	or	Rd, Rs, Rt	Rd = Rs | Rt  
✓	ori	Rd, Rs, Imm	Rd = Rs | Imm  
✓	xor	Rd, Rs, Rt	Rd = Rs ^ Rt  
✓	xori	Rd, Rs, Imm	Rd = Rs ^ Imm  
✓	sll	Rd, Rt, Imm	Rd = Rt << Imm  
✓	sllv	Rd, Rs, Rt	Rd = Rt << Rs  
✓	srl	Rd, Rt, Imm	Rd = Rt >> Imm  
✓	srlv	Rd, Rs, Rt	Rd = Rt >> Rs  
move	Rd, Rs	Rd = Rs  
✓	mfhi	Rd	Rd = Hi  
✓	mflo	Rd	Rd = Lo  
la	Rd, Addr	Rd = Addr  
li	Rd, Imm	Rd = Imm  
✓	lui	Rd, Imm	Rd[0..15] = 0, Rd[16..31] = Imm  
✓	lb	Rd, Addr	Rd = byte at Mem[Addr]   (sign extended, Addr could be Label(Rt))
✓	lw	Rd, Addr	Rd = word at Mem[Addr]   (Addr could be Label(Rt))
✓	sb	Rs, Addr	Mem[Addr] = Rs   (sign extended, Addr could be Label(Rt))
✓	sw	Rs, Addr	Mem[Addr] = Rs   (Addr could be Label(Rt))
✓	slt	Rd, Rs, Rt	Rd = 1 if Rs<Rt, Rd = 0 otherwise   (signed)
✓	slti	Rd, Rs, Imm	Rd = 1 if Rs<Imm, Rd = 0 otherwise   (signed)
✓	sltu	Rd, Rs, Rt	Rd = 1 if Rs<Rt, Rd = 0 otherwise   (unsigned)
✓	beq	Rs, Rt, Label	branch to Label if Rs=Rt   (signed)
beqz	Rs, Label	branch to Label if Rs=0   (signed)
bge	Rs, Rt, Label	branch to Label if Rs≥Rt   (signed)
✓	bgez	Rs, Label	branch to Label if Rs≥0   (signed)
✓	bgezal	Rs, Label	branch to Label and and $ra=PC+8 if Rs≥0   (signed)
bgt	Rs, Rt, Label	branch to Label if Rs>Rt   (signed)
bgtu	Rs, Rt, Label	branch to Label if Rs>Rt   (unsigned)
✓	bgtz	Rs, Label	branch to Label if Rs>0   (signed)
blt	Rs, Rt, Label	branch to Label if Rs<Rt   (signed)
bltu	Rs, Rt, Label	branch to Label if Rs<Rt   (unsigned)
✓	bltz	Rs, Label	branch to Label if Rs<0   (signed)
✓	bltzl	Rs, Label	branch to Label and $ra=PC+8 if Rs<0   (signed)
✓	bne	Rs, Rt, Label	branch to Label if Rs≠Rt  
✓	bnez	Rs, Label	branch to Label if Rs≠0  
✓	j	Label	jump to Label   (PC = Label)
✓	jal	Label	jump to Label and Link   ($ra = PC+8; PC = Label)
✓	jr	Rs	jump to location in Rs  
✓	jalr	Rs	jump to location in Rs and Link   ($ra = PC+8; PC = Label)
syscall		invoke system service; service given in $v0  
System Services
The SPIM emulator provides a number of mechanisms for interacting with the host system. These services are invoked via the syscall pseudo-instruction after storing the service code in the register $v0.

Service	Code	Arguments	Result
print_int	1	$a0 = integer	 
print_float	2	$f12 = float	 
print_double	3	$f12 = double	 
print_string	4	$a0 = char *	 
read_int	5	 	integer in $v0
read_float	6	 	float in $v0
read_double	7	 	double in $v0
read_string	8	$a0 = buffer, $a1 = length	string in buffer
sbrk	9	$a0 = # bytes	extend data segment
exit	10	 	program exits
print_char	11	$a0 = char	 
read_char	12	 	char in $v0
exit(status)	17	status in $a0	program exits
Directives
The SPIM assembler supports a number of directives, which allow things to be specified at assembly time.

Directive	Description
.text	the instructions following this directive are placed in the text segment of memory
.data	the data defined following this directive is placed in the data segment of memory
.space   n	allocate n unitialised bytes of space in the data segment of memory
.word   val1,val2,...	store values in successive words in the data segment of memory
.byte   val1,val2,...	store values in succesive bytes in the data segment of memory
.asciiz "string"	store '\0'-terminated string in the data segment of memory

# MIPS emulator
