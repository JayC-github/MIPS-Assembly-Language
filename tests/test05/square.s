main:
    li $v0, 5           #   scanf("%d", &x);
    syscall             #
    move $t0, $v0

    li $t1, 0           # int i = 0;
    
loop0:    
    bge $t1, $t0, end    # while(i < x)
    li $t2, 0           # int j = 0;    
loop1:    
    bge $t2, $t0, out1   # while (j < x)
    li $a0, '*'          # printf("%d\n", 42);
    li $v0, 11
    syscall
    add $t2, $t2, 1     # j = j + 1;
    b loop1
    
out1:    
    add $t1, $t1, 1     # i = i + 1;
    li   $a0, '\n'      # printf("%c", '\n');
    li   $v0, 11
    syscall
    b loop0
end:

    li $v0, 0           # return 0
    jr $31
