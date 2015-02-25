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
t20:	.asciiz "c2 = "
	.align 2
t30:	.asciiz "str0 = "
	.align 2
t22:	.asciiz "\n"
	.align 2
t41:	.asciiz "str1 = "
	.align 2
t16:	.asciiz "gc = "
	.align 2
t80:	.asciiz "str[2] = "
	.align 2
t35:	.asciiz "\n"
	.align 2
t18:	.asciiz "\n"
	.align 2
t47:	.asciiz "\n"
	.align 2
t85:	.asciiz "\n"
	.align 2
t68:	.asciiz "\n"
	.align 2
t59:	.asciiz "ga[2] = "
	.align 2
	.text
main:
	la $sp, -8($sp) # allocate space for old $fp and $ra
	sw $fp, 4($sp) # save old $fp on stack
	sw $ra, 0($sp) # save old $ra on stack
	la $fp, 0($sp) # set up frame pointer
	la $sp, -256($sp) # allocate stack frame for locals/tmps

	li $8, 99 # load constant < 16-bits
	sw $8, -24($fp)

	lw $8, -24($fp) # load local/tmp
	sb $8, -4($fp)

	li $8, 100 # load constant < 16-bits
	sw $8, -40($fp)

	lw $8, -40($fp) # load local/tmp
	sb $8, -8($fp)

	lw $8, -4($fp) # load c1
	lw $9, -8($fp)
	add $10, $8, $9
	sw $10, -64($fp)

	lw $8, -64($fp) # load local/tmp
	sb $8, gc # store value to global variable gc

	la $8, t16 # load string const addr
	sw $8, -112($fp) # store string const address

	lw $8, -112($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	lw $8 gc # pusing global variable as param
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_int
	la $sp, 4($sp)

	la $8, t18 # load string const addr
	sw $8, -172($fp) # store string const address

	lw $8, -172($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	la $8, t20 # load string const addr
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

	la $8, t22 # load string const addr
	sw $8, -36($fp) # store string const address

	lw $8, -36($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	li $8, 0 # load constant < 16-bits
	sw $8, -60($fp)

	lw $8, -60($fp) # load t24
	li $9, 1
	mul $10, $8, $9
	sw $10, -108($fp)

	la $8, str # load global array address str
	lw $9, -108($fp)
	add $10, $8, $9
	sw $10, -88($fp)

	lw $8, -4($fp) # load local/tmp
	lw $9, -88($fp)
	sb $8, ($9) # store value into char array

	li $8, 1 # load constant < 16-bits
	sw $8, -140($fp)

	lw $8, -140($fp) # load t27
	li $9, 1
	mul $10, $8, $9
	sw $10, -196($fp)

	la $8, str # load global array address str
	lw $9, -196($fp)
	add $10, $8, $9
	sw $10, -168($fp)

	lw $8, -8($fp) # load local/tmp
	lw $9, -168($fp)
	sb $8, ($9) # store value into char array

	la $8, t30 # load string const addr
	sw $8, -20($fp) # store string const address

	lw $8, -20($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	li $8, 0 # load constant < 16-bits
	sw $8, -32($fp)

	lw $8, -32($fp) # load t32
	li $9, 1
	mul $10, $8, $9
	sw $10, -84($fp)

	la $8, str # load global array address str
	lw $9, -84($fp)
	add $10, $8, $9
	sw $10, -56($fp)

	lw $9, -56($fp) # load address of parameter
	lb $8, ($9) # load value of char
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_int
	la $sp, 4($sp)

	la $8, t35 # load string const addr
	sw $8, -136($fp) # store string const address

	lw $8, -136($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	li $8, 1 # load constant < 16-bits
	sw $8, -164($fp)

	lw $8, -164($fp) # load t37
	li $9, 4
	mul $10, $8, $9
	sw $10, -220($fp)

	la $8, ga # load global array address ga
	lw $9, -220($fp)
	add $10, $8, $9
	sw $10, -192($fp)

	li $8, 5 # load constant < 16-bits
	sw $8, -16($fp)

	lw $8, -16($fp) # load local/tmp
	lw $9, -192($fp)
	sw $8, ($9) # store value into int array

	la $8, t41 # load string const addr
	sw $8, -52($fp) # store string const address

	lw $8, -52($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	li $8, 1 # load constant < 16-bits
	sw $8, -80($fp)

	lw $8, -80($fp) # load t43
	li $9, 1
	mul $10, $8, $9
	sw $10, -132($fp)

	la $8, str # load global array address str
	lw $9, -132($fp)
	add $10, $8, $9
	sw $10, -104($fp)

	lw $8, -4($fp) # load c1
	lw $9, -104($fp) # load array address
	lb $10, ($9) # load array element from address
	li $11, 0
	add $9, $10, $11
	add $10, $8, $9
	sw $10, -160($fp)

	lw $8, -160($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_int
	la $sp, 4($sp)

	la $8, t47 # load string const addr
	sw $8, -216($fp) # store string const address

	lw $8, -216($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	li $8, 2 # load constant < 16-bits
	sw $8, -236($fp)

	lw $8, -236($fp) # load t49
	li $9, 4
	mul $10, $8, $9
	sw $10, -48($fp)

	la $8, ga # load global array address ga
	lw $9, -48($fp)
	add $10, $8, $9
	sw $10, -28($fp)

	li $8, 1 # load constant < 16-bits
	sw $8, -76($fp)

	lw $8, -76($fp) # load t52
	li $9, 4
	mul $10, $8, $9
	sw $10, -128($fp)

	la $8, ga # load global array address ga
	lw $9, -128($fp)
	add $10, $8, $9
	sw $10, -100($fp)

	li $8, 0 # load constant < 16-bits
	sw $8, -156($fp)

	lw $8, -156($fp) # load t55
	li $9, 4
	mul $10, $8, $9
	sw $10, -212($fp)

	la $8, ga # load global array address ga
	lw $9, -212($fp)
	add $10, $8, $9
	sw $10, -188($fp)

	lw $8, -100($fp) # load array address
	lw $9, ($8) # load array element from address
	li $10, 0
	add $8, $9, $10
	lw $9, -188($fp) # load array address
	lw $10, ($9) # load array element from address
	li $11, 0
	add $9, $10, $11
	add $10, $8, $9
	sw $10, -232($fp)

	lw $8, -232($fp) # load local/tmp
	lw $9, -28($fp)
	sw $8, ($9) # store value into int array

	la $8, t59 # load string const addr
	sw $8, -44($fp) # store string const address

	lw $8, -44($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	li $8, 1 # load constant < 16-bits
	sw $8, -72($fp)

	lw $8, -72($fp) # load t61
	li $9, 1
	mul $10, $8, $9
	sw $10, -124($fp)

	la $8, str # load global array address str
	lw $9, -124($fp)
	add $10, $8, $9
	sw $10, -96($fp)

	li $8, 0 # load constant < 16-bits
	sw $8, -152($fp)

	lw $8, -152($fp) # load t64
	li $9, 1
	mul $10, $8, $9
	sw $10, -208($fp)

	la $8, str # load global array address str
	lw $9, -208($fp)
	add $10, $8, $9
	sw $10, -184($fp)

	lw $8, -96($fp) # load array address
	lb $9, ($8) # load array element from address
	li $10, 0
	add $8, $9, $10
	lw $9, -184($fp) # load array address
	lb $10, ($9) # load array element from address
	li $11, 0
	add $9, $10, $11
	add $10, $8, $9
	sw $10, -228($fp)

	lw $8, -228($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_int
	la $sp, 4($sp)

	la $8, t68 # load string const addr
	sw $8, -252($fp) # store string const address

	lw $8, -252($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	li $8, 2 # load constant < 16-bits
	sw $8, -68($fp)

	lw $8, -68($fp) # load t70
	li $9, 1
	mul $10, $8, $9
	sw $10, -120($fp)

	la $8, str # load global array address str
	lw $9, -120($fp)
	add $10, $8, $9
	sw $10, -92($fp)

	li $8, 2 # load constant < 16-bits
	sw $8, -148($fp)

	lw $8, -148($fp) # load t73
	li $9, 4
	mul $10, $8, $9
	sw $10, -204($fp)

	la $8, ga # load global array address ga
	lw $9, -204($fp)
	add $10, $8, $9
	sw $10, -180($fp)

	li $8, 1 # load constant < 16-bits
	sw $8, -224($fp)

	lw $8, -224($fp) # load t76
	li $9, 1
	mul $10, $8, $9
	sw $10, -248($fp)

	la $8, str # load global array address str
	lw $9, -248($fp)
	add $10, $8, $9
	sw $10, -244($fp)

	lw $8, -180($fp) # load array address
	lw $9, ($8) # load array element from address
	li $10, 0
	add $8, $9, $10
	lw $9, -244($fp) # load array address
	lb $10, ($9) # load array element from address
	li $11, 0
	add $9, $10, $11
	add $10, $8, $9
	sw $10, -256($fp)

	lw $8, -256($fp) # load local/tmp
	lw $9, -92($fp)
	sb $8, ($9) # store value into char array

	la $8, t80 # load string const addr
	sw $8, -116($fp) # store string const address

	lw $8, -116($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	li $8, 2 # load constant < 16-bits
	sw $8, -144($fp)

	lw $8, -144($fp) # load t82
	li $9, 1
	mul $10, $8, $9
	sw $10, -200($fp)

	la $8, str # load global array address str
	lw $9, -200($fp)
	add $10, $8, $9
	sw $10, -176($fp)

	lw $9, -176($fp) # load address of parameter
	lb $8, ($9) # load value of char
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_int
	la $sp, 4($sp)

	la $8, t85 # load string const addr
	sw $8, -240($fp) # store string const address

	lw $8, -240($fp) # load parameter
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
