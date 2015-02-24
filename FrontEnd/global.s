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
t2:	.asciiz "gi = "
	.align 2
t4:	.asciiz "\n"
	.align 2
t6:	.asciiz "gc = "
	.align 2
t8:	.asciiz "\n"
	.align 2
ga:	.space 20
gc:	.space 1
	.align 2
gi:	.space 4
t11:	.asciiz "x = "
	.align 2
t13:	.asciiz "\n"
	.align 2
	.text
foo:
	la $sp, -8($sp) # allocate space for old $fp and $ra
	sw $fp, 4($sp) # save old $fp on stack
	sw $ra, 0($sp) # save old $ra on stack
	la $fp, 0($sp) # set up frame pointer
	la $sp, -44($sp) # allocate stack frame for locals/tmps

	li $8, 5 # load constant < 16-bits
	sw $8, -12($fp)

	lw $8, -12($fp) # load local/tmp
	sw $8, gi # store value to global variable gi

	li $8, 98 # load constant < 16-bits
	sw $8, -16($fp)

	lw $8, -16($fp) # load local/tmp
	sb $8, -4($fp)

	la $8, t2 # load string const addr
	sw $8, -20($fp) # store string const address

	lw $8, -20($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	lw $8 gi # pusing global variable as param
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_int
	la $sp, 4($sp)

	la $8, t4 # load string const addr
	sw $8, -24($fp) # store string const address

	lw $8, -24($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	lw $8, -4($fp) # load local/tmp
	sw $8, gc # store value to global variable gc

	la $8, t6 # load string const addr
	sw $8, -28($fp) # store string const address

	lw $8, -28($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	lw $8 gc # pusing global variable as param
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_int
	la $sp, 4($sp)

	la $8, t8 # load string const addr
	sw $8, -32($fp) # store string const address

	lw $8, -32($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	li $8, 0 # load constant < 16-bits
	sw $8, -36($fp)

	lw $8, -36($fp) # load local/tmp
	sw $8, -8($fp)

	lw $8, gi # load global int HЛ}ии
	sw $8, -8($fp)

	la $8, t11 # load string const addr
	sw $8, -40($fp) # store string const address

	lw $8, -40($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	lw $8, -8($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_int
	la $sp, 4($sp)

	la $8, t13 # load string const addr
	sw $8, -44($fp) # store string const address

	lw $8, -44($fp) # load parameter
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
t15:	.asciiz "abc"
	.align 2
	.text
main:
	la $sp, -8($sp) # allocate space for old $fp and $ra
	sw $fp, 4($sp) # save old $fp on stack
	sw $ra, 0($sp) # save old $ra on stack
	la $fp, 0($sp) # set up frame pointer
	la $sp, -4($sp) # allocate stack frame for locals/tmps

	la $8, t15 # load string const addr
	sw $8, -4($fp) # store string const address

	lw $8, -4($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal foo
	la $sp, 4($sp)

	la $sp, 0($fp)
	lw $ra, 0($sp)
	lw $fp, 4($sp)
	la $sp, 8($sp)
	jr $ra

	# Ignore Leave operation for now.
