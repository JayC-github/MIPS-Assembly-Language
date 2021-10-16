# read a number n and print the integers 1..n one per line

main:                           # int main(void)
    
    la  $a0, prompt             # printf("Enter a number: ");
    li  $v0, 4
    syscall

    li  $v0, 5                  # scanf("%d", number);
    syscall
    move $t1, $v0               ## t1 = v0 num

    li $t0 1                    ## i = 1;    
        
loop:                           # loop
    bgt $t0, $t1 end            # if ($t0 > $t1) go to end
    
    move $a0, $t0               # printf("%d", i);
    li  $v0, 1
    syscall

    li   $a0, '\n'              # printf("%c", '\n');
    li   $v0, 11
    syscall
    
    addi $t0, $t0 1              #  i++;
    b   loop                    # loop again;
    
end:
    jr  $ra                     # return

    .data
prompt:
    .asciiz "Enter a number: "
