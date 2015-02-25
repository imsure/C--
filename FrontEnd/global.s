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
str:	.space 5
	.align 2
t9:	.asciiz "ga[0] = "
	.align 2
ga:	.space 20
gc:	.space 1
	.align 2
gi:	.space 4
t11:	.asciiz "\n"
	.align 2
	.text
foo:
	la $sp, -8($sp) # allocate space for old $fp and $ra
	sw $fp, 4($sp) # save old $fp on stack
	sw $ra, 0($sp) # save old $ra on stack
	la $fp, 0($sp) # set up frame pointer
	la $sp, -52($sp) # allocate stack frame for locals/tmps

	li $8, 5 # load constant < 16-bits
	sw $8, -12($fp)

	lw $8, -12($fp) # load local/tmp
	sw $8, gi # store value to global variable gi

	li $8, 98 # load constant < 16-bits
	sw $8, -16($fp)

	lw $8, -16($fp) # load local/tmp
	sb $8, -4($fp)

	li $8, 0 # load constant < 16-bits
	sw $8, -20($fp)

	lw $8, -20($fp) # load t2
	li $9, 4
	mul $10, $8, $9
	sw $10, -28($fp)

	la $8, ga # load global array address ga
	lw $9, -28($fp)
	add $10, $8, $9
	sw $10, -24($fp)

	lw $8, -4($fp) # load local/tmp
	lw $9, -24($fp)
	sw $8, ($9) # store value into int array

	li $8, 0 # load constant < 16-bits
	sw $8, -32($fp)

	lw $8, -32($fp) # load t5
	li $9, 4
	mul $10, $8, $9
	sw $10, -40($fp)

	la $8, ga # load global array address ga
	lw $9, -40($fp)
	add $10, $8, $9
	sw $10, -36($fp)

	lw $8, -36($fp) # load array address
	lw $9, ($8) # load array element from address
	li $10, 0
	add $8, $9, $10
	lw $9, -4($fp)
	add $10, $8, $9
	sw $10, -44($fp)

	lw $8, -44($fp) # load local/tmp
	sw $8, -8($fp)

	la $8, t9 # load string const addr
	sw $8, -48($fp) # store string const address

	lw $8, -48($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	lw $8, -8($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_int
	la $sp, 4($sp)

	la $8, t11 # load string const addr
	sw $8, -52($fp) # store string const address

	lw $8, -52($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	la $sp, 0($fp)
	lw $ra, 0($sp)
	lw $fp, 4($sp)
	la $sp, 8($sp)
	jr $ra

	# Ignore Leave operation for now.
	.data
t21:	.asciiz "\n"
	.align 2
t40:	.asciiz "str1 = "
	.align 2
t15:	.asciiz "c1 = "
	.align 2
t34:	.asciiz "\n"
	.align 2
t17:	.asciiz "\n"
	.align 2
t46:	.asciiz "\n"
	.align 2
t19:	.asciiz "c2 = "
	.align 2
t29:	.asciiz "str0 = "
	.align 2
	.text
main:
	la $sp, -8($sp) # allocate space for old $fp and $ra
	sw $fp, 4($sp) # save old $fp on stack
	sw $ra, 0($sp) # save old $ra on stack
	la $fp, 0($sp) # set up frame pointer
	la $sp, -116($sp) # allocate stack frame for locals/tmps

	li $8, 99 # load constant < 16-bits
	sw $8, -28($fp)

	lw $8, -28($fp) # load local/tmp
	sb $8, -4($fp)

	li $8, 100 # load constant < 16-bits
	sw $8, -44($fp)

	lw $8, -44($fp) # load local/tmp
	sb $8, -8($fp)

	la $8, t15 # load string const addr
	sw $8, -68($fp) # store string const address

	lw $8, -68($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	lw $8, -4($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_int
	la $sp, 4($sp)

	la $8, t17 # load string const addr
	sw $8, -96($fp) # store string const address

	lw $8, -96($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	la $8, t19 # load string const addr
	sw $8, -12($fp) # store string const address

	lw $8, -12($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	lw $8, -8($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_int
	la $sp, 4($sp)

	la $8, t21 # load string const addr
	sw $8, -24($fp) # store string const address

	lw $8, -24($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	li $8, 0 # load constant < 16-bits
	sw $8, -40($fp)

	lw $8, -40($fp) # load t23
	li $9, 1
	mul $10, $8, $9
	sw $10, -64($fp)

	la $8, str # load global array address str
	lw $9, -64($fp)
	add $10, $8, $9
	sw $10, -56($fp)

	lw $8, -4($fp) # load local/tmp
	lw $9, -56($fp)
	sb $8, ($9) # store value into char array

	li $8, 1 # load constant < 16-bits
	sw $8, -80($fp)

	lw $8, -80($fp) # load t26
	li $9, 1
	mul $10, $8, $9
	sw $10, -104($fp)

	la $8, str # load global array address str
	lw $9, -104($fp)
	add $10, $8, $9
	sw $10, -92($fp)

	lw $8, -8($fp) # load local/tmp
	lw $9, -92($fp)
	sb $8, ($9) # store value into char array

	la $8, t29 # load string const addr
	sw $8, -16($fp) # store string const address

	lw $8, -16($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	li $8, 0 # load constant < 16-bits
	sw $8, -20($fp)

	lw $8, -20($fp) # load t31
	li $9, 1
	mul $10, $8, $9
	sw $10, -52($fp)

	la $8, str # load global array address str
	lw $9, -52($fp)
	add $10, $8, $9
	sw $10, -36($fp)

	lw $9, -36($fp) # load address of parameter
	lb $8, ($9) # load value of char
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_int
	la $sp, 4($sp)

	la $8, t34 # load string const addr
	sw $8, -76($fp) # store string const address

	lw $8, -76($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	li $8, 1 # load constant < 16-bits
	sw $8, -88($fp)

	lw $8, -88($fp) # load t36
	li $9, 4
	mul $10, $8, $9
	sw $10, -112($fp)

	la $8, ga # load global array address ga
	lw $9, -112($fp)
	add $10, $8, $9
	sw $10, -100($fp)

	li $8, 5 # load constant < 16-bits
	sw $8, -116($fp)

	lw $8, -116($fp) # load local/tmp
	lw $9, -100($fp)
	sw $8, ($9) # store value into int array

	la $8, t40 # load string const addr
	sw $8, -32($fp) # store string const address

	lw $8, -32($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	li $8, 1 # load constant < 16-bits
	sw $8, -48($fp)

	lw $8, -48($fp) # load t42
	li $9, 1
	mul $10, $8, $9
	sw $10, -72($fp)

	la $8, str # load global array address str
	lw $9, -72($fp)
	add $10, $8, $9
	sw $10, -60($fp)

	lw $8, -4($fp) # load c1
	lw $9, -60($fp) # load array address
	lb $10, ($9) # load array element from address
	li $11, 0
	add $9, $10, $11
	add $10, $8, $9
	sw $10, -84($fp)

	lw $8, -84($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_int
	la $sp, 4($sp)

	la $8, t46 # load string const addr
	sw $8, -108($fp) # store string const address

	lw $8, -108($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	la $sp, 0($fp)
	lw $ra, 0($sp)
	lw $fp, 4($sp)
	la $sp, 8($sp)
	jr $ra

	# Ignore Leave operation for now.
