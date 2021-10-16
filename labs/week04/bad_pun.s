main:

    la $a0, string   # get address of string
    li $v0, 4        # 4 is printf string syscall 
    syscall
    
    #la $a0, string2
    #li $v0, 4
    #syscall
    
    
    jr $ra           # return
    
    .data           
string:
    .asciiz "Jay love Mercy!\n"
#string2:    
    #.asciiz "\n"
