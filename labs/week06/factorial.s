# Recursive factorial function
# n < 1 yields n! = 1
# $s0 is used for n
# we use an s register because the convention is their value
# is preserved across function calls
# f is in $t0

# DO NOT CHANGE THE CODE IN MAIN

main:
    addi $sp, $sp, -8  # create stack frame
    sw   $ra, 4($sp)   # save return address in the position 4 (-4) 
    sw   $s0, 0($sp)   # save $s0 in the position 0 of new $sp (-8)

    li   $s0, 0
    la   $a0, msg1     # printf(Enter n: ")
    li   $v0, 4
    syscall            

    li    $v0, 5
    syscall            # scanf("%d", &n)
    move  $s0, $v0

    move  $a0, $s0     # move the vale of n from $s0 into $a0
    jal   factorial    # factorial(a0);
    move  $t0, $v0     # v0 == factorial(n), move into t0

    move  $a0, $s0
    li    $v0, 1
    syscall            # printf ("%d", n)

    la    $a0, msg2
    li    $v0, 4
    syscall            # printf("! = ")

    move  $a0, $t0
    li    $v0, 1
    syscall            # printf ("%d", f)

    li   $a0, '\n'     # printf("%c", '\n');
    li   $v0, 11
    syscall

                       # clean up stack frame
    lw   $s0, 0($sp)   # restore $s0
    lw   $ra, 4($sp)   # restore $ra
    addi $sp, $sp, 8   # restore sp

    li  $v0, 0         # return 0
    jr  $ra

    .data
msg1:   .asciiz "Enter n: "
msg2:   .asciiz "! = "


# DO NOT CHANGE CODE ABOVE HERE

    .text
factorial:
    #  ADD CODE TO CREATE STACK FRAME
    addi $sp, $sp, -8  # create stack frame
    sw   $ra, 4($sp)   # save return address in the position 4 (-4) 
    sw   $s0, 0($sp)   # save $s0 in the position 0 of new $sp (-8)
    # ADD CODE FORFUNCTION HERE
    move $s0, $a0
    
    
    blt $s0, 1, else
    sub $t0, $s0, 1
    move $a0, $t0
    jal factorial
    move $t1, $v0
    
    mul $t3, $s0, $t1 
    b end_if
    
else:
    li $t3, 1

end_if:    
    
    move $v0, $t3
    # ADD CODE TO REMOVE STACK FRAME
                           # clean up stack frame
    lw   $s0, 0($sp)   # restore $s0
    lw   $ra, 4($sp)   # restore $ra
    addi $sp, $sp, 8   # restore sp

    jr  $ra

