	.text
print_int:
	li $v0, 1
	lw $a0, 0($sp)
	syscall
	jr $ra

	.text
main:
	la $sp, -8($sp) # allocate space for old $fp and $ra
	sw $fp, 4($sp) # save old $fp on stack
	sw $ra, 0($sp) # save old $ra on stack
	la $fp, 0($sp) # set up frame pointer
	la $sp, -52($sp) # allocate stack frame for locals/tmps

	li $8, 1 # load constant < 16-bits
	sw $8, -28($fp)

	lw $8, -28($fp)
	li $9, 1
	mul $10, $8, $9
	sw $10, -36($fp)

	la $8, -8($fp)
	lw $9, -36($fp)
	add $10, $8, $9
	sw $10, -32($fp)

	li $8, 45 # load constant < 16-bits
	sw $8, -40($fp)

	lw $8, -40($fp) # load local/tmp
	lw $9, -32($fp)
	sb $8, ($9) # store value into char array

	li $8, 1 # load constant < 16-bits
	sw $8, -44($fp)

	lw $8, -44($fp)
	li $9, 1
	mul $10, $8, $9
	sw $10, -52($fp)

	la $8, -8($fp)
	lw $9, -52($fp)
	add $10, $8, $9
	sw $10, -48($fp)

	lw $9, -48($fp) # load address of parameter
	lb $8, ($9) # load value of char
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_int
	la $sp, 4($sp)

	la $sp, 0($fp)
	lw $ra, 0($sp)
	lw $fp, 4($sp)
	la $sp, 8($sp)
	jr $ra

