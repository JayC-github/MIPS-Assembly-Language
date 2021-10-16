# print 42

main:
    li   $a0, 42        # printf("%d", 42);
    li   $v0, 1
    syscall
    li   $a0, '\n'      # printf("%c", '\n');
    li   $v0, 11
    syscall
    jr   $ra          # return


# add 17 and 25  and print result

main:                    #  x, y, z in $t0, $t1, $t2,
    li   $t0, 17         # x = 17;

    li   $t1, 25         # y = 25;

    add  $t2, $t1, $t0   # z = x + y

    move $a0, $t2        # printf("%d", a0);
    li   $v0, 1
    syscall

    li   $a0, '\n'       # printf("%c", '\n');
    li   $v0, 11
    syscall

    jr   $ra             # return



# add 17 and 25 use variabler stored in memory and print result

main:                    #  x, y, z in $t0, $t1, $t2,
    li   $t0, 17         # x = 17;
    sw   $t0, x

    li   $t0, 25         # y = 25;
    sw   $t0, y

    lw   $t0, x
    lw   $t1, y
    add  $t2, $t1, $t0   # z = x + y
    sw   $t2, z

    lw   $a0, z          # printf("%d", a0);
    li   $v0, 1
    syscall

    li   $a0, '\n'       # printf("%c", '\n');
    li   $v0, 11
    syscall

    jr   $ra             # return
.data
x:  .space 4
y:  .space 4
z:  .space 4


# print integerd 1..10 one per line

main:                 # int main(void) {
                      # int i;  // in register $t0

    li    $t0, 1      # i = 1;

loop:                 # loop:
    bgt  $t0, 10 end  # if (i > 10) goto end;

    move $a0, $t0     #   printf("%d" i);
    li   $v0, 1
    syscall

    li   $a0, '\n'      # printf("%c", '\n');
    li   $v0, 11
    syscall

    add  $t0, $t0 1   #   i++;

    b    loop         # goto loop;

end:
    jr   $ra          # return



# read 10 numbers into an array then print the 10 numbers
# i in register $t0
# registers $t1, $t2 & $t3 used to hold temporary results

main:

    li $t0, 0           # i = 0
loop0:
    bge $t0, 10, end0   # while (i < 10) {

    la $a0, string0     #   printf("Enter a number: ");
    li $v0, 4
    syscall

    li $v0, 5           #   scanf("%d", &numbers[i]);
    syscall             #

    mul $t1, $t0, 4     #   calculate &numbers[i]
    la $t2, numbers     #
    add $t3, $t1, $t2   #
    sw $v0, ($t3)       #   store entered number in array

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
    li $v0, 1           #   printf("%d", numbers[i])
    syscall

    li   $a0, '\n'      #   printf("%c", '\n');
    li   $v0, 11
    syscall

    add $t0, $t0, 1     #   i++
    b loop1             # }
end1:

    jr $31              # return

.data

numbers:
    .align 2            # ensure array aligned ona 4-byte boundary
    .space 40           # int numbers[10];

string0:
    .asciiz "Enter a number: "



# count in register $t0
# registers $t1 and $t2 used to hold temporary results
main:
    li $t0, 0           # count = 0

read:
    bge $t0, 10, print  # while (count < 10) {
    la $a0, string0     # printf("Enter a number: ");
    li $v0, 4
    syscall

    li $v0, 5           #   scanf("%d", &numbers[count]);
    syscall             #
    mul $t1, $t0, 4     #   calculate &numbers[count]
    la $t2, numbers     #
    add $t1, $t1, $t2   #
    sw $v0, ($t1)       #   store entered number in array

    add $t0, $t0, 1     #   count++;
    b read              # }

print:
    la $a0, string1     # printf("Reverse order:\n");
    li $v0, 4
    syscall
    li $t0, 9           # count = 9;
next:
    blt $t0, 0, end1    # while (count >= 0) {

    mul $t1, $t0, 4     #   printf("%d", numbers[count])
    la $t2, numbers     #   calculate &numbers[count]
    add $t1, $t1, $t2   #
    lw $a0, ($t1)       #   load numbers[count] into $a0
    li $v0, 1
    syscall

    li   $a0, '\n'      #   printf("%c", '\n');
    li   $v0, 11
    syscall

    sub $t0, $t0,1      #   count--;
    b next              # }
end1:

    jr $31              # return

.data

numbers:
    .space 40           # int numbers[10];

string0:
    .asciiz "Enter a number: "
string1:
    .asciiz "Reverse order:\n"



# calculate 1*1 + 2*2 + ... + 99 * 99 + 100 * 100

main:
    li  $t0, 0          # sum = 0;
    li  $t1, 0          # i = 0

loop:
    bgt $t1, 100 end    # if (i > 100) goto end;
    mul $t3, $t1, $t1   # t3 = i * i;
    add $t0, $t0, $t3   # sum = sum + t3;

    add $t1, $t1, 1     # i = i + 1;
    b   loop

end:
    move $a0, $t0      # printf("%d", sum);
    li   $v0, 1
    syscall

    li   $a0, '\n'      # printf("%c", '\n');
    li   $v0, 11
    syscall

    jr   $ra           # return