	.eqv SYSCALL_EXIT 10
	.eqv SYSCALL_GET_STRING 8
	.eqv SYSCALL_PRINT_STRING 4
	
	.eqv MAX_STRING 80
	
.data
	Prompt: .asciiz "Enter a string: "
	UserInput: .space 80
.text

	la	$a0, Prompt			# load prompt into $a0
	li 	$v0, SYSCALL_PRINT_STRING	# print the prompt
	syscall
	
	la	$a0, UserInput			# load the address of the input buffer into $a0
	li	$a1, MAX_STRING			# load max number of characters to read into input buffer
	li	$v0, SYSCALL_GET_STRING		# get user input
	syscall
	
	la	$a0, UserInput
	li	$v0, SYSCALL_PRINT_STRING
	syscall
	
	#exit
	li	$v0, SYSCALL_EXIT	# request to terminate application
	syscall