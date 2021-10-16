# Read a number n and print the first n tetrahedral numbers
# https://en.wikipedia.org/wiki/Tetrahedral_number

main:                  # int main(void) {
    
    la $a0, prompt     # printf("Enter how many: ");
    li $v0, 4
    syscall

    li $v0, 5           # scanf("%d", number);
    syscall

    move $t2, $v0       # t2 == how_many_number
    

    li $t1, 1          # n =1

loop1:
    bgt $t1, $t2, end  # while n <= how_many
    
    li $t0, 0          # total = t0 = 0
    li $t3, 1           # j = 1;

loop2:
    bgt $t3, $t1, out1  # while j <= n     
    
    li $t4, 1          # i = 1
    
loop3:
    bgt $t4, $t3, out2  # while i <= j
    
    add $t0, $t0, $t4   #total = total+i;
    
    add $t4, $t4, 1     # i = i + 1
    
    b loop3

out2:    
        
    add $t3, $t3, 1     # j = j + 1
    
    b loop2
        
out1:
    move $a0, $t0          #   printf("%d", total);
    li   $v0, 1
    syscall

    li   $a0, '\n'      # printf("%c", '\n');
    li   $v0, 11
    syscall
    
    
    add $t1, $t1, 1      #n++;
    b loop1

end:
    jr   $ra           # return

    .data
prompt:
    .asciiz "Enter how many: "
