# Read 10 numbers into an array
# then print the numbers which are
# larger than the last number read.

# i in register $t0
# registers $t1, $t2 & $t3 used to hold temporary results

main:

    li $t0, 0           # i = 0
loop0:
    bge $t0, 10, end0   # while (i < 10) {

    li $v0, 5           #   scanf("%d", &numbers[i]);
    syscall             #

    mul $t1, $t0, 4     #   calculate &numbers[i]
#    la $t2, numbers     #   the address of the numbers eg. 1000
#    add $t3, $t1, $t2   #   the address of each array eg. 1000+0,1000+4
    sw $v0, numbers($t1)       #   store entered number in array
    
    move $t4, $v0       #   store the last number in array
    
    
    add $t0, $t0, 1     #   i++;
    b loop0             # }
end0:


    li $t0, 0           # i = 0
loop1:
    bge $t0, 10, end1   # while (i < 10) {

    mul $t1, $t0, 4     #   calculate &numbers[i]
    la $t2, numbers     #
    add $t3, $t1, $t2   #
    lw $a0, ($t3)       #   load numbers[i] into $a0
    
    
    blt $a0, $t4, jump  # if (numbers[i] >= last_number) 
    li $v0, 1           #   printf("%d", numbers[i])
    syscall

    li   $a0, '\n'      #   printf("%c", '\n');
    li   $v0, 11
    syscall

jump:
    add $t0, $t0, 1     #   i++
    b loop1             # }
end1:

    jr $ra              # return

.data

numbers:
    .word 0 0 0 0 0 0 0 0 0 0  # int numbers[10] = {0};

