	.text
print_int:
	li $v0, 1
	lw $a0, 0($sp)
	syscall
	jr $ra

	.text
print_string:
	li $v0, 4
	lw $a0, 0($sp)
	syscall
	jr $ra

	.data
t0:	.asciiz "z1 = "
t2:	.asciiz "\n"
t4:	.asciiz "z = "
t7:	.asciiz "\n"
	.align 2
	.text
foo:
	la $sp, -8($sp) # allocate space for old $fp and $ra
	sw $fp, 4($sp) # save old $fp on stack
	sw $ra, 0($sp) # save old $ra on stack
	la $fp, 0($sp) # set up frame pointer
	la $sp, -32($sp) # allocate stack frame for locals/tmps

	lw $8, 12($fp) # load formal argument/tmp
	sw $8, -24($fp)

	lw $8, 8($fp) # load formal argument/tmp
	sw $8, -32($fp)

	la $8, t0 # load string const addr
	sw $8, -8($fp) # store string const address

	lw $8, -8($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	lw $8, -24($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_int
	la $sp, 4($sp)

	la $8, t2 # load string const addr
	sw $8, -12($fp) # store string const address

	lw $8, -12($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	la $8, t4 # load string const addr
	sw $8, -16($fp) # store string const address

	lw $8, -16($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	lw $8, -24($fp)
	lw $9, -32($fp)
	add $10, $8, $9
	sw $10, -20($fp)

	lw $8, -20($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_int
	la $sp, 4($sp)

	la $8, t7 # load string const addr
	sw $8, -28($fp) # store string const address

	lw $8, -28($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	la $sp, 0($fp)
	lw $ra, 0($sp)
	lw $fp, 4($sp)
	la $sp, 8($sp)
	jr $ra

	.data
t24:	.asciiz "\n"
t17:	.asciiz "A[1] = "
	.align 2
	.text
main:
	la $sp, -8($sp) # allocate space for old $fp and $ra
	sw $fp, 4($sp) # save old $fp on stack
	sw $ra, 0($sp) # save old $ra on stack
	la $fp, 0($sp) # set up frame pointer
	la $sp, -80($sp) # allocate stack frame for locals/tmps

	li $8, 0 # load constant < 16-bits
	sw $8, -24($fp)

	lw $8, -24($fp)
	li $9, 4
	mul $10, $8, $9
	sw $10, -36($fp)

	la $8, -20($fp) # load address of array A
	lw $9, -36($fp)
	add $10, $8, $9
	sw $10, -28($fp)

	li $8, 7 # load constant < 16-bits
	sw $8, -44($fp)

	lw $8, -44($fp) # load local/tmp
	lw $9, -28($fp)
	sw $8, ($9) # store value into int array

	li $8, 5 # load constant < 16-bits
	sw $8, -52($fp)

	li $8, 0 # load constant < 16-bits
	sw $8, -60($fp)

	lw $8, -60($fp)
	li $9, 4
	mul $10, $8, $9
	sw $10, -72($fp)

	la $8, -20($fp) # load address of array A
	lw $9, -72($fp)
	add $10, $8, $9
	sw $10, -64($fp)

	lw $8, -52($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	lw $9, -64($fp) # load address of parameter
	lw $8, ($9) # load value of int
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal foo
	la $sp, 8($sp)

	la $8, t17 # load string const addr
	sw $8, -76($fp) # store string const address

	lw $8, -76($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	li $8, 0 # load constant < 16-bits
	sw $8, -80($fp)

	lw $8, -80($fp)
	li $9, 4
	mul $10, $8, $9
	sw $10, -40($fp)

	la $8, -20($fp) # load address of array A
	lw $9, -40($fp)
	add $10, $8, $9
	sw $10, -32($fp)

	li $8, 3 # load constant < 16-bits
	sw $8, -48($fp)

	lw $8, -32($fp) # load array address
	lw $9, ($8) # load array element from address
	li $10, 0
	add $8, $9, $10
	lw $9, -48($fp)
	sub $10, $8, $9
	sw $10, -56($fp)

	lw $8, -56($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_int
	la $sp, 4($sp)

	la $8, t24 # load string const addr
	sw $8, -68($fp) # store string const address

	lw $8, -68($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	la $sp, 0($fp)
	lw $ra, 0($sp)
	lw $fp, 4($sp)
	la $sp, 8($sp)
	jr $ra

