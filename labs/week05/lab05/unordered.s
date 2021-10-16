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
    li $t6, 0           # int swapped = 0;
    
    li $t0, 1           # i = 1
loop1:
    bge $t0, 10, end1   # while (i < 10) {
        
    mul $t1, $t0, 4     #   calculate &numbers[i]
    la $t2, numbers     #   put address of numbers into t2
    add $t3, $t1, $t2   #   
    
    lw $t4, ($t3)       # int x = numbers[i];  x = t4          
    
    sub $t3, $t3, 4     # i = i - 1
    lw $t5, ($t3)       # int y = numbers[i - 1];  y = t5
    
    bge $t4, $t5 jump     # if (x < y)
    li $t6, 1           
    
jump:    
    
    addi $t0, $t0, 1     #   i++;
    b loop1             # }
end1:
    
    move $a0, $t6       # printf("%d", 0 or 1)
    li $v0, 1           #
    syscall

    li   $a0, '\n'      # printf("%c", '\n');
    li   $v0, 11
    syscall

    jr $ra

.data

numbers:
    .word 0 0 0 0 0 0 0 0 0 0  # int numbers[10] = {0};

