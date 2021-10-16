# read a mark and print the corresponding UNSW grade

main:
    la $a0, prompt      # printf("Enter a mark: ");
    li $v0, 4
    syscall

    li $v0, 5           # scanf("%d", mark);
    syscall

    la $a0, fl
    blt $v0, 50, print
    la $a0, ps
    blt $v0, 65, print
    la $a0, cr 
    blt $v0, 75, print
    la $a0, dn
    blt $v0, 85, print 
    la $a0, hd
    
    
print:    
    li $v0, 4
    syscall 
    jr $ra               #return



    .data
prompt:
    .asciiz "Enter a mark: "
fl:
    .asciiz "FL\n"
ps:
    .asciiz "PS\n"
cr:
    .asciiz "CR\n"
dn:
    .asciiz "DN\n"
hd:
    .asciiz "HD\n"
    
    
    
    
    
#########################################################    
    blt $v0, 50, con1    
    blt $v0, 65, con2  
    blt $v0, 75, con3    
    blt $v0, 85, con4

    la $a0, hd          # printf("HD\n");
    li $v0, 4
    syscall
    b end

con1:    
    la $a0, fl          # printf("FL\n");
    li $v0, 4
    syscall    
    b end
    
con2:    
    la $a0, ps          # printf("PS\n");
    li $v0, 4
    syscall
    b end
    
con3:    
    la $a0, cr          # printf("CR\n");
    li $v0, 4
    syscall    
    b end
    
con4:    
    la $a0, dn          # printf("DN\n");
    li $v0, 4
    syscall 

end:

    jr $ra              # return
    
####################################################################    
    
