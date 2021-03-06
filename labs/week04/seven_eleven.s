# Read a number and print positive multiples of 7 or 11 < n

main:                  # int main(void) {

    la $a0, prompt       # printf("Enter a number: ");
    li $v0, 4
    syscall

    li $v0, 5            # scanf("%d", number);
    syscall
    
    li $t0, 1            # i = 1
    move $t1, $v0        # t1 = entered number
    
                     
loop:    
    bge $t0, $t1 end     # if i >= number, goto end;
    
    rem $t2 $t0, 7       # t2 == t0 % 7
    rem $t3 $t0, 11      # t3 == t0 % 11
    
    beqz $t2, print      # i % 7  = 0, goto print
    beqz $t3, print      # i % 13  = 0, goto print
    b jump
             
print:
    move $a0, $t0        # printf("%d", i);
    li   $v0, 1
    syscall

    li   $a0, '\n'       # printf("%c", '\n');
    li   $v0, 11
    syscall
    
jump:    
    add $t0, $t0, 1      # i = i + 1;    
    b loop;              # goto loop;
    

end:
    jr   $ra           # return

    .data
prompt:
    .asciiz "Enter a number: "
