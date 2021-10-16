# Sieve of Eratosthenes
# https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
main:
    li $t0, 0           # int i = 0; 
loop1:
    bge $t0, 1000, end1    
    
    mul $t1, $t0, 4     
    
    li $t2, 1
    sw $t2, prime($t1)
    
    add $t0, $t0, 1
    b loop1
end1:  

 
    li $t0, 2          # int i = 2
loop2:  
    bge $t0, 1000, end2        
    
    mul $t1, $t0, 4     
    lw $t2, prime($t1)      # t4 == prime[i]
    
    bne $t2, 1, jump
    
    move $a0, $t0      # printf("%d", i);
    li $v0, 1
    syscall
    
    li   $a0, '\n'      # printf("%c", '\n');
    li   $v0, 11
    syscall
    
    mul $t5, $t0, 2      # int j = i * 2
loop3:
    bge $t5, 1000, end3
    
    mul $t1, $t5, 4          
    la $t2, prime
    add $t3, $t1, $t2
    
    li $t6, 0
    sw $t6, ($t3)          # prime[j] = 0
    
    add $t5, $t5, $t0    # j = j + i;    
    b loop3
end3:

jump:
    add $t0, $t0, 1    # i++     
    b loop2
end2:    
    
    li $v0, 0           # return 0
    jr $31

.data
prime:
    .space 1000
