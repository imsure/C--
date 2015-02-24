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
t0:	.asciiz "n = "
t5:	.asciiz "\n"
	.align 2
	.text
foo:
	la $sp, -8($sp) # allocate space for old $fp and $ra
	sw $fp, 4($sp) # save old $fp on stack
	sw $ra, 0($sp) # save old $ra on stack
	la $fp, 0($sp) # set up frame pointer
	la $sp, -20($sp) # allocate stack frame for locals/tmps

	la $8, t0 # load string const addr
	sw $8, -4($fp) # store string const address

	lw $8, -4($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	li $8, 1 # load constant < 16-bits
	sw $8, -8($fp)

	lw $8, -8($fp) # load t2
	li $9, 4
	mul $10, $8, $9
	sw $10, -16($fp)

	lw $8, 12($fp) # load address of array(formal) A
	lw $9, -16($fp)
	add $10, $8, $9
	sw $10, -12($fp)

	lw $9, -12($fp) # load address of parameter
	lw $8, ($9) # load value of int
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_int
	la $sp, 4($sp)

	la $8, t5 # load string const addr
	sw $8, -20($fp) # store string const address

	lw $8, -20($fp) # load parameter
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
	.align 2
	.text
main:
	la $sp, -8($sp) # allocate space for old $fp and $ra
	sw $fp, 4($sp) # save old $fp on stack
	sw $ra, 0($sp) # save old $ra on stack
	la $fp, 0($sp) # set up frame pointer
	la $sp, -72($sp) # allocate stack frame for locals/tmps

	li $8, 0 # load constant < 16-bits
	sw $8, -24($fp)

	lw $8, -24($fp) # load t7
	li $9, 4
	mul $10, $8, $9
	sw $10, -32($fp)

	la $8, -20($fp) # load address of array B
	lw $9, -32($fp)
	add $10, $8, $9
	sw $10, -28($fp)

	li $8, 46 # load constant < 16-bits
	sw $8, -36($fp)

	lw $8, -36($fp) # load local/tmp
	lw $9, -28($fp)
	sw $8, ($9) # store value into int array

	li $8, 1 # load constant < 16-bits
	sw $8, -40($fp)

	lw $8, -40($fp) # load t11
	li $9, 4
	mul $10, $8, $9
	sw $10, -48($fp)

	la $8, -20($fp) # load address of array B
	lw $9, -48($fp)
	add $10, $8, $9
	sw $10, -44($fp)

	li $8, 78 # load constant < 16-bits
	sw $8, -52($fp)

	lw $8, -52($fp) # load local/tmp
	lw $9, -44($fp)
	sw $8, ($9) # store value into int array

	li $8, 2 # load constant < 16-bits
	sw $8, -56($fp)

	lw $8, -56($fp) # load t15
	li $9, 4
	mul $10, $8, $9
	sw $10, -64($fp)

	la $8, -20($fp) # load address of array B
	lw $9, -64($fp)
	add $10, $8, $9
	sw $10, -60($fp)

	li $8, 36 # load constant < 16-bits
	sw $8, -68($fp)

	lw $8, -68($fp) # load local/tmp
	lw $9, -60($fp)
	sw $8, ($9) # store value into int array

	li $8, 21 # load constant < 16-bits
	sw $8, -72($fp)

	la $8 -20($fp) # passing array
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	lw $8, -72($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal foo
	la $sp, 8($sp)

	la $sp, 0($fp)
	lw $ra, 0($sp)
	lw $fp, 4($sp)
	la $sp, 8($sp)
	jr $ra

