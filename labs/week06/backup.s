    #  ADD CODE TO CREATE STACK FRAME
    addi $sp, $sp, -8  # create stack frame
    sw   $ra, 4($sp)   # save return address
    sw   $s0, 0($sp)   # save $s0

    # ADD CODE FORFUNCTION HERE
    move $s0, $a0      # s0 == int n;
    ble $a0, 1, else   # n
    
    sub $a0, $a0, 1    # n = n - 1; 
    jal factorial
    mul $s0, $s0, $v0  # 
    b finish
    
else:    
    li, $s0, 1         # result = 1
    

finish:    
    move $v0, $s0      # make result into the return $v0
    # ADD CODE TO REMOVE STACK FRAME
    
                       # clean up stack frame
    lw   $s0, 0($sp)   # restore $s0
    lw   $ra, 4($sp)   # restore $ra
    addi $sp, $sp, 8   # restore sp

    jr  $ra
