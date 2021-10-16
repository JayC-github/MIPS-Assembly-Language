# print 42 

main:
    la $a0, love        # printf("%d", 42);
    li $v0, 1
    syscall
    jr   $ra          # return
    
    .data
love: 
    .asciiz "I love Mercy!\n"
