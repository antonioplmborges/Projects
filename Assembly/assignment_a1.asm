    .eqv  SYSCALL_PRINT_STRING 4
    .eqv  SYSCALL_EXIT_PROG    10
    
    .data

i:  .word 11
j:  .word 10
A:  .word 0x11, 0x22, 0x33
B:  .word 0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8


    .text
    
    la $s3, i          # load address of i
    la $s4, j          # load address of j
    la $s6, A          # load address of A
    la $s7, B          # load address of B
    
    # B[8]=A[i-j]
    
    lw  $t1, 0($s3)	# $t1 = i
    lw  $t2, 0($s4)	# $t2 = j
    sub	$t0,$t1,$t2	# $t0 = i - j
    mul $t0,$t0,4   	# $t0 = $t0*4
    add $t0,$t0,$s6	# compute the address of A[1]
    lw  $t1, 0($t0) 	# get value of A[i-j]	   
    #sw	$t1, 32($s7)	# B[8]=A[i-j]
    
    li $t0, 32
    sw $t1, B($t0)	# B[8]=A[i-j]	
    # the value assigned is 0x22
    
    # Return to the operating system:
    li $v0, SYSCALL_EXIT_PROG
    syscall               # exit program
   