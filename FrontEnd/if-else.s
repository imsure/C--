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
t11:	.asciiz "n = "
t21:	.asciiz "\n"
t13:	.asciiz "\n"
t51:	.asciiz "\n"
t35:	.asciiz "i = "
t63:	.asciiz "j + i != n "
t54:	.asciiz "j + i = "
t45:	.asciiz "j + i == n "
t27:	.asciiz "i = "
t37:	.asciiz "\n"
t19:	.asciiz "i = "
t65:	.asciiz "\n"
t47:	.asciiz "\n"
t29:	.asciiz "\n"
t57:	.asciiz "\n"
t67:	.asciiz "j + i == n "
t49:	.asciiz "j + i != n "
t69:	.asciiz "\n"
	.align 2
	.text
main:
	la $sp, -8($sp) # allocate space for old $fp and $ra
	sw $fp, 4($sp) # save old $fp on stack
	sw $ra, 0($sp) # save old $ra on stack
	la $fp, 0($sp) # set up frame pointer
	la $sp, -212($sp) # allocate stack frame for locals/tmps

	li $8, 10 # load constant < 16-bits
	sw $8, -16($fp)

	lw $8, -16($fp) # load local/tmp
	sw $8, -12($fp)

	li $8, 10 # load constant < 16-bits
	sw $8, -36($fp)

	lw $8, -12($fp)
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
	j L4

	.text
