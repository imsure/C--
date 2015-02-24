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
	la $sp, -20($sp) # allocate stack frame for locals/tmps

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

	lw $8, 12($fp) # load value of (formal) x
	lw $9, 8($fp) # load value of (formal) y
	mul $10, $8, $9
	sw $10, -20($fp)

	lw $v0, -20($fp) # load t5
	la $sp, 0($fp)
	lw $ra, 0($sp)
	lw $fp, 4($sp)
	la $sp, 8($sp)
	jr $ra

	# Ignore Leave operation for now.
	.data
t7:	.asciiz "foo: z = "
t9:	.asciiz "\n"
t20:	.asciiz "foo: x = "
t22:	.asciiz "\n"
t13:	.asciiz "foo:loop: z = "
t15:	.asciiz "\n"
	.align 2
	.text
foo:
	la $sp, -8($sp) # allocate space for old $fp and $ra
	sw $fp, 4($sp) # save old $fp on stack
	sw $ra, 0($sp) # save old $ra on stack
	la $fp, 0($sp) # set up frame pointer
	la $sp, -52($sp) # allocate stack frame for locals/tmps

	lw $8, 12($fp) # load value of (formal) x
	lw $9, 8($fp) # load value of (formal) y
	add $10, $8, $9
	sw $10, -8($fp)

	lw $8, -8($fp) # load local/tmp
	sw $8, -4($fp)

	la $8, t7 # load string const addr
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

	la $8, t9 # load string const addr
	sw $8, -16($fp) # store string const address

	lw $8, -16($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	li $8, 0 # load constant < 16-bits
	sw $8, -20($fp)

	lw $8, -20($fp) # load local/tmp
	sw $8, -4($fp)

	j L1

	.text
L0:
	la $8, t13 # load string const addr
	sw $8, -36($fp) # store string const address

	lw $8, -36($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	lw $8, -4($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_int
	la $sp, 4($sp)

	la $8, t15 # load string const addr
	sw $8, -40($fp) # store string const address

	lw $8, -40($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	li $8, 1 # load constant < 16-bits
	sw $8, -44($fp)

	lw $8, -4($fp) # load z
	lw $9, -44($fp)
	add $10, $8, $9
	sw $10, -48($fp)

	lw $8, -48($fp) # load local/tmp
	sw $8, -4($fp)

	.text
L1:
	lw $8, 12($fp) # load value of (formal) x
	lw $9, 8($fp) # load value of (formal) y
	add $10, $8, $9
	sw $10, -28($fp)

	lw $8, -4($fp)
	lw $9, -28($fp)
	ble $8, $9, L0

	j L2

	.text
L2:
	lw $8 12($fp)
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	lw $8 8($fp)
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal bar
	la $sp, 8($sp)

	sw $v0, -52($fp) # store t19

	lw $8, -52($fp) # load local/tmp
	sw $8, 12($fp) # load formal argument/tmp

	la $8, t20 # load string const addr
	sw $8, -24($fp) # store string const address

	lw $8, -24($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	lw $8 12($fp)
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_int
	la $sp, 4($sp)

	la $8, t22 # load string const addr
	sw $8, -32($fp) # store string const address

	lw $8, -32($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	lw $v0, -4($fp) # load z
	la $sp, 0($fp)
	lw $ra, 0($sp)
	lw $fp, 4($sp)
	la $sp, 8($sp)
	jr $ra

	# Ignore Leave operation for now.
	.data
t41:	.asciiz "\n"
t36:	.asciiz "main: A[1] = "
	.align 2
	.text
main:
	la $sp, -8($sp) # allocate space for old $fp and $ra
	sw $fp, 4($sp) # save old $fp on stack
	sw $ra, 0($sp) # save old $ra on stack
	la $fp, 0($sp) # set up frame pointer
	la $sp, -92($sp) # allocate stack frame for locals/tmps

	li $8, 0 # load constant < 16-bits
	sw $8, -52($fp)

	lw $8, -52($fp) # load t24
	li $9, 4
	mul $10, $8, $9
	sw $10, -68($fp)

	la $8, -20($fp) # load address of array A
	lw $9, -68($fp)
	add $10, $8, $9
	sw $10, -60($fp)

	li $8, 7 # load constant < 16-bits
	sw $8, -72($fp)

	lw $8, -72($fp) # load local/tmp
	lw $9, -60($fp)
	sw $8, ($9) # store value into int array

	li $8, 1 # load constant < 16-bits
	sw $8, -80($fp)

	lw $8, -80($fp) # load t28
	li $9, 4
	mul $10, $8, $9
	sw $10, -28($fp)

	la $8, -20($fp) # load address of array A
	lw $9, -28($fp)
	add $10, $8, $9
	sw $10, -88($fp)

	li $8, 5 # load constant < 16-bits
	sw $8, -40($fp)

	li $8, 0 # load constant < 16-bits
	sw $8, -48($fp)

	lw $8, -48($fp) # load t33
	li $9, 4
	mul $10, $8, $9
	sw $10, -64($fp)

	la $8, -20($fp) # load address of array A
	lw $9, -64($fp)
	add $10, $8, $9
	sw $10, -56($fp)

	lw $8, -40($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	lw $9, -56($fp) # load address of parameter
	lw $8, ($9) # load value of int
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal foo
	la $sp, 8($sp)

	sw $v0, -36($fp) # store t31

	lw $8, -36($fp) # load local/tmp
	lw $9, -88($fp)
	sw $8, ($9) # store value into int array

	la $8, t36 # load string const addr
	sw $8, -76($fp) # store string const address

	lw $8, -76($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	li $8, 1 # load constant < 16-bits
	sw $8, -84($fp)

	lw $8, -84($fp) # load t38
	li $9, 4
	mul $10, $8, $9
	sw $10, -32($fp)

	la $8, -20($fp) # load address of array A
	lw $9, -32($fp)
	add $10, $8, $9
	sw $10, -92($fp)

	lw $9, -92($fp) # load address of parameter
	lw $8, ($9) # load value of int
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_int
	la $sp, 4($sp)

	la $8, t41 # load string const addr
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
