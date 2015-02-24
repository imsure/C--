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
t1:	.asciiz "bar: z = "
t3:	.asciiz "\n"
	.align 2
	.text
bar:
	la $sp, -8($sp) # allocate space for old $fp and $ra
	sw $fp, 4($sp) # save old $fp on stack
	sw $ra, 0($sp) # save old $ra on stack
	la $fp, 0($sp) # set up frame pointer
	la $sp, -16($sp) # allocate stack frame for locals/tmps

	lw $8, 12($fp) # load value of (formal) x
	lw $9, 8($fp) # load value of (formal) y
	mul $10, $8, $9
	sw $10, -8($fp)

	lw $8, -8($fp) # load local/tmp
	sw $8, -4($fp)

	la $8, t1 # load string const addr
	sw $8, -12($fp) # store string const address

	lw $8, -12($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	lw $8, -4($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_int
	la $sp, 4($sp)

	la $8, t3 # load string const addr
	sw $8, -16($fp) # store string const address

	lw $8, -16($fp) # load parameter
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
t6:	.asciiz "foo: z = "
t8:	.asciiz "\n"
	.align 2
	.text
foo:
	la $sp, -8($sp) # allocate space for old $fp and $ra
	sw $fp, 4($sp) # save old $fp on stack
	sw $ra, 0($sp) # save old $ra on stack
	la $fp, 0($sp) # set up frame pointer
	la $sp, -16($sp) # allocate stack frame for locals/tmps

	lw $8, 12($fp) # load value of (formal) x
	lw $9, 8($fp) # load value of (formal) y
	add $10, $8, $9
	sw $10, -8($fp)

	lw $8, -8($fp) # load local/tmp
	sw $8, -4($fp)

	la $8, t6 # load string const addr
	sw $8, -12($fp) # store string const address

	lw $8, -12($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	lw $8, -4($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_int
	la $sp, 4($sp)

	la $8, t8 # load string const addr
	sw $8, -16($fp) # store string const address

	lw $8, -16($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	lw $8 12($fp)
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	lw $8 8($fp)
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal bar
	la $sp, 8($sp)

	lw $v0, -4($fp) # load z
	la $sp, 0($fp)
	lw $ra, 0($sp)
	lw $fp, 4($sp)
	la $sp, 8($sp)
	jr $ra

	# Ignore Leave operation for now.
	.data
t21:	.asciiz "\n"
t19:	.asciiz "main: z = "
	.align 2
	.text
main:
	la $sp, -8($sp) # allocate space for old $fp and $ra
	sw $fp, 4($sp) # save old $fp on stack
	sw $ra, 0($sp) # save old $ra on stack
	la $fp, 0($sp) # set up frame pointer
	la $sp, -68($sp) # allocate stack frame for locals/tmps

	li $8, 0 # load constant < 16-bits
	sw $8, -28($fp)

	lw $8, -28($fp) # load t10
	li $9, 4
	mul $10, $8, $9
	sw $10, -40($fp)

	la $8, -20($fp) # load address of array A
	lw $9, -40($fp)
	add $10, $8, $9
	sw $10, -36($fp)

	li $8, 7 # load constant < 16-bits
	sw $8, -48($fp)

	lw $8, -48($fp) # load local/tmp
	lw $9, -36($fp)
	sw $8, ($9) # store value into int array

	li $8, 5 # load constant < 16-bits
	sw $8, -56($fp)

	li $8, 0 # load constant < 16-bits
	sw $8, -60($fp)

	lw $8, -60($fp) # load t16
	li $9, 4
	mul $10, $8, $9
	sw $10, -68($fp)

	la $8, -20($fp) # load address of array A
	lw $9, -68($fp)
	add $10, $8, $9
	sw $10, -64($fp)

	lw $8, -56($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	lw $9, -64($fp) # load address of parameter
	lw $8, ($9) # load value of int
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal foo
	la $sp, 8($sp)

	sw $v0, -52($fp) # store t14

	lw $8, -52($fp) # load local/tmp
	sw $8, -24($fp)

	la $8, t19 # load string const addr
	sw $8, -32($fp) # store string const address

	lw $8, -32($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	lw $8, -24($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_int
	la $sp, 4($sp)

	la $8, t21 # load string const addr
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
