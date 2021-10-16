main:

    li $t0, 1
    li $t1, 2
    add $t2, $t1, $t0
    move $a0, $t2
    li $v0, 1
    syscall
    
    li $a0, '\n'
    li $v0, 11
    syscall
    
    jr $ra
