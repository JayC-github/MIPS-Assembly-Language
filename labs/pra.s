# start of function

FuncName
    #function prologue
    sw $fp, -4($sp) #set up stack frame($sp, $fp if used)
    la $fp, -4($sp)
    sw $ra, -8($sp) #save relevant register($ra)
    sw $s0, -12($sp)
    sw $s1, -16($sp)
    sw $s2, -20($sp)
    add $sp, $sp, -20
    
    #function
    #argument $a0
    #result in $v0 (return value)
    
    move $v0, $t0   #restore saved registers(eg. $ra)
    
    lw $s2, -20($sp) #clean up stack frame
    lw $s1, -16($sp)
    lw $s0, -12($fp)
    lw $ra, -8($fp)
    
    la $sp, 4($fp)
    lw $fp, ($fp)
    
    jr $ra
    
    
