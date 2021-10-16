# Read 10 numbers into an array
# print 0 if they are in non-decreasing order
# print 1 otherwise

# i in register $t0

main:

    li $t0, 0           # i = 0
loop0:
    bge $t0, 10, end0   # while (i < 10) {

    li $v0, 5           #   scanf("%d", &numbers[i]);
    syscall             #

    mul $t1, $t0, 4     #   calculate &numbers[i]
    la $t2, numbers     #
    add $t3, $t1, $t2   #
    sw $v0, ($t3)       #   store entered number in array

    add $t0, $t0, 1     #   i++;
    b loop0             # }
end0:


    # PUT YOUR CODE HERE

    li $t7, 0          # swapped = 0
    li $t0, 1          # i = 1
loop2:
    bge $t0, 10, end2
    
    mul $t1, $t0, 4    #
    lw $t4, numbers($t1)
    
    sub $t1, $t1, 4
    lw $t5, numbers($t1)
    
    bge $t4, $t5, jump
    li $t7, 1

jump:
    add $t0, $t0, 1
    b loop2

end2:
    
    
    move $a0, $t7         # printf("%d", 42)
    li $v0, 1           #
    syscall

    li   $a0, '\n'      # printf("%c", '\n');
    li   $v0, 11
    syscall

    jr $31

.data

numbers:
    .word 0 0 0 0 0 0 0 0 0 0  # int numbers[10] = {0};


