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
t1:	.asciiz "\n"
t10:	.asciiz "\n"
t40:	.asciiz "\n"
t22:	.asciiz "\n"
t33:	.asciiz "\n"
t44:	.asciiz "\n"
t36:	.asciiz "\n"
t19:	.asciiz "\n"
	.text
main:
	la $sp, -8($sp) # allocate space for old $fp and $ra
	sw $fp, 4($sp) # save old $fp on stack
	sw $ra, 0($sp) # save old $ra on stack
	la $fp, 0($sp) # set up frame pointer
	la $sp, -196($sp) # allocate stack frame for locals/tmps

	li $8, 10 # load constant < 16-bits
	sw $8, -48($fp)

	lw $8, -48($fp) # load local/tmp
	sw $8, -36($fp)

	lw $8, -36($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_int
	la $sp, 4($sp)

	la $8, t1 # load string const addr
	sw $8, -52($fp) # store string const address

	lw $8, -52($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	li $8, 1 # load constant < 16-bits
	sw $8, -56($fp)

	lw $8, -56($fp)
	li $9, 1
	mul $10, $8, $9
	sw $10, -64($fp)

	la $8, -28($fp)
	lw $9, -64($fp)
	add $10, $8, $9
	sw $10, -60($fp)

	li $8, 45 # load constant < 16-bits
	sw $8, -68($fp)

	lw $8, -68($fp) # load local/tmp
	lw $9, -60($fp)
	sb $8, ($9) # store value into char array

	li $8, 1 # load constant < 16-bits
	sw $8, -72($fp)

	lw $8, -72($fp)
	li $9, 1
	mul $10, $8, $9
	sw $10, -80($fp)

	la $8, -28($fp)
	lw $9, -80($fp)
	add $10, $8, $9
	sw $10, -76($fp)

	lw $9, -76($fp) # load address of parameter
	lb $8, ($9) # load value of char
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_int
	la $sp, 4($sp)

	la $8, t10 # load string const addr
	sw $8, -88($fp) # store string const address

	lw $8, -88($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	li $8, 3 # load constant < 16-bits
	sw $8, -100($fp)

	lw $8, -100($fp)
	li $9, 1
	mul $10, $8, $9
	sw $10, -124($fp)

	la $8, -28($fp)
	lw $9, -124($fp)
	add $10, $8, $9
	sw $10, -108($fp)

	li $8, 21 # load constant < 16-bits
	sw $8, -136($fp)

	lw $8, -136($fp) # load local/tmp
	lw $9, -108($fp)
	sb $8, ($9) # store value into char array

	li $8, 3 # load constant < 16-bits
	sw $8, -152($fp)

	lw $8, -152($fp)
	li $9, 1
	mul $10, $8, $9
	sw $10, -176($fp)

	la $8, -28($fp)
	lw $9, -176($fp)
	add $10, $8, $9
	sw $10, -164($fp)

	lw $8, -164($fp) # load local/tmp
	lb $9, ($8) # load value of char array element
	sw $9, -40($fp) # store value of array element into int

	lw $8, -40($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_int
	la $sp, 4($sp)

	la $8, t19 # load string const addr
	sw $8, -84($fp) # store string const address

	lw $8, -84($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	li $8, 90 # load constant < 16-bits
	sw $8, -96($fp)

	lw $8, -96($fp) # load local/tmp
	sb $8, -32($fp)

	lw $8, -32($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_int
	la $sp, 4($sp)

	la $8, t22 # load string const addr
	sw $8, -120($fp) # store string const address

	lw $8, -120($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	li $8, 0 # load constant < 16-bits
	sw $8, -132($fp)

	lw $8, -132($fp)
	li $9, 4
	mul $10, $8, $9
	sw $10, -160($fp)

	la $8, -20($fp)
	lw $9, -160($fp)
	add $10, $8, $9
	sw $10, -148($fp)

	li $8, 3 # load constant < 16-bits
	sw $8, -172($fp)

	lw $8, -172($fp)
	li $9, 1
	mul $10, $8, $9
	sw $10, -192($fp)

	la $8, -28($fp)
	lw $9, -192($fp)
	add $10, $8, $9
	sw $10, -184($fp)

	lw $8, -184($fp) # load local/tmp
	lb $9, ($8) # load value of char array element
	lw $10, -148($fp) # load array address
	sw $9, ($10) # store array element into int array

	li $8, 0 # load constant < 16-bits
	sw $8, -92($fp)

	lw $8, -92($fp)
	li $9, 4
	mul $10, $8, $9
	sw $10, -116($fp)

	la $8, -20($fp)
	lw $9, -116($fp)
	add $10, $8, $9
	sw $10, -104($fp)

	lw $8, -104($fp) # load local/tmp
	lw $9, ($8) # load value of int array element
	sw $9, -44($fp) # store value of array element into int

	lw $8, -44($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_int
	la $sp, 4($sp)

	la $8, t33 # load string const addr
	sw $8, -144($fp) # store string const address

	lw $8, -144($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	li $8, 45 # load constant < 16-bits
	sw $8, -156($fp)

	lw $8, -156($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_int
	la $sp, 4($sp)

	la $8, t36 # load string const addr
	sw $8, -180($fp) # store string const address

	lw $8, -180($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	li $8, 50 # load constant < 16-bits
	sw $8, -188($fp)

	lw $8, -36($fp)
	lw $9, -188($fp)
	add $10, $8, $9
	sw $10, -196($fp)

	lw $8, -196($fp) # load local/tmp
	sw $8, -40($fp)

	lw $8, -40($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_int
	la $sp, 4($sp)

	la $8, t40 # load string const addr
	sw $8, -112($fp) # store string const address

	lw $8, -112($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	li $8, 10 # load constant < 16-bits
	sw $8, -128($fp)

	lw $8, -40($fp)
	lw $9, -128($fp)
	div $10, $8, $9
	sw $10, -140($fp)

	lw $8, -140($fp) # load local/tmp
	sw $8, -44($fp)

	lw $8, -44($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_int
	la $sp, 4($sp)

	la $8, t44 # load string const addr
	sw $8, -168($fp) # store string const address

	lw $8, -168($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	la $sp, 0($fp)
	lw $ra, 0($sp)
	lw $fp, 4($sp)
	la $sp, 8($sp)
	jr $ra

