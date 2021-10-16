main:
    li $v0, 5           #   scanf("%d", &x);
    syscall             #
    move $t0, $v0

    li $v0, 5           #   scanf("%d", &y);
    syscall             #
    move $t1, $v0

    add $t0, $t0, 1     # int i = x + 1;
loop:    
    bge $t0, $t1, enda
if_stat:    
    beq $t0, 13, out
        
    move $a0, $t0          #   printf("%d\n", i);
    li $v0, 1
    syscall
    li   $a0, '\n'      #   printf("%c", '\n');
    li   $v0, 11
    syscall
out:    
    add $t0, $t0, 1
    b loop
enda:

    li $v0, 0           # return 0
    jr $31

