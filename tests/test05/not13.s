main:
    li $v0, 5           #   scanf("%d", &x);
    syscall             #
    move $t0, $v0

    li $v0, 5           #   scanf("%d", &y);
    syscall             #
    move $t1, $v0

    add $t2, $t0, 1      # t2 = i = x + 1
    
loop:
    bge $t2, $t1, end
    
    
    beq $t2, 13, jump
    move $a0, $t2          #   printf("%d\n", );
    li $v0, 1
    syscall
    li   $a0, '\n'      #   printf("%c", '\n');
    li   $v0, 11
    syscall

jump:    
    add $t2, $t2, 1     # i++;
    b loop
    
end:

    li $v0, 0           # return 0
    jr $31
