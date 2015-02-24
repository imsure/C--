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
t1:	.asciiz "Then..."
t3:	.asciiz "\n"
t5:	.asciiz "Else..."
t7:	.asciiz "\n"
	.align 2
	.text
main:
	la $sp, -8($sp) # allocate space for old $fp and $ra
	sw $fp, 4($sp) # save old $fp on stack
	sw $ra, 0($sp) # save old $ra on stack
	la $fp, 0($sp) # set up frame pointer
	la $sp, -36($sp) # allocate stack frame for locals/tmps

	li $8, 10 # load constant < 16-bits
	sw $8, -16($fp)

	lw $8, -16($fp) # load local/tmp
	sw $8, -4($fp)

	li $8, 10 # load constant < 16-bits
	sw $8, -36($fp)

	lw $8, -4($fp)
	lw $9, -36($fp)
	bgt $8, $9, L0

	j L1

	.text
L0:
	la $8, t1 # load string const addr
	sw $8, -20($fp) # store string const address

	lw $8, -20($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	la $8, t3 # load string const addr
	sw $8, -24($fp) # store string const address

	lw $8, -24($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	j L2

	.text
L1:
	la $8, t5 # load string const addr
	sw $8, -28($fp) # store string const address

	lw $8, -28($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	la $8, t7 # load string const addr
	sw $8, -32($fp) # store string const address

	lw $8, -32($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	.text
L2:
	la $sp, 0($fp)
	lw $ra, 0($sp)
	lw $fp, 4($sp)
	la $sp, 8($sp)
	jr $ra

