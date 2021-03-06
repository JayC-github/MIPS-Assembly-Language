# read 10 numbers into an array
# bubblesort them
# then print the 10 numbers

# i in register $t0
# registers $t1, $t2 & $t3 used to hold temporary results

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

    li $t7, 1           # int swapped = 1;
loopswap:
    bne $t7, 1, endswap # while(swapped)   
        
    li $t7, 0          # swapped = 0;
    li $t0, 1          # i = 1
loop1:
    bge $t0, 10, end1   # while (i < 10) {
        
    mul $t1, $t0, 4     #   calculate &numbers[i]
    la $t2, numbers     #   put address of numbers into t2
    add $t3, $t1, $t2   #   
    
    lw $t4, ($t3)       # int x = numbers[i](t3);x = t4,t3 = i          
    
    sub $t5, $t3, 4     # t5 = i - 1
    lw $t6, ($t5)       # int y = numbers[i - 1];  y = t6
    
    bge $t4, $t6 jump     # if (x < y)
    sw  $t6, ($t3)        # numbers[i] = y;
    sw  $t4, ($t5)        # numbers[i - 1] = x;
    li $t7, 1             # swapped = 1;           
    
jump:    
    
    addi $t0, $t0, 1     #   i++;
    b loop1             # }
end1:


    b loopswap

endswap:

    
    
 li $t0, 0           # i = 0
loop2:
    bge $t0, 10, end2   # while (i < 10) {

    mul $t1, $t0, 4     #   calculate &numbers[i]
    #la $t2, numbers     #
    #add $t3, $t1, $t2   #   lw $a0, numbers($t1)
    lw $a0, numbers($t1)       #   load numbers[i] into $a0
                              
    li $v0, 1           #   printf("%d", numbers[i])
    syscall
    
    la   $a0, '\n'      #   printf("%c", '\n');
    li   $v0, 11
    syscall
    
    add $t0, $t0, 1     
    b loop2
end2:

     jr $ra              # return


.data

numbers:
    .word 0 0 0 0 0 0 0 0 0 0  # int numbers[10] = {0};

