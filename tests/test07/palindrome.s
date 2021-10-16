# read a line and print whether it is a palindrom

main:
    la   $a0, str0       # printf("Enter a line of input: ");
    li   $v0, 4
    syscall

    la   $a0, line
    la   $a1, 256
    li   $v0, 8          # fgets(buffer, 256, stdin)
    syscall              #

    
    li $t0, 0            # int i = 0;
loop:    
    lb $a0, line($t0)    # a0 = line[i]; 
    beqz $a0, end
    
    addi $t0, $t0, 1        # i++;
    b loop
end:

    li $t1, 0           # int j = 0; (t1 = j)
    sub $t2, $t0, 2     # int k = i - 2 (t2 = k)
    
    
loop2:    
    bge $t1, $t2, end2
    
if_stat:    
    
    lb $t3, line($t1)   # t3 = line[j];
    lb $t4, line($t2)   # t4 = line[k];
    
    beq $t3, $t4, out_if
    
    la   $a0, not_palindrome
    li   $v0, 4
    syscall
    li   $v0, 0          # return 0
    jr   $31

out_if:
    
    add $t1, $t1, 1      # j++;
    sub $t2, $t2, 1      # k--;
    b loop2

end2:
    
    la   $a0, palindrome
    li   $v0, 4
    syscall

    li   $v0, 0          # return 0
    jr   $31


.data
str0:
    .asciiz "Enter a line of input: "
palindrome:
    .asciiz "palindrome\n"
not_palindrome:
    .asciiz "not palindrome\n"


# line of input stored here
line:
    .space 256