L3:
	la $8, t11 # load string const addr
	sw $8, -52($fp) # store string const address

	lw $8, -52($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	lw $8, -12($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_int
	la $sp, 4($sp)

	la $8, t13 # load string const addr
	sw $8, -84($fp) # store string const address

	lw $8, -84($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	li $8, 1 # load constant < 16-bits
	sw $8, -104($fp)

	lw $8, -12($fp) # load n
	lw $9, -104($fp)
	sub $10, $8, $9
	sw $10, -132($fp)

	lw $8, -132($fp) # load local/tmp
	sw $8, -12($fp)

	.text
L4:
	li $8, 0 # load constant < 16-bits
	sw $8, -40($fp)

	lw $8, -12($fp)
	lw $9, -40($fp)
	bgt $8, $9, L3

	j L5

	.text
L5:
	li $8, 0 # load constant < 16-bits
	sw $8, -156($fp)

	lw $8, -156($fp) # load local/tmp
	sw $8, -4($fp)

	j L7

	.text
L6:
	la $8, t19 # load string const addr
	sw $8, -44($fp) # store string const address

	lw $8, -44($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	lw $8, -4($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_int
	la $sp, 4($sp)

	la $8, t21 # load string const addr
	sw $8, -64($fp) # store string const address

	lw $8, -64($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	li $8, 1 # load constant < 16-bits
	sw $8, -80($fp)

	lw $8, -4($fp) # load i
	lw $9, -80($fp)
	add $10, $8, $9
	sw $10, -100($fp)

	lw $8, -100($fp) # load local/tmp
	sw $8, -4($fp)

	.text
L7:
	li $8, 5 # load constant < 16-bits
	sw $8, -164($fp)

	lw $8, -4($fp)
	lw $9, -164($fp)
	blt $8, $9, L6

	j L8

	.text
L8:
	li $8, 10 # load constant < 16-bits
	sw $8, -128($fp)

	lw $8, -128($fp) # load local/tmp
	sw $8, -12($fp)

	j L10

	.text
L9:
	la $8, t27 # load string const addr
	sw $8, -180($fp) # store string const address

	lw $8, -180($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	lw $8, -4($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_int
	la $sp, 4($sp)

	la $8, t29 # load string const addr
	sw $8, -48($fp) # store string const address

	lw $8, -48($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	li $8, 1 # load constant < 16-bits
	sw $8, -60($fp)

	lw $8, -4($fp) # load i
	lw $9, -60($fp)
	sub $10, $8, $9
	sw $10, -76($fp)

	lw $8, -76($fp) # load local/tmp
	sw $8, -4($fp)

	.text
L10:
	lw $8, -4($fp)
	lw $9, -12($fp)
	ble $8, $9, L12

	j L11

	.text
L12:
	li $8, 0 # load constant < 16-bits
	sw $8, -152($fp)

	lw $8, -4($fp)
	lw $9, -152($fp)
	bge $8, $9, L9

	j L11

	.text
L11:
	li $8, 97 # load constant < 16-bits
	sw $8, -96($fp)

	lw $8, -96($fp) # load local/tmp
	sw $8, -4($fp)

	j L14

	.text
L13:
	la $8, t35 # load string const addr
	sw $8, -160($fp) # store string const address

	lw $8, -160($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	lw $8, -4($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_int
	la $sp, 4($sp)

	la $8, t37 # load string const addr
	sw $8, -188($fp) # store string const address

	lw $8, -188($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	li $8, 1 # load constant < 16-bits
	sw $8, -200($fp)

	lw $8, -4($fp) # load i
	lw $9, -200($fp)
	add $10, $8, $9
	sw $10, -56($fp)

	lw $8, -56($fp) # load local/tmp
	sw $8, -4($fp)

	.text
L14:
	li $8, 122 # load constant < 16-bits
	sw $8, -124($fp)

	lw $8, -4($fp)
	lw $9, -124($fp)
	blt $8, $9, L13

	j L15

	.text
L15:
	li $8, 2 # load constant < 16-bits
	sw $8, -72($fp)

	lw $8, -72($fp) # load t41
	neg $9, $8
	sw $9, -92($fp)

	lw $8, -92($fp) # load local/tmp
	sw $8, -4($fp)

	li $8, 5 # load constant < 16-bits
	sw $8, -120($fp)

	lw $8, -120($fp) # load local/tmp
	sw $8, -8($fp)

	li $8, 4 # load constant < 16-bits
	sw $8, -148($fp)

	lw $8, -148($fp) # load local/tmp
	sw $8, -12($fp)

	lw $8, -8($fp) # load j
	lw $9, -4($fp)
	add $10, $8, $9
	sw $10, -144($fp)

	lw $8, -144($fp)
	lw $9, -12($fp)
	beq $8, $9, L16

	j L17

	.text
L16:
	la $8, t45 # load string const addr
	sw $8, -176($fp) # store string const address

	lw $8, -176($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	la $8, t47 # load string const addr
	sw $8, -196($fp) # store string const address

	lw $8, -196($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	j L18

	.text
L17:
	la $8, t49 # load string const addr
	sw $8, -68($fp) # store string const address

	lw $8, -68($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	la $8, t51 # load string const addr
	sw $8, -116($fp) # store string const address

	lw $8, -116($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	.text
L18:
	la $8, t54 # load string const addr
	sw $8, -172($fp) # store string const address

	lw $8, -172($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	lw $8, -4($fp) # load i
	lw $9, -8($fp)
	add $10, $8, $9
	sw $10, -184($fp)

	lw $8, -184($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_int
	la $sp, 4($sp)

	la $8, t57 # load string const addr
	sw $8, -204($fp) # store string const address

	lw $8, -204($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	li $8, 1 # load constant < 16-bits
	sw $8, -212($fp)

	lw $8, -212($fp) # load t59
	neg $9, $8
	sw $9, -88($fp)

	lw $8, -88($fp) # load local/tmp
	sw $8, -4($fp)

	li $8, 5 # load constant < 16-bits
	sw $8, -112($fp)

	lw $8, -112($fp) # load local/tmp
	sw $8, -8($fp)

	li $8, 4 # load constant < 16-bits
	sw $8, -140($fp)

	lw $8, -140($fp) # load local/tmp
	sw $8, -12($fp)

	lw $8, -8($fp) # load j
	lw $9, -4($fp)
	add $10, $8, $9
	sw $10, -136($fp)

	lw $8, -136($fp)
	lw $9, -12($fp)
	beq $8, $9, L20

	j L19

	.text
L19:
	la $8, t63 # load string const addr
	sw $8, -168($fp) # store string const address

	lw $8, -168($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	la $8, t65 # load string const addr
	sw $8, -192($fp) # store string const address

	lw $8, -192($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	j L21

	.text
L20:
	la $8, t67 # load string const addr
	sw $8, -208($fp) # store string const address

	lw $8, -208($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	la $8, t69 # load string const addr
	sw $8, -108($fp) # store string const address

	lw $8, -108($fp) # load parameter
	la $sp, -4($sp) # allocate stack space for it
	sw $8, 0($sp) # push the parameter value onto stack

	jal print_string
	la $sp, 4($sp)

	.text
L21:
	la $sp, 0($fp)
	lw $ra, 0($sp)
	lw $fp, 4($sp)
	la $sp, 8($sp)
	jr $ra

